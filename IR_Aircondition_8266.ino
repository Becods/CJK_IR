/*
 * 代码原作者 bilibili @1812z 博客: 1812z.top
 * 仓库: https://github.com/1812z/Aircondition
 * 修改内容：
 * - 1.格力空调控制
 * - 2.天猫精灵支持
 * - 3.代码格式化
 */
#define BLINKER_WIFI
#define BLINKER_ALIGENIE_AIRCONDITION
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "ESP8266WiFi.h"
#include <ir_Gree.h>
#include <Blinker.h>
char auth[]	= "KEY";
char ssid[]	= "SSID";
char pswd[]	= "PASSWORD";
const uint16_t	kIrLed	= 14;
IRGreeAC ac( kIrLed );


/* wifi信号检测 */
BlinkerNumber TEXT( "rssi" );


#define Slider_1 "Slidert"      /* APP温度控制滑条 */
BlinkerSlider Slider1( Slider_1 );
#define Slider_2 "Sliderf"      /* APP风速控制滑条 */
BlinkerSlider Slider2( Slider_2 );


uint32_t read_time = 0;

/* 场景控防烧，非场景控请删除 */
#define ACSEND \
	ac.send();  \
	digitalWrite( kIrLed, HIGH ); \
	digitalWrite( 16, HIGH ); \
	delay( 800 ); \
	digitalWrite( 16, LOW );

bool oState	= false;
bool hsState = false;
bool vsState = false;
uint8_t setLevel;
uint8_t setTemp;
void aligenieLevel( uint8_t level )
{
	BLINKER_LOG( "need set level: ", level );
	/*
	 * 0:AUTO MODE, 1-3 LEVEL
	 * 格力控制风速的也和三星的不同
	 */
	switch ( level )
	{
	case 0:
		ac.setFan( kGreeFanAuto );
		ACSEND
		break;
	case 1:
		ac.setFan( kGreeFanMin );
		ACSEND
		break;
	case 2:
		ac.setFan( kGreeFanMed );
		ACSEND
		break;
	case 3:
		ac.setFan( kGreeFanMax );
		ACSEND
		break;
	default:
		break;
	}
	BlinkerAliGenie.level( level );
	BlinkerAliGenie.print();
}


void aligenieTemp( uint8_t temp )
{
	BLINKER_LOG( "need set temp: ", temp );
	setTemp = temp;
	ac.setTemp( setTemp );
	ACSEND
	Slider1.print( temp );
	BlinkerAliGenie.temp( temp );
	BlinkerAliGenie.print();
}


BlinkerButton Button1( "BUTTON_1" );
BlinkerButton Button2( "BUTTON_2" );
BlinkerButton Button3( "BUTTON_3" );
BlinkerButton Button4( "BUTTON_4" );
BlinkerButton Button5( "BUTTON_5" );
BlinkerButton Button6( "BUTTON_6" );
BlinkerButton Button7( "BUTTON_7" );


/* 温度APP控制 */
void slider1_callback( int32_t value )
{
	BLINKER_LOG( "get slider value: ", value );
	ac.setTemp( value );
	ACSEND
	BlinkerAliGenie.temp( value );
	BlinkerAliGenie.print();
}


/* 风速控制 */
void slider2_callback( int32_t value )
{
	BLINKER_LOG( "get slider value: ", value );
	switch ( value )
	{
	case 0:
		ac.setFan( kGreeFanAuto );
		ACSEND
		break;
	case 1:
		ac.setFan( kGreeFanMin );
		ACSEND
		break;
	case 2:
		ac.setFan( kGreeFanMed );
		ACSEND
		break;
	case 3:
		ac.setFan( kGreeFanMax );
		ACSEND
		break;
	default:
		break;
	}
	BlinkerAliGenie.level( value );
	BlinkerAliGenie.print();
}


void aligenieMode( const String & mode, const String & state )
{
	BLINKER_LOG( "need set mode: ", mode, ", state:", state );
	BlinkerAliGenie.mode( mode );
}


