#pragma once
#include<stdio.h>

class packet{

public:
	packet(int pin_number);
	float send_packet(int array_element_count, unsigned char txdate[]);
	short int check_sum(unsigned char txdate[], int dat_place);
	float torque_on_off(unsigned char servo_id,unsigned char on_off);
	float get_place(unsigned char servo_id);
	float receive_packet();
	unsigned char ck_sum = 0;
	int fd=0;
	int rxdate=0;

	unsigned char txdate[9]={0xFA,0xAF,0x01,0x00,0x24,0x01,0x01,0x01,0x00};
/*		txdate[0] = 0xFA;// Header
		txdate[1] = 0xAF;// Header
		txdate[2] = 0x01;// ID
		txdate[3] = 0x00;// Flags
		txdate[4] = 0x24;// Address
		txdate[5] = 0x01;// Length
		txdate[6] = 0x01;// Count
		txdate[7] = 0x01;
		txdate[8] = 0x00;
*/
};
