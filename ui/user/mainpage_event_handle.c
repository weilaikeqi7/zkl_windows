//
// Created by jinxing on 2026/1/8.
//

#include "reticle_feature.h"
#include "mainpage_event_handle.h"

Item DistanceUnit = {.des = {"Y", "M"}, .count = 2, .index = 0};
int Brightness = 4;
int Contrast = 4;
int Sharpness = 4;
int StandbyTime = 5;
Magnetic magnetic = {'+', 0, 0, 0, 0, 0, 0.0f};
Date date = {0, 0, 0};
Time tim = {0, 0, 0};
Item Language = {
    .des = {"English", "Chinese", "Russian"}, // 语言描述数组
    .count = 3, // 语言数量
    .index = 0 // 默认语言索引（英文）
};

void ui_event_rowlrf(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "LRF");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                hidden_menu_page1();
                show_menu_page3();
                lv_group_focus_obj(ui_rowsetting);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page1_item1();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowimagemode(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Image Mode");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page1_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowbrightness(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Brightness");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                Brightness += 1;
                if(Brightness > 10) {
                    Brightness = 1;
                }
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowbrightness, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                      "%d",
                                      Brightness);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                Brightness -= 1;
                if(Brightness < 1) {
                    Brightness = 10;
                }
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowbrightness, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                      "%d",
                                      Brightness);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowcontrast(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Contrast");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                Contrast += 1;
                if(Contrast > 10) {
                    Contrast = 1;
                }
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowcontrast, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                      "%d",
                                      Contrast);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                Contrast -= 1;
                if(Contrast < 1) {
                    Contrast = 10;
                }
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowcontrast, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                      "%d",
                                      Contrast);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowsharpness(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Sharpness");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                Sharpness += 1;
                if(Sharpness > 10) {
                    Sharpness = 1;
                }
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowsharpness, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                      "%d",
                                      Sharpness);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                Sharpness -= 1;
                if(Sharpness < 1) {
                    Sharpness = 10;
                }
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowsharpness, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                      "%d",
                                      Sharpness);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowultraclear(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Ultra-Clear");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowpip(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "PIP");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                hidden_menu_page1();
                show_menu_page2();
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1();
            break;
        default:
            break;
        }
    }
}

