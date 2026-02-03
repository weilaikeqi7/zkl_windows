// reticle_feature.c
// 按《分划板功能需求.xlsx》实现四级菜单逻辑
#include "reticle_feature.h"

#include "ui.h"

#include "distance_editor.h"
#include "reticle_distance_mgr.h"
#include "reticle_model.h"

extern lv_group_t *keypad_group;

/* forward declarations */
static void ev_distance_item(lv_event_t *e);

/* ===================== 观察区域/硬件层接口占位（你项目中自行对接） ===================== */
static void hw_reticle_set_visible(bool en) { (void)en; }
static void hw_reticle_set_rotate(bool en)  { (void)en; }
static void hw_reticle_set_style(uint8_t s) { (void)s; }
static void hw_reticle_set_color(uint8_t c) { (void)c; }
static void hw_reticle_apply_distance(const reticle_distance_entry_t *e){ (void)e; }

/* ===================== 状态/dirty ===================== */
static bool s_opened = false;

/* ===================== dialog 管理 ===================== */
typedef enum {
    DLG_NONE = 0,
    DLG_SAVE_ROW,        // ui_savereticle
    DLG_EXIT_PROMPT,     // ui_savechanges
    DLG_ZERO_ACTION,     // 运行时创建：Zero Clear/Reset
} dlg_kind_t;

static dlg_kind_t s_dlg_kind = DLG_NONE;
static lv_obj_t *s_restore_focus = NULL;
static lv_obj_t *s_dlg_zero = NULL; // 动态创建的 Zero dialog（组件 ui_comp_dialogeg）

/* ===================== 辅助：UI子菜单显示控制 ===================== */
static void hide_all_submenus(void)
{
    lv_obj_add_flag(ui_contmenureticle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);
}

static void focus_page2_main_only(void)
{
    lv_group_remove_all_objs(keypad_group);
    lv_group_add_obj(keypad_group, ui_rowwifi);
    lv_group_add_obj(keypad_group, ui_rowtilt);
    lv_group_add_obj(keypad_group, ui_rowcompass);
    lv_group_add_obj(keypad_group, ui_rowreticle);
    lv_group_add_obj(keypad_group, ui_rowballistic);
    lv_group_add_obj(keypad_group, ui_rowmic);
    lv_group_add_obj(keypad_group, ui_rowrav);
    lv_group_focus_obj(ui_rowreticle);
}

static void focus_level2_reticle(void)
{
    lv_group_remove_all_objs(keypad_group);

    // 固定 8 行
    lv_group_add_obj(keypad_group, ui_reticlerow1);
    lv_group_add_obj(keypad_group, ui_reticlerow2);
    lv_group_add_obj(keypad_group, ui_reticlerow3);
    lv_group_add_obj(keypad_group, ui_reticlerow4);
    lv_group_add_obj(keypad_group, ui_reticlerow5);
    lv_group_add_obj(keypad_group, ui_reticlerow6);
    lv_group_add_obj(keypad_group, ui_reticlerow7);
    lv_group_add_obj(keypad_group, ui_reticlerow8);

    // 动态距离条目：必须加入 group（解决“动态添加焦点”）
    uint8_t cnt = reticle_distance_mgr_count();
    for(uint8_t i=0;i<cnt;i++){
        lv_group_add_obj(keypad_group, reticle_distance_mgr_obj(i));
    }
}

static void focus_level3_distance(void)
{
    lv_group_remove_all_objs(keypad_group);
    lv_group_add_obj(keypad_group, ui_distancerow1); // Calibration Setting
    lv_group_add_obj(keypad_group, ui_distancerow2); // Set Primacy Distance
    lv_group_add_obj(keypad_group, ui_distancerow3); // Modify Distance
    lv_group_add_obj(keypad_group, ui_distancerow4); // Delete Distance
}

static void focus_level4_calibration(void)
{
    lv_group_remove_all_objs(keypad_group);
    lv_group_add_obj(keypad_group, ui_calibrationrow1); // X
    lv_group_add_obj(keypad_group, ui_calibrationrow2); // Y
    lv_group_add_obj(keypad_group, ui_calibrationrow3); // Zero Clear/Reset (合并)
    lv_group_add_obj(keypad_group, ui_calibrationrow4); // Zoom
    lv_group_add_obj(keypad_group, ui_calibrationrow5); // Freeze
}

