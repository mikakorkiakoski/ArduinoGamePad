#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "HID.h"

#if defined(_USING_HID)

typedef struct
{
	uint16_t buttons;
	int8_t leftXaxis;
	int8_t leftYaxis;
	int8_t rightXaxis;
	int8_t rightYaxis;
	//TODO: implement a R2 and L2 throttles or what it is
} gamepad_report_struct;

class Gamepad
{
private:
	gamepad_report_struct reportData;
public:
	Gamepad(bool useZRx = false);
	
	void sendUpdate();
	
	void setButtonState(uint8_t button, bool state);
	void setLeftXaxis (int8_t value);
	void setLeftYaxis (int8_t value);
	void setRightXaxis(int8_t value);
	void setRightYaxis(int8_t value);
	
};

#else
	#warning "HID is not supported for this chip"
#endif
#endif
