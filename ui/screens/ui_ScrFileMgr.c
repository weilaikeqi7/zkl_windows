#include "../ui.h"

lv_obj_t * ui_ScrFileMgr = NULL;
lv_obj_t * ui_UPLIST = NULL;
lv_obj_t * ui_BTN = NULL;
lv_obj_t * ui_LISTLABEL1 = NULL;
lv_obj_t * ui_year = NULL;
lv_obj_t * ui_LISTABEL = NULL;
lv_obj_t * ui_month = NULL;
lv_obj_t * ui_LISTLABEL2 = NULL;
lv_obj_t * ui_day = NULL;
lv_obj_t * ui_LISTLABEL3 = NULL;
lv_obj_t * ui_hour = NULL;
lv_obj_t * ui_LISTLABEL4 = NULL;
lv_obj_t * ui_min = NULL;
lv_obj_t * ui_LISTLABEL5 = NULL;
lv_obj_t * ui_BTN1 = NULL;
lv_obj_t * ui_BTN2 = NULL;
lv_obj_t * ui_BTN3 = NULL;
lv_obj_t * ui_List_Container = NULL;
lv_obj_t * ui_List_Header = NULL;
lv_obj_t * ui_List_Header_Item1 = NULL;
lv_obj_t * ui_List_Header_Item2 = NULL;
lv_obj_t * ui_List_Header_Item3 = NULL;
lv_obj_t * ui_List_Header_Item4 = NULL;
lv_obj_t * ui_DOWNLIST = NULL;
lv_obj_t * ui_BTN4 = NULL;
lv_obj_t * ui_BTN5 = NULL;
lv_obj_t * ui_BTN6 = NULL;
lv_obj_t * ui_BTN7 = NULL;
lv_obj_t * ui_PlayList[24];
// event funtions

// build funtions

