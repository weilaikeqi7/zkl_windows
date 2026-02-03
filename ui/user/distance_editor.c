//
// Created by jinxing on 2026/2/3.
//

#include "distance_editor.h"
#include "ui.h"

extern lv_group_t *keypad_group;

static bool s_inited = false;
static bool s_opened = false;

static distance_editor_ok_cb_t s_ok_cb = NULL;
static void *s_ok_user = NULL;
static distance_editor_cancel_cb_t s_cancel_cb = NULL;
static void *s_cancel_user = NULL;
static distance_editor_restore_cb_t s_restore_cb = NULL;
static void *s_restore_user = NULL;

static int s_d1 = 0, s_d2 = 0, s_d3 = 0, s_d4 = 0;

static int clamp_0_9999(int v) {
    if (v < 0) return 0;
    if (v > 9999) return 9999;
    return v;
}

static void set_digits_from_value(int v) {
    v = clamp_0_9999(v);
    s_d1 = (v / 1000) % 10;
    s_d2 = (v / 100) % 10;
    s_d3 = (v / 10) % 10;
    s_d4 = v % 10;
}

static int get_value_from_digits(void) { return s_d1 * 1000 + s_d2 * 100 + s_d3 * 10 + s_d4; }

static void refresh_digit_labels(void) {
    lv_label_set_text_fmt(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE1_PANELNUM_LABEL), "%d", s_d1);
    lv_label_set_text_fmt(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE2_PANELNUM_LABEL), "%d", s_d2);
    lv_label_set_text_fmt(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE3_PANELNUM_LABEL), "%d", s_d3);
    lv_label_set_text_fmt(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE4_PANELNUM_LABEL), "%d", s_d4);
}

static void hide_all_arrows(void) {
    lv_obj_add_flag(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE1_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE1_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE2_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE2_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE3_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE3_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE4_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE4_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
}

/** 弹窗打开后，把 group 的焦点对象切换到弹窗内部 */
static void focus_to_popup(void) {
    lv_group_remove_all_objs(keypad_group);

    lv_group_add_obj(keypad_group, ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE1_PANELNUM));
    lv_group_add_obj(keypad_group, ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE2_PANELNUM));
    lv_group_add_obj(keypad_group, ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE3_PANELNUM));
    lv_group_add_obj(keypad_group, ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE4_PANELNUM));
    lv_group_add_obj(keypad_group, ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_DISTANCEOK));
    lv_group_add_obj(keypad_group, ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_DISTANCECANCEL));

    lv_group_focus_obj(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE1_PANELNUM));
}

static void close_internal(bool call_cancel) {
    if (!s_opened) return;
    s_opened = false;

    lv_obj_add_flag(ui_editdistance, LV_OBJ_FLAG_HIDDEN);

    if (call_cancel && s_cancel_cb) s_cancel_cb(s_cancel_user);
    if (s_restore_cb) s_restore_cb(s_restore_user);

    s_ok_cb = NULL;
    s_ok_user = NULL;
    s_cancel_cb = NULL;
    s_cancel_user = NULL;
    s_restore_cb = NULL;
    s_restore_user = NULL;
}

static void ok_internal(void) {
    int v = get_value_from_digits();
    if (s_ok_cb) s_ok_cb(v, s_ok_user);
    close_internal(false);
}

/**
 * 四位数字单元的按键处理：
 * - 非编辑态：UP/DOWN 用于焦点移动
 * - 编辑态：UP/DOWN 修改数字
 * - ENTER：切换编辑态（并显示/隐藏上下箭头）
 */
