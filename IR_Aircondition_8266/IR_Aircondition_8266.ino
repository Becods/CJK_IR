/* ************************************************
 * 代码参考：https://github.com/1812z/Aircondition
 * 其他空调支持请在issue #1回复
 * 短接GND和DOWN，然后串口线接RX和TX直接刷机即可
 * ************************************************/

#define BLINKER_WIFI
#define BLINKER_ALIGENIE_AIRCONDITION
/* 啥时候支持了啥时候再取消注释 */
/* #define BLINKER_MIOT_AIRCONDITION */
/* #define BLINKER_DUEROS_LIGHT */
#define SliderLevel "LEVEL"
#define SliderTemp "TEMP"
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include <ir_Gree.h>
#include <Blinker.h>

uint32_t read_time = 0;
const uint16_t kIrLed = 14;
char auth[] = "KEY";
char ssid[] = "SSID";
char pswd[] = "PASSWORD";
bool oState = false;
bool hsState = false;
bool vsState = false;
uint8_t setLevel;
uint8_t setTemp;

IRGreeAC ac(kIrLed);

/* 场景控防烧，非场景控请删除 */
#define IRSEND \
  ac.send(); \
  digitalWrite(kIrLed, HIGH); \
  digitalWrite(16, HIGH); \
  delay(100); \
  digitalWrite(16, LOW);


/* APP支持开始 */
BlinkerSlider sTemp(SliderTemp);
BlinkerSlider sLevel(SliderLevel);
BlinkerButton Power("POWER");
BlinkerButton Swing("SWING");
BlinkerButton Auto("AUTO");
BlinkerButton Cool("COOL");
BlinkerButton Dry("DRY");
BlinkerButton Fan("FAN");
BlinkerButton Heat("HEAT");

/* APP温度开始 */
void sTemp_callback(int32_t value)
{
  BLINKER_LOG("get slider value: ", value);
  ac.setTemp(value);
  IRSEND
  BlinkerAliGenie.temp(value);
  BlinkerAliGenie.print();
}
/* APP温度结束 */

/* APP风速开始 */
void sLevel_callback(int32_t value)
{
  BLINKER_LOG("get slider value: ", value);
  switch (value)
  {
  case 0:
    ac.setFan(kGreeFanAuto);
    IRSEND
    break;
  case 1:
    ac.setFan(kGreeFanMin);
    IRSEND
    break;
  case 2:
    ac.setFan(kGreeFanMed);
    IRSEND
    break;
  case 3:
    ac.setFan(kGreeFanMax);
    IRSEND
    break;
  default:
    break;
  }
  BlinkerAliGenie.level(value);
  BlinkerAliGenie.print();
}
/* APP风速结束 */

/* APP电源开始 */
void power_callback(const String & state)
{
  BLINKER_LOG("get button state: ", state);
  if (state == BLINKER_CMD_ON)
  {
    BLINKER_LOG("Toggle on!");
    Power.icon("icon_1");
    Power.color("#FF0000");
    Power.text("电源开");
    Power.print("on");
    ac.on();
    IRSEND
  } else if (state == BLINKER_CMD_OFF)
  {
    BLINKER_LOG("Toggle off!");
    Power.icon("icon_1");
    Power.color("#FF0000");
    Power.text("电源关");
    Power.print("off");
    ac.off();
    IRSEND
  } else {
    BLINKER_LOG("Get user setting: ", state);
    Power.icon("icon_1");
    Power.color("#FFFFFF");
    Power.text("?");
    Power.print();
  }
}
/* APP电源结束 */

/* APP扫风开始 */
void swing_callback(const String & state)
{
  BLINKER_LOG("get button state: ", state);
  if (state == BLINKER_CMD_ON)
  {
    BLINKER_LOG("Toggle on!");
    Swing.icon("icon_1");
    Swing.color("#FF0000");
    Swing.text("扫风开");
    Swing.print("on");
    /* 格力的扫风是setSwingVertical而不是setSwing */
    ac.setSwingVertical(true, kGreeSwingAuto);
    IRSEND
    BlinkerAliGenie.vswing("on");
    BlinkerAliGenie.print();
    vsState = true;
  } else if (state == BLINKER_CMD_OFF)
  {
    BLINKER_LOG("Toggle off!");
    Swing.icon("icon_1");
    Swing.color("#FF0000");
    Swing.text("扫风关");
    Swing.print("off");
    ac.setSwingVertical(false, kGreeSwingUp);
    IRSEND
    BlinkerAliGenie.vswing("off");
    BlinkerAliGenie.print();
    vsState = false;
  } else {
    BLINKER_LOG("Get user setting: ", state);
    Power.icon("icon_1");
    Power.color("#FFFFFF");
    Power.text("?");
    Power.print();
  }
}
/* APP扫风结束 */

