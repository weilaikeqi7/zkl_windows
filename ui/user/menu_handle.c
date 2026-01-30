//
// Created by jinxing on 2026/1/5.
//

#include "menu_handle.h"

lv_obj_t *ui_focus_temp[30];

void show_menu_page1(void) {
    lv_obj_remove_flag(ui_contpage1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);

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
    lv_obj_remove_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);
}

void show_menu_page1_item1(void) {
    lv_obj_remove_flag(ui_contmenu2, LV_OBJ_FLAG_HIDDEN);

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
    lv_obj_add_flag(ui_contmenu2, LV_OBJ_FLAG_HIDDEN);
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
    lv_obj_add_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);

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
    lv_obj_remove_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);
}

void show_menu_page3(void) {
    lv_obj_remove_flag(ui_contpage3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);

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
    lv_obj_remove_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);
}

void show_menu_page3_item1(void) {
    lv_obj_remove_flag(ui_page3item1, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_rowswitch1;
    ui_focus_temp[1] = ui_rowitem1;
    ui_focus_temp[2] = ui_rowitem2;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 3; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void hidden_menu_page3_item1(void) {
    lv_obj_add_flag(ui_page3item1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowstandby, LV_STATE_USER_1, false);

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

void show_menu_page3_item2(void) {
    lv_obj_remove_flag(ui_page3item2, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_rowitem3;
    ui_focus_temp[1] = ui_rowitem4;
    ui_focus_temp[2] = ui_rowitem5;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 3; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void hidden_menu_page3_item2(void) {
    lv_obj_add_flag(ui_page3item2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowcompasscalibration, LV_STATE_USER_1, false);

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
    lv_group_focus_obj(ui_focus_temp[1]);
}

void show_menu_page3_item2_item2(void) {
    lv_obj_remove_flag(ui_numInput, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_comp_get_child(ui_num1, UI_COMP_NUM_PANELNUM);
    ui_focus_temp[1] = ui_comp_get_child(ui_num2, UI_COMP_NUM_PANELNUM);
    ui_focus_temp[2] = ui_comp_get_child(ui_num3, UI_COMP_NUM_PANELNUM);
    ui_focus_temp[3] = ui_comp_get_child(ui_num4, UI_COMP_NUM_PANELNUM);
    ui_focus_temp[4] = ui_comp_get_child(ui_num5, UI_COMP_NUM_PANELNUM);
    ui_focus_temp[5] = ui_comp_get_child(ui_num6, UI_COMP_NUM_PANELNUM);
    ui_focus_temp[6] = ui_rowitemOK;
    ui_focus_temp[7] = ui_rowitemCANCEL;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 8; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void hidden_menu_page3_item2_item2(void) {
    lv_obj_add_flag(ui_numInput, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowitem4, LV_STATE_USER_1, false);

    ui_focus_temp[0] = ui_rowitem3;
    ui_focus_temp[1] = ui_rowitem4;
    ui_focus_temp[2] = ui_rowitem5;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 3; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
    lv_group_focus_obj(ui_rowitem4);
}

void show_menu_page3_item6(void) {
    lv_obj_remove_flag(ui_contmenusetting, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_settingrow1;
    ui_focus_temp[1] = ui_settingrow2;
    ui_focus_temp[2] = ui_settingrow3;
    ui_focus_temp[3] = ui_settingrow4;
    ui_focus_temp[4] = ui_settingrow5;
    ui_focus_temp[5] = ui_settingrow6;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 6; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void hidden_menu_page3_item6(void) {
    lv_obj_add_flag(ui_contmenusetting, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowsetting, LV_STATE_USER_1, false);

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
    lv_group_focus_obj(ui_focus_temp[5]);
}

void show_menu_page3_itme6_item1(void) {
    lv_obj_remove_flag(ui_contdate, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_rowitemyear;
    ui_focus_temp[1] = ui_rowitemmonth;
    ui_focus_temp[2] = ui_rowitemday;
    ui_focus_temp[3] = ui_rowitemdateback;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 4; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
    date.year = datatime.year;
    date.month = datatime.month;
    date.day = datatime.day;
    lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemyear, UI_COMP_ROWITEM1_LABEL), "%d", date.year);
    lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemmonth, UI_COMP_ROWITEM1_LABEL), "%d", date.month);
    lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
}

void hidden_menu_page3_itme6_item1(void) {
    lv_obj_add_flag(ui_contdate, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow1, LV_STATE_USER_1, false);

    ui_focus_temp[0] = ui_settingrow1;
    ui_focus_temp[1] = ui_settingrow2;
    ui_focus_temp[2] = ui_settingrow3;
    ui_focus_temp[3] = ui_settingrow4;
    ui_focus_temp[4] = ui_settingrow5;
    ui_focus_temp[5] = ui_settingrow6;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 6; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void show_menu_page3_itme6_item2(void) {
    lv_obj_remove_flag(ui_conttime, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_rowitemhour;
    ui_focus_temp[1] = ui_rowitemmin;
    ui_focus_temp[2] = ui_rowitemtimeback;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 3; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
    tim.hour = datatime.hour;
    tim.min = datatime.min;
    lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemhour, UI_COMP_ROWITEM1_LABEL), "%02d", tim.hour);
    lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemmin, UI_COMP_ROWITEM1_LABEL), "%02d", tim.min);
}

void hidden_menu_page3_itme6_item2(void) {
    lv_obj_add_flag(ui_conttime, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow2, LV_STATE_USER_1, false);

    ui_focus_temp[0] = ui_settingrow1;
    ui_focus_temp[1] = ui_settingrow2;
    ui_focus_temp[2] = ui_settingrow3;
    ui_focus_temp[3] = ui_settingrow4;
    ui_focus_temp[4] = ui_settingrow5;
    ui_focus_temp[5] = ui_settingrow6;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 6; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
    lv_group_focus_obj(ui_focus_temp[1]);
}

void show_menu_page3_itme6_item4(void) {
    lv_obj_remove_flag(ui_DialogReset, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_resetOK;
    ui_focus_temp[1] = ui_resetCANCEL;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 2; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void hidden_menu_page3_itme6_item4(void) {
    lv_obj_add_flag(ui_DialogReset, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow4, LV_STATE_USER_1, false);

    ui_focus_temp[0] = ui_settingrow1;
    ui_focus_temp[1] = ui_settingrow2;
    ui_focus_temp[2] = ui_settingrow3;
    ui_focus_temp[3] = ui_settingrow4;
    ui_focus_temp[4] = ui_settingrow5;
    ui_focus_temp[5] = ui_settingrow6;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 6; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
    lv_group_focus_obj(ui_focus_temp[3]);
}

void show_menu_page3_itme6_item5(void) {
    lv_obj_remove_flag(ui_DialogInfo, LV_OBJ_FLAG_HIDDEN);

    ui_focus_temp[0] = ui_infoOK;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 1; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
}

void hidden_menu_page3_itme6_item5(void) {
    lv_obj_add_flag(ui_DialogInfo, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow5, LV_STATE_USER_1, false);

    ui_focus_temp[0] = ui_settingrow1;
    ui_focus_temp[1] = ui_settingrow2;
    ui_focus_temp[2] = ui_settingrow3;
    ui_focus_temp[3] = ui_settingrow4;
    ui_focus_temp[4] = ui_settingrow5;
    ui_focus_temp[5] = ui_settingrow6;

    lv_group_remove_all_objs(keypad_group);

    for (int i = 0; i < 6; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
    lv_group_focus_obj(ui_focus_temp[4]);
}