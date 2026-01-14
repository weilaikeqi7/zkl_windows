//
// Created by jinxing on 2026/1/8.
//

#ifndef ZKSL_75_6LC_EVENT_HANDLE_H
#define ZKSL_75_6LC_EVENT_HANDLE_H

#include "ui.h"

typedef struct {
    const char* des[10]; // 选项描述数组（直接内置）
    int count;           // 选项数量
    int index;           // 当前选中索引
} Item;

extern Item DistanceUnit;
extern int Brightness;
extern int Contrast;
extern int Sharpness;

void add_event_of_menu(void);

#endif //ZKSL_75_6LC_EVENT_HANDLE_H