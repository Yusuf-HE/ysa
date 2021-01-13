#include <stdio.h>
#include <stdlib.h>
#include <time.h>       /* clock */
#include <math.h>       /* sqrt */
#include <unistd.h>     /* sleep */
#include <sys/shm.h>
#include <fcntl.h>

#define SHM_KEY 0x1953



void lightLoop(){

	int shmid;
   	int *paylasilanBilgi;


	shmid = shmget(SHM_KEY, sizeof(int), 0644|O_RDWR);//bağlantı kurulana kadar simülasyon başlamıyor
	while (shmid == -1) {
		shmid = shmget(SHM_KEY, sizeof(int), 0644|O_RDWR);
		//printf("bağlantı bekleniyor");
	}

	//printf("bağlantı kuruldu\n");
	paylasilanBilgi = shmat(shmid, NULL, 0);
	if (paylasilanBilgi == (void *) -1) {
		perror("Shared memory attach");
	}

	//printf("bağlantı eklendi\n");
	char lightStatus='G'; //---All Lights for Vehicles, Pedestrian Lights Change With Red...---
	int *detectedPedestrianCount;
	detectedPedestrianCount = &paylasilanBilgi[0];
	//printf("her şey hazır\n");
	 //Red Light's independent appear time.
	while(1){
		int totalGreen=250;
		//lightStatus='G';
		printf("GREEN\n");
		while(totalGreen>0)
		{
			sleep(10);
			totalGreen-=10;
			if(detectedPedestrianCount[0]>5) totalGreen-=100;
			else if(detectedPedestrianCount[0]>=1) totalGreen-=50;
		}
		
		
		//lightStatus='R';
		printf("RED\n");
		sleep(10);
		
		//lightStatus='Y';
		printf("YELLOW\n");
		sleep(3);
	}
	if (shmdt(paylasilanBilgi) == -1) {
		perror("shmdt");
	}
	
	
}	
int main(int argc, char *argv[]) {
	lightLoop();
	return 0;
}
	 
		
	
	
	 
	