/* ===================== 模型 <-> UI 同步 ===================== */
static void ui_set_rowlabel_value(lv_obj_t *rowlabel, const char *fmt, int v)
{
    lv_label_set_text_fmt(ui_comp_get_child(rowlabel, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), fmt, v);
}

static void ui_set_rowswitch_checked(lv_obj_t *rowswitch, bool checked)
{
    lv_obj_t *sw = ui_comp_get_child(rowswitch, UI_COMP_ROWSWITCH_CONTPILL_SWITCH);
    if(checked) lv_obj_add_state(sw, LV_STATE_CHECKED);
    else        lv_obj_clear_state(sw, LV_STATE_CHECKED);
}

static void sync_distance_mgr_to_model(void)
{
    reticle_gun_cfg_t *gc = reticle_model_cur_gun_cfg();
    reticle_distance_mgr_save_to_cfg(gc);
}

static void load_gun_cfg_to_ui(void)
{
    reticle_gun_cfg_t *gc = reticle_model_cur_gun_cfg();

    // 2级固定行：显示数值/开关
    ui_set_rowswitch_checked(ui_reticlerow1, gc->visible);
    ui_set_rowswitch_checked(ui_reticlerow2, gc->rotate);
    ui_set_rowlabel_value(ui_reticlerow3, "G%d", (int)(reticle_model_get_cur_gun() + 1));
    ui_set_rowlabel_value(ui_reticlerow4, "S%d", (int)gc->style);
    ui_set_rowlabel_value(ui_reticlerow5, "C%d", (int)gc->color);

    // 绑定距离列表
    reticle_distance_mgr_load_from_cfg(gc, ev_distance_item); // 事件回调稍后统一绑定（见 bind_events）
    // 注意：load_from_cfg 会把 primary icon、selected style 都刷好
}

static void apply_gun_cfg_to_hw(void)
{
    reticle_gun_cfg_t *gc = reticle_model_cur_gun_cfg();
    hw_reticle_set_visible(gc->visible);
    hw_reticle_set_rotate(gc->rotate);
    hw_reticle_set_style(gc->style);
    hw_reticle_set_color(gc->color);

    uint8_t sel = reticle_distance_mgr_get_selected();
    reticle_distance_entry_t *e = reticle_distance_mgr_entry(sel);
    if(e) hw_reticle_apply_distance(e);
}

/* ===================== dialog 通用 ===================== */
static lv_obj_t *dialog_ok(lv_obj_t *dlg){ return ui_comp_get_child(dlg, UI_COMP_DIALOGEG_DIALOGOK); }
static lv_obj_t *dialog_cancel(lv_obj_t *dlg){ return ui_comp_get_child(dlg, UI_COMP_DIALOGEG_DIALOGCANCEL); }
static lv_obj_t *dialog_text_label(lv_obj_t *dlg){ return ui_comp_get_child(dlg, UI_COMP_DIALOGEG_DIALOGTEXT_LABEL); }
static lv_obj_t *dialog_ok_label(lv_obj_t *dlg){ return ui_comp_get_child(dlg, UI_COMP_DIALOGEG_DIALOGOK_LABEL); }
static lv_obj_t *dialog_cancel_label(lv_obj_t *dlg){ return ui_comp_get_child(dlg, UI_COMP_DIALOGEG_DIALOGCANCEL_LABEL); }

static void dialog_close(lv_obj_t *dlg)
{
    lv_obj_add_flag(dlg, LV_OBJ_FLAG_HIDDEN);
    s_dlg_kind = DLG_NONE;

    // 恢复焦点
    if(s_restore_focus){
        if(s_opened) focus_level2_reticle();
        else focus_page2_main_only();

        lv_group_focus_obj(s_restore_focus);
        s_restore_focus = NULL;
    }
}

static void dialog_open(lv_obj_t *dlg, dlg_kind_t kind, lv_obj_t *restore_focus)
{
    s_dlg_kind = kind;
    s_restore_focus = restore_focus;

    lv_obj_remove_flag(dlg, LV_OBJ_FLAG_HIDDEN);

    // 焦点组切换到弹框按钮
    lv_group_remove_all_objs(keypad_group);
    lv_group_add_obj(keypad_group, dialog_ok(dlg));
    lv_group_add_obj(keypad_group, dialog_cancel(dlg));
    lv_group_focus_obj(dialog_ok(dlg));
}

