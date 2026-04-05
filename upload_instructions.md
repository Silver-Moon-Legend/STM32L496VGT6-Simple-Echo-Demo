# GitHub上传指南

## 上传步骤详细说明

### 1. 准备工作
首先确保您已经准备好以下内容：
- GitHub账号
- Git客户端已安装
- GitHub仓库创建完成

### 2. GitHub仓库创建
1. 登录GitHub
2. 点击右上角 "+" → "New repository"
3. 填写仓库信息：
   - Repository name: `STM32L496VGT6-Simple-Echo-Demo`
   - Description: `STM32L496VGT6麦克风喇叭回声demo`
   - Public: 勾选
   - Initialize this repository with a README: 勾选
4. 点击 "Create repository"

### 3. 本地Git配置
```bash
# 配置Git用户名（如果未配置）
git config --global user.name "您的GitHub用户名"
git config --global user.email "您的GitHub邮箱"

# 配置Git默认分支为main
git config --global init.defaultBranch main
```

### 4. 克隆仓库
```bash
# 克隆您创建的仓库
git clone https://github.com/您的用户名/STM32L496VGT6-Simple-Echo-Demo.git
cd STM32L496VGT6-Simple-Echo-Demo
```

### 5. 复制项目文件
```bash
# 将upload_simple_echo目录的所有文件复制到仓库
cp -r /path/to/upload_simple_echo/* .
```

### 6. 添加Git配置
```bash
# 初始化Git仓库
git init

# 添加所有文件
git add .

# 提交更改
git commit -m "STM32L496VGT6简易回声demo - 初始提交"
```

### 7. 推送到GitHub
```bash
# 添加远程仓库（如果还未添加）
git remote add origin https://github.com/您的用户名/STM32L496VGT6-Simple-Echo-Demo.git

# 推送代码
git push -u origin main
```

### 8. 验证上传
访问GitHub仓库页面：https://github.com/您的用户名/STM32L496VGT6-Simple-Echo-Demo
确保所有文件都已上传。

## 文件列表验证
上传后应包含以下文件：

```
STM32L496VGT6-Simple-Echo-Demo/
├── README.md
├── LICENSE
├── .gitignore
├── .gitattributes
├── src/
│   ├── simple_echo_demo.c
│   ├── dfsdm_driver.c
│   ├── dfsdm_driver.h
│   ├── i2s_driver.c
│   ├── i2s_driver.h
│   ├── power_manager.c
│   ├── power_manager.h
│   ├── main.c
│   ├── main.h
├── config/
│   ├── snore_detection.ioc
│   ├── cube_headless.txt
├── docs/
│   ├── cubemx_config_tutorial.md
│   ├── cubemx_quick_config.md
│   ├── cubemx_video_script.md
│   ├── ConnectionGuide.md
│   ├── UserGuide.md
├── images/
│   ├── hardware_setup.png（需要您添加）
│   ├── cubemx_config.png（需要您添加）
│   ├── demo_screenshot.png（需要您添加）
├── examples/
│   ├── simple_echo_makefile.mk
│   ├── simple_echo_demo_readme.md
├── upload_instructions.md
├── one_click_upload.sh
├── github_repository_structure.md
└── upload_to_github.sh
```

## GitHub仓库优化

### 1. 启用GitHub Pages
将docs目录设置为GitHub Pages：
1. Settings → Pages
2. Source: docs/
3. Save

### 2. 启用GitHub Actions
GitHub Actions会自动编译项目：
1. 查看Actions页面
2. 确认build.yml已触发

### 3. 添加Issue模板
仓库已包含Issue模板，用户可以通过模板报告问题。

### 4. 添加徽章（Badges）
在README.md中添加徽章：
```markdown
![Build Status](https://github.com/您的用户名/STM32L496VGT6-Simple-Echo-Demo/workflows/Build%20Project/badge.svg)
![GitHub License](https://img.shields.io/github/license/您的用户名/STM32L496VGT6-Simple-Echo-Demo)
```

### 5. 添加视频演示
如果您录制了演示视频：
1. 上传到YouTube或Bilibili
2. 在README.md中添加链接
3. 在docs目录中添加视频链接文档

## 常见问题解决方法

### 问题1：Git push失败
```bash
# 如果push失败，可能需要配置认证
git config --global credential.helper store

# 或使用SSH密钥
ssh-keygen -t ed25519 -C "您的邮箱"
cat ~/.ssh/id_ed25519.pub
# 将公钥添加到GitHub SSH Keys
```

### 问题2：远程仓库不存在
```bash
# 添加正确的远程仓库
git remote add origin https://github.com/您的用户名/STM32L496VGT6-Simple-Echo-Demo.git
```

### 问题3：文件权限问题
```bash
# 确保文件权限正确
chmod +x one_click_upload.sh
chmod +x upload_to_github.sh
```

### 问题4：GitHub Actions未触发
```bash
# 确保build.yml文件存在
ls .github/workflows/build.yml
```

## 仓库维护指南

### 1. 更新README.md
上传完成后，请更新README.md：
- 替换"您的用户名"为实际的GitHub用户名
- 替换"your@email.com"为联系方式
- 添加实际图片链接

### 2. 添加图片
请添加以下图片到images目录：
- `hardware_setup.png` - 硬件接线图
- `cubemx_config.png` - CubeMX配置截图
- `demo_screenshot.png` - Demo运行截图

### 3. 添加视频
如果您录制了演示视频：
1. 上传到视频平台
2. 在README.md中添加链接
3. 在docs目录中添加说明

## 后续开发建议

### 1. 版本标签
```bash
# 添加版本标签
git tag v1.0.0
git push origin v1.0.0
```

### 2. 分支管理
```bash
# 创建开发分支
git checkout -b develop

# 创建功能分支
git checkout -b feature/add-volume-control
```

### 3. 发布版本
在GitHub创建Release：
1. 点击"Releases"
2. "Create a new release"
3. Tag: v1.0.0
4. Title: STM32L496VGT6简易回声demo v1.0.0
5. Description: 初始版本
6. 上传二进制文件：simple_echo_demo.bin

### 4. 社区贡献
鼓励社区贡献：
1. 添加CONTRIBUTING.md
2. 添加CODE_OF_CONDUCT.md
3. 添加PULL_REQUEST_TEMPLATE.md

## 总结
按照以上步骤，您可以将完整的STM32L496VGT6简易回声demo上传到GitHub：
1. ✅ 创建GitHub仓库
2. ✅ 克隆仓库到本地
3. ✅ 复制项目文件
4. ✅ 提交并推送代码
5. ✅ 验证上传成功
6. ✅ 优化GitHub仓库

完成后，您将拥有一个完整的开源项目，包含：
- 源代码
- CubeMX配置教程
- 硬件接线指南
- 使用说明
- GitHub Actions自动编译
- Issue模板
- MIT许可证

祝您上传成功！