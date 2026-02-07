//
// Created by jinxing on 2026/1/14.
//

#include "play_handle.h"

void show_play_page(void)
{
    lv_screen_load(ui_ScrFileMgr);
}

void hidden_play_page(void)
{
    lv_screen_load(ui_MainPage);
}

void ui_event_PlayList_1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_1_5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_7(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_8(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_back(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_prev(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_next(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_video_play(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            break;
        case LV_KEY_DOWN:
            break;
        case LV_KEY_ENTER:
            break;
        default:
            break;
        }
    }
}

void play_event_init(void)
{
    ui_PlayList[0] = ui_BTN;
    ui_PlayList[1] = ui_comp_get_child(ui_year, UI_COMP_DATEITEM_NUM);
    ui_PlayList[2] = ui_comp_get_child(ui_month, UI_COMP_DATEITEM_NUM);
    ui_PlayList[3] = ui_comp_get_child(ui_day, UI_COMP_DATEITEM_NUM);
    ui_PlayList[4] = ui_comp_get_child(ui_hour, UI_COMP_DATEITEM_NUM);
    ui_PlayList[5] = ui_comp_get_child(ui_min, UI_COMP_DATEITEM_NUM);
    ui_PlayList[6] = ui_BTN1;
    ui_PlayList[7] = ui_BTN2;
    ui_PlayList[8] = ui_BTN3;

    lv_obj_add_event_cb(ui_PlayList[0], ui_event_PlayList_1, LV_EVENT_ALL, ui_PlayList[0]);
    for(int i = 1; i < 6; i++) {
        lv_obj_add_event_cb(ui_PlayList[i], ui_event_PlayList_1_5, LV_EVENT_ALL, ui_PlayList[i]);
    }

    lv_obj_add_event_cb(ui_PlayList[6], ui_event_PlayList_6, LV_EVENT_ALL, ui_PlayList[6]);
    lv_obj_add_event_cb(ui_PlayList[7], ui_event_PlayList_7, LV_EVENT_ALL, ui_PlayList[7]);
    lv_obj_add_event_cb(ui_PlayList[8], ui_event_PlayList_8, LV_EVENT_ALL, ui_PlayList[8]);
    lv_obj_add_event_cb(ui_BTN4, ui_event_PlayList_back, LV_EVENT_ALL, ui_BTN4);
    lv_obj_add_event_cb(ui_BTN5, ui_event_PlayList_prev, LV_EVENT_ALL, ui_BTN5);
    lv_obj_add_event_cb(ui_BTN6, ui_event_PlayList_next, LV_EVENT_ALL, ui_BTN6);
    lv_obj_add_event_cb(ui_PlayBar, ui_event_video_play, LV_EVENT_ALL, ui_PlayBar);
}