#pragma once
#include<stdio.h>

class packet{
	public:
		packet(int pin_number);
		short int send_packet(int array_element_count, unsigned char txdate[]);
		short int receive_packet();
		short int check_sum(unsigned char txdate[], int sum_array_place);

		short int torque_on_off(unsigned char servo_id,unsigned char on_off);
		short int get_place(unsigned char servo_id);
		short int set_place(unsigned char servo_id);

		unsigned char ck_sum = 0;
		short int fd=0;
		short int rxdate=0;
		unsigned char buf[256]={0};
		unsigned char receive_date[256]={0};
        	int rd=0;
		//unsigned char txdate[9]={0xFA,0xAF,0x01,0x00,0x24,0x01,0x01,0x01,0x00};
/*			txdate[0] = 0xFA;// Header
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

class long_packet :public packet{
	public:
		//short int long_torque_on_off(unsigned char servo_id,unsigned char on_off);
};
