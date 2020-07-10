#列出所有wifi驱动模块，查看是否有硬件和软件阻塞问题
$ rfkill list all
激活所有模块，通常是解除软件阻塞
$ rfkill unblock all
#联想主机有的自带驱动，ubuntu下无法正常工作，需要禁用
在/etc/modprobe.d/目录下，添加ideawifiblacklist.conf文件，内容为
blacklist ideapad_laptop #联想
blacklist acer-wmi  #宏碁
或者通过以下命令移除联想的驱动，但该方法重启失效
$sudo modprobe -r ideapad_laptop

#如果没有驱动，则需要连接网线安装wifi驱动
$sudo apt-get install bcmwl-kernel-source