/* ===================== 运行时创建 Zero Action dialog ===================== */
static void ensure_zero_dialog(void)
{
    if(s_dlg_zero) return;

    // 把 dialog 放在 MainPage 上层（不依赖 SquareLine 生成对象）
    s_dlg_zero = ui_dialogeg_create(ui_MainPage);
    lv_obj_center(s_dlg_zero);
    lv_obj_add_flag(s_dlg_zero, LV_OBJ_FLAG_HIDDEN);

    // 设置默认文案（可按需改中文/英文）
    lv_label_set_text(dialog_text_label(s_dlg_zero), "Zero Action?");
    lv_label_set_text(dialog_ok_label(s_dlg_zero), "Clear");
    lv_label_set_text(dialog_cancel_label(s_dlg_zero), "Reset");
}

/* ===================== 子菜单切换 ===================== */
static void show_level2(void)
{
    lv_obj_remove_flag(ui_contmenureticle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);

    // 先从模型加载当前枪型配置并重建距离列表
    load_gun_cfg_to_ui();

    focus_level2_reticle();

    // 默认选中距离列表第一条（需求表 14）
    if(reticle_distance_mgr_count() > 0){
        reticle_distance_mgr_set_selected(0);
        lv_group_focus_obj(reticle_distance_mgr_obj(0));
    }else{
        lv_group_focus_obj(ui_reticlerow7); // 没有距离时默认聚焦 Add Distance
    }
}

static void show_level3(void)
{
    lv_obj_remove_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);

    focus_level3_distance();
    lv_group_focus_obj(ui_distancerow1);
}

static void show_level4(void)
{
    lv_obj_remove_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);

    uint8_t idx = reticle_distance_mgr_get_selected();
    reticle_distance_mgr_refresh_calibration_ui(idx);

    focus_level4_calibration();
    lv_group_focus_obj(ui_calibrationrow1);
}

/* ===================== 事件：动态距离条目（2级） ===================== */
static void ev_distance_item(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;

    lv_obj_t *obj = lv_event_get_target(e);
    int idx = reticle_distance_mgr_find_idx_by_obj(obj);
    if(idx < 0) return;

    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_UP) lv_group_focus_next(keypad_group);
    else if(key == LV_KEY_DOWN) lv_group_focus_prev(keypad_group);
    else if(key == LV_KEY_ENTER){
        reticle_distance_mgr_set_selected((uint8_t)idx);
        apply_gun_cfg_to_hw();
        show_level3();
    }else if(key == LV_KEY_ESC){
        reticle_feature_close();
        lv_obj_clear_state(ui_rowreticle, LV_STATE_USER_1);
    }
}

/* ===================== distance editor：Add/Modify 回调 ===================== */
static void restore_to_level2(void *user)
{
    (void)user;
    focus_level2_reticle();
    if(reticle_distance_mgr_count() > 0){
        lv_group_focus_obj(reticle_distance_mgr_obj(reticle_distance_mgr_get_selected()));
    }else{
        lv_group_focus_obj(ui_reticlerow7);
    }
}

static void on_add_distance_ok(int v, void *user)
{
    (void)user;

    uint8_t new_idx = 0;
    lv_obj_t *new_obj = NULL;

    if(!reticle_distance_mgr_insert_sorted(v, &new_idx, &new_obj)){
        restore_to_level2(NULL);
        return;
    }

    // 新条目必须绑定事件 + 加入 group
    if(new_obj){
        lv_obj_add_event_cb(new_obj, ev_distance_item, LV_EVENT_ALL, NULL);
    }

    reticle_distance_mgr_set_selected(new_idx);

    // 修改即 dirty
    reticle_model_mark_dirty();
    sync_distance_mgr_to_model();

    focus_level2_reticle();
    if(new_obj) lv_group_focus_obj(new_obj);
}

static uint8_t s_modify_old_idx = 0;

static void on_modify_ok(int new_val, void *user)
{
    (void)user;

    uint8_t new_idx = s_modify_old_idx;
    if(!reticle_distance_mgr_modify(s_modify_old_idx, new_val, &new_idx)){
        // 修改失败（重复）-> 回到三级聚焦 Modify
        focus_level3_distance();
        lv_group_focus_obj(ui_distancerow3);
        return;
    }

    reticle_distance_mgr_set_selected(new_idx);

    reticle_model_mark_dirty();
    sync_distance_mgr_to_model();

    // 返回二级，聚焦修改后的条目
    lv_obj_add_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);

    focus_level2_reticle();
    lv_group_focus_obj(reticle_distance_mgr_obj(new_idx));
}

