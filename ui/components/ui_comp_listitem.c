//
// Created by Administrator on 2025/9/2.
//

#include "ui_comp_listitem.h"

void
ui_event_comp_ListItem(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t ** comp_ListItem = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_obj_set_style_text_color(comp_ListItem[UI_COMP_LISTITEM_1],
                                    lv_color_hex(0x37F6FA),
                                    LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_text_opa(comp_ListItem[UI_COMP_LISTITEM_1], 255, LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_text_color(comp_ListItem[UI_COMP_LISTITEM_2],
                                    lv_color_hex(0x37F6FA),
                                    LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_text_opa(comp_ListItem[UI_COMP_LISTITEM_2], 255, LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_text_color(comp_ListItem[UI_COMP_LISTITEM_3],
                                    lv_color_hex(0x37F6FA),
                                    LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_text_opa(comp_ListItem[UI_COMP_LISTITEM_3], 255, LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_text_color(comp_ListItem[UI_COMP_LISTITEM_4],
                                    lv_color_hex(0x37F6FA),
                                    LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_text_opa(comp_ListItem[UI_COMP_LISTITEM_4], 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
        ui_object_set_themeable_style_property(comp_ListItem[UI_COMP_LISTITEM_1],
                                               LV_PART_MAIN | LV_STATE_DEFAULT,
                                               LV_STYLE_TEXT_COLOR,
                                               _ui_theme_color_Text);
        ui_object_set_themeable_style_property(comp_ListItem[UI_COMP_LISTITEM_1],
                                               LV_PART_MAIN | LV_STATE_DEFAULT,
                                               LV_STYLE_TEXT_OPA,
                                               _ui_theme_alpha_Text);
        ui_object_set_themeable_style_property(comp_ListItem[UI_COMP_LISTITEM_2],
                                               LV_PART_MAIN | LV_STATE_DEFAULT,
                                               LV_STYLE_TEXT_COLOR,
                                               _ui_theme_color_Text);
        ui_object_set_themeable_style_property(comp_ListItem[UI_COMP_LISTITEM_2],
                                               LV_PART_MAIN | LV_STATE_DEFAULT,
                                               LV_STYLE_TEXT_OPA,
                                               _ui_theme_alpha_Text);
        ui_object_set_themeable_style_property(comp_ListItem[UI_COMP_LISTITEM_3],
                                               LV_PART_MAIN | LV_STATE_DEFAULT,
                                               LV_STYLE_TEXT_COLOR,
                                               _ui_theme_color_Text);
        ui_object_set_themeable_style_property(comp_ListItem[UI_COMP_LISTITEM_3],
                                               LV_PART_MAIN | LV_STATE_DEFAULT,
                                               LV_STYLE_TEXT_OPA,
                                               _ui_theme_alpha_Text);
        ui_object_set_themeable_style_property(comp_ListItem[UI_COMP_LISTITEM_4],
                                               LV_PART_MAIN | LV_STATE_DEFAULT,
                                               LV_STYLE_TEXT_COLOR,
                                               _ui_theme_color_Text);
        ui_object_set_themeable_style_property(comp_ListItem[UI_COMP_LISTITEM_4],
                                               LV_PART_MAIN | LV_STATE_DEFAULT,
                                               LV_STYLE_TEXT_OPA,
                                               _ui_theme_alpha_Text);
    }
}

lv_obj_t * ui_listItem_create(lv_obj_t * comp_parent)
{
    lv_obj_t * cui_List_Header = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_List_Header, 928);
    lv_obj_set_height(cui_List_Header, 42);
    lv_obj_remove_flag(cui_List_Header, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_flow(cui_List_Header, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_List_Header, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_bg_color(cui_List_Header, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_List_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_List_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cui_List_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(cui_List_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_List_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_List_Header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_List_Header_Item1 = lv_label_create(cui_List_Header);
    lv_obj_set_width(cui_List_Header_Item1, 300);
    lv_obj_set_height(cui_List_Header_Item1, LV_SIZE_CONTENT);
    lv_obj_set_style_text_align(cui_List_Header_Item1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_List_Header_Item1, ui_font_WebnarRegular18, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(cui_List_Header_Item1,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Text);
    ui_object_set_themeable_style_property(cui_List_Header_Item1,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Text);

    lv_obj_t * cui_List_Header_Item2 = lv_label_create(cui_List_Header);
    lv_obj_set_width(cui_List_Header_Item2, 199);
    lv_obj_set_height(cui_List_Header_Item2, LV_SIZE_CONTENT);
    lv_obj_set_style_text_align(cui_List_Header_Item2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_List_Header_Item2, ui_font_WebnarRegular18, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(cui_List_Header_Item2,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Text);
    ui_object_set_themeable_style_property(cui_List_Header_Item2,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Text);

    lv_obj_t * cui_List_Header_Item3 = lv_label_create(cui_List_Header);
    lv_obj_set_width(cui_List_Header_Item3, 220);
    lv_obj_set_height(cui_List_Header_Item3, LV_SIZE_CONTENT);
    lv_obj_set_style_text_align(cui_List_Header_Item3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_List_Header_Item3, ui_font_WebnarRegular18, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(cui_List_Header_Item3,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Text);
    ui_object_set_themeable_style_property(cui_List_Header_Item3,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Text);

    lv_obj_t * cui_List_Header_Item4 = lv_label_create(cui_List_Header);
    lv_obj_set_width(cui_List_Header_Item4, 209);
    lv_obj_set_height(cui_List_Header_Item4, LV_SIZE_CONTENT);
    lv_obj_set_style_text_align(cui_List_Header_Item4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_List_Header_Item4, ui_font_WebnarRegular18, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(cui_List_Header_Item4,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Text);
    ui_object_set_themeable_style_property(cui_List_Header_Item4,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Text);

    lv_obj_t ** children = lv_malloc(sizeof(lv_obj_t *) * _UI_COMP_LISTITEM_NUM);
    children[UI_COMP_LISTITEM_LISTITEM] = cui_List_Header;
    children[UI_COMP_LISTITEM_1] = cui_List_Header_Item1;
    children[UI_COMP_LISTITEM_2] = cui_List_Header_Item2;
    children[UI_COMP_LISTITEM_3] = cui_List_Header_Item3;
    children[UI_COMP_LISTITEM_4] = cui_List_Header_Item4;
    lv_obj_add_event_cb(cui_List_Header, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_List_Header, del_component_child_event_cb, LV_EVENT_DELETE, children);
    lv_obj_add_event_cb(cui_List_Header, ui_event_comp_ListItem, LV_EVENT_ALL, children);
    ui_comp_ListItem_create_hook(cui_List_Header);
    return cui_List_Header;
}