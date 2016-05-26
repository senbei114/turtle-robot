#include "rcb4.h"

RCB4::RCB4(PinName tx, PinName rx) :_serial(tx, rx) {
	_serial.baud(115200);
	_serial.format(8, Serial::Even, 1);
}

void RCB4::write (unsigned char *dat, unsigned char cnt ) {
	int i;
	
	for (i = 0; i < cnt; i++)
	{
		_serial.putc(dat[i]);
	}
}

unsigned char RCB4::check_sum (unsigned char *dat, unsigned char cnt ) {
	int i;
	unsigned int sum = 0;

	for (i = 0; i < cnt; i++)
	{
		sum += dat[i];
	}

	return sum;
}


bool RCB4::SendCtrlData (
	unsigned int  code,
	unsigned char PA1,
	unsigned char PA2,
	unsigned char PA3,
	unsigned char PA4 
)
{
	unsigned char rx_cnt, rx_timeout;
	unsigned char cmd[13] , ret[4];

	cmd[0]  = 0x0D;
	cmd[1]  = 0x00;
	cmd[2]  = 0x02;
	cmd[3]  = 0x50;
	cmd[4]  = 0x03;
	cmd[5]  = 0x00;
	cmd[6]  = (code >> 8) & 0xFF;
	cmd[7]  = code & 0xFF;
	cmd[8]  = PA1;
	cmd[9]  = PA2;
	cmd[10] = PA3;
	cmd[11] = PA4;
	cmd[12] = check_sum (cmd, 12);

	write (cmd, 13);

	rx_cnt = 0;
	rx_timeout = 0;
	while (1)
	{
		if (_serial.readable()) {
			ret[rx_cnt] = _serial.getc();
			rx_cnt++;
		}
		else{
			rx_timeout++;
			wait(0.005);
		}
		if( (rx_cnt == 4) || (rx_timeout == 20) ) break;
	}

	if ( ret[2] == 0x06 )
	{
		return  true;
	}
	else    return false;
}
