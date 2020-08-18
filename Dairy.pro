TEMPLATE = subdirs

SUBDIRS = LxDairy \
#    LxDairyUpd \
    PaletteSetting \
    PluginTest/pluginTest

CONFIG += ordered
# 子项目默认*.pro与工程名一.pro与工程名不一通过file属性指#data_engine.file = data_engine/data_engine_qt4.pro
#auth_interface.file = auth_interface/auth_interface_qt4.pro
