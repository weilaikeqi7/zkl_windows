//
// Created by jinxing on 2026/2/3.
//

#ifndef ZKSL_75_6LC_DISTANCE_EDITOR_H
#define ZKSL_75_6LC_DISTANCE_EDITOR_H

#include <stdbool.h>
#include "lvgl.h"

#ifdef __cplusplus
extern "C" {

#endif

/**
 * 通用距离编辑弹窗（复用 SquareLine 生成的 ui_editdistance 组件）
 * - 不耦合 Reticle，可在其它功能里重复使用
 * - 4位数字逐位编辑：ENTER切换编辑态，UP/DOWN改数
 * - OK 返回一个 0~9999 的整数
 */

typedef void (*distance_editor_ok_cb_t)(int value, void *user);

typedef void (*distance_editor_cancel_cb_t)(void *user);

typedef void (*distance_editor_restore_cb_t)(void *user);

/** 在 ui_init() 之后调用一次即可 */
void distance_editor_init(void);

/**
 * 打开弹窗（扩展版）
 * @param initial_value   初值（0~9999）
 * @param owner_obj       触发弹窗的控件；弹窗显示期间会临时加 LV_STATE_USER_1，关闭时清除
 * @param align_right     true: 弹窗靠右（用于 Modify Distance），false: 保持原位置（用于 Add Distance）
 */
void distance_editor_open_ex(int initial_value, lv_obj_t *owner_obj, bool align_right,
                             distance_editor_ok_cb_t ok_cb, void *ok_user,
                             distance_editor_cancel_cb_t cancel_cb, void *cancel_user,
                             distance_editor_restore_cb_t restore_cb, void *restore_user);

/**
 * 打开弹窗
 * @param initial_value   初值（0~9999）
 * @param ok_cb           OK/ENTER 确认回调
 * @param cancel_cb       Cancel/ESC 取消回调
 * @param restore_cb      弹窗关闭后恢复焦点组回调（例如恢复到二级菜单）
 */
void distance_editor_open(int initial_value,
                          distance_editor_ok_cb_t ok_cb, void *ok_user,
                          distance_editor_cancel_cb_t cancel_cb, void *cancel_user,
                          distance_editor_restore_cb_t restore_cb, void *restore_user);

bool distance_editor_is_open(void);

void distance_editor_close(void);

#ifdef __cplusplus
}
#endif

#endif //ZKSL_75_6LC_DISTANCE_EDITOR_H
