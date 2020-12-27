#include"packet.h"
//#include <wiringPi.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
//#include <wiringSerial.h>

int main(void) {
/*
	unsigned char txdate[9]={};
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
	//packet2.torque_on_off(1,torque_on);
	packet2.get_place(1);
	//packet2.set_place(1);
	sleep(1);


	//while(1){
		//printf("\n Get Place START \n\n");
		packet2.receive_packet();
		//printf("\n Get Place END \n\n");
		//delay(1000);
	//}
	close(packet2.fd);
	return 0;
}

