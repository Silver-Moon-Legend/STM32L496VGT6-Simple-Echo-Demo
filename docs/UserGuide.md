# 用户指南

## 项目概述
STM32L496VGT6简易回声demo是一个简单的硬件验证项目，用于测试麦克风采集和喇叭输出功能。

## 硬件准备

### 所需硬件
1. **STM32L496VGT6开发板**
2. **MP34DT01 PDM麦克风**（1个）
3. **4016腔体喇叭**（2个）
4. **MAX98357数字功放**
5. **ST-LINK或JTAG调试器**
6. **USB转串口调试器**
7. **3.3V电源**

### 接线图

#### 麦克风接线：
```
麦克风1:
  CK → PC2 (DFSDM1_CKIN0)
  DATA → PC3 (DFSDM1_DATIN0)
  VDD → 3.3V电源
  GND → GND
```

#### MAX98357功放接线：
```
MAX98357:
  LRCLK → PB12 (I2S3_WS)
  DATA → PB15 (I2S3_SD)
  SCLK → PC10 (I2S3_SCK)
  MCLK → PC12 (I2S3_MCK)
  GND → GND
  VCC → 3.3V
```

#### 喇叭接线：
```
喇叭:
  +端子 → MAX98357 OUT+
  -端子 → MAX98357 OUT-
```

## 软件准备

### 1. 安装STM32CubeMX
1. 访问STM32CubeMX官网：https://www.st.com/en/development-tools/stm32cubemx.html
2. 下载适用于您系统的版本
3. 安装STM32CubeMX
4. 安装STM32Cube_FW_L4软件包

### 2. 安装ARM GCC工具链
```bash
# Linux/Ubuntu
sudo apt-get install gcc-arm-none-eabi

# macOS
brew install arm-none-eabi-gcc

# Windows
下载ARM GCC Windows版本并安装
```

### 3. 安装OpenOCD（用于烧录）
```bash
# Linux/Ubuntu
sudo apt-get install openocd

# macOS
brew install openocd

# Windows
下载OpenOCD Windows版本并安装
```

## 配置步骤

### 方法1：手动配置（使用CubeMX GUI）
1. 打开STM32CubeMX
2. 导入`snore_detection.ioc`配置文件
3. 按照[CubeMX配置教程](../cubemx_config_tutorial.md)进行配置
4. 生成代码

### 方法2：自动配置（使用命令行）
```bash
STM32CubeMX -q cube_headless.txt
```

### 方法3：使用已有配置文件
项目中已包含完整的CubeMX配置文件：
- `snore_detection.ioc` - CubeMX项目文件
- `cube_headless.txt` - CubeMX命令行脚本

## 编译步骤

### 1. 进入项目目录
```bash
cd STM32L496VGT6-Simple-Echo-Demo
```

### 2. 编译程序
```bash
make -f simple_echo_makefile.mk
```

### 3. 生成二进制文件
```bash
make
```

### 4. 查看编译结果
编译成功后，会生成以下文件：
- `simple_echo_demo.bin` - 二进制文件
- `simple_echo_demo.elf` - ELF文件
- `simple_echo_demo.map` - 内存映射文件

## 烧录步骤

### 方法1：使用OpenOCD（推荐）
```bash
openocd -f interface/stlink.cfg -f target/stm32l4x.cfg -c "program simple_echo_demo.bin 0x08000000 verify reset exit"
```

### 方法2：使用ST-LINK Utility
1. 打开ST-LINK Utility
2. 选择`simple_echo_demo.bin`文件
3. 烧录到STM32

### 方法3：使用STM32CubeProgrammer
1. 打开STM32CubeProgrammer
2. 选择STM32L496VGT6芯片
3. 烧录`simple_echo_demo.bin`文件

## 测试步骤

### 1. 连接串口调试器
1. 连接USB转串口调试器
2. 配置串口波特率：115200
3. 打开串口调试工具（如putty、serial）

### 2. 运行程序
烧录完成后，STM32会自动运行程序。

