#ifndef MBED_RCB4_H
#define MBED_RCB4_H

#include "mbed.h"

class RCB4 {
	public: 
	RCB4(PinName tx, PinName rx);
	bool SendCtrlData (
		unsigned int  code, 
		unsigned char PA1, 
		unsigned char PA2, 
		unsigned char PA3,
		unsigned char PA4
	);

	private:
	unsigned char check_sum (unsigned char *dat, unsigned char cnt );
	void write (unsigned char *dat, unsigned char cnt );

	protected:
	Serial _serial;
};

#endif