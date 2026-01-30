//
// Created by jinxing on 2026/1/30.
//

#ifndef ZKSL_75_6LC_TIMER_HANDLE_H
#define ZKSL_75_6LC_TIMER_HANDLE_H

#include "ui.h"
#include "types.h"

typedef struct {
    int year;
    int month; /* 1-12 */
    int day;   /* 1-31 */
    int hour;   /* 0-23 */
    int min; /* 0-59 */
    int sec; /* 0-59 */
} DateTime;

void datetime_get_local(DateTime *d);

void datetime_update_now(void);

void timer_init(void);

extern DateTime datatime;
extern lv_timer_t *timer_datetime;
#endif //ZKSL_75_6LC_TIMER_HANDLE_H