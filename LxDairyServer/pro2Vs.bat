cd LHttpServer
qmake -r -tp vc
::若有多个.pro
::qmake -r -tp vc LHttpServer.pro

::建议使用开始菜单qt命令行工具执行命令

::如果是多人开发，因为每个人的电脑环境不一样，所以也不能使用上述方法。还得手动新建空工程把文件加上去，环境变量使用设置里的QTDIR,这样每个人都不用再配置了
pause