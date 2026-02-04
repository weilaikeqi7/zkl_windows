// reticle_distance_mgr.h
// 距离列表 UI 管理器：负责
// - 动态创建/删除距离条目（复用 ui_distance1 为模板）
// - 保持距离升序 + 去重
// - 选中高亮（LV_STATE_USER_1）
// - 优先距离图标显示（dots 图标）
// - 在 UI 与 reticle_gun_cfg_t 之间同步数据

#ifndef RETICLE_DISTANCE_MGR_H
#define RETICLE_DISTANCE_MGR_H

#include <stdint.h>
#include <stdbool.h>
#include "lvgl.h"
#include "reticle_types.h"

void reticle_distance_mgr_init(void);

/* --- 基础访问 --- */
uint8_t reticle_distance_mgr_count(void);
reticle_distance_entry_t *reticle_distance_mgr_entry(uint8_t idx);
lv_obj_t *reticle_distance_mgr_obj(uint8_t idx);

int reticle_distance_mgr_find_idx_by_obj(lv_obj_t *obj);

/* --- 选中/优先 --- */
void    reticle_distance_mgr_set_selected(uint8_t idx);
uint8_t reticle_distance_mgr_get_selected(void);

void    reticle_distance_mgr_set_primary(uint8_t idx);
uint8_t reticle_distance_mgr_get_primary(void);

/* --- UI刷新 --- */
void reticle_distance_mgr_apply_selected_style(void);
void reticle_distance_mgr_apply_primary_icon(void);
void reticle_distance_mgr_refresh_calibration_ui(uint8_t idx);

/* 细粒度刷新：避免每次修改 X/Y/Zoom/Freeze 都刷新整套四级菜单 */
void reticle_distance_mgr_refresh_calib_x_ui(uint8_t idx);
void reticle_distance_mgr_refresh_calib_y_ui(uint8_t idx);
void reticle_distance_mgr_refresh_calib_zoom_ui(uint8_t idx);
void reticle_distance_mgr_refresh_calib_freeze_ui(uint8_t idx);

/* --- 数据操作 --- */
bool reticle_distance_mgr_insert_sorted(int dist, uint8_t *new_idx, lv_obj_t **new_obj);
bool reticle_distance_mgr_delete(uint8_t idx);
bool reticle_distance_mgr_modify(uint8_t idx, int new_dist, uint8_t *new_idx_out);
void reticle_distance_mgr_clear_all(void);

/* --- 与模型同步 --- */
void reticle_distance_mgr_load_from_cfg(const reticle_gun_cfg_t *cfg, lv_event_cb_t item_event_cb);
void reticle_distance_mgr_save_to_cfg(reticle_gun_cfg_t *cfg);

#endif