void ui_ScrFileMgr_screen_init(void)
{
    ui_ScrFileMgr = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_ScrFileMgr, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_ScrFileMgr, lv_color_hex(0x2E2D2F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScrFileMgr, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_UPLIST = lv_obj_create(ui_ScrFileMgr);
    lv_obj_set_width(ui_UPLIST, LV_SIZE_CONTENT); /// 1
    lv_obj_set_height(ui_UPLIST, LV_SIZE_CONTENT); /// 1
    /* Top-left filter row */
    lv_obj_set_x(ui_UPLIST, 16);
    lv_obj_set_y(ui_UPLIST, 12);
    lv_obj_set_flex_flow(ui_UPLIST, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_UPLIST, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_remove_flag(ui_UPLIST, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_UPLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_UPLIST, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_UPLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_UPLIST, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_UPLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_UPLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_UPLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_UPLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_UPLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_UPLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_UPLIST, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BTN = ui_BTN_create(ui_UPLIST);
    lv_obj_set_x(ui_BTN, 0);
    lv_obj_set_y(ui_BTN, 0);

    lv_obj_set_width(ui_BTN, 60);
    lv_obj_set_height(ui_BTN, 32);

    ui_LISTLABEL1 = ui_LISTLABEL_create(ui_UPLIST);
    lv_obj_set_x(ui_LISTLABEL1, 0);
    lv_obj_set_y(ui_LISTLABEL1, 0);
    lv_label_set_text(ui_LISTLABEL1, "   ");

    ui_year = ui_DateItem_create(ui_UPLIST);
    lv_obj_set_x(ui_year, 0);
    lv_obj_set_y(ui_year, 0);
    lv_obj_set_width(ui_comp_get_child(ui_year, UI_COMP_DATEITEM_NUM), 56);

    lv_obj_set_style_bg_color(ui_comp_get_child(ui_year, UI_COMP_DATEITEM_NUM),
                              lv_color_hex(0x122128),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_year, UI_COMP_DATEITEM_NUM), 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_year, UI_COMP_DATEITEM_NUM),
                              lv_color_hex(0x122128),
                              LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_year, UI_COMP_DATEITEM_NUM), 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_LISTABEL = ui_LISTLABEL_create(ui_UPLIST);
    lv_obj_set_x(ui_LISTABEL, 0);
    lv_obj_set_y(ui_LISTABEL, 0);
    lv_label_set_text(ui_LISTABEL, " - ");

    ui_month = ui_DateItem_create(ui_UPLIST);
    lv_obj_set_x(ui_month, 0);
    lv_obj_set_y(ui_month, 0);
    lv_obj_set_width(ui_comp_get_child(ui_month, UI_COMP_DATEITEM_NUM), 48);

    lv_label_set_text(ui_comp_get_child(ui_month, UI_COMP_DATEITEM_NUM), "12");
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_month, UI_COMP_DATEITEM_NUM),
                              lv_color_hex(0x122128),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_month, UI_COMP_DATEITEM_NUM), 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_month, UI_COMP_DATEITEM_NUM),
                              lv_color_hex(0x122128),
                              LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_month, UI_COMP_DATEITEM_NUM), 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_LISTLABEL2 = ui_LISTLABEL_create(ui_UPLIST);
    lv_obj_set_x(ui_LISTLABEL2, 0);
    lv_obj_set_y(ui_LISTLABEL2, 0);
    lv_label_set_text(ui_LISTLABEL2, " - ");

    ui_day = ui_DateItem_create(ui_UPLIST);
    lv_obj_set_x(ui_day, 0);
    lv_obj_set_y(ui_day, 0);
    lv_obj_set_width(ui_comp_get_child(ui_day, UI_COMP_DATEITEM_NUM), 48);

    lv_label_set_text(ui_comp_get_child(ui_day, UI_COMP_DATEITEM_NUM), "30");

    lv_obj_set_style_bg_color(ui_comp_get_child(ui_day, UI_COMP_DATEITEM_NUM),
                              lv_color_hex(0x122128),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_day, UI_COMP_DATEITEM_NUM), 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_day, UI_COMP_DATEITEM_NUM),
                              lv_color_hex(0x122128),
                              LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_day, UI_COMP_DATEITEM_NUM), 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_LISTLABEL3 = ui_LISTLABEL_create(ui_UPLIST);
    lv_obj_set_x(ui_LISTLABEL3, 0);
    lv_obj_set_y(ui_LISTLABEL3, 0);
    lv_label_set_text(ui_LISTLABEL3, "   ");

    ui_hour = ui_DateItem_create(ui_UPLIST);
    lv_obj_set_x(ui_hour, 0);
    lv_obj_set_y(ui_hour, 0);
    lv_obj_set_width(ui_comp_get_child(ui_hour, UI_COMP_DATEITEM_NUM), 48);

    lv_label_set_text(ui_comp_get_child(ui_hour, UI_COMP_DATEITEM_NUM), "12");

    lv_obj_set_style_bg_color(ui_comp_get_child(ui_hour, UI_COMP_DATEITEM_NUM),
                              lv_color_hex(0x122128),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_hour, UI_COMP_DATEITEM_NUM), 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_hour, UI_COMP_DATEITEM_NUM),
                              lv_color_hex(0x122128),
                              LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_hour, UI_COMP_DATEITEM_NUM), 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_LISTLABEL4 = ui_LISTLABEL_create(ui_UPLIST);
    lv_obj_set_x(ui_LISTLABEL4, 0);
    lv_obj_set_y(ui_LISTLABEL4, 0);
    lv_label_set_text(ui_LISTLABEL4, " : ");

    ui_min = ui_DateItem_create(ui_UPLIST);
    lv_obj_set_x(ui_min, 0);
    lv_obj_set_y(ui_min, 0);
    lv_obj_set_width(ui_comp_get_child(ui_min, UI_COMP_DATEITEM_NUM), 48);

    lv_label_set_text(ui_comp_get_child(ui_min, UI_COMP_DATEITEM_NUM), "59");
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_min, UI_COMP_DATEITEM_NUM),
                              lv_color_hex(0x122128),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_min, UI_COMP_DATEITEM_NUM), 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_min, UI_COMP_DATEITEM_NUM),
                              lv_color_hex(0x122128),
                              LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_min, UI_COMP_DATEITEM_NUM), 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    ui_LISTLABEL5 = ui_LISTLABEL_create(ui_UPLIST);
    lv_obj_set_x(ui_LISTLABEL5, 0);
    lv_obj_set_y(ui_LISTLABEL5, 0);
    lv_label_set_text(ui_LISTLABEL5, "   ");

    ui_BTN1 = ui_BTN_create(ui_UPLIST);
    lv_obj_set_x(ui_BTN1, 0);
    lv_obj_set_y(ui_BTN1, 0);
    lv_obj_set_width(ui_BTN1, 96);
    lv_obj_set_height(ui_BTN1, 32);

    lv_label_set_text(ui_comp_get_child(ui_BTN1, UI_COMP_BTN_BTNL), "Search");

    /* Top-right mode buttons */
    ui_BTN2 = ui_BTN_create(ui_ScrFileMgr);
    lv_obj_set_width(ui_BTN2, 140);
    lv_obj_set_height(ui_BTN2, 32);
    lv_obj_set_align(ui_BTN2, LV_ALIGN_TOP_RIGHT);
    lv_obj_set_x(ui_BTN2, -188);
    lv_obj_set_y(ui_BTN2, 12);

    lv_label_set_text(ui_comp_get_child(ui_BTN2, UI_COMP_BTN_BTNL), "Preview Mode");

    ui_BTN3 = ui_BTN_create(ui_ScrFileMgr);
    lv_obj_set_width(ui_BTN3, 140);
    lv_obj_set_height(ui_BTN3, 32);
    lv_obj_set_align(ui_BTN3, LV_ALIGN_TOP_RIGHT);
    lv_obj_set_x(ui_BTN3, -32);
    lv_obj_set_y(ui_BTN3, 12);

    lv_label_set_text(ui_comp_get_child(ui_BTN3, UI_COMP_BTN_BTNL), "Delete Mode");

    ui_List_Container = lv_obj_create(ui_ScrFileMgr);
    lv_obj_set_width(ui_List_Container, 992);
    lv_obj_set_align(ui_List_Container, LV_ALIGN_TOP_LEFT);
    lv_obj_set_x(ui_List_Container, 16);
    lv_obj_set_y(ui_List_Container, 56);
    lv_obj_set_height(ui_List_Container, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_List_Container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_List_Container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_remove_flag(ui_List_Container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_List_Container, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_List_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_List_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_List_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui_List_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_List_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_List_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_List_Header = lv_obj_create(ui_List_Container);
    lv_obj_set_width(ui_List_Header, 992);
    lv_obj_set_height(ui_List_Header, 36);
    lv_obj_remove_flag(ui_List_Header, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_flow(ui_List_Header, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_List_Header, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_List_Header, lv_color_hex(0x122128), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_List_Header, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_List_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_List_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui_List_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_List_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_List_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_List_Header_Item1 = lv_label_create(ui_List_Header);
    lv_obj_set_width(ui_List_Header_Item1, 360);
    lv_obj_set_height(ui_List_Header_Item1, LV_SIZE_CONTENT);
    lv_label_set_text(ui_List_Header_Item1, "File Name");
    lv_obj_set_style_text_align(ui_List_Header_Item1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_List_Header_Item1, ui_font_WebnarMedium18, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(ui_List_Header_Item1,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Text);
    ui_object_set_themeable_style_property(ui_List_Header_Item1,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Text);

    ui_List_Header_Item2 = lv_label_create(ui_List_Header);
    lv_obj_set_width(ui_List_Header_Item2, 160);
    lv_obj_set_height(ui_List_Header_Item2, LV_SIZE_CONTENT);
    lv_label_set_text(ui_List_Header_Item2, "File Size");
    lv_obj_set_style_text_align(ui_List_Header_Item2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_List_Header_Item2, ui_font_WebnarMedium18, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(ui_List_Header_Item2,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Text);
    ui_object_set_themeable_style_property(ui_List_Header_Item2,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Text);

    ui_List_Header_Item3 = lv_label_create(ui_List_Header);
    lv_obj_set_width(ui_List_Header_Item3, 160);
    lv_obj_set_height(ui_List_Header_Item3, LV_SIZE_CONTENT);
    lv_label_set_text(ui_List_Header_Item3, "Type");
    lv_obj_set_style_text_align(ui_List_Header_Item3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_List_Header_Item3, ui_font_WebnarMedium18, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(ui_List_Header_Item3,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Text);
    ui_object_set_themeable_style_property(ui_List_Header_Item3,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Text);

    ui_List_Header_Item4 = lv_label_create(ui_List_Header);
    lv_obj_set_width(ui_List_Header_Item4, 312);
    lv_obj_set_height(ui_List_Header_Item4, LV_SIZE_CONTENT);
    lv_label_set_text(ui_List_Header_Item4, "Date Created");
    lv_obj_set_style_text_align(ui_List_Header_Item4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_List_Header_Item4, ui_font_WebnarMedium18, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(ui_List_Header_Item4,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Text);
    ui_object_set_themeable_style_property(ui_List_Header_Item4,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Text);

    ui_DOWNLIST = lv_obj_create(ui_ScrFileMgr);
    lv_obj_set_width(ui_DOWNLIST, LV_SIZE_CONTENT); /// 1
    lv_obj_set_height(ui_DOWNLIST, LV_SIZE_CONTENT); /// 1
    /* Bottom-right pagination */
    lv_obj_set_x(ui_DOWNLIST, -20);
    lv_obj_set_y(ui_DOWNLIST, -20);
    lv_obj_set_align(ui_DOWNLIST, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_set_flex_flow(ui_DOWNLIST, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_DOWNLIST, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_remove_flag(ui_DOWNLIST, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_DOWNLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DOWNLIST, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DOWNLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_DOWNLIST, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_DOWNLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_DOWNLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_DOWNLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_DOWNLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_DOWNLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_DOWNLIST, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_DOWNLIST, 12, LV_PART_MAIN | LV_STATE_DEFAULT);

    /* Keep Back in codebase but hide it to match reference layout */
    ui_BTN4 = ui_BTN_create(ui_DOWNLIST);
    lv_obj_set_width(ui_BTN4, 120);
    lv_obj_set_height(ui_BTN4, 32);
    lv_label_set_text(ui_comp_get_child(ui_BTN4, UI_COMP_BTN_BTNL), "Back");

    ui_BTN5 = ui_BTN_create(ui_DOWNLIST);
    lv_obj_set_width(ui_BTN5, 96);
    lv_obj_set_height(ui_BTN5, 32);
    lv_label_set_text(ui_comp_get_child(ui_BTN5, UI_COMP_BTN_BTNL), "Previous");

    ui_BTN7 = ui_BTN_create(ui_DOWNLIST);
    lv_obj_set_width(ui_BTN7, 40);
    lv_obj_set_height(ui_BTN7, 32);
    lv_label_set_text(ui_comp_get_child(ui_BTN7, UI_COMP_BTN_BTNL), "1");

    ui_BTN6 = ui_BTN_create(ui_DOWNLIST);
    lv_obj_set_width(ui_BTN6, 80);
    lv_obj_set_height(ui_BTN6, 32);
    lv_label_set_text(ui_comp_get_child(ui_BTN6, UI_COMP_BTN_BTNL), "Next");
}

void ui_ScrFileMgr_screen_destroy(void)
{
    if(ui_ScrFileMgr)
        lv_obj_del(ui_ScrFileMgr);

    // NULL screen variables
    ui_ScrFileMgr = NULL;
    ui_UPLIST = NULL;
    ui_BTN = NULL;
    ui_LISTLABEL1 = NULL;
    ui_year = NULL;
    ui_LISTABEL = NULL;
    ui_month = NULL;
    ui_LISTLABEL2 = NULL;
    ui_day = NULL;
    ui_LISTLABEL3 = NULL;
    ui_hour = NULL;
    ui_LISTLABEL4 = NULL;
    ui_min = NULL;
    ui_LISTLABEL5 = NULL;
    ui_BTN1 = NULL;
    ui_BTN2 = NULL;
    ui_BTN3 = NULL;
    ui_List_Container = NULL;
    ui_List_Header = NULL;
    ui_List_Header_Item1 = NULL;
    ui_List_Header_Item2 = NULL;
    ui_List_Header_Item3 = NULL;
    ui_List_Header_Item4 = NULL;
    ui_DOWNLIST = NULL;
    ui_BTN4 = NULL;
    ui_BTN5 = NULL;
    ui_BTN6 = NULL;
    ui_BTN7 = NULL;
}