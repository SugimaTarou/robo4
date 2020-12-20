#include "packet.h"
#include <stdio.h>
//use namespace std;
#include <wiringPi.h>
#include <wiringSerial.h>
#include "unistd.h"
//#define pin 7

packet::packet(int pin_number) {
	wiringPiSetup();
	fd = serialOpen("/dev/ttyAMA0",115200);
  	wiringPiSetup();
	fflush(stdout);
	//pinMode(pin_number,OUTPUT);
 	if(fd<0) printf("can not open serialport\n");    
  	else       printf("serialport opened\n");
	serialFlush(fd);
}
float packet::send_packet(int array_element_count, unsigned char txdate[]){
	for(int i=0; i<=( array_element_count - 1); i++){
		serialPutchar( fd,txdate[i] );
		printf("send: %d\n" , txdate[i] );
		//delay(1000);
         }
	return 0;
}
float packet::receive_packet() {
	//unsigned char rxdate[];
	//printf("receive : \n");
	printf("\n\nDate count: %d \n", serialDataAvail(fd) );
	//if( serialDataAvail(fd)>=0 ){
		while( serialDataAvail(fd) ){
			printf("receive: %d\n" , serialGetchar(fd) );
			fflush(stdout);
		//}
         	//delay(1000);
	}
	return 0;
}

short int packet::check_sum(unsigned char txdate[], int dat_place) {
	for (int i = 2; i < dat_place; i++) {
		ck_sum = ck_sum ^ txdate[i];
	}
	//txdate[8]=ck_sum;
	//printf("ck_sum: %d\n", ck_sum);
	return 0;
}
float packet::torque_on_off(unsigned char servo_id, unsigned char on_off){
	//unsigned char txdate[9] = {};
	txdate[7]=on_off;
	if(on_off==1){
		printf("\n\nTorque  ON \n");
	}
	if(on_off==0){
		printf("\n\nTorque OFF \n");
	}
	check_sum(txdate, 8);
	txdate[8] = ck_sum;
	printf("ck_sum: %d\n", txdate[8]);
	//delay(1000);
	send_packet(9,txdate);
	ck_sum=0;
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
