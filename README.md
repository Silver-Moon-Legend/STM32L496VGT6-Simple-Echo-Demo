# STM32L496VGT6简易回声Demo

## 项目简介
这是一个STM32L496VGT6的简易回声demo，实现麦克风讲话喇叭输出的基本功能。项目包含完整的STM32CubeMX V6.3.0 Windows环境配置教程、硬件接线指南和示例代码。

**重要特性：**
- 完整的Windows环境STM32CubeMX V6.3.0配置教程
- 详细的硬件连接和PCB布局指南
- 一键编译和烧录脚本
- GitHub Actions自动编译测试

![STM32L496VGT6](images/stm32_board.png)

## 功能特点
- **麦克风采集**: 使用MP34DT01 PDM麦克风采集声音
- **喇叭输出**: 使用4016腔体喇叭通过MAX98357功放输出声音
- **实时回声**: 麦克风采集后直接喇叭输出，实现回声效果
- **硬件验证**: 可以验证麦克风和喇叭硬件功能
- **CubeMX教程**: 包含详细的STM32CubeMX配置教程
- **GitHub Action**: 自动编译测试

## 硬件需求
- STM32L496VGT6开发板
- MP34DT01 PDM麦克风（1个）
- 4016腔体喇叭（2个）
- MAX98357 I2S数字功放
- ST-LINK或JTAG调试器
- 3.3V电源

## 接线方法

### 简化接线（只使用1个麦克风）
```
麦克风接线：
  MP34DT01 CK → PC2 (DFSDM1_CKIN0)
  MP34DT01 DATA → PC3 (DFSDM1_DATIN0)
  VDD → 3.3V电源
  GND → GND

喇叭接线：
  4016喇叭1 → MAX98357 OUT+
  4016喇叭2 → MAX98357 OUT-

MAX98357接线：
  LRCLK → PB12 (I2S3_WS)
  DATA → PB15 (I2S3_SD)
  SCLK → PC10 (I2S3_SCK)
  MCLK → PC12 (I2S3_MCK)
  GND → GND
  VCC → 3.3V
```

详细接线图请查看[接线指南](docs/ConnectionGuide.md)

## 使用方法

### 1. STM32CubeMX配置
详细配置教程请查看[CubeMX配置教程](docs/cubemx_config_tutorial.md)

### 2. 编译程序
```bash
# 安装ARM GCC工具链
sudo apt-get install gcc-arm-none-eabi

# 编译程序
make -f simple_echo_makefile.mk
```

### 3. 烧录到STM32
```bash
# 使用ST-LINK烧录
make flash

# 或使用OpenOCD
openocd -f interface/stlink.cfg -f target/stm32l4x.cfg -c "program simple_echo_demo.bin 0x08000000 verify reset exit"
```

### 4. 运行程序
1. 连接麦克风和喇叭
2. 对着麦克风讲话
3. 喇叭会实时输出声音
4. 查看串口输出结果

## 程序功能

### 测试流程
1. **麦克风灵敏度测试** - 检测麦克风是否能采集声音
2. **喇叭输出测试** - 播放1kHz正弦波测试喇叭
3. **实时回声功能** - 麦克风采集的声音立即输出到喇叭

### 串口输出示例
```
STM32L496VGT6 简易回声demo
=====================================================

步骤1：测试麦克风灵敏度
环境噪声水平：xxx
✅ 麦克风可以检测到环境声音

步骤2：测试喇叭输出
✅ 喇叭可以输出声音
播放了1kHz测试音频

步骤3：运行完整回声demo
开始麦克风回声demo...
开始回声演示...
对着麦克风讲话，喇叭会实时输出
```