### 3. 查看串口输出
程序会通过串口输出以下信息：
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

### 4. 功能测试
1. **麦克风测试**：对着麦克风讲话或制造声音
2. **喇叭测试**：听到喇叭输出声音
3. **回声测试**：麦克风采集的声音会立即从喇叭输出

## 故障排除

### 常见问题

#### 1. 喇叭没有声音
- 检查MAX98357连接是否正确
- 检查喇叭是否插好
- 检查电源是否稳定
- 检查I2S引脚配置是否正确

#### 2. 麦克风没有声音
- 检查PDM麦克风连接
- 检查DFSDM时钟信号
- 确保麦克风有声音输入
- 检查麦克风电源是否稳定

#### 3. 编译错误
- 检查ARM GCC是否安装
- 检查头文件路径
- 检查Makefile配置
- 检查CubeMX生成的代码是否正确

#### 4. 烧录失败
- 检查ST-LINK连接是否正常
- 检查STM32是否正常工作
- 检查电源是否正常
- 尝试使用其他烧录方法

#### 5. 串口无输出
- 检查串口波特率是否正确（115200）
- 检查串口线是否连接正确
- 检查STM32串口引脚配置是否正确

## 性能优化

### 1. 降低功耗
```c
// 在程序中添加低功耗模式
HAL_PWR_EnableLowPowerMode();
```

### 2. 提高采样率
```c
// 修改DFSDM配置
FOSR: 64 -> 32
IOSR: 4 -> 8
```

### 3. 优化音频质量
```c
// 添加音频滤波
void audio_filter(uint32_t* data, uint32_t size) {
    // 实现简单的音频滤波
}
```

### 4. 添加音量控制
```c
// 添加音量调节函数
void volume_control(uint32_t* data, uint32_t size, float volume) {
    for(int i = 0; i < size; i++) {
        data[i] = data[i] * volume;
    }
}
```

## 扩展功能

### 1. 添加回声延时
```c
void echo_with_delay(uint32_t* mic_data, uint32_t* speaker_data) {
    // 添加回声延时
    uint32_t delay_ms = 100; // 100ms延时
    // 实现延时回声
}
```

### 2. 添加音频处理
```c
void audio_processing(uint32_t* data, uint32_t size) {
    // 添加音频处理算法
    // 如滤波、增益、降噪等
}
```

### 3. 添加LED指示
```c
void led_indicator(uint32_t audio_level) {
    // 根据音频水平控制LED
    if(audio_level > threshold) {
        LED_ON();
    } else {
        LED_OFF();
    }
}
```

### 4. 添加串口控制
```c
void serial_control(void) {
    // 通过串口接收控制命令
    // 如调整音量、设置延时等
}
```

## 最佳实践

### 1. 硬件布局
- 麦克风远离喇叭以减少干扰
- 电源线远离信号线
- 使用屏蔽线连接麦克风

### 2. 软件设计
- 使用DMA传输减少CPU负担
- 使用中断处理实时音频数据
- 添加错误处理机制

### 3. 调试技巧
- 使用串口打印调试信息
- 分段测试（先测试麦克风，再测试喇叭）
- 使用示波器检查信号波形

### 4. 性能监控
- 监控CPU使用率
- 监控内存使用情况
- 监控音频延迟

## 技术支持

### 官方文档
- STM32L496参考手册
- STM32CubeMX用户指南
- ARM GCC工具链文档

### 社区支持
- STM32官方论坛
- GitHub Issue
- Stack Overflow

### 联系方式
- GitHub Issue: https://github.com/yourusername/STM32L496VGT6-Simple-Echo-Demo/issues
- Email: your@email.com

## 更新记录

### v1.0.0
- 初始版本
- 基础回声功能
- CubeMX配置教程

### v1.1.0（计划）
- 回声延时功能
- 音频滤波功能
- LED指示功能
- 串口控制功能

## 许可证
本项目采用MIT许可证，可以自由使用、修改和分发。