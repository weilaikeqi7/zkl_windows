// reticle_types.h
// 按《分划板功能需求.xlsx》抽象出的分划板配置数据结构
// - 支持 10 个枪型(G1~G10)
// - 每个枪型包含：分划板类型(样式)(S1~S10)、颜色(C1~C10)、距离列表(100/200/300...)
// - 每个距离包含：校准数据(X/Y/Zoom/Freeze)
// 说明：本文件与 UI 无关，仅定义数据结构（便于保存/加载/迁移）

#ifndef RETICLE_TYPES_H
#define RETICLE_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#ifndef RETICLE_MAX_DISTANCE_ITEMS
#define RETICLE_MAX_DISTANCE_ITEMS 16
#endif

#define RETICLE_GUN_COUNT   10
#define RETICLE_STYLE_COUNT 10
#define RETICLE_COLOR_COUNT 10

// 需求表：X -512~+512, Y -384~+384；Zoom 未给上限，这里先保守设 1~4（可按实际修改）
#define RETICLE_X_MIN  (-512)
#define RETICLE_X_MAX  ( 512)
#define RETICLE_Y_MIN  (-384)
#define RETICLE_Y_MAX  ( 384)
#define RETICLE_ZOOM_MIN 1
#define RETICLE_ZOOM_MAX 4

typedef struct {
    int16_t x; // Zero Modify: X
    int16_t y; // Zero Modify: Y
    uint8_t zoom; // Digital Zoom
    bool freeze; // Freeze On/Off
} reticle_calib_t;

typedef struct {
    int16_t dist; // 距离(瞄准点) 1~9999
    reticle_calib_t calib; // 校准
} reticle_distance_entry_t;

typedef struct {
    uint8_t style; // 1..RETICLE_STYLE_COUNT  -> S1..S10
    uint8_t color; // 1..RETICLE_COLOR_COUNT  -> C1..C10

    uint8_t primary_idx; // 优先距离索引（Set Primacy Distance）
    uint8_t count; // 距离数量
    reticle_distance_entry_t items[RETICLE_MAX_DISTANCE_ITEMS];
} reticle_gun_cfg_t;

typedef struct {
    uint8_t version; // 预留：NV 版本号
    bool visible; // 全局显示开关（不随枪型变化）
    bool rotate; // 全局旋转开关（不随枪型变化）
    uint8_t cur_gun; // 当前枪型索引 0..9
    reticle_gun_cfg_t guns[RETICLE_GUN_COUNT];
} reticle_cfg_t;

#endif // RETICLE_TYPES_H