static void on_modify_cancel(void *user)
{
    (void)user;
    focus_level3_distance();
    lv_group_focus_obj(ui_distancerow3);
}

/* ===================== 2级：固定行事件（显示/旋转/Gun/Style/Color/Reset/Add/Save） ===================== */
static void ev_level2_common_nav(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_UP) lv_group_focus_next(keypad_group);
    else if(key == LV_KEY_DOWN) lv_group_focus_prev(keypad_group);
    else if(key == LV_KEY_ESC){
        reticle_feature_close();
        lv_obj_clear_state(ui_rowreticle, LV_STATE_USER_1);
    }
}

// 显示开关（rowswitch）
static void ev_visible(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_ENTER){
        reticle_gun_cfg_t *gc = reticle_model_cur_gun_cfg();
        gc->visible = !gc->visible;
        ui_set_rowswitch_checked(ui_reticlerow1, gc->visible);
        hw_reticle_set_visible(gc->visible);
        reticle_model_mark_dirty();
    }else{
        ev_level2_common_nav(e);
    }
}

// 旋转开关（rowswitch）
static void ev_rotate(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_ENTER){
        reticle_gun_cfg_t *gc = reticle_model_cur_gun_cfg();
        gc->rotate = !gc->rotate;
        ui_set_rowswitch_checked(ui_reticlerow2, gc->rotate);
        hw_reticle_set_rotate(gc->rotate);
        reticle_model_mark_dirty();
    }else{
        ev_level2_common_nav(e);
    }
}

// Gun Type（rowlabel）：ENTER 进入编辑态，UP/DOWN 切换 G1~G10，ENTER 退出编辑态并加载对应枪型
static void ev_gun_type(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;

    uint32_t key = lv_indev_get_key(lv_indev_active());
    bool editing = lv_obj_has_state(ui_reticlerow3, LV_STATE_USER_1);

    if(key == LV_KEY_ENTER){
        if(!editing){
            lv_obj_add_state(ui_reticlerow3, LV_STATE_USER_1);
        }else{
            // 退出编辑态：根据当前显示的 gun idx（已经更新到模型）重载 UI/距离列表
            lv_obj_clear_state(ui_reticlerow3, LV_STATE_USER_1);

            // 保存当前枪型距离（避免切枪丢失）
            sync_distance_mgr_to_model();

            // 切枪后重建距离列表与UI
            load_gun_cfg_to_ui();

            apply_gun_cfg_to_hw();
            focus_level2_reticle();
            lv_group_focus_obj(ui_reticlerow3);
        }
        return;
    }

    if(editing){
        // 在编辑态下：UP/DOWN 切换枪型
        if(key == LV_KEY_UP || key == LV_KEY_DOWN){
            uint8_t g = reticle_model_get_cur_gun();
            if(key == LV_KEY_UP) g = (uint8_t)((g + 1) % RETICLE_GUN_COUNT);
            else                 g = (uint8_t)((g + RETICLE_GUN_COUNT - 1) % RETICLE_GUN_COUNT);

            reticle_model_set_cur_gun(g);
            ui_set_rowlabel_value(ui_reticlerow3, "G%d", (int)(g+1));
        }
        return;
    }

    // 非编辑态：正常导航/退出
    ev_level2_common_nav(e);
}

// Style（rowlabel）：ENTER编辑态，UP/DOWN 切 S1~S10，实时生效并置dirty
static void ev_style(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    bool editing = lv_obj_has_state(ui_reticlerow4, LV_STATE_USER_1);

    if(key == LV_KEY_ENTER){
        if(editing) lv_obj_clear_state(ui_reticlerow4, LV_STATE_USER_1);
        else        lv_obj_add_state(ui_reticlerow4, LV_STATE_USER_1);
        return;
    }

    if(editing){
        if(key == LV_KEY_UP || key == LV_KEY_DOWN){
            reticle_gun_cfg_t *gc = reticle_model_cur_gun_cfg();
            uint8_t s = gc->style;
            if(s < 1 || s > RETICLE_STYLE_COUNT) s = 1;
            if(key == LV_KEY_UP) s = (uint8_t)(s % RETICLE_STYLE_COUNT + 1);
            else                 s = (uint8_t)((s + RETICLE_STYLE_COUNT - 2) % RETICLE_STYLE_COUNT + 1);

            gc->style = s;
            ui_set_rowlabel_value(ui_reticlerow4, "S%d", (int)s);
            hw_reticle_set_style(s);
            reticle_model_mark_dirty();
        }
        return;
    }

    ev_level2_common_nav(e);
}

