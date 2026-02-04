// reticle_model.c
#include "reticle_model.h"
#include <string.h>

static reticle_cfg_t s_cfg;
static bool s_dirty = false;

// 给每个枪型设置默认值：
// - 全局 visible/rotate 默认关闭 (false)
// - style=S1, color=C1
// - 默认 1 条距离=100（若你希望“默认无100”，可把 count=0 并不初始化 items）
static void set_defaults(reticle_cfg_t *cfg) {
    memset(cfg, 0, sizeof(*cfg));
    cfg->version = 1;
    cfg->cur_gun = 0;
    cfg->visible = false;
    cfg->rotate = false;

    for (uint8_t g = 0; g < RETICLE_GUN_COUNT; g++) {
        reticle_gun_cfg_t *gc = &cfg->guns[g];
        gc->style = 1;
        gc->color = 1;

        gc->count = 1;
        gc->primary_idx = 0;
        gc->items[0].dist = 100;
        gc->items[0].calib.x = 0;
        gc->items[0].calib.y = 0;
        gc->items[0].calib.zoom = RETICLE_ZOOM_MIN;
        gc->items[0].calib.freeze = false;
    }
}

void reticle_model_init(void) {
    reticle_cfg_t tmp;
    if (reticle_model_nv_load(&tmp)) {
        s_cfg = tmp;
    } else {
        set_defaults(&s_cfg);
    }
    s_dirty = false;
}

void reticle_model_mark_dirty(void) { s_dirty = true; }
void reticle_model_clear_dirty(void) { s_dirty = false; }
bool reticle_model_is_dirty(void) { return s_dirty; }

reticle_cfg_t *reticle_model_cfg(void) { return &s_cfg; }

uint8_t reticle_model_get_cur_gun(void) { return s_cfg.cur_gun; }

void reticle_model_set_cur_gun(uint8_t idx) {
    if (idx >= RETICLE_GUN_COUNT) idx = 0;
    s_cfg.cur_gun = idx;
}

reticle_gun_cfg_t *reticle_model_cur_gun_cfg(void) {
    return &s_cfg.guns[s_cfg.cur_gun];
}

// ---------------- NV 占位 ----------------
// 你需要在这里对接 Flash/NVS。
// 返回 true 表示加载/保存成功，false 表示失败（则用默认值）。
bool reticle_model_nv_load(reticle_cfg_t *out) {
    (void) out;
    return false;
}

bool reticle_model_nv_save(const reticle_cfg_t *in) {
    (void) in;
    return true;
}
