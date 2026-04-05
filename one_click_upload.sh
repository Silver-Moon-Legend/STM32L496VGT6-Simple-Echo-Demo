#!/bin/bash
# GitHub一键上传脚本

echo "STM32L496VGT6简易回声demo一键上传到GitHub"
echo "====================================================="

echo "步骤1：检查当前目录结构"
ls -la

echo ""
echo "步骤2：确保上传目录结构正确"
if [ ! -d "upload_simple_echo" ]; then
    echo "上传目录不存在，请先运行 upload_to_github.sh"
    exit 1
fi

echo ""
echo "步骤3：检查上传目录内容"
ls -la upload_simple_echo/

echo ""
echo "步骤4：GitHub仓库创建说明"
echo "请在GitHub上创建仓库：STM32L496VGT6-Simple-Echo-Demo"
echo "仓库描述：STM32L496VGT6麦克风喇叭回声demo"
echo "仓库类型：Public"
echo ""
echo "创建完成后，使用以下命令克隆仓库："
echo "git clone https://github.com/yourusername/STM32L496VGT6-Simple-Echo-Demo.git"

echo ""
echo "步骤5：上传命令"
echo "假设您已经克隆了仓库，可以使用以下命令上传："
echo ""
echo "cd STM32L496VGT6-Simple-Echo-Demo"
echo "cp -r upload_simple_echo/* ."
echo "git add ."
echo "git commit -m 'STM32L496VGT6简易回声demo'"
echo "git push origin main"

echo ""
echo "步骤6：GitHub仓库设置"
echo ""
echo "1. 启用GitHub Pages："
echo "   Settings → Pages → Source: docs/"
echo ""
echo "2. 添加GitHub Actions："
echo "   .github/workflows/build.yml"
echo ""
echo "3. 添加Issue模板："
echo "   .github/ISSUE_TEMPLATE/"
echo ""
echo "4. 添加Pull Request模板："
echo "   .github/PULL_REQUEST_TEMPLATE.md"

echo ""
echo "步骤7：添加示例图片"
echo "如果您有硬件接线图，请添加到 images/ 目录："
echo "upload_simple_echo/images/hardware_setup.png"
echo "upload_simple_echo/images/cubemx_config.png"
echo "upload_simple_echo/images/demo_screenshot.png"

echo ""
echo "步骤8：创建GitHub Actions配置文件"
cat > upload_simple_echo/.github/workflows/build.yml << 'EOF'
name: Build Project

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Install ARM GCC
        run: sudo apt-get install gcc-arm-none-eabi
      - name: Build project
        run: make -f simple_echo_makefile.mk
EOF

echo ""
echo "步骤9：创建Issue模板"
mkdir -p upload_simple_echo/.github/ISSUE_TEMPLATE
cat > upload_simple_echo/.github/ISSUE_TEMPLATE/config.yml << 'EOF'
blank_issues_enabled: false
contact_links:
  - name: Documentation
    url: https://github.com/yourusername/STM32L496VGT6-Simple-Echo-Demo/docs
    about: Please check the documentation before asking
EOF

cat > upload_simple_echo/.github/ISSUE_TEMPLATE/issue.md << 'EOF'
---
name: Issue Report
about: Report an issue with the project
title: ''
labels: ''
assignees: ''

---

## 硬件问题
- [ ] 麦克风不工作
- [ ] 喇叭不出声
- [ ] CubeMX配置问题
- [ ] 接线问题

## 软件问题
- [ ] 编译错误
- [ ] 烧录错误
- [ ] 运行错误
- [ ] CubeMX配置错误

## 环境信息
- 操作系统: 
- STM32CubeMX版本: 
- ARM GCC版本: 
- ST-LINK版本: 

## 错误信息
如果有错误信息，请粘贴：

## 预期行为
描述您期望的行为：

## 实际行为
描述实际发生的行为：

## 额外信息
任何其他相关信息：
EOF

echo ""
echo "步骤10：完成上传准备"
echo "上传目录已包含所有文件："
echo "✅ 源代码"
echo "✅ CubeMX配置文件"
echo "✅ CubeMX教程"
echo "✅ GitHub Actions配置"
echo "✅ Issue模板"
echo "✅ README和LICENSE"
echo "✅ 硬件接线指南"
echo ""
echo "您现在可以将这些文件上传到GitHub仓库。"

echo ""
echo "步骤11：上传成功后"
echo ""
echo "请在README.md中更新："
echo "1. 替换yourusername为您实际的GitHub用户名"
echo "2. 替换your@email.com为您的联系方式"
echo "3. 添加图片链接"
echo "4. 添加视频演示链接"

echo ""
echo "步骤12：添加badges（可选）"
echo ""
echo "可以在README.md中添加："
echo "![Build Status](https://github.com/yourusername/STM32L496VGT6-Simple-Echo-Demo/workflows/Build%20Project/badge.svg)"
echo "![GitHub License](https://img.shields.io/github/license/yourusername/STM32L496VGT6-Simple-Echo-Demo)"

echo ""
echo "一键上传完成！"
echo "====================================================="