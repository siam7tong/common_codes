
# 记Qtcreator xcb报错调试
>文件/usr/lib/x86_64-linux-gnu/qt-default/qtchooser/default.conf  #默认链接的是qt4，已更改  
>Qt安装路径的bin目录下打开终端
* $ export QT_DEBUG_PLUGINS=1
>然后从终端打开IDE
* $ qtcreator 或者
* $ sh qtctreator.sh
>可以看到详细的报错信息。  
>xcb报错为libQt5XcbQpa.so.5和libQt5DBus.so.5库的路径错误
>最终解决办法：  
>替换/usr/lib/x86_64-linux-gnu下的libQt5XcbQpa.so.5和libQt5DBus.so.5为Qt5/5.13.2/gcc中的相应文件。





