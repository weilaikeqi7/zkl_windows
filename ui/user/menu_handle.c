//
// Created by jinxing on 2026/1/5.
//

#include "menu_handle.h"

lv_obj_t *ui_focus_temp[30];

void show_menu_page1(void) {
    lv_obj_remove_flag(ui_contpage1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_rowlrf;
    ui_focus_temp[1] = ui_rowimagemode;
    ui_focus_temp[2] = ui_rowbrightness;
    ui_focus_temp[3] = ui_rowcontrast;
    ui_focus_temp[4] = ui_rowsharpness;
    ui_focus_temp[5] = ui_rowultraclear;
    ui_focus_temp[6] = ui_rowpip;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 7; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void hidden_menu_page1(void) {
    lv_obj_add_flag(ui_contpage1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    lv_group_remove_all_objs(keypad_group);
    lv_group_add_obj(keypad_group, ui_keytest);
}

void show_menu_page1_item1(void) {
    lv_obj_remove_flag(ui_contpages2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_lbltitle2, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_menu1row1;
    ui_focus_temp[1] = ui_menu1row2;
    ui_focus_temp[2] = ui_menu1row3;
    ui_focus_temp[3] = ui_menu1row4;
    ui_focus_temp[4] = ui_menu1row5;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 5; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void hidden_menu_page1_item1(void) {
    lv_obj_add_flag(ui_contpages2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_lbltitle2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowlrf, LV_STATE_USER_1, false);

    ui_focus_temp[0] = ui_rowlrf;
    ui_focus_temp[1] = ui_rowimagemode;
    ui_focus_temp[2] = ui_rowbrightness;
    ui_focus_temp[3] = ui_rowcontrast;
    ui_focus_temp[4] = ui_rowsharpness;
    ui_focus_temp[5] = ui_rowultraclear;
    ui_focus_temp[6] = ui_rowpip;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 7; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void show_menu_page1_item2(void) {
    lv_obj_remove_flag(ui_contitem2, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_rowitem21;
    ui_focus_temp[1] = ui_rowitem22;
    ui_focus_temp[2] = ui_rowitem23;
    ui_focus_temp[3] = ui_rowitem24;
    ui_focus_temp[4] = ui_rowitem25;
    ui_focus_temp[5] = ui_rowitem26;
    ui_focus_temp[6] = ui_rowitem27;
    ui_focus_temp[7] = ui_rowitem28;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 8; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void hidden_menu_page1_item2(void) {
    lv_obj_add_flag(ui_contitem2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowimagemode, LV_STATE_USER_1, false);

    ui_focus_temp[0] = ui_rowlrf;
    ui_focus_temp[1] = ui_rowimagemode;
    ui_focus_temp[2] = ui_rowbrightness;
    ui_focus_temp[3] = ui_rowcontrast;
    ui_focus_temp[4] = ui_rowsharpness;
    ui_focus_temp[5] = ui_rowultraclear;
    ui_focus_temp[6] = ui_rowpip;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 7; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }

    lv_group_focus_obj(ui_focus_temp[1]);
}

void show_menu_page2(void) {
    lv_obj_remove_flag(ui_contpage2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_rowwifi;
    ui_focus_temp[1] = ui_rowtilt;
    ui_focus_temp[2] = ui_rowcompass;
    ui_focus_temp[3] = ui_rowreticle;
    ui_focus_temp[4] = ui_rowballistic;
    ui_focus_temp[5] = ui_rowmic;
    ui_focus_temp[6] = ui_rowrav;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 7; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void hidden_menu_page2(void) {
    lv_obj_add_flag(ui_contpage2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    lv_group_remove_all_objs(keypad_group);
    lv_group_add_obj(keypad_group, ui_keytest);
}

void show_menu_page3(void) {
    lv_obj_remove_flag(ui_contpage3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_rowstandby;
    ui_focus_temp[1] = ui_rowcompasscalibration;
    ui_focus_temp[2] = ui_rowdeadpixel;
    ui_focus_temp[3] = ui_rowstatusbar;
    ui_focus_temp[4] = ui_rowdeletefile;
    ui_focus_temp[5] = ui_rowsetting;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 6; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void hidden_menu_page3(void) {
    lv_obj_add_flag(ui_contpage3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    lv_group_remove_all_objs(keypad_group);
    lv_group_add_obj(keypad_group, ui_keytest);
}