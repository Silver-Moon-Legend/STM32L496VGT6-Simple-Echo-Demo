# STM32CubeMX配置教程 - 麦克风喇叭回声demo

## 1. STM32CubeMX安装

### 1.1 下载STM32CubeMX
1. 访问官网：https://www.st.com/en/development-tools/stm32cubemx.html
2. 选择适用于您系统的版本（Windows、Linux或macOS）
3. 下载并安装STM32CubeMX

### 1.2 安装STM32L4软件包
打开STM32CubeMX后：
1. 点击菜单栏的 "Help" → "Install Software Packs"
2. 搜索 "STM32Cube_FW_L4"
3. 安装最新的STM32L4软件包
4. 等待下载和安装完成

## 2. 创建新项目

### 2.1 选择芯片型号
1. 点击 "New Project"
2. 在搜索框中输入 "STM32L496VGT6"
3. 双击 "STM32L496VGT6" 芯片
4. 选择封装类型 "LQFP100"
5. 点击 "Start Project"

### 2.2 时钟配置

#### 时钟树配置：
1. **RCC配置**：
   - High Speed Clock (HSE): Disabled
   - Low Speed Clock (LSE): Disabled
   - Clock Configuration: System Clock Source: HSI

2. **PLL配置**：
   - PLL Source: HSI
   - PLLM: 1
   - PLLN: 20
   - PLLP: 7
   - PLLQ: 2
   - PLLR: 2

3. **时钟频率**：
   - System Clock (MHz): 80
   - HCLK (MHz): 80
   - APB1 Clock (MHz): 80
   - APB2 Clock (MHz): 80

