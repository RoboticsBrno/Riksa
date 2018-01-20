#include "Arduino.h"
#include "RB_RoboClaw_SimpleSerial.h"

//
// Constructor
//
RoboClawSimpleSerial::RoboClawSimpleSerial(HardwareSerial *serial, uint32_t tout)
{
	timeout = tout;
	hserial = serial;
#ifdef __AVR__
	sserial = 0;
#endif
}

#ifdef __AVR__
RoboClawSimpleSerial::RoboClawSimpleSerial(SoftwareSerial *serial, uint32_t tout)
{
	timeout = tout;
	sserial = serial;
	hserial = 0;
}
#endif

//
// Destructor
//
RoboClawSimpleSerial::~RoboClawSimpleSerial()
{
}

void RoboClawSimpleSerial::begin(long speed)
{
	if(hserial){
		hserial->begin(speed);
	}
#ifdef __AVR__
	else{
		sserial->begin(speed);
	}
#endif
}

bool RoboClawSimpleSerial::listen()
{
#ifdef __AVR__
	if(sserial){
		return sserial->listen();
	}
#endif
	return false;
}

bool RoboClawSimpleSerial::isListening()
{
#ifdef __AVR__
	if(sserial)
		return sserial->isListening();
#endif
	return false;
}

bool RoboClawSimpleSerial::overflow()
{
#ifdef __AVR__
	if(sserial)
		return sserial->overflow();
#endif
	return false;
}

int RoboClawSimpleSerial::peek()
{
	if(hserial)
		return hserial->peek();
#ifdef __AVR__
	else
		return sserial->peek();
#endif
}

size_t RoboClawSimpleSerial::write(uint8_t byte)
{
	if(hserial)
		return hserial->write(byte);
#ifdef __AVR__
	else
		return sserial->write(byte);
#endif
}

int RoboClawSimpleSerial::read()
{
	if(hserial)
		return hserial->read();
#ifdef __AVR__
	else
		return sserial->read();
#endif
}

int RoboClawSimpleSerial::available()
{
	if(hserial)
		return hserial->available();
#ifdef __AVR__
	else
		return sserial->available();
#endif
}

void RoboClawSimpleSerial::flush()
{
	if(hserial)
		hserial->flush();
}

int RoboClawSimpleSerial::read(uint32_t timeout)
{
	if(hserial){
		uint32_t start = micros();
		// Empty buffer?
		while(!hserial->available()){
		   if((micros()-start)>=timeout)
		      return -1;
		}
		return hserial->read();
	}
#ifdef __AVR__
	else{
		if(sserial->isListening()){
			uint32_t start = micros();
			// Empty buffer?
			while(!sserial->available()){
			   if((micros()-start)>=timeout)
				  return -1;
			}
			return sserial->read();
		}
	}
#endif
}

void RoboClawSimpleSerial::clear()
{
	if(hserial){
		while(hserial->available())
			hserial->read();
	}
#ifdef __AVR__
	else{
		while(sserial->available())
			sserial->read();
	}
#endif
}
                 
#define M1min 0
#define M1max 127
#define M1middle 64
                  
#define M2min 128
#define M2max 255
#define M2middle 192

// speed = 0 - 127
bool RoboClawSimpleSerial::ForwardM1(uint8_t speed){
	return write(M1middle + speed/2);
}

bool RoboClawSimpleSerial::BackwardM1(uint8_t speed){
	return write(M1middle - speed/2);
}

bool RoboClawSimpleSerial::ForwardM2(uint8_t speed){
	return write(M2middle + speed/2);
}

bool RoboClawSimpleSerial::BackwardM2(uint8_t speed){
	return write(M2middle - speed/2);
}

bool RoboClawSimpleSerial::ForwardBackwardM1(uint8_t speed){
	return write(M1min + speed);
}                            

bool RoboClawSimpleSerial::ForwardBackwardM2(uint8_t speed){
	return write(M2min + speed);
}

// Next function just for compatibility with official RoboClaw Arduino library
// uint8_t adress - not use in SimpleSerial 
/*
  bool ForwardM1(uint8_t address, uint8_t speed);
  bool BackwardM1(uint8_t address, uint8_t speed);
  bool ForwardM2(uint8_t address, uint8_t speed);
  bool BackwardM2(uint8_t address, uint8_t speed);
  bool ForwardBackwardM1(uint8_t address, uint8_t speed);
  bool ForwardBackwardM2(uint8_t address, uint8_t speed);
*/

bool RoboClawSimpleSerial::ForwardM1(uint8_t address, uint8_t speed){
  return RoboClawSimpleSerial::ForwardM1(speed);
}

bool RoboClawSimpleSerial::BackwardM1(uint8_t address, uint8_t speed){
  return RoboClawSimpleSerial::BackwardM1(speed);
}

bool RoboClawSimpleSerial::ForwardM2(uint8_t address, uint8_t speed){
  return RoboClawSimpleSerial::ForwardM2(speed);
}

bool RoboClawSimpleSerial::BackwardM2(uint8_t address, uint8_t speed){
  return RoboClawSimpleSerial::BackwardM2(speed);
}

bool RoboClawSimpleSerial::ForwardBackwardM1(uint8_t address, uint8_t speed){
  return RoboClawSimpleSerial::ForwardBackwardM1(speed);
}                            

bool RoboClawSimpleSerial::ForwardBackwardM2(uint8_t address, uint8_t speed){
  return RoboClawSimpleSerial::ForwardBackwardM2(speed);
}