void aligenieHSwingState( const String & state )
{
	BLINKER_LOG( "need set HSwing state: ", state );
	if ( state == BLINKER_CMD_ON )
	{
		BlinkerAliGenie.hswing( "on" );
		BlinkerAliGenie.print();

		hsState = true;
	} else if ( state == BLINKER_CMD_OFF )
	{
		BlinkerAliGenie.hswing( "off" );
		BlinkerAliGenie.print();

		hsState = false;
	}
}


void heartbeat() /* 心跳 */
{
	TEXT.print( WiFi.RSSI() );
}


/* APP控制开关 */
void button1_callback( const String & state )
{
	BLINKER_LOG( "get button state: ", state );
	if ( state == BLINKER_CMD_ON )
	{
		BLINKER_LOG( "Toggle on!" );
		Button1.icon( "icon_1" );
		Button1.color( "#FF0000" );
		Button1.text( "电源开" );
		Button1.print( "on" );
		ac.on();
		ACSEND
	} else if ( state == BLINKER_CMD_OFF )
	{
		BLINKER_LOG( "Toggle off!" );
		Button1.icon( "icon_1" );
		Button1.color( "#FF0000" );
		Button1.text( "电源关" );
		Button1.print( "off" );
		ac.off();
		ACSEND
	} else {
		BLINKER_LOG( "Get user setting: ", state );
		Button1.icon( "icon_1" );
		Button1.color( "#FFFFFF" );
		Button1.text( "?" );
		Button1.print();
	}
}


/* APP控制开关-扫风 */
void button2_callback( const String & state )
{
	BLINKER_LOG( "get button state: ", state );
	if ( state == BLINKER_CMD_ON )
	{
		BLINKER_LOG( "Toggle on!" );
		Button2.icon( "icon_1" );
		Button2.color( "#FF0000" );
		Button2.text( "扫风开" );
		Button2.print( "on" );
		/* 格力的扫风是setSwingVertical而不是setSwing */
		ac.setSwingVertical( true, kGreeSwingAuto );
		ACSEND
		BlinkerAliGenie.vswing( "on" );
		BlinkerAliGenie.print();
		vsState = true;
	} else if ( state == BLINKER_CMD_OFF )
	{
		BLINKER_LOG( "Toggle off!" );
		Button2.icon( "icon_1" );
		Button2.color( "#FF0000" );
		Button2.text( "扫风关" );
		Button2.print( "off" );
		ac.setSwingVertical( false, kGreeSwingUp );
		ACSEND
		BlinkerAliGenie.vswing( "off" );
		BlinkerAliGenie.print();
		vsState = false;
	} else {
		BLINKER_LOG( "Get user setting: ", state );
		Button1.icon( "icon_1" );
		Button1.color( "#FFFFFF" );
		Button1.text( "?" );
		Button1.print();
	}
}


/* APP控制-模式 */
void button3_callback( const String & state )
{
	BLINKER_LOG( "get button state: ", state );
	if ( state == BLINKER_CMD_BUTTON_TAP )
	{
		BLINKER_LOG( "Toggle on!" );
		ac.setMode( kGreeAuto );
		ACSEND
	}
}


void button4_callback( const String & state )
{
	BLINKER_LOG( "get button state: ", state );
	if ( state == BLINKER_CMD_BUTTON_TAP )
	{
		BLINKER_LOG( "Toggle on!" );
		ac.setMode( kGreeCool );
		ACSEND
	}
}


void button5_callback( const String & state )
{
	BLINKER_LOG( "get button state: ", state );
	if ( state == BLINKER_CMD_BUTTON_TAP )
	{
		BLINKER_LOG( "Toggle on!" );
		ac.setMode( kGreeDry );
		ACSEND
	}
}


void button6_callback( const String & state )
{
	BLINKER_LOG( "get button state: ", state );
	if ( state == BLINKER_CMD_BUTTON_TAP )
	{
		BLINKER_LOG( "Toggle on!" );
		ac.setMode( kGreeFan );
		ACSEND
	}
}


void button7_callback( const String & state )
{
	BLINKER_LOG( "get button state: ", state );
	if ( state == BLINKER_CMD_BUTTON_TAP )
	{
		BLINKER_LOG( "Toggle on!" );
		ac.setMode( kGreeHeat );
		ACSEND
	}
}