![时钟配置](https://raw.githubusercontent.com/stm32demo/cubemx_config_tutorial/images/clock_config.png)

## 3. DFSDM配置（PDM麦克风）

### 3.1 DFSDM滤波器配置

#### DFSDM Filter 0：
1. 在左侧 "Pinout & Configuration" 面板中找到 "DFSDM"
2. 展开 "DFSDM1"
3. 找到 "Filter0"
4. 配置以下参数：
   - Clock Source: System Clock
   - Serial Interface Type: SPI Falling Edge
   - Sinc Order: Sinc5
   - FOSR: 64
   - IOSR: 4
   - Fast Mode: Disabled
   - DMA Mode: Enabled
   - Trigger: Software Trigger

#### DFSDM Filter 1-3：
重复以上步骤，配置 Filter1、Filter2、Filter3，参数相同。

### 3.2 DFSDM引脚配置

#### 通道0（麦克风1）：
1. 找到引脚 PC2
2. 右键点击 PC2 → "Set as DFSDM1_CKIN0"
3. 找到引脚 PC3
4. 右键点击 PC3 → "Set as DFSDM1_DATIN0"

#### 通道1（麦克风2）：
1. 找到引脚 PE9
2. 右键点击 PE9 → "Set as DFSDM1_CKIN1"
3. 找到引脚 PE10
4. 右键点击 PE10 → "Set as DFSDM1_DATIN1"

#### 其他通道（可选）：
如果需要更多麦克风，可以配置：
- 通道2: PD12 → DFSDM1_CKIN2, PD13 → DFSDM1_DATIN2
- 通道3: PB1 → DFSDM1_CKIN3, PB2 → DFSDM1_DATIN3

![DFSDM配置](https://raw.githubusercontent.com/stm32demo/cubemx_config_tutorial/images/dfsdm_config.png)

## 4. I2S配置（MAX98357功放）

### 4.1 I2S外设配置
1. 在左侧面板中找到 "I2S"
2. 找到 "I2S3"
3. 点击选中 I2S3
4. 配置以下参数：
   - Mode: Master Transmit
   - Standard: I2S Philips Standard
   - Data Format: 24 Bits
   - Master Clock Output: Enabled
   - Audio Frequency: 48 kHz
   - Clock Source: PLL
   - DMA Mode: Enabled

### 4.2 I2S引脚配置
1. **LRCLK**: PB12 → I2S3_WS
2. **DATA**: PB15 → I2S3_SD
3. **SCLK**: PC10 → I2S3_SCK
4. **MCLK**: PC12 → I2S3_MCK

配置步骤：
1. 找到引脚 PB12
2. 右键点击 PB12 → "Set as I2S3_WS"
3. 重复以上步骤，配置 PB15, PC10, PC12

![I2S配置](https://raw.githubusercontent.com/stm32demo/cubemx_config_tutorial/images/i2s_config.png)

## 5. DMA配置

### 5.1 DFSDM DMA配置
1. 在左侧面板中找到 "DMA"
2. 找到 "DMA2"
3. 添加 DMA 通道：

| 外设 | DMA通道 | 方向 | 优先级 |
|------|---------|------|--------|
| DFSDM1_FLT0 | DMA2_Channel1 | Peripheral to Memory | High |
| DFSDM1_FLT1 | DMA2_Channel2 | Peripheral to Memory | High |
| DFSDM1_FLT2 | DMA2_Channel3 | Peripheral to Memory | High |
| DFSDM1_FLT3 | DMA2_Channel4 | Peripheral to Memory | High |

配置方法：
1. 点击 "DMA2_Channel1"
2. 选择 "Request" 为 "DFSDM1_FLT0"
3. 设置 "Direction" 为 "Peripheral to Memory"
4. 设置 "Priority" 为 "High"

### 5.2 I2S DMA配置
1. 找到 "DMA1"
2. 添加 DMA 通道：

| 外设 | DMA通道 | 方向 | 优先级 |
|------|---------|------|--------|
| I2S3_TX | DMA1_Channel4 | Memory to Peripheral | Medium |
| I2S3_RX | DMA1_Channel5 | Peripheral to Memory | Medium |

![DMA配置](https://raw.githubusercontent.com/stm32demo/cubemx_config_tutorial/images/dma_config.png)

## 6. NVIC配置（中断）

### 6.1 中断优先级配置
在 "NVIC" 面板中配置以下中断：

| 中断 | 优先级 | 设置 |
|------|--------|------|
| DFSDM1_IRQn | 0 | Enabled |
| DMA1_Channel4_IRQn | 0 | Enabled |
| DMA1_Channel5_IRQn | 0 | Enabled |
| DMA2_Channel1_IRQn | 0 | Enabled |
| DMA2_Channel2_IRQn | 0 | Enabled |
| DMA2_Channel3_IRQn | 0 | Enabled |
| DMA2_Channel4_IRQn | 0 | Enabled |

配置方法：
1. 找到 "DFSDM1_IRQn"
2. 勾选复选框启用中断
3. 设置 Priority 为 0 (最高优先级)
4. 重复以上步骤配置其他中断

![NVIC配置](https://raw.githubusercontent.com/stm32demo/cubemx_config_tutorial/images/nvic_config.png)

## 7. 电源配置

### 7.1 电压调节器
在 "PWR" 面板中配置：
- Voltage Regulator: Scale3
- Overdrive: Enabled

### 7.2 时钟源
确保 "System Power Mode" 为 "Run mode"

## 8. 生成代码

### 8.1 Project Manager 配置
1. 点击 "Project Manager"
2. 配置项目信息：
   - Project Name: Simple_Echo_Demo
   - Project Location: 选择您的工作目录
   - Toolchain/IDE: Makefile
   - Application Structure: Advanced

### 8.2 Code Generator 配置
1. 点击 "Code Generator"
2. 勾选以下选项：
   - Generate peripheral initialization as a pair of .c/.h files per peripheral
   - Backup previously generated files when re-generating
   - Keep user code when re-generating

### 8.3 生成代码
1. 点击右上角的 "Generate Code"
2. CubeMX会生成所有代码和Makefile
3. 等待生成完成

![代码生成](https://raw.githubusercontent.com/stm32demo/cubemx_config_tutorial/images/code_generation.png)

## 9. 命令行方式配置

如果您想使用命令行生成项目，可以使用我提供的自动化脚本：

### 9.1 准备工作
1. 下载配置文件：`snore_detection.ioc`
2. 下载脚本：`cube_headless.txt`

### 9.2 运行命令
```bash
# 确保CubeMX已安装
STM32CubeMX -q cube_headless.txt
```

### 9.3 cube_headless.txt内容
```
Mcu.UserName=STM32L496VGT6
Mcu.Family=STM32L4
Mcu.Package=LQFP100
Mcu.Cpu=Cortex-M4
ProjectManager.ProjectName=Simple_Echo_Demo
ProjectManager.OutputDirectory=.
ProjectManager.ToolChainFolder=Makefile
ProjectManager.ToolChain=Makefile
ProjectManager.UnderRoot=true
ProjectManager.MainLocation=Core/Src/main.c
ProjectManager.SrcLocation=Core/Src
ProjectManager.IncLocation=Core/Inc
ProjectManager.LinkerScript=STM32L496VGTx_FLASH.ld
ProjectManager.CpuClock=80

# 配置DFSDM
PC2.Signal=DFSDM1_CKIN0
PC3.Signal=DFSDM1_DATIN0
PE9.Signal=DFSDM1_CKIN1
PE10.Signal=DFSDM1_DATIN1

# 配置I2S
PB12.Signal=I2S3_WS
PB15.Signal=I2S3_SD
PC10.Signal=I2S3_CK
PC12.Signal=I2S3_MCK

# DFSDM Filter配置
DFSDM1_Filter0.FilterParam-0=Sinc5
DFSDM1_Filter0.FilterParam-1=FOSR=64
DFSDM1_Filter0.FilterParam-2=IOSR=4
DFSDM1_Filter0.FilterParam-3=DmaModeEnabled=1
DFSDM1_Filter0.FilterParam-4=TriggerMode=Software

# I2S配置
I2S3.Mode=Master
I2S3.Standard=I2S Philips
I2S3.DataFormat=24b
I2S3.MCLKOutput=Enabled
I2S3.AudioFrequency=48000

# 生成代码
ProjectManager.functionlistsort=SystemClockConfig,N-MX_PWR_Init-PWR-false-HAL-true,N-MX_DFSDM1_Init-DFSDM1-false-HAL-true,N-MX_I2S3_Init-I2S3-false-HAL-true,N-MX_DMA_Init-DMA-false-HAL-true,N-MX_NVIC_Init-NVIC-false-HAL-true
```

## 10. 验证配置

### 10.1 配置完成后检查
确保以下配置正确：
1. **时钟**: 80MHz
2. **DFSDM**: 至少配置2个通道
3. **I2S**: 配置完整
4. **DMA**: 6个DMA通道正确配置
5. **NVIC**: 中断优先级正确设置

### 10.2 验证引脚
在 "Pinout" 视图中检查引脚配置：
- PC2: DFSDM1_CKIN0
- PC3: DFSDM1_DATIN0
- PB12: I2S3_WS
- PB15: I2S3_SD
- PC10: I2S3_SCK
- PC12: I2S3_MCK

![引脚验证](https://raw.githubusercontent.com/stm32demo/cubemx_config_tutorial/images/pinout_check.png)

## 11. 常见问题解决

### 11.1 CubeMX无法打开.ioc文件
解决方案：
1. 手动创建新项目，按照上述步骤配置
2. 使用命令行方式：`STM32CubeMX -q cube_headless.txt`
3. 检查CubeMX版本，建议使用最新版本

### 11.2 DMA配置失败
解决方案：
1. 确保DMA通道没有被其他外设占用
2. 调整DMA通道分配
3. 检查优先级设置

### 11.3 时钟配置错误
解决方案：
1. 检查HSI时钟源是否正确启用
2. 检查PLL配置是否正确
3. 检查时钟树中是否存在红色错误提示

### 11.4 生成代码时出现警告
解决方案：
1. 检查是否缺少必要的软件包
2. 更新STM32CubeMX到最新版本
3. 重新安装STM32Cube_FW_L4软件包

## 12. 配置完成后的下一步

### 12.1 添加驱动程序
1. 在CubeMX生成的代码中添加我们的驱动文件
2. 复制 `dfsdm_driver.c/h`, `i2s_driver.c/h`, `power_manager.c/h`
3. 更新Makefile包含这些文件

### 12.2 编译测试
```bash
# 安装ARM GCC工具链
sudo apt-get install gcc-arm-none-eabi

# 编译程序
make

# 烧录到STM32
make flash
```

### 12.3 运行测试
1. 烧录程序后运行
2. 使用串口查看测试结果
3. 检查喇叭是否有声音输出
4. 检查麦克风是否能采集声音

## 13. 总结

本教程涵盖了STM32CubeMX配置的所有关键步骤：
1. **时钟配置** - 80MHz系统时钟
2. **DFSDM配置** - PDM麦克风采集
3. **I2S配置** - MAX98357功放输出
4. **DMA配置** - 数据传输优化
5. **NVIC配置** - 中断优先级设置
6. **引脚配置** - 硬件连接映射

完成这些配置后，您将得到一个完整的STM32L496VGT6项目，可以运行麦克风讲话喇叭输出的demo。

## 14. 参考资源

### 官方文档：
- STM32CubeMX官方文档：https://www.st.com/resource/en/user_manual/dm00104712.pdf
- STM32L4参考手册：https://www.st.com/resource/en/reference_manual/dm00171116.pdf

### 示例代码：
- DFSDM示例：https://github.com/STMicroelectronics/STM32CubeL4/blob/master/Projects/STM32L496VGT6_Discovery/Examples/DFSDM/DFSDM_Example.md
- I2S示例：https://github.com/STMicroelectronics/STM32CubeL4/blob/master/Projects/STM32L496VGT6_Discovery/Examples/I2S/I2S_Example.md

### 社区支持：
- STM32社区论坛：https://community.st.com/s/topic/0TO0X0000001qUaW/stm32cube-mx
- GitHub项目：https://github.com/STMicroelectronics/STM32CubeL4