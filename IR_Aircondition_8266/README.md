智能空调控制，通过Blinker实现猫精开关空调，设置温度等等
---

### 目前状况
- 能用则行
- 暂停维护
- 准备弃用blinker

![1.png](https://raw.githubusercontent.com/BecodReyes/CJK_IR/master/pic/1.png)

### 已实现的功能:
- 远程开关
- 温度调节
- 风速调节
- 模式调节 [只支持APP]
- 定时任务 [APP自带功能]
- 信号强度显示

### 界面配置： 

```
{¨config¨{¨headerColor¨¨transparent¨¨headerStyle¨¨dark¨¨background¨{¨img¨¨assets/img/headerbg.jpg¨}}¨dashboard¨|{¨type¨¨btn¨¨ico¨¨fad fa-power-off¨¨mode¨Ê¨t0¨¨电源¨¨t1¨¨文本2¨¨bg¨É¨cols¨Ë¨rows¨Ë¨key¨¨POWER¨´x´É´y´Î¨speech¨|{¨cmd¨¨开关电脑¨¨act¨¨tap¨}÷¨lstyle¨Ê¨clr¨¨#076EEF¨}{ß9¨ran¨ßE¨设定温度¨ßT¨#389BEE¨¨max¨¤U¨min¨¤GßIÉßJÑßKËßL¨TEMP¨´x´É´y´ÌßN|÷ßSË}{ß9¨deb¨ßDÉßIÉßJÑßKÌßL¨debug¨´x´É´y´ÒßN|÷}{ß9ßVßE¨风速¨ßTßXßYÌßZÉßIÉßJÑßKËßL¨LEVEL¨´x´É´y´ÊßN|÷ßSË}{ß9ßAßB¨fal fa-power-off¨ßDÊßE¨扫风¨ßGßHßIÉßJËßKËßL¨SWING¨´x´Ë´y´ÎßN|÷ßSÊßTßU}{ß9ßAßB¨fad fa-snowflakes¨ßDÉßE¨制冷¨ßGßHßIÉßJËßKËßL¨COOL¨´x´Ï´y´ÎßN|÷ßSÉßTßU}{ß9ßAßB¨fad fa-humidity¨ßDÉßE¨除湿¨ßGßHßIÉßJËßKËßL¨DRY¨´x´Ë´y´ÐßN|÷ßSÉßTßU}{ß9ßAßB¨fad fa-wind¨ßDÉßE¨送风¨ßGßHßIÉßJËßKËßL¨FAN¨´x´Í´y´ÐßN|÷ßSÉßTßU}{ß9ßAßB¨fad fa-sun¨ßDÉßE¨制热¨ßGßHßIÉßJËßKËßL¨HEAT¨´x´Í´y´ÎßN|÷ßSÉßTßU}{ß9ßAßB¨fad fa-chart-network¨ßDÉßE¨自动¨ßGßHßIÉßJËßKËßL¨AUTO¨´x´É´y´ÐßN|÷ßTßU}{ß9¨num¨ßE¨信号强度¨ßB¨fad fa-signal¨ßTßUßZÉßY¢1c¨uni¨´db´ßIÉßJËßKËßL¨rssi¨´x´Ï´y´ÐßN|÷ßSÉ}÷¨actions¨|¦ßO¦¨switch¨‡¨text¨‡´on´¨打开?name¨¨off¨¨关闭?name¨—÷¨triggers¨|{¨source¨ß13¨source_zh¨¨开关状态¨¨state¨|´on´ß16÷¨state_zh¨|´打开´´关闭´÷}÷}
```

### Todo
- 智障助手支持 - 37%
- 其他空调支持 - 0% `请在issue提出，我会尽量添加支持`
- MQTT - 0%

### 库
- [crankyoldgit/IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266)
- [blinker-iot/blinker-library](https://github.com/blinker-iot/blinker-library)
- [esp8266/Arduino](https://github.com/esp8266/Arduino)

### 代码参考：
- [1812z/Aircondition](https://github.com/1812z/Aircondition/blob/main/Aircondition.ino)
- [blinker-iot/blinker-library](https://github.com/Blinker_Voice_Assistant/Blinker_AliGenie/AliGenie_AIRCONDITION/AliGenie_AIRCONDITION.ino)
