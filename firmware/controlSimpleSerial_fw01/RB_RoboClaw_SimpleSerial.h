#ifndef RB_RoboClaw_SimpleSerial_h
#define RB_RoboClaw_SimpleSerial_h

#define _RB_RoboClaw_SimpleSerial_VERSION 1 // software version of this library

/*  RB_RoboClaw_SimpleSerial library
    RoboticsBrno RoboClaw Simple Serial library
    Fork of RoboClaw Arduino library (http://www.ionmc.com/downloads)
    Created by Jarek Paral <paral@robotikabrno.cz>
*/    

#include <stdarg.h>

#include <inttypes.h>
#include <Stream.h>
#include <HardwareSerial.h>
#ifdef __AVR__
	#include <SoftwareSerial.h>
#endif

/******************************************************************************
* Definitions
******************************************************************************/

#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif


class RoboClawSimpleSerial : public Stream
{
	uint16_t crc;
	uint32_t timeout;
	
	HardwareSerial *hserial;
#ifdef __AVR__
	SoftwareSerial *sserial;
#endif
	
public:
	// public methods
	RoboClawSimpleSerial(HardwareSerial *hserial,uint32_t tout);
#ifdef __AVR__
	RoboClawSimpleSerial(SoftwareSerial *sserial,uint32_t tout);
#endif
	
	~RoboClawSimpleSerial();

	bool ForwardM1(uint8_t speed);
	bool BackwardM1(uint8_t speed);
	bool ForwardM2(uint8_t speed);
	bool BackwardM2(uint8_t speed);
	bool ForwardBackwardM1(uint8_t speed);
	bool ForwardBackwardM2(uint8_t speed);

	// just for compatibility with official RoboClaw Arduino library
	// uint8_t adress - not use in SimpleSerial 
	bool ForwardM1(uint8_t address, uint8_t speed);
	bool BackwardM1(uint8_t address, uint8_t speed);
	bool ForwardM2(uint8_t address, uint8_t speed);
	bool BackwardM2(uint8_t address, uint8_t speed);
	bool ForwardBackwardM1(uint8_t address, uint8_t speed);
	bool ForwardBackwardM2(uint8_t address, uint8_t speed);

	static int16_t library_version() { return _RB_RoboClaw_SimpleSerial_VERSION; }

	virtual int available();
	void begin(long speed);
	bool isListening();
	bool overflow();
	int peek();
	virtual int read();
	int read(uint32_t timeout);
	bool listen();
	virtual size_t write(uint8_t byte);
	virtual void flush();
	void clear();

};

#endif
