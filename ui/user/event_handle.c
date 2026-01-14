//
// Created by jinxing on 2026/1/8.
//

#include "event_handle.h"

Item DistanceUnit = {.des = {"Y", "M"}, .count = 2, .index = 0};
int Brightness = 4;
int Contrast = 4;
int Sharpness = 4;

void ui_event_rowlrf(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "LRF");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }
    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_obj_set_state(obj, LV_STATE_USER_1, false);
                } else {
                    lv_obj_set_state(obj, LV_STATE_USER_1, true);
                }
                show_menu_page1_item1();
                break;
            case LV_KEY_ESC:
                hidden_menu_page1();
                break;
            default: break;
        }
    }
}

void ui_event_rowimagemode(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Image Mode");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_obj_set_state(obj, LV_STATE_USER_1, false);
                } else {
                    lv_obj_set_state(obj, LV_STATE_USER_1, true);
                }
                show_menu_page1_item2();
                break;
            case LV_KEY_ESC:
                hidden_menu_page1();
                break;
            default: break;
        }
    }
}

void ui_event_rowbrightness(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Brightness");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                } else {
                    Brightness += 1;
                    if (Brightness > 10) {
                        Brightness = 10;
                    }
                    lv_label_set_text_fmt(ui_comp_get_child(ui_rowbrightness, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                          "%d", Brightness);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                } else {
                    Brightness -= 1;
                    if (Brightness < 1) {
                        Brightness = 1;
                    }
                    lv_label_set_text_fmt(ui_comp_get_child(ui_rowbrightness, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                          "%d", Brightness);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_obj_set_state(obj, LV_STATE_USER_1, false);
                } else {
                    lv_obj_set_state(obj, LV_STATE_USER_1, true);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page1();
                break;
            default: break;
        }
    }
}

void ui_event_rowcontrast(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Contrast");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                } else {
                    Contrast += 1;
                    if (Contrast > 10) {
                        Contrast = 10;
                    }
                    lv_label_set_text_fmt(ui_comp_get_child(ui_rowcontrast, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                          "%d", Contrast);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                } else {
                    Contrast -= 1;
                    if (Contrast < 1) {
                        Contrast = 1;
                    }
                    lv_label_set_text_fmt(ui_comp_get_child(ui_rowcontrast, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                          "%d", Contrast);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_obj_set_state(obj, LV_STATE_USER_1, false);
                } else {
                    lv_obj_set_state(obj, LV_STATE_USER_1, true);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page1();
                break;
            default: break;
        }
    }
}

void ui_event_rowsharpness(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Sharpness");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                } else {
                    Sharpness += 1;
                    if (Sharpness > 10) {
                        Sharpness = 10;
                    }
                    lv_label_set_text_fmt(ui_comp_get_child(ui_rowsharpness, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                          "%d", Sharpness);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                } else {
                    Sharpness -= 1;
                    if (Sharpness < 1) {
                        Sharpness = 1;
                    }
                    lv_label_set_text_fmt(ui_comp_get_child(ui_rowsharpness, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                          "%d", Sharpness);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_obj_set_state(obj, LV_STATE_USER_1, false);
                } else {
                    lv_obj_set_state(obj, LV_STATE_USER_1, true);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page1();
                break;
            default: break;
        }
    }
}

void ui_event_rowultraclear(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Ultra-Clear");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                } else {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page1();
                break;
            default: break;
        }
    }
}

void ui_event_rowpip(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "PIP");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    hidden_menu_page1();
                    show_menu_page2();
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                } else {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page1();
                break;
            default: break;
        }
    }
}

void ui_event_menu1row1(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Switch");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                    lv_label_set_text(ui_comp_get_child(ui_rowlrf, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "OFF");
                } else {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                    lv_label_set_text(ui_comp_get_child(ui_rowlrf, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "ON");
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item1();
                break;
            default: break;
        }
    }
}

void ui_event_menu1row2(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Single Measure");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item1();
                break;
            default: break;
        }
    }
}

void ui_event_menu1row3(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Continuous Measure");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                } else {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item1();
                break;
            default: break;
        }
    }
}

void ui_event_menu1row4(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Unit");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                } else {
                    DistanceUnit.index = (DistanceUnit.index + 1) % DistanceUnit.count;
                    lv_label_set_text(ui_comp_get_child(ui_menu1row4, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                      DistanceUnit.des[DistanceUnit.index]);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                } else {
                    DistanceUnit.index = (DistanceUnit.index - 1 + DistanceUnit.count) % DistanceUnit.count;
                    lv_label_set_text(ui_comp_get_child(ui_menu1row4, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                      DistanceUnit.des[DistanceUnit.index]);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_obj_set_state(obj, LV_STATE_USER_1, false);
                } else {
                    lv_obj_set_state(obj, LV_STATE_USER_1, true);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item1();
                break;
            default: break;
        }
    }
}

void ui_event_menu1row5(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Return");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                hidden_menu_page1_item1();
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item1();
                break;
            default: break;
        }
    }
}

void ui_event_rowitem21(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                }
                break;
            case LV_KEY_ENTER:
                hidden_menu_page1_item2();
                lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  "White Hot");
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item2();
                break;
            default: break;
        }
    }
}

void ui_event_rowitem22(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                hidden_menu_page1_item2();
                lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  "Black Hot");
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item2();
                break;
            default: break;
        }
    }
}

