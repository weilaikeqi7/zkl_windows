//
// Created by jinxing on 2026/2/3.
//

#ifndef ZKSL_75_6LC_DISTANCE_EDITOR_H
#define ZKSL_75_6LC_DISTANCE_EDITOR_H

#include <stdbool.h>

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
