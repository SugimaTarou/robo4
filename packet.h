#pragma once
#include<stdio.h>

class packet{

public:
	packet(int pin_number);
	float make_packet();
	float check_sum(unsigned char txdate[], int dat_place);
	float torque_on_off(unsigned char servo_id,unsigned char on_off);
	float get_place(unsigned char servo_id);
	float send_packet();
	unsigned char ck_sum = 0;
	int fd=0;
};
