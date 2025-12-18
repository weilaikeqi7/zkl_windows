//
// Created by jinxing on 2025/12/15.
//

#ifndef ZKSL_75_6LC_UI_ATTITUDE_SCALE_H
#define ZKSL_75_6LC_UI_ATTITUDE_SCALE_H

#include "ui.h"

/* 在 ui_init() 之后调用一次，创建 3 个刻度 */
void ui_attitude_scale_init(void);

/* IMU 更新时调用，单位：度 */
void ui_attitude_scale_update(float yaw_deg,
                              float roll_deg,
                              float pitch_deg);
void ui_attitude_start_test_timer(void);
#endif //ZKSL_75_6LC_UI_ATTITUDE_SCALE_H