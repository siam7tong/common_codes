sudo find /usr -name "*libboost*"

记Qt xcb报错调试
/usr/lib/x86_64-linux-gnu/qt-default/qtchooser/default.conf  #默认链接的是qt4，已更改
终端export QT_DEBUG_PLUGINS=1
然后再打开
qtcreator
或者
sh qtctreator.sh
可以查看详细的报错信息。


最终解决办法：
替换/usr/lib/x86_64-linux-gnu下的libQt5XcbQpa.so.5和libQt5DBus.so.5为Qt5/5.13.2/gcc中的相应文件。


# ssh远程连接
ssh -X research@192.168.11.117


