# 移植过程

## 1. 硬件方案：

采用的是UP主[神秘藏宝室 (bilibili.com)](https://space.bilibili.com/250687146)在淘宝出售的硬件(~~手残党~~)

- STM32L051K8U6   
  - 墨水屏显示
  - 驱动ST25DV
- ST25DV16K-IER6S3
  - 能量采集
  - 与手机app进行通信
- TP4056
  - 锂电池充电
- 中景园的1.54英寸墨水屏
- CH340C
  - uart转usb

## 2. 软件方案：

方案来源：稚晖君

代码移植的源：

- ST官方提供的驱动ST25dv的代码
- 中景园提供的墨水屏驱动代码
- 稚晖君开源的安卓APP

## 3.开发过程中遇到的问题：

### 3.1 ST官方代码找不到

一般都在产品的资源里，这里以ST25dv为例子，展示如何寻找软件资源：

==1.搜索ST25Dv==

![屏幕截图 2024-09-27 100847](.\picture\屏幕截图 2024-09-27 100847.png)

==2.选择我们要用的芯片==

![屏幕截图 2024-09-27 101040](.\picture\屏幕截图 2024-09-27 101040.png)

==3.点击tool&software==

![屏幕截图 2024-09-27 101201](.\picture\屏幕截图 2024-09-27 101201.png)

==4.点击**MCU and MPU embedded software**==

![屏幕截图 2024-09-27 101412](.\picture\屏幕截图 2024-09-27 101412.png)

**5.下载**

>
>
>这个库可以内置到stm32cubemx一起使用（直接生成代码）

---

### 3.2 墨水屏显示异常(乱码)

==稚晖君的驱动代码和中景园提供的驱动代码都可驱动各自型号的墨水屏，但是由于我们的硬件是中景园的墨水屏，所以显而易见，我们应该采用中景园的驱动代码。==

但是这里会出现一个问题：==如果要用稚晖君的app进行图片的传输，会出现乱码== 

**本质原因**：对信息的编码或者解码方式不一样，我们只需要将中景园代码对图片的解码方式更改为与稚晖君的解码方式一致即可 

经过验证，我们只需要修改：

```c
OLED_GUIInit();
```

```c
OLED_WR_REG(0x01); //Driver output control      
OLED_WR_DATA8(0xC7);
OLED_WR_DATA8(0x00);
OLED_WR_DATA8(0x00);   //修改 将0x01更改为0x00即可
```