static void digit_key_handler(lv_obj_t *panelnum, lv_obj_t *img_up, lv_obj_t *img_down, int *digit, lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_KEY) return;

    uint32_t key = lv_indev_get_key(lv_indev_active());
    bool editing = lv_obj_has_state(panelnum, LV_STATE_USER_1);

    switch (key) {
        case LV_KEY_UP:
            if (!editing) lv_group_focus_next(keypad_group);
            else {
                (*digit) = (*digit + 1) % 10;
                refresh_digit_labels();
            }
            break;

        case LV_KEY_DOWN:
            if (!editing) lv_group_focus_prev(keypad_group);
            else {
                (*digit) = (*digit + 9) % 10;
                refresh_digit_labels();
            }
            break;

        case LV_KEY_ENTER:
            if (editing) {
                lv_obj_clear_state(panelnum, LV_STATE_USER_1);
                lv_obj_add_flag(img_up, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(img_down, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_add_state(panelnum, LV_STATE_USER_1);
                lv_obj_remove_flag(img_up, LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(img_down, LV_OBJ_FLAG_HIDDEN);
            }
            break;

        case LV_KEY_ESC:
            close_internal(true);
            break;

        default: break;
    }
}

static void ev_digit1(lv_event_t *e) {
    digit_key_handler(
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE1_PANELNUM),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE1_IMAGEUP),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE1_IMAGEDOWN),
        &s_d1, e
    );
}

static void ev_digit2(lv_event_t *e) {
    digit_key_handler(
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE2_PANELNUM),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE2_IMAGEUP),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE2_IMAGEDOWN),
        &s_d2, e
    );
}

static void ev_digit3(lv_event_t *e) {
    digit_key_handler(
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE3_PANELNUM),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE3_IMAGEUP),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE3_IMAGEDOWN),
        &s_d3, e
    );
}

static void ev_digit4(lv_event_t *e) {
    digit_key_handler(
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE4_PANELNUM),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE4_IMAGEUP),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE4_IMAGEDOWN),
        &s_d4, e
    );
}

static void ev_ok(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if (key == LV_KEY_ENTER) ok_internal();
    else if (key == LV_KEY_ESC) close_internal(true);
    else if (key == LV_KEY_UP) lv_group_focus_next(keypad_group);
    else if (key == LV_KEY_DOWN) lv_group_focus_prev(keypad_group);
}

static void ev_cancel(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if (key == LV_KEY_ENTER || key == LV_KEY_ESC) close_internal(true);
    else if (key == LV_KEY_UP) lv_group_focus_next(keypad_group);
    else if (key == LV_KEY_DOWN) lv_group_focus_prev(keypad_group);
}

void distance_editor_init(void) {
    if (s_inited) return;
    s_inited = true;

    lv_obj_add_flag(ui_editdistance, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_event_cb(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE1_PANELNUM), ev_digit1, LV_EVENT_ALL,
                        NULL);
    lv_obj_add_event_cb(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE2_PANELNUM), ev_digit2, LV_EVENT_ALL,
                        NULL);
    lv_obj_add_event_cb(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE3_PANELNUM), ev_digit3, LV_EVENT_ALL,
                        NULL);
    lv_obj_add_event_cb(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE4_PANELNUM), ev_digit4, LV_EVENT_ALL,
                        NULL);

    lv_obj_add_event_cb(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_DISTANCEOK), ev_ok, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_DISTANCECANCEL), ev_cancel, LV_EVENT_ALL,
                        NULL);

    hide_all_arrows();
}

void distance_editor_open(int initial_value,
                          distance_editor_ok_cb_t ok_cb, void *ok_user,
                          distance_editor_cancel_cb_t cancel_cb, void *cancel_user,
                          distance_editor_restore_cb_t restore_cb, void *restore_user) {
    distance_editor_init();

    s_ok_cb = ok_cb;
    s_ok_user = ok_user;
    s_cancel_cb = cancel_cb;
    s_cancel_user = cancel_user;
    s_restore_cb = restore_cb;
    s_restore_user = restore_user;

    set_digits_from_value(initial_value);
    refresh_digit_labels();

    // 清除四位的编辑态
    lv_obj_clear_state(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE1_PANELNUM), LV_STATE_USER_1);
    lv_obj_clear_state(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE2_PANELNUM), LV_STATE_USER_1);
    lv_obj_clear_state(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE3_PANELNUM), LV_STATE_USER_1);
    lv_obj_clear_state(ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE4_PANELNUM), LV_STATE_USER_1);
    hide_all_arrows();

    lv_obj_remove_flag(ui_editdistance, LV_OBJ_FLAG_HIDDEN);
    s_opened = true;

    focus_to_popup();
}

bool distance_editor_is_open(void) { return s_opened; }
void distance_editor_close(void) { close_internal(false); }