## 文件结构
```
STM32L496VGT6-Simple-Echo-Demo/
├── README.md                    # 项目主README
├── LICENSE                      # MIT许可证
├── .gitignore                   # Git忽略文件
├── src/
│   ├── simple_echo_demo.c      # 主程序代码
│   ├── dfsdm_driver.c          # DFSDM驱动
│   ├── dfsdm_driver.h          # DFSDM头文件
│   ├── i2s_driver.c            # I2S驱动
│   ├── i2s_driver.h            # I2S头文件
│   ├── power_manager.c         # 电源管理驱动
│   ├── power_manager.h         # 电源管理头文件
│   ├── main.c                   # CubeMX生成的主文件
│   ├── main.h                   # CubeMX生成的头文件
├── config/
│   ├── snore_detection.ioc     # CubeMX配置文件
│   ├── cube_headless.txt       # CubeMX自动化脚本
├── docs/
│   ├── cubemx_config_tutorial.md     # 详细CubeMX配置教程
│   ├── cubemx_quick_config.md        # 快速配置指南
│   ├── cubemx_video_script.md        # 视频教程脚本
│   ├── ConnectionGuide.md             # 硬件接线指南
│   ├── UserGuide.md                  # 用户指南
├── images/
│   ├── hardware_setup.png            # 硬件接线图（示例）
│   ├── cubemx_config.png             # CubeMX配置截图（示例）
│   ├── demo_screenshot.png           # Demo运行截图（示例）
├── examples/
│   ├── simple_echo_makefile.mk       # Makefile编译脚本
│   ├── simple_echo_demo_readme.md    # Demo使用说明
```

## 文档教程

### CubeMX配置教程
包含三种形式的教程：
1. **[详细教程](docs/cubemx_config_tutorial.md)** - 完整配置流程
2. **[快速指南](docs/cubemx_quick_config.md)** - 10分钟快速配置
3. **[视频脚本](docs/cubemx_video_script.md)** - 录制教学视频脚本

### 硬件接线指南
详细接线方法和PCB布局建议：[接线指南](docs/ConnectionGuide.md)

## 编译步骤
```bash
# 下载项目
git clone https://github.com/yourusername/STM32L496VGT6-Simple-Echo-Demo.git

# 进入项目目录
cd STM32L496VGT6-Simple-Echo-Demo

# 安装ARM GCC工具链
sudo apt-get install gcc-arm-none-eabi

# 编译程序
make -f examples/simple_echo_makefile.mk

# 生成二进制文件
make
```

## 故障排除

### 常见问题
1. **喇叭没有声音**
   - 检查MAX98357连接是否正确
   - 检查喇叭是否插好
   - 检查电源是否稳定

2. **麦克风没有声音**
   - 检查PDM麦克风连接
   - 检查DFSDM时钟信号
   - 确保麦克风有声音输入

3. **编译错误**
   - 检查ARM GCC是否安装
   - 检查头文件路径
   - 检查Makefile配置

4. **CubeMX配置错误**
   - 检查STM32L4软件包是否安装
   - 检查时钟配置是否正确
   - 检查引脚配置是否有冲突

### 调试方法
1. 使用串口查看程序输出
2. 检查DFSDM时钟频率
3. 检查I2S时钟频率
4. 检查电源电压

## 扩展功能
如果想要扩展这个demo，可以：
1. **添加音量调节** - 添加PWM控制音量
2. **添加回声延时** - 实现延时回声效果
3. **添加音频处理** - 添加简单滤波或增益
4. **添加LED指示** - 用LED显示音频活动

## 视频演示建议
拍摄demo视频时：
1. **硬件展示** - 展示STM32、麦克风、喇叭连接
2. **功能演示** - 对着麦克风讲话，喇叭播放声音
3. **测试输出** - 展示串口输出结果
4. **GitHub链接** - 展示仓库和代码

## Windows环境STM32CubeMX V6.3.0配置教程
本项目包含详细的STM32CubeMX V6.3.0 Windows环境配置教程，包括：

### 详细教程内容
1. **CubeMX安装** - 安装STM32CubeMX V6.3.0
2. **STM32Cube_FW_L4软件包** - 下载和安装
3. **引脚配置** - 完整的引脚映射配置
4. **DFSDM参数配置** - 麦克风音频采集参数
5. **SAI参数配置** - 喇叭输出参数
6. **时钟配置** - 系统时钟和音频时钟
7. **DMA配置** - DMA数据传输配置
8. **NVIC配置** - 中断配置
9. **生成代码** - 生成完整的项目代码

### Windows环境注意事项
- Java环境要求：Java 8或更高版本
- 环境变量配置：ARM GCC路径和CubeMX路径
- 权限问题：可能需要管理员权限
- 中文界面支持：CubeMX V6.3.0支持中文界面

查看[Windows配置教程](README_Windows.md)获取完整信息。

## 许可证
MIT许可证 - 可以自由使用、修改和分发

## 联系
如有问题请联系：your@email.com

## 贡献
欢迎提交问题和改进建议！

## GitHub Actions
该项目包含GitHub Actions配置，可以在云端自动编译测试代码。查看[GitHub Actions](.github/workflows/build.yml)了解更多。