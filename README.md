# imx6ull-linux-driver-demo

本仓库用于学习和实践 **NXP i.MX6ULL** 平台上的 **Linux 驱动开发**，  
主要基于 **100ASK（百问网）i.MX6ULL 开发板** 及其配套 Linux 系统。

内容以 **驱动示例（demo）+ 学习记录** 为主，适合嵌入式 Linux 驱动入门与复习。

---

## 开发环境

- **SoC**：NXP i.MX6ULL  
- **开发板**：100ASK i.MX6ULL  
- **Linux 内核版本**：Linux 4.9.88  
- **工具链**：arm-linux-gnueabihf-gcc  
- **开发主机**：Windows / Linux / WSL  
- **调试方式**：串口 / printk / dmesg  

---

## 仓库内容

```text
.
├── drivers/            # Linux 驱动示例代码
│   ├── 01_led/         # LED 字符设备/平台驱动示例
│   ├── 02_gpio/
│   └── ...
│
├── dts/                # 设备树相关文件
│
├── docs/               # 学习笔记、原理总结
│
└── README.md
