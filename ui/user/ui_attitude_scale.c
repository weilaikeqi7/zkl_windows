//
// Created by jinxing on 2025/12/15.
//

#include "ui_attitude_scale.h"

/* 三个实际的 scale 对象 */
static lv_obj_t* s_yaw = NULL;
static lv_obj_t* s_roll = NULL;
static lv_obj_t* s_pitch = NULL;

/* 展开后的方位角（可以累积很多圈），和上一次原始 yaw */
static float yaw_unwrap = 0.0f;
static float last_yaw_raw = 0.0f;
static bool yaw_inited = false;

/* 一共显示 +/-45° 的窗口 */
#define AZI_WINDOW_DEG   45.0f

/* 8 个方位字符串 */
static const char* dir8[8] = {
    "N", "NE", "E", "SE", "S", "SW", "W", "NW"
};

/* 3 个刻度上要显示的文本（左/中/右），最后一个 NULL 是结束标记 */
static const char* s_scale_labels[4] = {"NW", "N", "NE", NULL};

/* 左侧 roll 标尺的“零位”旋转角度，和 create_roll_scale 里保持一致 */
#define ROLL_ZERO_ROTATION   10

/* pitch 标尺在 pitch = 0° 时的基准 Y，及每度对应多少像素 */
static float s_pitch_px_per_deg = 0.0f;
static bool s_pitch_inited = false;

/* -------- 工具函数 -------- */

static float normalize_deg_360(float a)
{
    while (a < 0.0f) a += 360.0f;
    while (a >= 360.0f) a -= 360.0f;
    return a;
}

/* 把任意角度映射成 N / NE / ... / NW */
static const char* azimuth_from_deg(float deg)
{
    float a = normalize_deg_360(deg);
    int idx = (int)((a + 22.5f) / 45.0f) & 7; /* 每 45° 一个扇区 */
    return dir8[idx];
}

/* 顶部方位角：整圆罗盘 */
static void create_yaw_scale(void)
{
    if (!ui_yawscale) return;

    s_yaw = lv_scale_create(ui_yawscale);
    lv_obj_set_size(s_yaw, 194, 44);
    lv_obj_set_align(s_yaw, LV_ALIGN_TOP_MID);

    lv_scale_set_mode(s_yaw, LV_SCALE_MODE_HORIZONTAL_BOTTOM);

    lv_scale_set_range(s_yaw, -AZI_WINDOW_DEG, AZI_WINDOW_DEG);

    lv_scale_set_total_tick_count(s_yaw, 3);
    lv_scale_set_major_tick_every(s_yaw, 1);
    lv_scale_set_label_show(s_yaw, true);

    static lv_style_t indicator_style;
    lv_style_init(&indicator_style);

    lv_style_set_text_font(&indicator_style, &ui_font_WebnarSemiBold18);
    lv_style_set_text_color(&indicator_style, lv_color_hex(0xFFFFFF));

    lv_style_set_line_color(&indicator_style, lv_color_hex(0xFFFFFF));
    lv_style_set_line_opa(&indicator_style, LV_OPA_COVER);
    lv_style_set_length(&indicator_style, 16U); /*Tick length*/
    lv_style_set_line_width(&indicator_style, 4U); /*Tick width*/
    lv_obj_add_style(s_yaw, &indicator_style, LV_PART_INDICATOR);

    static lv_style_t minor_ticks_style;
    lv_style_init(&minor_ticks_style);
    lv_style_set_line_color(&minor_ticks_style, lv_color_hex(0xFFFFFF));
    lv_style_set_line_opa(&minor_ticks_style, LV_OPA_COVER);
    lv_style_set_length(&minor_ticks_style, 0U); /*Tick length*/
    lv_style_set_line_width(&minor_ticks_style, 0U); /*Tick width*/
    lv_obj_add_style(s_yaw, &minor_ticks_style, LV_PART_ITEMS);

    static lv_style_t main_line_style;
    lv_style_init(&main_line_style);
    lv_style_set_arc_width(&main_line_style, 0U); /*Tick width*/
    lv_obj_add_style(s_yaw, &main_line_style, LV_PART_MAIN);

    lv_obj_move_foreground(ui_arrowyawimage);

    lv_scale_set_text_src(s_yaw, s_scale_labels);

    /* 初始展开角度清零 */
    yaw_unwrap = 0.0f;
    last_yaw_raw = 0.0f;
    yaw_inited = false;
}

