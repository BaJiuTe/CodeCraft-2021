# CodeCraft-2021

## git 使用教程
1. 克隆仓库到本地当前目录
```bash
git clone git@github.com:BaJiuTe/CodeCraft-2021.git
```

2. 以后每天写代码，都需要 pull 一下仓库，更新版本
```bash
git pull origin main
```

3. 将本地仓库推送到远程仓库
```bash
git add .

git commit -m "写上你所作的更改"

git push -u origin main
```


## 文件结构说明
- 所有的代码都放在 `/CodeCraft-2021/SDK_C++/CodeCraft-2021`，包括.h .hpp .cpp
- `build_and_run.sh` 包括了`build.sh`，所以只需要执行 `./build_and_run.sh`，就行了，脚本还会自动帮我们生成 bin 目录和 build 目录
- 我们只需要往 `CodeCraft-2021.cpp` 里面写主程序就好了
- 打包提交作品的话，执行 `./CodeCraft_zip.sh` 就行