void ui_event_menu1row1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Switch");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
                lv_label_set_text(ui_comp_get_child(ui_rowlrf, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "OFF");
            } else {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
                lv_label_set_text(ui_comp_get_child(ui_rowlrf, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "ON");
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_menu1row2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Single Measure");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_menu1row3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Continuous Measure");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_menu1row4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Unit");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                DistanceUnit.index = (DistanceUnit.index + 1) % DistanceUnit.count;
                lv_label_set_text(ui_comp_get_child(ui_menu1row4, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  DistanceUnit.des[DistanceUnit.index]);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                DistanceUnit.index = (DistanceUnit.index - 1 + DistanceUnit.count) % DistanceUnit.count;
                lv_label_set_text(ui_comp_get_child(ui_menu1row4, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  DistanceUnit.des[DistanceUnit.index]);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_menu1row5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Return");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page1_item1();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem21(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page1_item2();
            lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                              "White Hot");
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem22(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page1_item2();
            lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                              "Black Hot");
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem23(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page1_item2();
            lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                              "Iron Red");
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem24(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page1_item2();
            lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                              "Desert Yellow");
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem25(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page1_item2();
            lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                              "Green Hot");
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem26(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page1_item2();
            lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                              "Red Hot");
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem27(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page1_item2();
            lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                              "Outline");
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem28(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page1_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowwifi(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Wi-Fi");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                hidden_menu_page2();
                show_menu_page1();
                lv_group_focus_obj(ui_rowpip);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowtilt(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Tilt");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowcompass(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Compass");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowreticle(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Reticle");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            reticle_feature_open();
            break;
        case LV_KEY_ESC:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                // 菜单打开时：先关二级菜单，不退出page2
                reticle_feature_close();
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                // 菜单未打开：执行原来的退出page2逻辑
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
                hidden_menu_page2();
            }
        default:
            break;
        }
    }
}

void ui_event_rowballistic(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Ballistic");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowmic(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Microphone");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowrav(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "RAV Recording");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                hidden_menu_page2();
                show_menu_page3();
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowstandby(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Standby Timer");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                hidden_menu_page3();
                show_menu_page2();
                lv_group_focus_obj(ui_rowrav);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_item1();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowcompasscalibration(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Compass Calibration");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowdeadpixel(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Dead Pixel Repair");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowstatusbar(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Status Bar");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowdeletefile(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Playback");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page3();
            show_play_page();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowsetting(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Setting");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                hidden_menu_page3();
                show_menu_page1();
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_item6();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowswitch1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                                  LV_EVENT_VALUE_CHANGED,
                                  NULL);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                int rem;
                /* 防护：非正数归 1 */
                if(StandbyTime <= 0) {
                    StandbyTime = 1;
                } else {
                    rem = StandbyTime % 5;
                    if(rem == 0) {
                        StandbyTime += 5; /* 已是 5 的倍数 -> 加 5 */
                    } else {
                        StandbyTime += (5 - rem); /* 向上取整到下一个 5 的倍数 */
                    }
                    if(StandbyTime > 60) {
                        StandbyTime = 1; /* 超过 60 回绕到 1 */
                    }
                }
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitem1, UI_COMP_ROWITEM1_LABEL),
                                      "%d minutes",
                                      StandbyTime);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                if(StandbyTime == 1) {
                    /* 从 1 往下按变为 60 */
                    StandbyTime = 60;
                } else if(StandbyTime % 5 != 0) {
                    /* 非 5 的倍数向下对齐到最近的 5 的倍数（可能为 0，后面修正为 1） */
                    StandbyTime = (StandbyTime / 5) * 5;
                    if(StandbyTime == 0) StandbyTime = 1;
                } else {
                    /* 已是 5 的倍数 */
                    if(StandbyTime == 5) {
                        /* 5 -> 1 */
                        StandbyTime = 1;
                    } else {
                        /* 其它 5 的倍数减 5 */
                        StandbyTime -= 5;
                    }
                }

                /* 任何小于 1 的意外情况都循环到 60 */
                if(StandbyTime < 1) {
                    StandbyTime = 60;
                }

                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitem1, UI_COMP_ROWITEM1_LABEL),
                                      "%d minutes",
                                      StandbyTime);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page3_item1();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_item2_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page3_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_num1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * Papa_obj = lv_event_get_user_data(e);
    lv_obj_t * child_obj = ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                magnetic.symbol = (magnetic.symbol == '+') ? '-' : '+';
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL),
                                      "%c",
                                      magnetic.symbol);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                magnetic.symbol = (magnetic.symbol == '+') ? '-' : '+';
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL),
                                      "%c",
                                      magnetic.symbol);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, true);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_num2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * Papa_obj = lv_event_get_user_data(e);
    lv_obj_t * child_obj = ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                magnetic.num1++;
                if(magnetic.num1 > 9) {
                    magnetic.num1 = 0;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL),
                                      "%d",
                                      magnetic.num1);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                magnetic.num1--;
                if(magnetic.num1 < 0) {
                    magnetic.num1 = 9;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL),
                                      "%d",
                                      magnetic.num1);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, true);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_num3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * Papa_obj = lv_event_get_user_data(e);
    lv_obj_t * child_obj = ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                magnetic.num2++;
                if(magnetic.num2 > 9) {
                    magnetic.num2 = 0;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL),
                                      "%d",
                                      magnetic.num2);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                magnetic.num2--;
                if(magnetic.num2 < 0) {
                    magnetic.num2 = 9;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL),
                                      "%d",
                                      magnetic.num2);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, true);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_num4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * Papa_obj = lv_event_get_user_data(e);
    lv_obj_t * child_obj = ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                magnetic.num3++;
                if(magnetic.num3 > 9) {
                    magnetic.num3 = 0;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL),
                                      "%d",
                                      magnetic.num3);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                magnetic.num3--;
                if(magnetic.num3 < 0) {
                    magnetic.num3 = 9;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL),
                                      "%d",
                                      magnetic.num3);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, true);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_num5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * Papa_obj = lv_event_get_user_data(e);
    lv_obj_t * child_obj = ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                magnetic.num4++;
                if(magnetic.num4 > 9) {
                    magnetic.num4 = 0;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL),
                                      "%d",
                                      magnetic.num4);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                magnetic.num4--;
                if(magnetic.num4 < 0) {
                    magnetic.num4 = 9;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL),
                                      "%d",
                                      magnetic.num4);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, true);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_num6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * Papa_obj = lv_event_get_user_data(e);
    lv_obj_t * child_obj = ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                magnetic.num5++;
                if(magnetic.num5 > 9) {
                    magnetic.num5 = 0;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL),
                                      "%d",
                                      magnetic.num5);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                magnetic.num5--;
                if(magnetic.num5 < 0) {
                    magnetic.num5 = 9;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL),
                                      "%d",
                                      magnetic.num5);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, true);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemOK(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page3_item2_item2();
            int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
            int frac = magnetic.num4 * 10 + magnetic.num5;
            float v = integer + (frac / 100.0f);
            if(magnetic.symbol == '-') {
                v = -v;
            }
            magnetic.magnetic = v;
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemCANCEL(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page3_item2_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_settingrow1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle3, "Date");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_itme6_item1();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item6();
            break;
        default:
            break;
        }
    }
}