/* 左侧横滚：弧形刻度 */
static void create_roll_scale(void)
{
    if (!ui_rollscale) return;

    s_roll = lv_scale_create(ui_rollscale);
    lv_obj_set_size(s_roll, 625, 625);
    lv_obj_set_align(s_roll, LV_ALIGN_LEFT_MID);
    lv_scale_set_mode(s_roll, LV_SCALE_MODE_ROUND_INNER);

    lv_scale_set_total_tick_count(s_roll, 181);
    lv_scale_set_major_tick_every(s_roll, 5);
    lv_scale_set_label_show(s_roll, true);

    static const char* custom_labels[] = {
        "     ", "   -160", "     ", "   -140", "     ", "   -120", "     ", "   -100", "     ", "   -80",
        "     ", "   -60", "     ", "   -40", "     ", "   -20", "     ", "   0", "     ", "   20",
        "     ", "   40", "     ", "   60", "     ", "   80", "     ", "   100", "     ", "   120",
        "     ", "   140", "     ", "   160", "     ", "   180", NULL
    };
    lv_scale_set_text_src(s_roll, custom_labels);

    static lv_style_t indicator_style;
    lv_style_init(&indicator_style);

    lv_style_set_text_font(&indicator_style, &ui_font_WebnarSemiBold18);
    lv_style_set_text_color(&indicator_style, lv_color_hex(0xFFFFFF));

    lv_style_set_line_color(&indicator_style, lv_color_hex(0x2EEEFC));
    lv_style_set_line_opa(&indicator_style, LV_OPA_COVER);
    lv_style_set_length(&indicator_style, 21U); /*Tick length*/
    lv_style_set_line_width(&indicator_style, 2U); /*Tick width*/
    lv_obj_add_style(s_roll, &indicator_style, LV_PART_INDICATOR);

    static lv_style_t minor_ticks_style;
    lv_style_init(&minor_ticks_style);
    lv_style_set_line_color(&minor_ticks_style, lv_color_hex(0xFFFFFF));
    lv_style_set_line_opa(&minor_ticks_style, LV_OPA_COVER);
    lv_style_set_length(&minor_ticks_style, 12U); /*Tick length*/
    lv_style_set_line_width(&minor_ticks_style, 2U); /*Tick width*/
    lv_obj_add_style(s_roll, &minor_ticks_style, LV_PART_ITEMS);

    static lv_style_t main_line_style;
    lv_style_init(&main_line_style);
    lv_style_set_arc_width(&main_line_style, 0U); /*Tick width*/
    lv_obj_add_style(s_roll, &main_line_style, LV_PART_MAIN);

    lv_scale_set_angle_range(s_roll, 360);
    lv_scale_set_rotation(s_roll, ROLL_ZERO_ROTATION);

    lv_obj_align_to(ui_arrowrollimage, s_roll, LV_ALIGN_OUT_LEFT_MID, -5, 0);
}

