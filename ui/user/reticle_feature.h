// reticle_feature.h
#ifndef RETICLE_FEATURE_H
#define RETICLE_FEATURE_H

#include <stdbool.h>

// Reticle 四级菜单功能入口（按《分划板功能需求.xlsx》实现）
//
// 功能要点：
// - 2级：显示开关/旋转开关/GunType/Style/Color/Reset/AddDistance/Save + 动态距离列表
// - 3级：Calibration/Primacy/Modify/Delete
// - 4级：X/Y/Zero(Clear+Reset确认)/Zoom/Freeze
// - 动态新增距离条目自动加入焦点组（解决“动态添加焦点”）
// - 退出时 dirty 检测：若有修改弹框提示保存
// - ui_editdistance 作为通用组件复用（distance_editor）
//
// 依赖：
// - user/distance_editor.*
// - user/reticle_distance_mgr.*
// - user/reticle_model.* (10枪型配置模型)

void reticle_feature_init(void);
void reticle_feature_bind_events(void);

void reticle_feature_open(void);
void reticle_feature_close(void);
bool reticle_feature_is_open(void);

#endif
