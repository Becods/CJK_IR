智能空调控制，通过最新的Blinker实现猫精开关空调，设置温度等等
---
### 已实现的功能:
- 风速调节
- 温度调节
- 模式调节 [只支持APP]
- 定时任务 [APP自带功能]
- 信号检测

### 界面配置： 

```
{¨config¨{¨headerColor¨¨transparent¨¨headerStyle¨¨dark¨¨background¨{¨img¨¨assets/img/bg/f5.jpg¨¨isFull¨»}}¨dashboard¨|{¨type¨¨btn¨¨ico¨¨fad fa-power-off¨¨mode¨Ê¨t0¨¨电源¨¨t1¨¨文本2¨¨bg¨É¨cols¨Ë¨rows¨Ë¨key¨¨BUTTON_1¨´x´É´y´Î¨speech¨|{¨cmd¨¨开关电脑¨¨act¨¨tap¨}÷¨lstyle¨Ê¨clr¨¨#076EEF¨}{ßA¨ran¨ßF¨设定温度¨ßU¨#389BEE¨¨max¨¤U¨min¨¤GßJÉßKÑßLËßM¨Slidert¨´x´É´y´ÌßO|÷ßTË}{ßA¨deb¨ßEÉßJÉßKÑßLÌßM¨debug¨´x´É´y´ÒßO|÷}{ßAßWßF¨风速¨ßUßYßZÌßaÉßJÉßKÑßLËßM¨Sliderf¨´x´É´y´ÊßO|÷ßTË}{ßAßBßC¨fal fa-power-off¨ßEÊßF¨扫风¨ßHßIßJÉßKËßLËßM¨BUTTON_2¨´x´Ë´y´ÎßO|÷ßTÊßUßV}{ßAßBßC¨fad fa-snowflakes¨ßEÉßF¨制冷¨ßHßIßJÉßKËßLËßM¨BUTTON_4¨´x´Ï´y´ÎßO|÷ßTÉßUßV}{ßAßBßC¨fad fa-humidity¨ßEÉßF¨除湿¨ßHßIßJÉßKËßLËßM¨BUTTON_5¨´x´Ë´y´ÐßO|÷ßTÉßUßV}{ßAßBßC¨fad fa-wind¨ßEÉßF¨送风¨ßHßIßJÉßKËßLËßM¨BUTTON_6¨´x´Í´y´ÐßO|÷ßTÉßUßV}{ßAßBßC¨fad fa-sun¨ßEÉßF¨制热¨ßHßIßJÉßKËßLËßM¨BUTTON_7¨´x´Í´y´ÎßO|÷ßTÉßUßV}{ßAßBßC¨fad fa-chart-network¨ßEÉßF¨自动¨ßHßIßJÉßKËßLËßM¨BUTTON_3¨´x´É´y´ÐßO|÷ßUßV}{ßA¨num¨ßF¨信号强度¨ßC¨fad fa-signal¨ßUßVßaÉßZ¢1c¨uni¨´db´ßJÉßKËßLËßM¨rssi¨´x´Ï´y´ÐßO|÷ßTÉ}÷¨actions¨|¦ßP¦¨switch¨‡¨text¨‡´on´¨打开?name¨¨off¨¨关闭?name¨—÷¨triggers¨|{¨source¨ß14¨source_zh¨¨开关状态¨¨state¨|´on´ß17÷¨state_zh¨|´打开´´关闭´÷}÷}
```