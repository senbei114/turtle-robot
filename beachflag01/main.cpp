#include "mbed.h"
#include "rcb4.h"
#include <math.h>

#define SW_ON   0
#define SW_OFF  1

#define MOT_FW  1
#define MOT_BK  2
#define MOT_RT  4
#define MOT_LT  8
#define MOT_FG  1024
#define MOT_SP  2048

#define COND_DIFF  300
#define COND_SUM  3700
#define COND_PSD  2300

DigitalOut  activity( LED1 ) ;
DigitalIn   startSW(p21);
AnalogIn    psd(p20);
AnalogIn    usR(p19);
AnalogIn    usL(p18);
RCB4        rcb4( p13 ,  p14 ) ; // tx, rx




int main() 
{
	unsigned short psd_data ,usR_data, usL_data;
	unsigned int ctrlData;
	int          us_Diff, us_Sum;
	
	startSW.mode(PullUp);
	while( startSW == SW_OFF );
	while( startSW == SW_ON  );
	
	while (1) {
		psd_data = psd.read_u16() >> 4;
		usR_data = usR.read_u16() >> 4;
		usL_data = usL.read_u16() >> 4;
		
		us_Diff = usR_data - usL_data;
		us_Sum  = usL_data + usR_data;
		
		if( (psd_data > COND_PSD) || (us_Sum > COND_SUM) )
		{
			ctrlData = 0;
		} else {
			if( abs(us_Diff) < COND_DIFF )
			{
				ctrlData = MOT_FW;
			} else if( us_Diff < 0 )
			{
				ctrlData = MOT_LT;
			} else {
				ctrlData = MOT_RT;
			}
		}
		
		rcb4.SendCtrlData(ctrlData, 0, 0, 0, 0);
		wait(0.1);
		activity = !activity;
	}
}