// Color（rowlabel）：ENTER编辑态，UP/DOWN 切 C1~C10，实时生效并置dirty
static void ev_color(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    bool editing = lv_obj_has_state(ui_reticlerow5, LV_STATE_USER_1);

    if(key == LV_KEY_ENTER){
        if(editing) lv_obj_clear_state(ui_reticlerow5, LV_STATE_USER_1);
        else        lv_obj_add_state(ui_reticlerow5, LV_STATE_USER_1);
        return;
    }

    if(editing){
        if(key == LV_KEY_UP || key == LV_KEY_DOWN){
            reticle_gun_cfg_t *gc = reticle_model_cur_gun_cfg();
            uint8_t c = gc->color;
            if(c < 1 || c > RETICLE_COLOR_COUNT) c = 1;
            if(key == LV_KEY_UP) c = (uint8_t)(c % RETICLE_COLOR_COUNT + 1);
            else                 c = (uint8_t)((c + RETICLE_COLOR_COUNT - 2) % RETICLE_COLOR_COUNT + 1);

            gc->color = c;
            ui_set_rowlabel_value(ui_reticlerow5, "C%d", (int)c);
            hw_reticle_set_color(c);
            reticle_model_mark_dirty();
        }
        return;
    }

    ev_level2_common_nav(e);
}

// Reset：仅保留一条距离=100，且零位重置到中心点；同时 style/color 重置为 S1/C1（可按你产品修改）
static void do_reticle_reset(void)
{
    reticle_gun_cfg_t *gc = reticle_model_cur_gun_cfg();

    gc->style = 1;
    gc->color = 1;
    // 是否重置 visible/rotate：需求表未强制，这里不改（如需也可重置）
    // gc->visible = true;
    // gc->rotate = false;

    gc->count = 1;
    gc->primary_idx = 0;
    gc->items[0].dist = 100;
    gc->items[0].calib.x = 0;
    gc->items[0].calib.y = 0;
    gc->items[0].calib.zoom = RETICLE_ZOOM_MIN;
    gc->items[0].calib.freeze = false;

    // 重建 UI 距离列表
    reticle_distance_mgr_load_from_cfg(gc, ev_distance_item);

    // 刷新 UI 行显示
    ui_set_rowlabel_value(ui_reticlerow4, "S%d", (int)gc->style);
    ui_set_rowlabel_value(ui_reticlerow5, "C%d", (int)gc->color);

    reticle_model_mark_dirty();
    apply_gun_cfg_to_hw();

    focus_level2_reticle();
    lv_group_focus_obj(reticle_distance_mgr_obj(0));
}

static void ev_reset(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_ENTER) do_reticle_reset();
    else ev_level2_common_nav(e);
}

// Add Distance（rowenter）
static void ev_add_distance(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_ENTER){
        distance_editor_open(100, on_add_distance_ok, NULL, NULL, NULL, restore_to_level2, NULL);
    }else{
        ev_level2_common_nav(e);
    }
}

// Save（rowlabel）：弹 ui_savereticle
static void ev_save(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_ENTER){
        dialog_open(ui_savereticle, DLG_SAVE_ROW, ui_reticlerow8);
    }else{
        ev_level2_common_nav(e);
    }
}

