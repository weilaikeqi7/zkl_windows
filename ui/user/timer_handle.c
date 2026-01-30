//
// Created by jinxing on 2026/1/30.
//

#include "timer_handle.h"

DateTime datatime;
lv_timer_t *timer_datetime = NULL;

/* 从系统获取本地年月日并写入传入的 Date 指针（若为 NULL 则不操作） */
void datetime_get_local(DateTime *d) {
    if (!d) return;
    time_t t = time(NULL);
    struct tm tm_now;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm_now, &t);
#else
    localtime_r(&t, &tm_now);
#endif
    d->year = tm_now.tm_year + 1900;
    d->month = tm_now.tm_mon + 1;
    d->day = tm_now.tm_mday;
    d->hour = tm_now.tm_hour;
    d->min = tm_now.tm_min;
    d->sec = tm_now.tm_sec;
}

/* 更新全局 date 为当前本地日期（调用此函数以赋值到上面的结构体） */
void datetime_update_now(void) {
    datetime_get_local(&datatime);
    /* 可选：确保日期合法（防御性处理） */
    if (date.year < 1900) date.year = 1900;
    if (date.month < 1 || date.month > 12) date.month = 1;
    int dim = days_in_month(date.year, date.month);
    if (date.day < 1) date.day = 1;
    if (date.day > dim) date.day = dim;
    if (tim.hour < 0 || tim.hour > 23) tim.hour = 0;
    if (tim.min < 0 || tim.min > 59) tim.min = 0;
    if (tim.sec < 0 || tim.sec > 59) tim.sec = 0;
}

void datetime_timer_event(lv_timer_t *timer) {
    (void) timer; // 未使用参数
    datetime_get_local(&datatime);
    lv_label_set_text_fmt(ui_labeldate, "%02d/%02d/%02d", datatime.year, datatime.month, datatime.day);
    lv_label_set_text_fmt(ui_labeltime, "%02d:%02d", datatime.hour, datatime.min);
    lv_label_set_text_fmt(ui_comp_get_child(ui_settingrow1, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "%04d/%02d/%02d",
                          datatime.year, datatime.month, datatime.day);
    lv_label_set_text_fmt(ui_comp_get_child(ui_settingrow2, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "%02d:%02d",
                          datatime.hour, datatime.min);
}

void timer_init(void) {
    timer_datetime = lv_timer_create(datetime_timer_event, 1000, NULL);
    lv_timer_ready(timer_datetime);
}
