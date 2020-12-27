#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main()
{   
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

    int fd1=open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NONBLOCK);
    fcntl(fd1, F_SETFL,0);
    //load configuration
    struct termios conf_tio;
    tcgetattr(fd1,&conf_tio);
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
    tcsetattr(fd1,TCSANOW,&conf_tio);

    write(fd1,txdate,9);
    printf("SEND Finish\n");   
    sleep(1);
   
    char buff[100]={0};//="=======================";
    int rd=read(fd1,buff,sizeof(buff));
    printf("Receive byte count : %d\n\n",rd);
    for(int i=0; i<rd; i++){
    //printf("Bytes sent are %d\n",buff);
    	printf("receive [%d] : %d\n",i,buff[i]);
    }
    close(fd1);
    return 0;
}



/*
#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(){
// シリアルポートオープン //
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
*/
