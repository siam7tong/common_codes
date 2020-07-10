# 安装docker
1. 创建/etc/apt/sources.list.d/docker.list文件并添加以下内容
>deb [arch=amd64] https://download.docker.com/linux/ubuntu bionic stable
2. 更新
* $ sudo apt-get update
3. 添加密钥
>官方
* $ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
>阿里
* $ curl -fsSL https://mirrors.aliyun.com/docker-ce/linux/ubuntu/gpg | sudo apt-key add -
>验证
* $ sudo apt-key fingerprint 0EBFCD88
4. 安装
* $ sudo apt-get install docker-ce[=<VERSION>]
5. 验证
* $ sudo docker run hello-world
6. 卸载
* $ sudo apt-get remove docker docker-engine docker-ce docker.io
***
# 安装nvidia-docker
1. 添加密钥
* $ distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
* $ curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey | sudo apt-key add -
2. 添加源
* $ curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list | sudo tee /etc/apt/sources.list.d/nvidia-docker.list
* $ sudo apt-get update 
3. 安装
* $ sudo apt-get install nvidia-docker2
4. 激活
* $ sudo systemctl restart docker
***
## NVIDIA NGC API Key
有些docker安装时需要nvidia-docker支持，需要登录账号  
网址: https://ngc.nvidia.com/catalog/all  
账号: 1193985497@qq.com  
进入点击头像，选择Generate API Key，得到key，然后命令行操作如下
>$ docker login nvcr.io  
>Username: $oauthtoken  
>Password: <Your Key>  
>mykey:dmE2bWZ0Y3ZiNzU2cWJmcXJkZjluNmIzZWE6ZTkzMzI5NmItYjAxNS00OTA0LWJiNGYtNWY2OGI4ZDgyODc0
***
# docker命令
## 查看docker版本
* $ docker --version
## 删除容器
* $ docker rm container_id
## 删除镜像
* $ docker rmi image_id
## 查询镜像
* $ docker images
## 查询容器
>查看所有容器
* $ docker ps -a
>查看激活状态的容器
* $ docker ps
>查看容器的详细信息
* $ docker ps container_id
## 从镜像建立容器
>-d 参数是后台运行 --name 容器名字 最后是镜像的名字
* $ docker run -it --name chineseocr-app8080  -p 8080:8080 -v /host/path:/docker/path chineseocr:app
## 从终端进入正在运行的容器
* $ docker exec -it container_id /bin/bash
