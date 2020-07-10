# 生成新的密钥对，放在/home/name/.ssh下，-P参数为私钥设置密码
* $ ssh-keygen -t rsa -b 4096 -C "zl94@bova.tech" -P "123456"
# 将公钥添加到远程用户的公钥认证文件中
* $ ssh-copy-id -i ~/.ssh/id_rsa.pub bova@192.168.0.108
# 连接远程服务器，-i 手动指定连接时的密钥私钥
* $ ssh root@192.168.0.108
* $ ssh -i ~/.ssh/id_rsa bova@192.168.0.108

# 启动ssh-agent后台运行，并将秘钥交给ssh-agent进行管理，连接时自动匹配私钥
* $ eval `ssh-agent -s`
* $ ssh-add ~/.ssh/id_rsa


