# Git图形管理工具
    SourceTree
***
# 准备
## 安装
* $ sudo apt-get install git
## 配置用户信息
>--global表示这台机器上所有的Git仓库都会使用这个配置
>当前仓库的配置文件为 projectpath/.git/config，当前用户的配置文件为/home/name/.gitconfig
* $ git config --global user.email "you@example.com"
* $ git config --global user.name "Your Name"
>让Git显示颜色
* $ git config --global color.ui true
>配置别名
* $ git config --global alias.st status
* $ git config --global alias.co checkout
* $ git config --global alias.ci commit
* $ git config --global alias.br branch
* $ git config --global alias.unstage 'reset HEAD'
* $ git config --global alias.last 'log -1'
* $ git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
## 初始化目录
>自动创建唯一的master分支，master指针指向最新的提交
* $ git init
***
# 修改，提交
## 添加修改
>可以同时添加多个文件到暂存区
* $ git add readme.txt
>添加当前的所有修改
* $ git add .
## 提交修改
>一次可以提交多个文件到当前分支
* $ git commit -m "explaination"
>提交所有本地修改，仅限已追踪的文件
* $ git commit -a 
## 查看历史提交
* $ git log [--pretty=oneline] [--abbrev-commit] [-p file]
## 查看某文件的提交历史
* $ git blame file
## 查看历史操作
>可以看到所有版本号
* $ git reflog
## 版本回退
>当前版本HEAD(指向当前分支的指针)，上一版HEAD^，上上一版HEAD^^，往前100个版本HEAD~100
* $ git reset --hard HEAD^
## 版本恢复
>找到该版本的commit id，就可以恢复到该版本，无论是回退还是恢复
* $ git reset --hard commit_id
## 查看状态
* $ git status
## 对比文件
>查看工作区和版本库里面最新版本的区别
* $ git diff HEAD -- readme.txt
## 撤销修改
>撤销工作区修改，回到最近一次git commit或git add后的状态
* $ git checkout -- file 
>可以把暂存区的修改撤销掉，放回工作区
* $ git reset HEAD file
## 删除文件
* $ git rm file
* $ git commit -m "remove file"
>如果删错了，则一键还原，用版本库里的版本替换工作区的版本
* $ git checkout -- file
***
# 远程仓库
## 关联远程仓库
>origin是远程库的名字，也可以改为别的
1. 关联仓库
* $ git remote add origin git@github.com:siam7tong/common_codes.git
* $ git remote set-url origin git+ssh://git@github.com/siam7tong/common_codes.git

>可以同时关联两个远程仓库，需要通过命名来区分
* $ git remote add github git@github.com:siam7tong/common_codes.git
* $ git remote add gitee git@gitee.com:siam7tong/common_codes.git
2. 关联分支
* $ git branch --set-upstream-to=origin/dev dev
* $ git checkout --track origin/dev
## 查看远程仓库
* $ git remote [-v]
* $ git remote show origin
## 推送本地分支
>-u只在第一次push时添加即可
* $ git push [-u] origin master
## 拉取远程库
>ssh 协议
* $ git clone git@github.com:siam7tong/common_codes.git
>https 协议
* $ git clone https://github.com/siam7tong/common_codes.git
## 删除远程关联
* $ git remote rm origin
***
# 分支管理
## 创建分支
>从当前分支上创建分支，-b表示创建并切换，origin/dev表示从远程仓库的dev分支创建本地dev分支
* $ git checkout -b dev [origin/dev]
* $ git checkout --track origin/dev
>新版Git用法
* $ git switch -c dev
## 切换分支
* $ git checkout master
* $ git switch master
## 查看当前分支
* $ git branch [-av]
## 合并分支
>将dev分支合并到当前分支上．合并分支时，如果可能，Git会用Fast forward模式，但这种模式下，删除分支后，会丢掉分支信息
* $ git merge dev
* $ git merge --no-ff -m "merge with no-ff" dev
## 删除分支
>-d会因为该分支没有被合并而删除失败，-D会强制删除
* $ git branch -d dev
* $ git branch -D dev
>删除远程分支
* $ git branch -dr origin/dev
## 保护、恢复现场
>适用于临时调bug，添加新的feature
* $ git stash                      此时在dev分支
* $ git stash list
1. 两步恢复
* $ git stash apply [stash@{0}]        切换到dev分支
* $ git stash drop [stash@{0}]
2. 一步恢复
* $ git stash pop 
## 同步某次提交到当前分支
>master修复的bug同样存在与dev分支上，将master的这次提交应用在dev分支上
* $ git cherry-pick commit_id
## 拉取远程关联分支进行合并
>本地分支和远程分支必须要进行关联，否则会拉取失败，当拉取出现冲突时，利用git status查看状态
* $ git pull
## 将本地未push的分叉提交历史整理成直线
* $ git rebase
***
# 标签管理
## 打标签
>标签总是和commit挂钩，默认打到当前的commit上，-a 后跟标签名字
* $ git tag -a tagname -m "explaination" [commit_id]
## 查看标签
* $ git tag
## 查看标签信息
* $ git show tagname
## 删除标签
* $ git -d tagname
## 推送标签
1. 推送某个标签
* $ git push origin tagname
2. 一次性推送所有标签
* $ git push origin --tags
## 删除远程的标签
>需要先在本地删除,然后进行如下操作
* $ git push origin :refs/tags/<tagname>
