/* ===================== 3级：Calibration/Primacy/Modify/Delete ===================== */
static void ev_level3(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;

    lv_obj_t *obj = lv_event_get_user_data(e);
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_UP) { lv_group_focus_next(keypad_group); return; }
    if(key == LV_KEY_DOWN){ lv_group_focus_prev(keypad_group); return; }

    if(key == LV_KEY_ESC){
        // 返回二级
        lv_obj_add_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);
        focus_level2_reticle();
        if(reticle_distance_mgr_count() > 0)
            lv_group_focus_obj(reticle_distance_mgr_obj(reticle_distance_mgr_get_selected()));
        else
            lv_group_focus_obj(ui_reticlerow7);
        return;
    }

    if(key != LV_KEY_ENTER) return;

    uint8_t sel = reticle_distance_mgr_get_selected();
    reticle_distance_entry_t *en = reticle_distance_mgr_entry(sel);
    if(!en) return;

    if(obj == ui_distancerow1){
        show_level4();
        return;
    }

    if(obj == ui_distancerow2){
        reticle_distance_mgr_set_primary(sel);
        reticle_model_mark_dirty();
        sync_distance_mgr_to_model();
        return;
    }

    if(obj == ui_distancerow3){
        s_modify_old_idx = sel;
        distance_editor_open(en->dist, on_modify_ok, NULL, on_modify_cancel, NULL, NULL, NULL);
        return;
    }

    if(obj == ui_distancerow4){
        reticle_distance_mgr_delete(sel);
        reticle_model_mark_dirty();
        sync_distance_mgr_to_model();

        // 删除后回二级
        lv_obj_add_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);

        focus_level2_reticle();
        if(reticle_distance_mgr_count() > 0){
            lv_group_focus_obj(reticle_distance_mgr_obj(reticle_distance_mgr_get_selected()));
        }else{
            lv_group_focus_obj(ui_reticlerow7);
        }
        return;
    }
}

/* ===================== 4级：X/Y/Zero/ClearReset/Zoom/Freeze ===================== */
static void do_zero_clear(void)
{
    uint8_t idx = reticle_distance_mgr_get_selected();
    reticle_distance_entry_t *en = reticle_distance_mgr_entry(idx);
    if(!en) return;

    en->calib.x = 0;
    en->calib.y = 0;
    reticle_distance_mgr_refresh_calibration_ui(idx);
    reticle_model_mark_dirty();
    sync_distance_mgr_to_model();
    apply_gun_cfg_to_hw();
}
static void do_zero_reset(void)
{
    // 需求表动作同 Clear：X/Y 清 0（后续如你要区分相对/绝对，这里可扩展）
    do_zero_clear();
}

static void ev_level4(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;

    lv_obj_t *obj = lv_event_get_user_data(e);
    uint32_t key = lv_indev_get_key(lv_indev_active());

    uint8_t idx = reticle_distance_mgr_get_selected();
    reticle_distance_entry_t *en = reticle_distance_mgr_entry(idx);
    if(!en) return;

    bool editing = lv_obj_has_state(obj, LV_STATE_USER_1);

    if(key == LV_KEY_ESC){
        lv_obj_clear_state(obj, LV_STATE_USER_1);
        lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);
        focus_level3_distance();
        lv_group_focus_obj(ui_distancerow1);
        return;
    }

    if(!editing){
        if(key == LV_KEY_UP)   { lv_group_focus_next(keypad_group); return; }
        if(key == LV_KEY_DOWN) { lv_group_focus_prev(keypad_group); return; }
    }

    if(key == LV_KEY_ENTER){
        // X/Y/Zoom：切换编辑态
        if(obj == ui_calibrationrow1 || obj == ui_calibrationrow2 || obj == ui_calibrationrow4){
            if(editing) lv_obj_clear_state(obj, LV_STATE_USER_1);
            else        lv_obj_add_state(obj, LV_STATE_USER_1);
            return;
        }

        // Zero Clear/Reset：弹框选择并确认（需求表 10/11：弹框确认后清零）
        if(obj == ui_calibrationrow3){
            ensure_zero_dialog();
            // 文案可改为中文
            lv_label_set_text(dialog_text_label(s_dlg_zero), "Clear or Reset zero?");
            lv_label_set_text(dialog_ok_label(s_dlg_zero), "Clear");
            lv_label_set_text(dialog_cancel_label(s_dlg_zero), "Reset");
            dialog_open(s_dlg_zero, DLG_ZERO_ACTION, ui_calibrationrow3);
            return;
        }

        // Freeze：切换开关
        if(obj == ui_calibrationrow5){
            en->calib.freeze = !en->calib.freeze;
            reticle_distance_mgr_refresh_calibration_ui(idx);
            reticle_model_mark_dirty();
            sync_distance_mgr_to_model();
            apply_gun_cfg_to_hw();
            return;
        }
    }

    if(editing){
        if(obj == ui_calibrationrow1){
            if(key == LV_KEY_UP   && en->calib.x < RETICLE_X_MAX) en->calib.x++;
            if(key == LV_KEY_DOWN && en->calib.x > RETICLE_X_MIN) en->calib.x--;
            reticle_distance_mgr_refresh_calibration_ui(idx);
            reticle_model_mark_dirty();
            sync_distance_mgr_to_model();
            apply_gun_cfg_to_hw();
            return;
        }
        if(obj == ui_calibrationrow2){
            if(key == LV_KEY_UP   && en->calib.y < RETICLE_Y_MAX) en->calib.y++;
            if(key == LV_KEY_DOWN && en->calib.y > RETICLE_Y_MIN) en->calib.y--;
            reticle_distance_mgr_refresh_calibration_ui(idx);
            reticle_model_mark_dirty();
            sync_distance_mgr_to_model();
            apply_gun_cfg_to_hw();
            return;
        }
        if(obj == ui_calibrationrow4){
            if(key == LV_KEY_UP   && en->calib.zoom < RETICLE_ZOOM_MAX) en->calib.zoom++;
            if(key == LV_KEY_DOWN && en->calib.zoom > RETICLE_ZOOM_MIN) en->calib.zoom--;
            reticle_distance_mgr_refresh_calibration_ui(idx);
            reticle_model_mark_dirty();
            sync_distance_mgr_to_model();
            apply_gun_cfg_to_hw();
            return;
        }
    }
}

