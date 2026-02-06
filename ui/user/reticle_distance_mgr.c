// reticle_distance_mgr.c
#include "reticle_distance_mgr.h"
#include "ui.h"

static lv_obj_t *s_obj[RETICLE_MAX_DISTANCE_ITEMS];
static reticle_distance_entry_t s_entry[RETICLE_MAX_DISTANCE_ITEMS];
static uint8_t s_cnt = 0;

static uint8_t s_sel = 0;
static uint8_t s_primary = 0;

static int clamp_int(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static void entry_set_default(reticle_distance_entry_t *e, int dist) {
    e->dist = (int16_t) dist;
    e->calib.x = 0;
    e->calib.y = 0;
    e->calib.zoom = RETICLE_ZOOM_MIN;
    e->calib.freeze = false;
}

static void set_item_text(lv_obj_t *item, int dist) {
    lv_label_set_text_fmt(ui_comp_get_child(item, UI_COMP_DISTANCELABEL_CONTPILL_ITEMLABEL), "%d", dist);
}

static void set_item_primary_icon(lv_obj_t *item, bool en) {
    lv_obj_t *icon = ui_comp_get_child(item, UI_COMP_DISTANCELABEL_IMGICON);
    (void) en;
    /* 需求变更：所有距离条目都显示 dots 图标，不再用 dots 区分“优先距离”。
     * 这里只保证 icon 永远可见；优先距离请用 LV_STATE_USER_2 做样式区分。
     */
    lv_obj_remove_flag(icon, LV_OBJ_FLAG_HIDDEN);
}

static lv_obj_t *create_item_obj(void) {
    lv_obj_t *item = ui_distancelabel_create(ui_contpagereticle);
    lv_obj_add_flag(item, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    return item;
}

static uint32_t get_distance_base_index(void) {
    /* 需求变更：距离条目必须放在二级菜单固定项（row1~row8）之后，
       不能通过 move_to_index(i) 把距离挪到最前面（会跑到 Display/菜单前面）。
       这里以 ui_reticlerow8(Save) 作为锚点：距离条目从 Save 的下一个位置开始摆放。 */
    if (ui_reticlerow8) {
        return (uint32_t) lv_obj_get_index(ui_reticlerow8) + 1;
    }
    /* 兜底：如果锚点不存在，就从末尾开始 */
    return (uint32_t) lv_obj_get_child_cnt(ui_contpagereticle);
}

static void move_all_obj_to_match_order(void) {
    uint32_t base = get_distance_base_index();
    for (uint8_t i = 0; i < s_cnt; i++) {
        lv_obj_move_to_index(s_obj[i], (uint32_t) (base + i));
    }
}

void reticle_distance_mgr_apply_selected_style(void) {
    /* 需求变更：
     * - LV_STATE_USER_1 仅用于“编辑态”区分（用于 Gun/Style/Color/X/Y/Zoom 等行），
     *   不再用于距离条目的“选中/高亮”。
     * - 距离列表每个枪型只有一个“优先距离”，用 LV_STATE_USER_2 标识并做样式。
     *   焦点移动时由 LVGL 自带 FOCUSED 样式提示即可。
     */
    (void) s_sel;
}

void reticle_distance_mgr_apply_primary_icon(void) {
    /* 需求变更：dots 全部显示；优先距离仅用 LV_STATE_USER_2 标识（便于样式区分） */
    for (uint8_t i = 0; i < s_cnt; i++) {
        bool is_primary = (i == s_primary);
        set_item_primary_icon(s_obj[i], is_primary);

        if (is_primary) lv_obj_add_state(s_obj[i], LV_STATE_USER_2);
        else
            lv_obj_clear_state(s_obj[i], LV_STATE_USER_2);
    }
}

void reticle_distance_mgr_init(void) {
    s_cnt = 0;
    s_sel = 0;
    s_primary = 0;
}

uint8_t reticle_distance_mgr_count(void) { return s_cnt; }

reticle_distance_entry_t *reticle_distance_mgr_entry(uint8_t idx) {
    return (idx < s_cnt) ? &s_entry[idx] : NULL;
}

lv_obj_t *reticle_distance_mgr_obj(uint8_t idx) {
    return (idx < s_cnt) ? s_obj[idx] : NULL;
}

void reticle_distance_mgr_set_visible_range(uint8_t start, uint8_t count) {
    /* 隐藏不在[start, start+count)区间内的距离条目，用于“每页2条距离”的分页显示 */
    for (uint8_t i = 0; i < s_cnt; i++) {
        bool in_range = (i >= start) && (i < (uint8_t)(start + count));
        if (in_range) lv_obj_clear_flag(s_obj[i], LV_OBJ_FLAG_HIDDEN);
        else lv_obj_add_flag(s_obj[i], LV_OBJ_FLAG_HIDDEN);
    }
}

int reticle_distance_mgr_find_idx_by_obj(lv_obj_t *obj) {
    for (uint8_t i = 0; i < s_cnt; i++) if (s_obj[i] == obj) return (int) i;
    return -1;
}

void reticle_distance_mgr_set_selected(uint8_t idx) {
    if (idx < s_cnt) {
        s_sel = idx;
        /* 不再通过 USER_1 高亮距离条目；这里只更新逻辑选中索引即可 */
    }
}

uint8_t reticle_distance_mgr_get_selected(void) { return s_sel; }

void reticle_distance_mgr_set_primary(uint8_t idx) {
    if (idx < s_cnt) {
        s_primary = idx;
        reticle_distance_mgr_apply_primary_icon();
    }
}

uint8_t reticle_distance_mgr_get_primary(void) { return s_primary; }

bool reticle_distance_mgr_insert_sorted(int dist, uint8_t *new_idx, lv_obj_t **new_obj) {
    if (dist <= 0 || dist > 9999) return false;
    if (s_cnt >= RETICLE_MAX_DISTANCE_ITEMS) return false;

    for (uint8_t i = 0; i < s_cnt; i++) if (s_entry[i].dist == dist) return false;

    uint8_t pos = 0;
    while (pos < s_cnt && s_entry[pos].dist < dist) pos++;

    lv_obj_t *item = create_item_obj();
    if (!item) return false;

    for (int i = (int) s_cnt; i > (int) pos; i--) {
        s_obj[i] = s_obj[i - 1];
        s_entry[i] = s_entry[i - 1];
    }

    s_obj[pos] = item;
    entry_set_default(&s_entry[pos], dist);
    set_item_text(item, dist);
    set_item_primary_icon(item, false);

    s_cnt++;

    if (s_sel >= pos) s_sel++;
    if (s_primary >= pos) s_primary++;

    if (s_cnt == 1) {
        s_sel = 0;
        s_primary = 0;
    }

    move_all_obj_to_match_order();
    reticle_distance_mgr_apply_selected_style();
    reticle_distance_mgr_apply_primary_icon();

    if (new_idx) *new_idx = pos;
    if (new_obj) *new_obj = item;
    return true;
}

bool reticle_distance_mgr_delete(uint8_t idx) {
    if (idx >= s_cnt) return false;

    lv_obj_del(s_obj[idx]);

    for (uint8_t i = idx; i + 1 < s_cnt; i++) {
        s_obj[i] = s_obj[i + 1];
        s_entry[i] = s_entry[i + 1];
    }
    s_cnt--;

    if (s_cnt == 0) {
        s_sel = 0;
        s_primary = 0;
        return true;
    }

    // 删除后：选中条目刷新规则（需求表 16 行）
    if (s_sel == idx) {
        if (idx == 0) s_sel = 0;
        else s_sel = (uint8_t) (idx - 1);
    } else if (s_sel > idx) {
        s_sel--;
    }

    if (s_primary == idx) s_primary = 0;
    else if (s_primary > idx) s_primary--;

    if (s_sel >= s_cnt) s_sel = (uint8_t) (s_cnt - 1);
    if (s_primary >= s_cnt) s_primary = 0;

    move_all_obj_to_match_order();
    reticle_distance_mgr_apply_selected_style();
    reticle_distance_mgr_apply_primary_icon();
    return true;
}

bool reticle_distance_mgr_modify(uint8_t idx, int new_dist, uint8_t *new_idx_out) {
    if (idx >= s_cnt) return false;
    if (new_dist <= 0 || new_dist > 9999) return false;

    for (uint8_t i = 0; i < s_cnt; i++) {
        if (i != idx && s_entry[i].dist == new_dist) return false;
    }

    s_entry[idx].dist = (int16_t) new_dist;
    set_item_text(s_obj[idx], new_dist);

    uint8_t sel = s_sel;
    uint8_t pri = s_primary;

    bool changed = true;
    while (changed) {
        changed = false;
        for (uint8_t i = 0; i + 1 < s_cnt; i++) {
            if (s_entry[i].dist > s_entry[i + 1].dist) {
                reticle_distance_entry_t te = s_entry[i];
                s_entry[i] = s_entry[i + 1];
                s_entry[i + 1] = te;
                lv_obj_t *to = s_obj[i];
                s_obj[i] = s_obj[i + 1];
                s_obj[i + 1] = to;

                if (sel == i) sel = i + 1;
                else if (sel == i + 1) sel = i;
                if (pri == i) pri = i + 1;
                else if (pri == i + 1) pri = i;

                changed = true;
            }
        }
    }

    s_sel = sel;
    s_primary = pri;

    move_all_obj_to_match_order();
    reticle_distance_mgr_apply_selected_style();
    reticle_distance_mgr_apply_primary_icon();

    if (new_idx_out) *new_idx_out = s_sel;
    return true;
}

void reticle_distance_mgr_clear_all(void) {
    for (int i = (int) s_cnt - 1; i >= 0; i--) {
        lv_obj_del(s_obj[i]);
    }
    s_cnt = 0;
    s_sel = 0;
    s_primary = 0;
}

void reticle_distance_mgr_load_from_cfg(const reticle_gun_cfg_t *cfg, lv_event_cb_t item_event_cb) {
    reticle_distance_mgr_clear_all();
    if (!cfg) return;

    for (uint8_t i = 0; i < cfg->count && i < RETICLE_MAX_DISTANCE_ITEMS; i++) {
        uint8_t idx = 0;
        lv_obj_t *obj = NULL;
        reticle_distance_mgr_insert_sorted(cfg->items[i].dist, &idx, &obj);

        s_entry[idx].calib = cfg->items[i].calib;

        if (item_event_cb && obj) {
            lv_obj_add_event_cb(obj, item_event_cb, LV_EVENT_ALL, NULL);
        }
    }

    if (s_cnt > 0) s_sel = 0;

    s_primary = 0;
    if (cfg->count > 0) {
        int16_t primary_dist = cfg->items[clamp_int(cfg->primary_idx, 0, cfg->count - 1)].dist;
        for (uint8_t i = 0; i < s_cnt; i++) {
            if (s_entry[i].dist == primary_dist) {
                s_primary = i;
                break;
            }
        }
    }

    reticle_distance_mgr_apply_selected_style();
    reticle_distance_mgr_apply_primary_icon();
}

void reticle_distance_mgr_save_to_cfg(reticle_gun_cfg_t *cfg) {
    if (!cfg) return;

    cfg->count = s_cnt;
    cfg->primary_idx = (s_cnt > 0) ? s_primary : 0;

    for (uint8_t i = 0; i < s_cnt; i++) {
        cfg->items[i] = s_entry[i];
    }
}

void reticle_distance_mgr_refresh_calibration_ui(uint8_t idx) {
    if (idx >= s_cnt) return;
    reticle_calib_t *c = &s_entry[idx].calib;

    lv_label_set_text_fmt(ui_comp_get_child(ui_calibrationrow1, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "%d",
                          (int) c->x);
    lv_label_set_text_fmt(ui_comp_get_child(ui_calibrationrow2, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "%d",
                          (int) c->y);
    lv_label_set_text_fmt(ui_comp_get_child(ui_calibrationrow4, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "%d",
                          (int) c->zoom);

    lv_obj_t *sw = ui_comp_get_child(ui_calibrationrow5, UI_COMP_ROWSWITCH_CONTPILL_SWITCH);
    if (c->freeze) {
        lv_obj_add_state(sw, LV_STATE_CHECKED);
        lv_obj_send_event(sw, LV_EVENT_VALUE_CHANGED, NULL);
    } else {
        lv_obj_clear_state(sw, LV_STATE_CHECKED);
        lv_obj_send_event(sw, LV_EVENT_VALUE_CHANGED, NULL);
    }
}

void reticle_distance_mgr_refresh_calib_x_ui(uint8_t idx) {
    if (idx >= s_cnt) return;
    reticle_calib_t *c = &s_entry[idx].calib;
    lv_label_set_text_fmt(ui_comp_get_child(ui_calibrationrow1, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "%d",
                          (int) c->x);
}

void reticle_distance_mgr_refresh_calib_y_ui(uint8_t idx) {
    if (idx >= s_cnt) return;
    reticle_calib_t *c = &s_entry[idx].calib;
    lv_label_set_text_fmt(ui_comp_get_child(ui_calibrationrow2, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "%d",
                          (int) c->y);
}

void reticle_distance_mgr_refresh_calib_zoom_ui(uint8_t idx) {
    if (idx >= s_cnt) return;
    reticle_calib_t *c = &s_entry[idx].calib;
    lv_label_set_text_fmt(ui_comp_get_child(ui_calibrationrow4, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "%d",
                          (int) c->zoom);
}

void reticle_distance_mgr_refresh_calib_freeze_ui(uint8_t idx) {
    if (idx >= s_cnt) return;
    reticle_calib_t *c = &s_entry[idx].calib;
    lv_obj_t *sw = ui_comp_get_child(ui_calibrationrow5, UI_COMP_ROWSWITCH_CONTPILL_SWITCH);
    if (c->freeze) {
        lv_obj_add_state(sw, LV_STATE_CHECKED);
        lv_obj_send_event(sw, LV_EVENT_VALUE_CHANGED, NULL);
    } else {
        lv_obj_clear_state(sw, LV_STATE_CHECKED);
        lv_obj_send_event(sw, LV_EVENT_VALUE_CHANGED, NULL);
    }
}