/* 右侧俯仰：竖直刻度 */
static void create_pitch_scale(void)
{
    if (!ui_pitchscale) return;

    s_pitch = lv_scale_create(ui_pitchscale);
    lv_obj_set_size(s_pitch, 23, 940);
    lv_scale_set_mode(s_pitch, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_obj_set_align(s_pitch, LV_ALIGN_CENTER);


    lv_scale_set_range(s_pitch, -90, 90);
    lv_scale_set_total_tick_count(s_pitch, 91); // -20..20 每 2° 一刻度
    lv_scale_set_major_tick_every(s_pitch, 5);
    lv_scale_set_label_show(s_pitch, true);

    static const char* custom_labels[] = {
        "     ", "-80  ", "     ", "-60  ", "     ", "-40  ", "     ",
        "-20  ", "     ", "0  ", "     ", "20  ", "     ", "40  ",
        "     ", "60  ", "     ", "80  ", "     ", NULL
    };
    lv_scale_set_text_src(s_pitch, custom_labels);

    static lv_style_t indicator_style;
    lv_style_init(&indicator_style);

    lv_style_set_text_font(&indicator_style, &ui_font_WebnarSemiBold18);
    lv_style_set_text_color(&indicator_style, lv_color_hex(0xFFFFFF));

    lv_style_set_line_color(&indicator_style, lv_color_hex(0x2EEEFC));
    lv_style_set_line_opa(&indicator_style, LV_OPA_COVER);
    lv_style_set_length(&indicator_style, 21U); /*Tick length*/
    lv_style_set_line_width(&indicator_style, 2U); /*Tick width*/
    lv_obj_add_style(s_pitch, &indicator_style, LV_PART_INDICATOR);

    static lv_style_t minor_ticks_style;
    lv_style_init(&minor_ticks_style);
    lv_style_set_line_color(&minor_ticks_style, lv_color_hex(0xFFFFFF));
    lv_style_set_line_opa(&minor_ticks_style, LV_OPA_COVER);
    lv_style_set_length(&minor_ticks_style, 12U); /*Tick length*/
    lv_style_set_line_width(&minor_ticks_style, 2U); /*Tick width*/
    lv_obj_add_style(s_pitch, &minor_ticks_style, LV_PART_ITEMS);

    static lv_style_t main_line_style;
    lv_style_init(&main_line_style);
    lv_style_set_line_width(&main_line_style, 0U); /*Tick width*/
    lv_obj_add_style(s_pitch, &main_line_style, LV_PART_MAIN);
    lv_obj_align_to(ui_arrowpitchimage, s_pitch, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    /* ===== 记录 pitch=0° 时标尺的位置，用来后面做平移 ===== */
    lv_obj_update_layout(s_pitch);
    /* 每 1° 对应多少像素：总高度 / 180° （-90~+90） */
    lv_coord_t h = lv_obj_get_height(s_pitch);
    s_pitch_px_per_deg = (h > 0) ? ((float)h / 180.0f) : 0.0f;

    s_pitch_inited = true;
}

/* 对外初始化：在 ui_init() 后调用 */
void ui_attitude_scale_init(void)
{
    create_yaw_scale();
    create_roll_scale();
    create_pitch_scale();
}

/* 顶部罗盘：只改 rotation，让刻度盘转起来 */
static void update_yaw(float yaw_raw_deg)
{
    if (s_yaw == NULL) return;

    /* 传感器原始角度归一到 0~360 */
    yaw_raw_deg = normalize_deg_360(yaw_raw_deg);

    if (!yaw_inited)
    {
        yaw_unwrap = yaw_raw_deg;
        last_yaw_raw = yaw_raw_deg;
        yaw_inited = true;
    }
    else
    {
        float diff = yaw_raw_deg - last_yaw_raw;

        /* 处理跨 0/360 的情况，保证 diff 在 (-180, 180] 范围 */
        if (diff > 180.0f) diff -= 360.0f;
        if (diff < -180.0f) diff += 360.0f;

        yaw_unwrap += diff; /* 让 yaw_unwrap 连续增长/减小 */
        last_yaw_raw = yaw_raw_deg;
    }

    /* 当前窗口：center = yaw_unwrap，范围 [center-45, center+45] */
    float center = yaw_unwrap;
    int32_t min = (int32_t)(center - AZI_WINDOW_DEG);
    int32_t max = (int32_t)(center + AZI_WINDOW_DEG);
    lv_scale_set_range(s_yaw, min, max);

    /* 计算三格应该显示的文字：左（-45）、中、右（+45） */
    float left_deg = center - AZI_WINDOW_DEG;
    float middle_deg = center;
    float right_deg = center + AZI_WINDOW_DEG;

    s_scale_labels[0] = azimuth_from_deg(left_deg);
    s_scale_labels[1] = azimuth_from_deg(middle_deg);
    s_scale_labels[2] = azimuth_from_deg(right_deg);
    s_scale_labels[3] = NULL;

    /* 再告诉 scale 用这组三个 label */
    lv_scale_set_text_src(s_yaw, s_scale_labels);

    /* 要求重绘 */
    lv_obj_invalidate(s_yaw);
}

/* 左侧横滚：保持窗口宽度 ±ROLL_WINDOW，改数值范围实现“滚动” */
static void update_roll(float roll_deg)
{
    if (s_roll == NULL) return;

    /* 限制一下范围，防止传感器偶尔给出 >180 的数 */
    if (roll_deg > 180.0f) roll_deg = 180.0f;
    if (roll_deg < -180.0f) roll_deg = -180.0f;

    /*
     * ROLL_ZERO_ROTATION 对应 roll = 0° 时的标尺角度。
     * 假设 roll 顺时针为正，希望刻度逆着设备转，就用 “零位角度 - roll”。
     * 如果你发现方向反了，把减号改成加号即可：
     *     lv_scale_set_rotation(s_roll, ROLL_ZERO_ROTATION + (int32_t)roll_deg);
     */
    int32_t rot = ROLL_ZERO_ROTATION - (int32_t)roll_deg;
    lv_scale_set_rotation(s_roll, rot);
    lv_label_set_text_fmt(ui_rolllabel, "%.2f°", roll_deg);
}

/* 右侧俯仰：通过平移 s_pitch，让刻度在红箭头后面上下滚动 */
static void update_pitch(float pitch_deg)
{
    if (s_pitch == NULL || !s_pitch_inited || s_pitch_px_per_deg <= 0.0f) return;

    /* 限制到 [-90, 90] */
    if (pitch_deg > 90.0f) pitch_deg = 90.0f;
    if (pitch_deg < -90.0f) pitch_deg = -90.0f;

    /*
     * 设计：pitch = 0° 时，s_pitch 在 s_pitch_y0；
     *      pitch > 0（抬头）时，刻度整体向下/向上移动，看你想要的方向。
     *
     * 下面这行含义：
     *   - 正 pitch 时，刻度往上走（看起来箭头指向更高的位置）：
     *       offset = - pitch_deg * 像素/度
     *   - 你如果想反过来，只要去掉前面的负号即可。
     */
    float offset = pitch_deg * s_pitch_px_per_deg;

    lv_coord_t new_y = (lv_coord_t)offset;
    lv_obj_set_y(s_pitch, new_y);
    lv_label_set_text_fmt(ui_pitchlabel, "%.2f°", pitch_deg);
}

/* 给外部 IMU 调用的统一接口 */
void ui_attitude_scale_update(float yaw_deg,
                              float roll_deg,
                              float pitch_deg)
{
    update_yaw(yaw_deg);
    update_roll(roll_deg);
    update_pitch(pitch_deg);
}

static void attitude_test_timer_cb(lv_timer_t * timer)
{
    LV_UNUSED(timer);

    /* 静态变量：每次回调在上次基础上增加 */
    static float yaw   = 0.0f;
    static float roll  = -30.0f;
    static float pitch = 0.0f;

    /* 让 yaw 一直绕圈转（0~360） */
    yaw += 2.0f;                 // 每次+2°
    if(yaw >= 360.0f) yaw -= 360.0f;

    /* roll 在 -30° ~ +30° 之间来回摆动 */
    static float roll_dir = 1.0f;  // 1 往上，-1 往下
    roll += roll_dir * 1.5f;
    if(roll > 30.0f)  { roll = 30.0f;  roll_dir = -1.0f; }
    if(roll < -30.0f) { roll = -30.0f; roll_dir =  1.0f; }

    /* pitch 在 -20° ~ +20° 之间上下摆动 */
    static float pitch_dir = 1.0f;
    pitch += pitch_dir * 1.0f;
    if(pitch > 20.0f)  { pitch = 20.0f;  pitch_dir = -1.0f; }
    if(pitch < -20.0f) { pitch = -20.0f; pitch_dir =  1.0f; }

    /* 调用你已有的更新函数 */
    ui_attitude_scale_update(yaw, roll, pitch);
}

/* 对外提供一个接口：创建测试定时器 */
void ui_attitude_start_test_timer(void)
{
    /* 每 50ms 更新一次，大约 20 FPS */
    lv_timer_create(attitude_test_timer_cb, 50, NULL);
}