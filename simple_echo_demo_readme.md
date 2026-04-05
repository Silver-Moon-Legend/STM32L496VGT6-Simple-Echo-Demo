# 简易回声demo - 麦克风讲话喇叭输出

## 简介
这是一个简单的STM32L496VGT6程序，用于验证麦克风采集和喇叭输出功能。程序实现麦克风讲话，喇叭实时输出的基本功能。

## 硬件需求
- **STM32L496VGT6开发板**
- **MP34DT01 PDM麦克风（1个）**
- **4016腔体喇叭（2个）**
- **MAX98357 I2S数字功放**
- **ST-LINK或JTAG调试器**

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

## 程序功能

### 1. 麦克风灵敏度测试
- 采集环境声音
- 计算噪声水平
- 验证麦克风连接

### 2. 喇叭输出测试
- 播放1kHz正弦波
- 验证喇叭连接
- 检查音频输出质量

### 3. 回声demo
- 麦克风实时采集声音
- 喇叭实时输出声音
- 简单回声效果

## 编译步骤

### 安装ARM GCC工具链
```bash
sudo apt-get install gcc-arm-none-eabi
```

### 编译程序
```bash
cd stm32l496_snore_detection
make -f simple_echo_makefile.mk
```

### 烧录程序
使用ST-LINK或JTAG调试器烧录 `simple_echo_demo.bin` 文件

## 运行测试

1. 烧录程序后，STM32会自动运行测试
2. 程序会通过串口输出测试结果：
   ```
   STM32L496VGT6 简易回声demo
   
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
   
   demo完成！
   麦克风采集样本数：xxx
   喇叭输出样本数：xxx
   回声效果：成功
   ✅ 测试成功！麦克风和喇叭功能正常
   ```

## GitHub上传指南

### 准备上传的文件
1. **程序文件**：
   - `simple_echo_demo.c` - 主程序
   - `simple_echo_makefile.mk` - Makefile
   - `simple_echo_demo_readme.md` - 使用说明

2. **配置文件**：
   - `snore_detection.ioc` - STM32CubeMX配置文件
   - `cube_headless.txt` - CubeMX自动化脚本

### GitHub仓库创建
```bash
# 创建新仓库
git init
git add simple_echo_demo.c simple_echo_makefile.mk simple_echo_demo_readme.md snore_detection.ioc cube_headless.txt
git commit -m "STM32L496VGT6简易回声demo"
git remote add origin https://github.com/<用户名>/<仓库名>.git
git push -u origin main
```

### GitHub仓库结构
```
STM32-Simple-Echo-Demo/
├── src/
│   ├── simple_echo_demo.c          # 主程序
│   ├── dfsdm_driver.c              # DFSDM驱动
│   ├── i2s_driver.c                # I2S驱动
│   ├── power_manager.c            # 电源管理驱动
│   ├── main.h                      # 头文件
├── config/
│   ├── snore_detection.ioc        # CubeMX配置文件
│   ├── cube_headless.txt          # CubeMX自动化脚本
├── Makefile
├── README.md                       # 使用说明
└── Documentation/
    ├── ConnectionGuide.md         # 接线指南
    ├── UserGuide.md               # 用户指南
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

### 调试方法
1. 使用串口查看程序输出
2. 检查DFSDM时钟频率
3. 检查I2S时钟频率

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

## 许可证
MIT许可证 - 可以自由使用、修改和分发
