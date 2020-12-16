#include "packet.h"
#include <stdio.h>
//use namespace std;
#include "/home/ubuntu/gitwork/wiringpi-2.50/wiringPi/wiringPi.h"
#include "/home/ubuntu/gitwork/wiringpi-2.50/wiringPi/wiringSerial.h"
#include "unistd.h"
//#define pin 7

packet::packet(int pin_number) {
	wiringPiSetup();
	fd = serialOpen("/dev/serial0",19200);
  	wiringPiSetup();
	fflush(stdout);
	//pinMode(pin_number,OUTPUT);

 	if(fd<0) printf("can not open serialport\n");    
  	else       printf("serialport opened\n");
}

float packet::make_packet() {
	return 0;
}

float packet::check_sum(unsigned char txdate[], int dat_place) {
	//unsigned char check_sum = 0;
	for (int i = 2; i < dat_place; i++) {
		ck_sum = ck_sum ^ txdate[i];
	}
	return 0;
}

float packet::torque_on_off(unsigned char servo_id, unsigned char on_off){
	unsigned char txdate[9] = {};
	txdate[0] = 0xFA;
	txdate[1] = 0xAF;
	txdate[2] = servo_id;
	txdate[3] = 0x00;
	txdate[4] = 0x24;
	txdate[5] = 0x01;
	txdate[6] = 0x01;
	txdate[7] = on_off;

	check_sum(txdate, 8);
	txdate[8] = ck_sum;
	printf("%d\n", txdate[8]);

            // パケットデータ送信
	for(int i=0; i<=8; i++){
		serialPutchar(fd,txdate[i]);              //cntの値を送る
		printf("RPi : send %d \n",txdate[i]);    //ついでにターミナルにcntの値を出力する
	}
	return 0;
}

float packet::get_place(unsigned char servo_id) {
	unsigned char txdate[8] = {};
	txdate[0] = 0xFA;
	txdate[1] = 0xAF;
	txdate[2] = servo_id;
	txdate[3] = 0x09;
	txdate[4] = 0x00;
	txdate[5] = 0x00;
	txdate[6] = 0x01;
	return 0;
}