void ui_event_settingrow2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle3, "Time");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_itme6_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item6();
            break;
        default:
            break;
        }
    }
}

void ui_event_settingrow3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle3, "Langauge");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                Language.index = (Language.index + 1) % Language.count;
                lv_label_set_text(ui_comp_get_child(obj, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  Language.des[Language.index]);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                Language.index = (Language.index - 1 + Language.count) % Language.count;
                lv_label_set_text(ui_comp_get_child(obj, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  Language.des[Language.index]);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item6();
            break;
        default:
            break;
        }
    }
}

void ui_event_settingrow4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle3, "Factory Reset");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_itme6_item4();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item6();
            break;
        default:
            break;
        }
    }
}

void ui_event_settingrow5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle3, "System Info");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_itme6_item5();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item6();
            break;
        default:
            break;
        }
    }
}

void ui_event_settingrow6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle3, "");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page3_item6();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item6();
            break;
        default:
            break;
        }
    }
}

/* 辅助函数：闰年 & 当月天数 */
int is_leap_year(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int days_in_month(int y, int m)
{
    static const int dim[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(m < 1 || m > 12) return 31;
    if(m == 2 && is_leap_year(y)) return 29;
    return dim[m];
}

void ui_event_rowitemyear(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                date.year++;
                if(date.year > 2099) date.year = 2026;
                /* 修正 day */
                int dim = days_in_month(date.year, date.month);
                if(date.day > dim) date.day = dim;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemyear, UI_COMP_ROWITEM1_LABEL), "%d", date.year);
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                date.year--;
                if(date.year < 2026) date.year = 2099;
                int dim = days_in_month(date.year, date.month);
                if(date.day > dim) date.day = dim;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemyear, UI_COMP_ROWITEM1_LABEL), "%d", date.year);
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemmonth(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                date.month++;
                if(date.month > 12) date.month = 1;
                int dim = days_in_month(date.year, date.month);
                if(date.day > dim) date.day = dim;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemmonth, UI_COMP_ROWITEM1_LABEL), "%d", date.month);
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                date.month--;
                if(date.month < 1) date.month = 12;
                int dim = days_in_month(date.year, date.month);
                if(date.day > dim) date.day = dim;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemmonth, UI_COMP_ROWITEM1_LABEL), "%d", date.month);
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemday(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                int dim = days_in_month(date.year, date.month);
                date.day++;
                if(date.day > dim) date.day = 1;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                int dim = days_in_month(date.year, date.month);
                date.day--;
                if(date.day < 1) date.day = dim;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemback(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page3_itme6_item1();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemhour(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                tim.hour++;
                if(tim.hour > 23) tim.hour = 0;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemhour, UI_COMP_ROWITEM1_LABEL), "%02d", tim.hour);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                tim.hour--;
                if(tim.hour < 0) tim.hour = 23;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemhour, UI_COMP_ROWITEM1_LABEL), "%02d", tim.hour);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemmin(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                tim.min++;
                if(tim.min > 59) tim.min = 0;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemmin, UI_COMP_ROWITEM1_LABEL), "%02d", tim.min);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                tim.min--;
                if(tim.min < 0) tim.min = 59;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemmin, UI_COMP_ROWITEM1_LABEL), "%02d", tim.min);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemtimeback(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page3_itme6_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_resetOK(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page3_itme6_item4();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item4();
            break;
        default:
            break;
        }
    }
}

void ui_event_resetCANCEL(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page3_itme6_item4();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item4();
            break;
        default:
            break;
        }
    }
}

void ui_event_infoOK(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            hidden_menu_page3_itme6_item5();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item5();
            break;
        default:
            break;
        }
    }
}

