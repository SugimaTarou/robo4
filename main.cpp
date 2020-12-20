#include"packet.h"
#include <wiringPi.h>
//#include <wiringSerial.h>

int main(void) {
/*	unsigned char txdate[9]={};
	txdate[0] = 0xFA;// Header
	txdate[1] = 0xAF;// Header
	txdate[2] = 0x01;// ID
	txdate[3] = 0x00;// Flags
	txdate[4] = 0x24;// Address
	txdate[5] = 0x01;// Length
	txdate[6] = 0x01;// Count
	txdate[7] = 0x01;
	txdate[8] = 0x06;
*/
	//unsigned char date=0x00 & 0x00;
	unsigned char torque_off = 0x00;
	unsigned char torque_on  = 0x01;
	packet packet2(1);//Pin_number
	//while(1){
		//packet2.check_sum(txdate,8);
		packet2.torque_on_off(1,torque_off);
		delay(2000);
		//packet2.receive_packet();
		//delay(2000);
	//}
	return 0;
}