/* APP自动模式开始 */
void auto_callback(const String & state)
{
  BLINKER_LOG("get auto state: ", state);
  if (state == BLINKER_CMD_BUTTON_TAP)
  {
    BLINKER_LOG("Toggle on!");
    ac.setMode(kGreeAuto);
    IRSEND
  }
}
/* APP自动模式结束 */

/* APP制冷模式开始 */
void cool_callback(const String & state)
{
  BLINKER_LOG("get cool state: ", state);
  if (state == BLINKER_CMD_BUTTON_TAP)
  {
    BLINKER_LOG("Toggle on!");
    ac.setMode(kGreeCool);
    IRSEND
  }
}
/* APP制冷模式结束 */

/* APP干燥模式开始 */
void dry_callback(const String & state)
{
  BLINKER_LOG("get dry state: ", state);
  if (state == BLINKER_CMD_BUTTON_TAP)
  {
    BLINKER_LOG("Toggle on!");
    ac.setMode(kGreeDry);
    IRSEND
  }
}
/* APP干燥模式结束 */

/* APP送风模式开始 */
void fan_callback(const String & state)
{
  BLINKER_LOG("get fan state: ", state);
  if (state == BLINKER_CMD_BUTTON_TAP)
  {
    BLINKER_LOG("Toggle on!");
    ac.setMode(kGreeFan);
    IRSEND
  }
}
/* APP送风模式结束 */

/* APP制热模式开始 */
void heat_callback(const String & state)
{
  BLINKER_LOG("get heat state: ", state);
  if (state == BLINKER_CMD_BUTTON_TAP)
  {
    BLINKER_LOG("Toggle on!");
    ac.setMode(kGreeHeat);
    IRSEND
  }
}
/* APP制热模式结束 */
/* APP支持结束 */


/* 猫精公共调用开始 */
/* 猫精风速开始 */
void aligenieLevel(uint8_t level) {
  BLINKER_LOG("need set level: ", level);
  switch (level)
  {
  case 0:
    ac.setFan(kGreeFanAuto);
    IRSEND
    break;
  case 1:
    ac.setFan(kGreeFanMin);
    IRSEND
    break;
  case 2:
    ac.setFan(kGreeFanMed);
    IRSEND
    break;
  case 3:
    ac.setFan(kGreeFanMax);
    IRSEND
    break;
  default:
    break;
  }
  BlinkerAliGenie.level(level);
  BlinkerAliGenie.print();
}
/* 猫精风速结束 */

/* 猫精温度开始 */
void aligenieTemp(uint8_t temp){
  BLINKER_LOG("need set temp: ", temp);
  setTemp = temp;
  ac.setTemp(setTemp);
  IRSEND
  sTemp.print(temp);
  BlinkerAliGenie.temp(temp);
  BlinkerAliGenie.print();
}
/* 猫精温度结束 */

/* 猫精模式开始 */
void aligenieMode(const String & mode, const String & state)
{
  BLINKER_LOG("need set mode: ", mode, ", state:", state);
  BlinkerAliGenie.mode(mode);
}
/* 猫精模式结束 */

/* 猫精左右摆风开始 */
void aligenieHSwingState(const String & state)
{
  BLINKER_LOG("need set HSwing state: ", state);
  if (state == BLINKER_CMD_ON)
  {
    BlinkerAliGenie.hswing("on");
    BlinkerAliGenie.print();
    hsState = true;
  } else if (state == BLINKER_CMD_OFF)
  {
    BlinkerAliGenie.hswing("off");
    BlinkerAliGenie.print();
    hsState = false;
  }
}
/* 猫精左右摆风结束 */

