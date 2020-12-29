#include "packet.h"
#include <stdio.h>
//#include <wiringPi.h>
//#include <wiringSerial.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
//#define pin 7


////////////////////////////////////	Open Serial-Communication	////////////////////////////////////
packet::packet(int pin_number) {
/*
	wiringPiSetup();
	fd = serialOpen("/dev/ttyAMA0",115200);
  	wiringPiSetup();
	fflush(stdout);
	//pinMode(pin_number,OUTPUT);
 	if(fd<0) printf("can not open serialport\n");    
  	else       printf("serialport opened\n");
	serialFlush(fd);
*/
	fd=open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NONBLOCK);
        fcntl(fd, F_SETFL,0);
        //load configuration
        struct termios conf_tio;
        tcgetattr(fd,&conf_tio);
        //set baudrate
        speed_t BAUDRATE = B115200;
        cfsetispeed(&conf_tio, BAUDRATE);
        cfsetospeed(&conf_tio, BAUDRATE);
        //non canonical, non echo back
        conf_tio.c_lflag &= ~(ECHO | ICANON);
        //non blocking
        conf_tio.c_cc[VMIN]=0;
        conf_tio.c_cc[VTIME]=0;
        //store configuration
        tcsetattr(fd,TCSANOW,&conf_tio);

	        //pinMode(pin_number,OUTPUT);
        if(fd<0)printf("can not open serialport\n");
        else	printf("serialport opened\n");
}

////////////////////////////////////	Config Receive-Send Serial	////////////////////////////////////
short int packet::send_packet(int array_element_count, unsigned char txdate[]){
	for(int i=0; i<=( array_element_count - 1); i++){
		//write(fd,txdate, array_element_count);
		write(fd, &txdate[i],1);

		//serialPutchar( fd,txdate[i] );
		printf("send: %d\n" , txdate[i] );
		//sleep(1);
		//delay(1000);
        }
	printf("\n\n send finish");
	return 0;
}

short int packet::receive_packet() {
	int re_sum=0;
	rd= read(fd,buf,sizeof(buf));

	//if( rd==26 ){
	printf("\n\nDate count: %d \n", rd-9 );
		for( int i=8; i<rd; i++ ){
			receive_date[i-8]=buf[i];
			printf("receive: [%d] : %d \n" , i-8, receive_date[i-8] );
			//fflush(stdout);
                }
	//}

	check_sum(receive_date,25);
	printf("ck_sum  : %d\n",ck_sum);
	printf("buf[rd-1]  : %d\n",buf[rd-1]);
	if( ck_sum ==buf[rd-1] ){
		("\nGET DATE TRUE");
	}
	else{
		printf("\n\n\n==========   GET DATE FALSE   ==========\n\n\n");
		for(int i=0; i<25; i++){
			receive_date[i]=0;
		}
	}
	ck_sum=0;
	//close(fd);

	/*
	printf("\n\nDate count: %d \n", serialDataAvail(fd) );
	if( serialDataAvail(fd)>=0 ){
		while( serialDataAvail(fd) ){
			printf("receive: %d\n" , serialGetchar(fd) );
			fflush(stdout);
		}
         	//delay(1000);
	}
	*/
	return 0;
}
////////////////////////////////////	END	////////////////////////////////////





////////////////////////////////////	Make-Send Serial Short Packet	////////////////////////////////////
short int packet::check_sum(unsigned char txdate[], int sum_array_place) {
	for (int i = 2; i < sum_array_place; i++) {
		ck_sum = ck_sum ^ txdate[i];
	}
	//txdate[8]=ck_sum;
	//printf("ck_sum: %d\n", ck_sum);
	return 0;
}
short int packet::torque_on_off(unsigned char servo_id, unsigned char on_off){
	//unsigned char txdate[9] = {};
	unsigned char txdate[9]={0xFA,0xAF,0x01,0x00,0x24,0x01,0x01,0x01,0x00};

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
short int packet::get_place(unsigned char servo_id) {
	unsigned char txdate[8] = {};
	txdate[0] = 0xFA;
	txdate[1] = 0xAF;
	txdate[2] = servo_id;
	txdate[3] = 0x09;
	txdate[4] = 0x00;
	txdate[5] = 0x00;
	txdate[6] = 0x01;
	check_sum(txdate,7);
	txdate[7]=ck_sum;
	printf("ck_sum: %d\n", txdate[7]);
	printf("request servo place \n");
	send_packet(8,txdate);
	ck_sum=0;
	return 0;
}
short int packet::set_place(unsigned char servo_id) {
	unsigned char txdate[10] = {};
	txdate[0] = 0xFA;
	txdate[1] = 0xAF;
	txdate[2] = servo_id;
	txdate[3] = 0x00;
	txdate[4] = 0x1E;
	txdate[5] = 0x02;
	txdate[6] = 0x01;
	txdate[7] = 0xC2;
	txdate[8] = 0x01;
	check_sum(txdate,9);
	txdate[9]=ck_sum;
	printf("ck_sum: %d\n", txdate[9]);
	send_packet(10,txdate);
	ck_sum=0;
	return 0;
}
////////////////////////////////////	END	////////////////////////////////////



////////////////////////////////////	Make-Send Srial Long Packet	////////////////////////////////////
