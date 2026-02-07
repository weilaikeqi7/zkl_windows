//
// Created by Administrator on 2025/9/2.
//

#ifndef RG26BUIAARCH64V01C01GLIBC_UI_COMP_LISTITEM_H
#define RG26BUIAARCH64V01C01GLIBC_UI_COMP_LISTITEM_H

#include "../ui.h"

#ifdef __cplusplus
extern "C" {
#endif

// COMPONENT VideoList
#define UI_COMP_LISTITEM_LISTITEM 0
#define UI_COMP_LISTITEM_1        1
#define UI_COMP_LISTITEM_2        2
#define UI_COMP_LISTITEM_3        3
#define UI_COMP_LISTITEM_4        4
#define _UI_COMP_LISTITEM_NUM     5
lv_obj_t* ui_listItem_create(lv_obj_t* comp_parent);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //RG26BUIAARCH64V01C01GLIBC_UI_COMP_LISTITEM_H