void ui_event_rowitem23(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                hidden_menu_page1_item2();
                lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  "Iron Red");
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item2();
                break;
            default: break;
        }
    }
}

void ui_event_rowitem24(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                hidden_menu_page1_item2();
                lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  "Desert Yellow");
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item2();
                break;
            default: break;
        }
    }
}

void ui_event_rowitem25(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                hidden_menu_page1_item2();
                lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  "Green Hot");
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item2();
                break;
            default: break;
        }
    }
}

void ui_event_rowitem26(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                hidden_menu_page1_item2();
                lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  "Red Hot");
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item2();
                break;
            default: break;
        }
    }
}

void ui_event_rowitem27(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                hidden_menu_page1_item2();
                lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  "Outline");
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item2();
                break;
            default: break;
        }
    }
}

void ui_event_rowitem28(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                hidden_menu_page1_item2();
                break;
            case LV_KEY_ESC:
                hidden_menu_page1_item2();
                break;
            default: break;
        }
    }
}

void ui_event_rowwifi(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Wi-Fi");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    hidden_menu_page2();
                    show_menu_page1();
                    lv_group_focus_obj(ui_rowpip);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                } else {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page2();
                break;
            default: break;
        }
    }
}

void ui_event_rowtilt(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Tilt");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                } else {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page2();
                break;
            default: break;
        }
    }
}

void ui_event_rowcompass(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Compass");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                } else {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page2();
                break;
            default: break;
        }
    }
}

void ui_event_rowreticle(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Reticle");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_obj_set_state(obj, LV_STATE_USER_1, false);
                } else {
                    lv_obj_set_state(obj, LV_STATE_USER_1, true);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page2();
                break;
            default: break;
        }
    }
}

void ui_event_rowballistic(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Ballistic");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                } else {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page2();
                break;
            default: break;
        }
    }
}

void ui_event_rowmic(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Microphone");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                } else {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page2();
                break;
            default: break;
        }
    }
}

void ui_event_rowrav(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "RAV Recording");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }

    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    hidden_menu_page2();
                    show_menu_page3();
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                } else {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page2();
                break;
            default: break;
        }
    }
}

void ui_event_rowstandby(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Standby Timer");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }
    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    hidden_menu_page3();
                    show_menu_page2();
                    lv_group_focus_obj(ui_rowrav);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_obj_set_state(obj, LV_STATE_USER_1, false);
                } else {
                    lv_obj_set_state(obj, LV_STATE_USER_1, true);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page3();
                break;
            default: break;
        }
    }
}

void ui_event_rowcompasscalibration(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Compass Calibration");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }
    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_obj_set_state(obj, LV_STATE_USER_1, false);
                } else {
                    lv_obj_set_state(obj, LV_STATE_USER_1, true);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page3();
                break;
            default: break;
        }
    }
}

void ui_event_rowdeadpixel(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Dead Pixel Repair");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }
    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_obj_set_state(obj, LV_STATE_USER_1, false);
                } else {
                    lv_obj_set_state(obj, LV_STATE_USER_1, true);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page3();
                break;
            default: break;
        }
    }
}

void ui_event_rowstatusbar(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Status Bar");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }
    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                } else {
                    lv_obj_set_state(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                    lv_obj_send_event(ui_comp_get_child(obj,UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_EVENT_VALUE_CHANGED,
                                      NULL);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page3();
                break;
            default: break;
        }
    }
}

void ui_event_rowdeletefile(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Playback");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }
    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_next(keypad_group);
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                hidden_menu_page3();
                show_play_page();
                break;
            case LV_KEY_ESC:
                hidden_menu_page3();
                break;
            default: break;
        }
    }
}

void ui_event_rowsetting(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_user_data(e);

    if (event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Setting");
    }
    if (event_code == LV_EVENT_DEFOCUSED) {
    }
    if (event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch (key) {
            case LV_KEY_UP:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                }
                break;
            case LV_KEY_DOWN:
                if (!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_group_focus_prev(keypad_group);
                }
                break;
            case LV_KEY_ENTER:
                if (lv_obj_has_state(obj, LV_STATE_USER_1)) {
                    lv_obj_set_state(obj, LV_STATE_USER_1, false);
                } else {
                    lv_obj_set_state(obj, LV_STATE_USER_1, true);
                }
                break;
            case LV_KEY_ESC:
                hidden_menu_page3();
                break;
            default: break;
        }
    }
}

void add_event_of_menu(void) {
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
    lv_obj_add_event_cb(ui_rowcompasscalibration, ui_event_rowcompasscalibration, LV_EVENT_ALL, ui_rowcompasscalibration);
    lv_obj_add_event_cb(ui_rowdeadpixel, ui_event_rowdeadpixel, LV_EVENT_ALL, ui_rowdeadpixel);
    lv_obj_add_event_cb(ui_rowstatusbar, ui_event_rowstatusbar, LV_EVENT_ALL, ui_rowstatusbar);
    lv_obj_add_event_cb(ui_rowdeletefile, ui_event_rowdeletefile, LV_EVENT_ALL, ui_rowdeletefile);
    lv_obj_add_event_cb(ui_rowsetting, ui_event_rowsetting, LV_EVENT_ALL, ui_rowsetting);
}