void add_event_of_menu(void)
{
    lv_obj_add_event_cb(ui_rowlrf, ui_event_rowlrf, LV_EVENT_ALL, ui_rowlrf);
    lv_obj_add_event_cb(ui_rowimagemode, ui_event_rowimagemode, LV_EVENT_ALL, ui_rowimagemode);
    lv_obj_add_event_cb(ui_rowbrightness, ui_event_rowbrightness, LV_EVENT_ALL, ui_rowbrightness);
    lv_obj_add_event_cb(ui_rowcontrast, ui_event_rowcontrast, LV_EVENT_ALL, ui_rowcontrast);
    lv_obj_add_event_cb(ui_rowsharpness, ui_event_rowsharpness, LV_EVENT_ALL, ui_rowsharpness);
    lv_obj_add_event_cb(ui_rowultraclear, ui_event_rowultraclear, LV_EVENT_ALL, ui_rowultraclear);
    lv_obj_add_event_cb(ui_rowpip, ui_event_rowpip, LV_EVENT_ALL, ui_rowpip);
    lv_obj_add_event_cb(ui_menu1row1, ui_event_menu1row1, LV_EVENT_ALL, ui_menu1row1);
    lv_obj_add_event_cb(ui_menu1row2, ui_event_menu1row2, LV_EVENT_ALL, ui_menu1row2);
    lv_obj_add_event_cb(ui_menu1row3, ui_event_menu1row3, LV_EVENT_ALL, ui_menu1row3);
    lv_obj_add_event_cb(ui_menu1row4, ui_event_menu1row4, LV_EVENT_ALL, ui_menu1row4);
    lv_obj_add_event_cb(ui_menu1row5, ui_event_menu1row5, LV_EVENT_ALL, ui_menu1row5);
    lv_obj_add_event_cb(ui_rowitem21, ui_event_rowitem21, LV_EVENT_ALL, ui_rowitem21);
    lv_obj_add_event_cb(ui_rowitem22, ui_event_rowitem22, LV_EVENT_ALL, ui_rowitem22);
    lv_obj_add_event_cb(ui_rowitem23, ui_event_rowitem23, LV_EVENT_ALL, ui_rowitem23);
    lv_obj_add_event_cb(ui_rowitem24, ui_event_rowitem24, LV_EVENT_ALL, ui_rowitem24);
    lv_obj_add_event_cb(ui_rowitem25, ui_event_rowitem25, LV_EVENT_ALL, ui_rowitem25);
    lv_obj_add_event_cb(ui_rowitem26, ui_event_rowitem26, LV_EVENT_ALL, ui_rowitem26);
    lv_obj_add_event_cb(ui_rowitem27, ui_event_rowitem27, LV_EVENT_ALL, ui_rowitem27);
    lv_obj_add_event_cb(ui_rowitem28, ui_event_rowitem28, LV_EVENT_ALL, ui_rowitem28);
    lv_obj_add_event_cb(ui_rowwifi, ui_event_rowwifi, LV_EVENT_ALL, ui_rowwifi);
    lv_obj_add_event_cb(ui_rowtilt, ui_event_rowtilt, LV_EVENT_ALL, ui_rowtilt);
    lv_obj_add_event_cb(ui_rowcompass, ui_event_rowcompass, LV_EVENT_ALL, ui_rowcompass);
    lv_obj_add_event_cb(ui_rowreticle, ui_event_rowreticle, LV_EVENT_ALL, ui_rowreticle);
    lv_obj_add_event_cb(ui_rowballistic, ui_event_rowballistic, LV_EVENT_ALL, ui_rowballistic);
    lv_obj_add_event_cb(ui_rowmic, ui_event_rowmic, LV_EVENT_ALL, ui_rowmic);
    lv_obj_add_event_cb(ui_rowrav, ui_event_rowrav, LV_EVENT_ALL, ui_rowrav);
    lv_obj_add_event_cb(ui_rowstandby, ui_event_rowstandby, LV_EVENT_ALL, ui_rowstandby);
    lv_obj_add_event_cb(ui_rowcompasscalibration,
                        ui_event_rowcompasscalibration,
                        LV_EVENT_ALL,
                        ui_rowcompasscalibration);
    lv_obj_add_event_cb(ui_rowdeadpixel, ui_event_rowdeadpixel, LV_EVENT_ALL, ui_rowdeadpixel);
    lv_obj_add_event_cb(ui_rowstatusbar, ui_event_rowstatusbar, LV_EVENT_ALL, ui_rowstatusbar);
    lv_obj_add_event_cb(ui_rowdeletefile, ui_event_rowdeletefile, LV_EVENT_ALL, ui_rowdeletefile);
    lv_obj_add_event_cb(ui_rowsetting, ui_event_rowsetting, LV_EVENT_ALL, ui_rowsetting);
    lv_obj_add_event_cb(ui_rowswitch1, ui_event_rowswitch1, LV_EVENT_ALL, ui_rowswitch1);
    lv_obj_add_event_cb(ui_rowitem1, ui_event_rowitem1, LV_EVENT_ALL, ui_rowitem1);
    lv_obj_add_event_cb(ui_rowitem2, ui_event_rowitem2, LV_EVENT_ALL, ui_rowitem2);
    lv_obj_add_event_cb(ui_rowitem3, ui_event_rowitem3, LV_EVENT_ALL, ui_rowitem3);
    lv_obj_add_event_cb(ui_rowitem4, ui_event_rowitem4, LV_EVENT_ALL, ui_rowitem4);
    lv_obj_add_event_cb(ui_rowitem5, ui_event_rowitem5, LV_EVENT_ALL, ui_rowitem5);
    lv_obj_add_event_cb(ui_comp_get_child(ui_num1, UI_COMP_NUM_PANELNUM), ui_event_num1, LV_EVENT_ALL, ui_num1);
    lv_obj_add_event_cb(ui_comp_get_child(ui_num2, UI_COMP_NUM_PANELNUM), ui_event_num2, LV_EVENT_ALL, ui_num2);
    lv_obj_add_event_cb(ui_comp_get_child(ui_num3, UI_COMP_NUM_PANELNUM), ui_event_num3, LV_EVENT_ALL, ui_num3);
    lv_obj_add_event_cb(ui_comp_get_child(ui_num4, UI_COMP_NUM_PANELNUM), ui_event_num4, LV_EVENT_ALL, ui_num4);
    lv_obj_add_event_cb(ui_comp_get_child(ui_num5, UI_COMP_NUM_PANELNUM), ui_event_num5, LV_EVENT_ALL, ui_num5);
    lv_obj_add_event_cb(ui_comp_get_child(ui_num6, UI_COMP_NUM_PANELNUM), ui_event_num6, LV_EVENT_ALL, ui_num6);
    lv_obj_add_event_cb(ui_rowitemOK, ui_event_rowitemOK, LV_EVENT_ALL, ui_rowitemOK);
    lv_obj_add_event_cb(ui_rowitemCANCEL, ui_event_rowitemCANCEL, LV_EVENT_ALL, ui_rowitemCANCEL);
    lv_obj_add_event_cb(ui_settingrow1, ui_event_settingrow1, LV_EVENT_ALL, ui_settingrow1);
    lv_obj_add_event_cb(ui_settingrow2, ui_event_settingrow2, LV_EVENT_ALL, ui_settingrow2);
    lv_obj_add_event_cb(ui_settingrow3, ui_event_settingrow3, LV_EVENT_ALL, ui_settingrow3);
    lv_obj_add_event_cb(ui_settingrow4, ui_event_settingrow4, LV_EVENT_ALL, ui_settingrow4);
    lv_obj_add_event_cb(ui_settingrow5, ui_event_settingrow5, LV_EVENT_ALL, ui_settingrow5);
    lv_obj_add_event_cb(ui_settingrow6, ui_event_settingrow6, LV_EVENT_ALL, ui_settingrow6);
    lv_obj_add_event_cb(ui_rowitemyear, ui_event_rowitemyear, LV_EVENT_ALL, ui_rowitemyear);
    lv_obj_add_event_cb(ui_rowitemmonth, ui_event_rowitemmonth, LV_EVENT_ALL, ui_rowitemmonth);
    lv_obj_add_event_cb(ui_rowitemday, ui_event_rowitemday, LV_EVENT_ALL, ui_rowitemday);
    lv_obj_add_event_cb(ui_rowitemdateback, ui_event_rowitemback, LV_EVENT_ALL, ui_rowitemdateback);
    lv_obj_add_event_cb(ui_rowitemhour, ui_event_rowitemhour, LV_EVENT_ALL, ui_rowitemhour);
    lv_obj_add_event_cb(ui_rowitemmin, ui_event_rowitemmin, LV_EVENT_ALL, ui_rowitemmin);
    lv_obj_add_event_cb(ui_rowitemtimeback, ui_event_rowitemtimeback, LV_EVENT_ALL, ui_rowitemtimeback);
    lv_obj_add_event_cb(ui_resetOK, ui_event_resetOK, LV_EVENT_ALL, ui_resetOK);
    lv_obj_add_event_cb(ui_resetCANCEL, ui_event_resetCANCEL, LV_EVENT_ALL, ui_resetCANCEL);
    lv_obj_add_event_cb(ui_infoOK, ui_event_infoOK, LV_EVENT_ALL, ui_infoOK);
    reticle_feature_init();
    reticle_feature_bind_events();
    play_event_init();
}
