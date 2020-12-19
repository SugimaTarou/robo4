#include <stdio.h>
//#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(){
/* シリアルポートオープン */
	unsigned char txdate[9];
	txdate[0] = 0xFA;           // Header
	txdate[1] = 0xAF;           // Header
	txdate[2] = 0x01;             // ID
	txdate[3] = 0x00;           // Flags
	txdate[4] = 0x24;           // Address
 	txdate[5] = 0x01;           // Length
 	txdate[6] = 0x01;           // Count
 	txdate[7] = 0x00;
 	txdate[8] = 0x24;
	int rxdate=0;
	int fd = serialOpen("/dev/ttyAMA0",115200);
   	if(fd<0){
		printf("can not open serialport");
	}
	while(1){
		// 送信処理
		//printf("receive : \n");
		//delay(1000);
		//delay(1000);
		printf("Send START\n");
		//fflush(stdout);
		for(int i=0; i<=8; i++){
			serialPutchar(fd,txdate[i]);
			while(serialDataAvail(fd)){
				rxdate=serialGetchar(fd);
                 		printf("receive : %d\n" , rxdate );
                 		fflush(stdout);
				 //delay(1000);
        		}
		delay(1000);
		}
	printf("Send END\n");
	}

return 0;
}
