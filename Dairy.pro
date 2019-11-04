TEMPLATE = subdirs

SUBDIRS = LxDairy \
    LxDairyUpd

CONFIG += ordered
# 子项目列表,默认*.pro与工程名一致
# 当*.pro与工程名不一致,通过file属性指定
#data_engine.file = data_engine/data_engine_qt4.pro
#auth_interface.file = auth_interface/auth_interface_qt4.pro