void aligenieVSwingState( const String & state )
{
	BLINKER_LOG( "need set VSwing state: ", state );
	if ( state == BLINKER_CMD_ON )
	{
		BlinkerAliGenie.vswing( "on" );
		BlinkerAliGenie.print();
		ac.setSwingVertical( true, kGreeSwingAuto );
		ACSEND
		vsState = true;
	} else if ( state == BLINKER_CMD_OFF )
	{
		BlinkerAliGenie.vswing( "off" );
		BlinkerAliGenie.print();
		ac.setSwingVertical( false, kGreeSwingUp );
		ACSEND
		vsState = false;
	}
}


/* 猫精电源控制 */
void aligeniePowerState( const String & state )
{
	BLINKER_LOG( "need set power state: ", state );

	if ( state == BLINKER_CMD_ON )
	{
		ac.on();
		ACSEND
		BlinkerAliGenie.powerState( "on" );
		BlinkerAliGenie.print();
		oState = true;
	} else if ( state == BLINKER_CMD_OFF )
	{
		ac.off();
		ACSEND
		BlinkerAliGenie.powerState( "off" );
		BlinkerAliGenie.print();
		oState = false;
	}
}


void aligenieQuery( int32_t queryCode )
{
	BLINKER_LOG( "aligenie Query codes: ", queryCode );

	switch ( queryCode )
	{
	case BLINKER_CMD_QUERY_ALL_NUMBER:
		BLINKER_LOG( "aligenie Query All" );
		/* 猫精很多参数不支持，故删除 */
		BlinkerAliGenie.powerState( oState ? "on" : "off" );
		BlinkerAliGenie.hswing( hsState ? "on" : "off" );
		BlinkerAliGenie.vswing( vsState ? "on" : "off" );
		BlinkerAliGenie.level( setLevel );
		BlinkerAliGenie.temp( setTemp );
		BlinkerAliGenie.print();
		break;
	case BLINKER_CMD_QUERY_POWERSTATE_NUMBER:
		BLINKER_LOG( "aligenie Query Power State" );
		BlinkerAliGenie.powerState( oState ? "on" : "off" );
		BlinkerAliGenie.print();
		break;
	default:
		BlinkerAliGenie.powerState( oState ? "on" : "off" );
		BlinkerAliGenie.hswing( hsState ? "on" : "off" );
		BlinkerAliGenie.vswing( vsState ? "on" : "off" );
		BlinkerAliGenie.level( setLevel );
		BlinkerAliGenie.temp( setTemp );
		BlinkerAliGenie.print();
		break;
	}
}


void dataRead( const String & data )
{
	BLINKER_LOG( "Blinker readString: ", data );
	Blinker.vibrate();
	uint32_t BlinkerTime = millis();
	Blinker.print( "millis", BlinkerTime );
}


void setup()
{
	ac.begin();
	Serial.begin( 9600 );
	BLINKER_DEBUG.stream( Serial );
	Button1.attach( button1_callback );
	Button2.attach( button2_callback );
	Button3.attach( button3_callback );
	Button4.attach( button4_callback );
	Button5.attach( button5_callback );
	Button6.attach( button6_callback );
	Button7.attach( button7_callback );
	Blinker.begin( auth, ssid, pswd );
	Blinker.attachData( dataRead );
	Blinker.attachHeartbeat( heartbeat );
	BlinkerAliGenie.attachPowerState( aligeniePowerState );
	BlinkerAliGenie.attachHSwing( aligenieHSwingState );
	BlinkerAliGenie.attachVSwing( aligenieVSwingState );
	BlinkerAliGenie.attachLevel( aligenieLevel );
	BlinkerAliGenie.attachTemp( aligenieTemp );
	BlinkerAliGenie.attachQuery( aligenieQuery );
	Slider1.attach( slider1_callback );
	Slider2.attach( slider2_callback );
	pinMode( kIrLed, OUTPUT );
	digitalWrite( kIrLed, HIGH );
	pinMode( 16, OUTPUT );
	digitalWrite( 16, LOW );
}

void loop()
{
	Blinker.run();
}
