// reticle_model.h
// Reticle 配置模型层：集中管理 10 个枪型的配置、dirty 标志、save/load 接口
// UI 层（reticle_feature）只通过本接口读写配置。

#ifndef RETICLE_MODEL_H
#define RETICLE_MODEL_H

#include <stdbool.h>
#include <stdint.h>
#include "reticle_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void reticle_model_init(void);     // 初始化（默认值 + 尝试从NV加载）
void reticle_model_mark_dirty(void);
void reticle_model_clear_dirty(void);
bool reticle_model_is_dirty(void);

// 获取当前配置（可读写）
reticle_cfg_t *reticle_model_cfg(void);

// 当前枪型
uint8_t reticle_model_get_cur_gun(void);
void    reticle_model_set_cur_gun(uint8_t idx);

// 读取当前枪型配置
reticle_gun_cfg_t *reticle_model_cur_gun_cfg(void);

// 保存/加载（占位：你可在这里对接 Flash/NVS）
bool reticle_model_nv_load(reticle_cfg_t *out);
bool reticle_model_nv_save(const reticle_cfg_t *in);

#ifdef __cplusplus
}
#endif

#endif // RETICLE_MODEL_H