/* 猫精上下摆风开始 */
void aligenieVSwingState(const String & state)
{
  BLINKER_LOG("need set VSwing state: ", state);
  if (state == BLINKER_CMD_ON)
  {
    BlinkerAliGenie.vswing("on");
    BlinkerAliGenie.print();
    ac.setSwingVertical(true, kGreeSwingAuto);
    IRSEND
    vsState = true;
  } else if (state == BLINKER_CMD_OFF)
  {
    BlinkerAliGenie.vswing("off");
    BlinkerAliGenie.print();
    ac.setSwingVertical(false, kGreeSwingUp);
    IRSEND
    vsState = false;
  }
}
/* 猫精上下摆风结束 */

/* 猫精电源开始 */
void aligeniePowerState(const String & state)
{
  BLINKER_LOG("need set power state: ", state);

  if (state == BLINKER_CMD_ON)
  {
    ac.on();
    IRSEND
    BlinkerAliGenie.powerState("on");
    BlinkerAliGenie.print();
    oState = true;
  } else if (state == BLINKER_CMD_OFF)
  {
    ac.off();
    IRSEND
    BlinkerAliGenie.powerState("off");
    BlinkerAliGenie.print();
    oState = false;
  }
}
/* 猫精电源结束 */
/* 猫精公共调用结束 */


/* 猫精回调开始 */
void aligenieQuery(int32_t queryCode)
{
  BLINKER_LOG("aligenie Query codes: ", queryCode);
  switch (queryCode)
  {
  /* 猫精很多参数不支持，故删除部分 */
  case BLINKER_CMD_QUERY_ALL_NUMBER:
    BLINKER_LOG("aligenie Query All");
    BlinkerAliGenie.powerState(oState ? "on" : "off");
    BlinkerAliGenie.hswing(hsState ? "on" : "off");
    BlinkerAliGenie.vswing(vsState ? "on" : "off");
    BlinkerAliGenie.level(setLevel);
    BlinkerAliGenie.temp(setTemp);
    BlinkerAliGenie.print();
    break;
  case BLINKER_CMD_QUERY_POWERSTATE_NUMBER:
    BLINKER_LOG("aligenie Query Power State");
    BlinkerAliGenie.powerState(oState ? "on" : "off");
    BlinkerAliGenie.print();
    break;
  default:
    BlinkerAliGenie.powerState(oState ? "on" : "off");
    BlinkerAliGenie.hswing(hsState ? "on" : "off");
    BlinkerAliGenie.vswing(vsState ? "on" : "off");
    BlinkerAliGenie.level(setLevel);
    BlinkerAliGenie.temp(setTemp);
    BlinkerAliGenie.print();
    break;
  }
}
/* 猫精回调结束 */

void dataRead(const String & data)
{
  BLINKER_LOG("Blinker readString: ", data);
  Blinker.vibrate();
  uint32_t BlinkerTime = millis();
  Blinker.print("millis", BlinkerTime);
}

/* wifi信号检测开始 */
BlinkerNumber TEXT("rssi");
void heartbeat() /* 心跳 */
{
  TEXT.print(WiFi.RSSI());
}
/* wifi信号检测结束 */

/* 初始化注册开始 */
void setup()
{ 
  ac.begin();
  Serial.begin(115200);
  BLINKER_DEBUG.stream(Serial);
  Blinker.begin(auth, ssid, pswd);
  Blinker.attachData(dataRead);
  Blinker.attachHeartbeat(heartbeat);

  /* APP注册开始 */
  Power.attach(power_callback);
  Swing.attach(swing_callback);
  Auto.attach(auto_callback);
  Cool.attach(cool_callback);
  Dry.attach(dry_callback);
  Fan.attach(fan_callback);
  Heat.attach(heat_callback);
  sTemp.attach(sTemp_callback);
  sLevel.attach(sLevel_callback);
  /* APP注册结束 */
  
  /* 猫精注册开始 */
  BlinkerAliGenie.attachPowerState(aligeniePowerState);
  BlinkerAliGenie.attachHSwing(aligenieHSwingState);
  BlinkerAliGenie.attachVSwing(aligenieVSwingState);
  BlinkerAliGenie.attachLevel(aligenieLevel);
  BlinkerAliGenie.attachTemp(aligenieTemp);
  BlinkerAliGenie.attachQuery(aligenieQuery);
  /* 猫精注册结束 */

  pinMode(kIrLed, OUTPUT);
  digitalWrite(kIrLed, HIGH);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
}
/* 初始化注册结束 */

void loop()
{
  Blinker.run();
}
