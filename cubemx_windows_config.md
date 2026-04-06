# STM32CubeMX V6.3.0 Windows环境配置指南

## 环境准备

### 1. 安装STM32CubeMX
1. 访问ST官网：https://www.st.com/en/development-tools/stm32cubemx.html
2. 下载STM32CubeMX V6.3.0 Windows版本
3. 安装STM32CubeMX
4. 安装STM32Cube_FW_L4软件包

### 2. 安装ARM GCC工具链
推荐使用STM32CubeIDE或单独安装ARM GCC：
- STM32CubeIDE自带ARM GCC
- 或下载ARM GCC：https://developer.arm.com/downloads/-/gnu-rm

### 3. 安装调试工具
- ST-LINK驱动程序
- OpenOCD或STM32CubeProgrammer

## STM32CubeMX配置步骤

### 第1步：打开STM32CubeMX
1. 启动STM32CubeMX
2. 点击 "New Project"
3. 选择芯片型号：STM32L496VGT6

![CubeMX界面](images/cubemx_main.png)

### 第2步：芯片选择
1. 在搜索框输入 "STM32L496VGT6"
2. 选择芯片型号
3. 选择封装 "LQFP100"
4. 点击 "Start Project"

![芯片选择](images/chip_selection.png)

### 第3步：引脚配置

#### DFSDM配置
1. 在 "Pinout & Configuration" 左侧面板找到 "Digital Filter"
2. 点击 "DFSDM1"
3. 配置DFSMD通道：

![DFSDM配置](images/dfsdm_config.png)

##### 引脚配置：
- PE9 → DFSDM1_CKOUT
- PB1 → DFSDM1_DATIN0

##### Filter配置：
- Filter0 → DFSDM1_Filter0
- Channel0 → DFSDM1_Channel0

##### 参数配置：
- Sinc Order: Sinc5
- FOSR: 25
- IOSR: 1
- DMA Mode: Enabled
- Trigger: Software Trigger

#### SAI配置
1. 在左侧面板找到 "Audio"
2. 点击 "SAI1"
3. 配置SAI Block A：

![SAI配置](images/sai_config.png)

##### 引脚配置：
- PE4 → SAI1_FS_A
- PE5 → SAI1_SCK_A
- PE6 → SAI1_SD_A

##### SAI参数：
- Operating Mode: Master
- Protocol: I2S Philips Standard
- Data Size: 24 bits
- Master Clock Output: Enabled
- Audio Frequency: 48 kHz
- Frame Length: 64
- Slot Size: 16 bits
- Slot Number: 2

### 第4步：时钟配置
1. 点击 "Clock Configuration"
2. 设置系统时钟为80MHz

![时钟配置](images/clock_config.png)

##### PLL配置：
- PLL Source: HSI
- PLLM: 1
- PLLN: 20
- PLLP: 7
- PLLQ: 2
- PLLR: 2
- System Clock: 80MHz

### 第5步：DMA配置
1. 点击 "DMA"
2. 配置DFSMD DMA：

![DMA配置](images/dma_config.png)

##### DFSMD DMA：
- DFSDM1_FLT0 → DMA2_Channel1
- Direction: Peripheral to Memory
- Priority: High

##### SAI DMA：
- SAI1_A → DMA1_Channel1
- Direction: Memory to Peripheral
- Priority: Medium

### 第6步：NVIC配置
1. 点击 "NVIC"
2. 启用以下中断：

![NVIC配置](images/nvic_config.png)

##### 中断列表：
- DFSDM1_IRQn: Enabled, Priority 0
- DMA1_Channel1_IRQn: Enabled, Priority 0
- DMA2_Channel1_IRQn: Enabled, Priority 0

### 第7步：电源配置
1. 点击 "Power"
2. 配置电源：

![电源配置](images/power_config.png)

##### 电源参数：
- Voltage Regulator: Scale3
- Overdrive: Enabled
- System Power Mode: Run

### 第8步：生成代码
1. 点击 "Project Manager"
2. 配置项目信息：

![项目配置](images/project_manager.png)

##### 项目设置：
- Project Name: STM32_Simple_Echo_Demo
- Project Location: 选择您的项目目录
- Toolchain/IDE: Makefile
- Application Structure: Advanced

