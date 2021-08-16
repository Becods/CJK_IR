艾韵智能场景控固件适配
---

## 目前状况
- 能用则行
- 不定期更新

## Patch / 项目
- [IR_Aircondition_8266](https://github.com/BecodReyes/CJK_IR/tree/master/IR_Aircondition_8266): 最初版本，已弃坑
- [ESP8266-HTTP-IR-Blaster.diff](https://github.com/BecodReyes/CJK_IR/tree/master/ESP8266-HTTP-IR-Blaster.diff): 第二版，支持使用HTTP进行控制、学习
- [IRbaby.diff](https://github.com/BecodReyes/CJK_IR/tree/master/IRbaby.diff): 最新版，支持HASS、MQTT、APP、多种空调

## 使用方法
>
> 1. **前往 [Releases](https://github.com/BecodReyes/CJK_IR/releases) 下载并烧录固件**
> 2. **设备上电，移动端搜索连接到 `ESP**` 信号，并在浏览器中输入 192.168.4.1 对设备进行联网设置**
> 3. **下载 `Android` 客户端并运行,对设备进行 MQTT 和红外收发引脚设定。[IRbaby-android](https://github.com/Caffreyfans/IRbaby-android/releases)**
> 4. **匹配电器，完成控制, HomeAssistant 用户可在控制界面导出配置文件（现已支持 HomeAssistant 自动发现功能，设备添加之后，可直接在 HA 集成中看到）**

> **clone项目后patch diff**
> ```
> git clone https://github.com/Caffreyfans/IRbaby-firmware
> cd IRbaby-firmware
> wget https://raw.githubusercontent.com/BecodReyes/CJK_IR/master/IRbaby.diff
> git apply IRbaby.diff
> ```

## 抄板电路
> ***注意!电路图可能不正确***

![Schematic.png](https://raw.githubusercontent.com/BecodReyes/CJK_IR/master/pic/Schematic.png)

## 感谢
- [1812z/Aircondition](https://github.com/1812z/Aircondition)
- [mdhiggins/ESP8266-HTTP-IR-Blaster](https://github.com/mdhiggins/ESP8266-HTTP-IR-Blaster)
- [Caffreyfans/IRbaby](https://github.com/Caffreyfans/IRbaby)