/* ===================== dialog：OK/Cancel 共用事件 ===================== */
static void ev_dialog_button(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;

    lv_obj_t *btn = lv_event_get_target(e);
    uint32_t key = lv_indev_get_key(lv_indev_active());

    lv_obj_t *dlg = NULL;
    if(s_dlg_kind == DLG_SAVE_ROW) dlg = ui_savereticle;
    else if(s_dlg_kind == DLG_EXIT_PROMPT) dlg = ui_savechanges;
    else if(s_dlg_kind == DLG_ZERO_ACTION) dlg = s_dlg_zero;
    else return;

    if(key == LV_KEY_UP){ lv_group_focus_next(keypad_group); return; }
    if(key == LV_KEY_DOWN){ lv_group_focus_prev(keypad_group); return; }

    if(key == LV_KEY_ESC){
        dialog_close(dlg);
        return;
    }

    if(key != LV_KEY_ENTER) return;

    bool is_ok = (btn == dialog_ok(dlg));

    if(s_dlg_kind == DLG_SAVE_ROW){
        // Save 行：OK 保存但不退出；Cancel 不保存
        if(is_ok){
            sync_distance_mgr_to_model();
            reticle_model_nv_save(reticle_model_cfg());
            reticle_model_clear_dirty();
        }
        dialog_close(dlg);
        return;
    }

    if(s_dlg_kind == DLG_EXIT_PROMPT){
        // 退出提示：OK 保存并退出；Cancel 不保存也退出
        if(is_ok){
            sync_distance_mgr_to_model();
            reticle_model_nv_save(reticle_model_cfg());
            reticle_model_clear_dirty();
        }

        // 真正退出到一级菜单（page2列表）
        lv_obj_add_flag(dlg, LV_OBJ_FLAG_HIDDEN);
        s_dlg_kind = DLG_NONE;
        s_restore_focus = NULL;

        hide_all_submenus();
        s_opened = false;
        focus_page2_main_only();
        return;
    }

    if(s_dlg_kind == DLG_ZERO_ACTION){
        // OK=Clear, Cancel=Reset（两者都“确认”）
        if(is_ok) do_zero_clear();
        else      do_zero_reset();
        dialog_close(dlg);
        return;
    }
}

/* ===================== 对外接口 ===================== */
void reticle_feature_init(void)
{
    hide_all_submenus();

    // 确保弹框隐藏
    lv_obj_add_flag(ui_savereticle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_savechanges, LV_OBJ_FLAG_HIDDEN);

    ensure_zero_dialog();

    distance_editor_init();
    reticle_distance_mgr_init();
    reticle_model_init();

    // 初次加载当前枪型配置到 UI（保持页面一致）
    load_gun_cfg_to_ui();

    apply_gun_cfg_to_hw();

    s_opened = false;
    s_dlg_kind = DLG_NONE;
    s_restore_focus = NULL;
}