##### Code Generator：
- Generate peripheral initialization as a pair of .c/.h files per peripheral
- Backup previously generated files when re-generating
- Keep user code when re-generating

3. 点击 "Generate Code"

![生成代码](images/generate_code.png)

## 使用命令行配置

如果您想使用命令行自动配置，使用我提供的配置文件：

### 1. 准备配置文件
```bash
# 使用我提供的cube_headless_real.txt文件
STM32CubeMX -q cube_headless_real.txt
```

### 2. 命令行配置参数
```
Mcu.UserName=STM32L496VGT6
Mcu.Family=STM32L4
Mcu.Package=LQFP100
Mcu.Cpu=Cortex-M4
ProjectManager.ProjectName=STM32_Simple_Echo_Demo
ProjectManager.OutputDirectory=.
ProjectManager.ToolChainFolder=Makefile
ProjectManager.ToolChain=Makefile
ProjectManager.UnderRoot=true
ProjectManager.MainLocation=Core/Src/main.c
ProjectManager.SrcLocation=Core/Src
ProjectManager.IncLocation=Core/Inc
ProjectManager.LinkerScript=STM32L496VGTx_FLASH.ld
ProjectManager.CpuClock=80
```

## 编译步骤

### 第1步：创建Makefile
CubeMX会自动生成Makefile。确保Makefile包含以下源文件：
```makefile
SRC_FILES = simple_echo_demo_real.c \
            dfsdm_driver.c \
            sai_driver.c \
            power_manager.c
```

### 第2步：安装ARM GCC
```bash
# 如果您使用STM32CubeIDE，ARM GCC已经包含
# 如果您单独安装ARM GCC：
# 下载ARM GCC Toolchain
# 添加到系统PATH
```

### 第3步：编译项目
```bash
# 进入项目目录
cd STM32_Simple_Echo_Demo

# 编译
make

# 生成二进制文件
make all
```

## 常见问题解决

### 问题1：CubeMX无法生成项目
解决方案：
1. 检查STM32Cube_FW_L4软件包是否安装
2. 检查Java是否安装（CubeMX需要Java）
3. 尝试以管理员权限运行CubeMX

### 问题2：编译错误
解决方案：
1. 检查ARM GCC是否安装
2. 检查Makefile配置是否正确
3. 检查头文件路径是否正确

### 问题3：烧录失败
解决方案：
1. 检查ST-LINK连接
2. 检查STM32CubeProgrammer配置
3. 检查芯片是否供电

## 配置截图位置

建议保存以下截图：
1. 芯片选择截图
2. 引脚配置截图
3. 时钟配置截图
4. SAI配置截图
5. DFSDM配置截图
6. DMA配置截图
7. NVIC配置截图
8. 生成代码截图

## Windows环境注意事项

### Java环境
STM32CubeMX需要Java运行环境：
- Java版本：Java 8或更高
- Java安装路径添加到PATH

### 环境变量
```
ARM_GCC_PATH=C:\Program Files (x86)\Arm GNU Toolchain\arm-none-eabi
STM32CUBEMX_PATH=C:\Program Files\STMicroelectronics\STM32CubeMX
```

### 权限问题
Windows环境下可能需要管理员权限才能安装STM32Cube_FW_L4软件包。

## 自动化脚本

您可以创建自动化脚本：
```bash
@echo off
REM Windows环境STM32CubeMX配置脚本
set CUBEMX_PATH=C:\Program Files\STMicroelectronics\STM32CubeMX
set PROJECT_PATH=C:\STM32_Simple_Echo_Demo

REM 使用CubeMX命令行配置
%CUBEMX_PATH%\STM32CubeMX.exe -q cube_headless_real.txt -o %PROJECT_PATH%

REM 编译
make -f Makefile
```

## 总结

STM32CubeMX V6.3.0在Windows环境下的配置流程：
1. 安装STM32CubeMX和软件包
2. 创建新项目
3. 配置引脚（DFSDM和SAI）
4. 配置时钟
5. 配置DMA
6. 配置NVIC
7. 配置电源
8. 生成代码
9. 编译项目
10. 烧录到STM32

使用我提供的配置文件可以自动化这个过程，减少配置错误。