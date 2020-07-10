# 绑定USB串口，端口，其实都是在.rule中通过映射规则将usb设备名映射为一个不变的名称
>查看串口信息，可以获得设备出厂ID，，但同一批产品可能一致
* $ lsusb
>ID在规则中的对应值设置如下
```
ATTRS{idVendor}=="067b", ATTRS{idProduct}=="2303"
```
>获得每个usb的KERNELS(即电脑上这个USB口的编号)，如果想要把某个usb设备绑定到某一端口，需要插入该设备进行绑定，否则没有该usb的信息
* $ udevadm info [-a] /dev/ttyUSB*  或者 
* $ ls -l /sys/class/tty/ttyUSB*
## 绑定USB端口号
插到这个USB端口的串口名都被改为imu、video3...
* $ sudo gedit /etc/udev/rules.d/myusb.rule  
>添加（好像这里改成"1-1.2"才能成功）：
```
ACTION=="add",KERNELS=="1-1.2:1.0",SUBSYSTEMS=="usb",MODE:="0777",SYMLINK+="imu"
```
```
ACTION=="add",KERNELS=="1-1.2:1.0",SUBSYSTEMS=="video*",MODE:="0777",SYMLINK+="video3"
```
## 绑定USB串口号
当两个设备的出厂ID相同时，会出现混乱
* $ sudo gedit /etc/udev/rules.d/myusb.rule  
>添加：
```
KERNEL=="ttyUSB*", ATTRS{idVendor}=="067b", ATTRS{idProduct}=="2303", MODE:="0666", SYMLINK+="lidar"
```