void reticle_feature_bind_events(void)
{
    // 二级
    lv_obj_add_event_cb(ui_reticlerow1, ev_visible,      LV_EVENT_ALL, ui_reticlerow1);
    lv_obj_add_event_cb(ui_reticlerow2, ev_rotate,       LV_EVENT_ALL, ui_reticlerow2);
    lv_obj_add_event_cb(ui_reticlerow3, ev_gun_type,     LV_EVENT_ALL, ui_reticlerow3);
    lv_obj_add_event_cb(ui_reticlerow4, ev_style,        LV_EVENT_ALL, ui_reticlerow4);
    lv_obj_add_event_cb(ui_reticlerow5, ev_color,        LV_EVENT_ALL, ui_reticlerow5);
    lv_obj_add_event_cb(ui_reticlerow6, ev_reset,        LV_EVENT_ALL, ui_reticlerow6);
    lv_obj_add_event_cb(ui_reticlerow7, ev_add_distance, LV_EVENT_ALL, ui_reticlerow7);
    lv_obj_add_event_cb(ui_reticlerow8, ev_save,         LV_EVENT_ALL, ui_reticlerow8);

    // 动态距离项（init 时已经绑定；若后续动态创建也会绑定）
    // 三级
    lv_obj_add_event_cb(ui_distancerow1, ev_level3, LV_EVENT_ALL, ui_distancerow1);
    lv_obj_add_event_cb(ui_distancerow2, ev_level3, LV_EVENT_ALL, ui_distancerow2);
    lv_obj_add_event_cb(ui_distancerow3, ev_level3, LV_EVENT_ALL, ui_distancerow3);
    lv_obj_add_event_cb(ui_distancerow4, ev_level3, LV_EVENT_ALL, ui_distancerow4);

    // 四级
    lv_obj_add_event_cb(ui_calibrationrow1, ev_level4, LV_EVENT_ALL, ui_calibrationrow1);
    lv_obj_add_event_cb(ui_calibrationrow2, ev_level4, LV_EVENT_ALL, ui_calibrationrow2);
    lv_obj_add_event_cb(ui_calibrationrow3, ev_level4, LV_EVENT_ALL, ui_calibrationrow3);
    lv_obj_add_event_cb(ui_calibrationrow4, ev_level4, LV_EVENT_ALL, ui_calibrationrow4);
    lv_obj_add_event_cb(ui_calibrationrow5, ev_level4, LV_EVENT_ALL, ui_calibrationrow5);

    // dialog：Save/Exit/Zero
    lv_obj_add_event_cb(dialog_ok(ui_savereticle), ev_dialog_button, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(dialog_cancel(ui_savereticle), ev_dialog_button, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(dialog_ok(ui_savechanges), ev_dialog_button, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(dialog_cancel(ui_savechanges), ev_dialog_button, LV_EVENT_ALL, NULL);

    if(s_dlg_zero){
        lv_obj_add_event_cb(dialog_ok(s_dlg_zero), ev_dialog_button, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(dialog_cancel(s_dlg_zero), ev_dialog_button, LV_EVENT_ALL, NULL);
    }
}

void reticle_feature_open(void)
{
    if(s_opened) return;
    s_opened = true;

    // 每次打开都从模型重建 UI（确保动态距离/枪型切换后一致）
    load_gun_cfg_to_ui();
    apply_gun_cfg_to_hw();

    // 展示二级
    lv_obj_remove_flag(ui_contmenureticle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);

    focus_level2_reticle();

    // 默认选中距离列表第一条（需求表 14）
    if(reticle_distance_mgr_count() > 0){
        reticle_distance_mgr_set_selected(0);
        lv_group_focus_obj(reticle_distance_mgr_obj(0));
    }else{
        lv_group_focus_obj(ui_reticlerow7);
    }
}

void reticle_feature_close(void)
{
    // 弹框显示中不响应重复关闭
    if(s_dlg_kind != DLG_NONE) return;

    if(!s_opened){
        hide_all_submenus();
        focus_page2_main_only();
        return;
    }

    // 退出前把当前距离列表同步回模型
    sync_distance_mgr_to_model();

    // 需求表：返回至一级菜单时若检测到有修改则提示保存
    if(reticle_model_is_dirty()){
        dialog_open(ui_savechanges, DLG_EXIT_PROMPT, ui_rowreticle);
        return;
    }

    hide_all_submenus();
    s_opened = false;
    focus_page2_main_only();
}

bool reticle_feature_is_open(void){ return s_opened; }
