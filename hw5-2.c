#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <strings.h>


#define BUFFSIZE 1024

typedef struct  {
  char caName[20];
  char caIdNo[10];
  char cGender;
  int iAge;
  char caPhone[12];
} stDefStudent;


int main(int argc, char **argv){
	int iShmId;
	key_t key;
	char *caShmAddr;

	stDefStudent *stStudent;



	//if((key = ftok("./", 2018)) == -1){ 
	//	perror("ftok error");
	//}
	
	//Segement key.
	
	if(argc > 1){
		key = atoi(argv[1]);
	}else{
		key = 8889;
	}
	
	printf("key:%d\n", key);
		
	//Create the segment

	if((iShmId = shmget(key,BUFFSIZE, IPC_CREAT|0666)) <0){
		perror("shmget error.");
		exit(1);
	}
	printf("shmid:%d\n",iShmId);
	

	//Attach the segment to the data space.
	if((caShmAddr = shmat(iShmId, NULL, 0)) == (char*)-1){
		perror("shmat error.");
		exit(1);
	}
	if(argc > 2){
		char caCtlType = argv[2][0];
		int iRc;
		printf("%c\n", caCtlType);
		switch(caCtlType){
			case 'd':
				iRc = shmctl(iShmId, IPC_RMID, 0);
				if(iRc == 0){
					printf("Destroy shared memory successfully\n");
				}	
				else{
					printf("Destory fail.\n");
				}
			break;
			//case 'p':
			//	stStudent = (stDefStudent *)caShmAddr; 
			//	printf("shmId:%d\tData:{%s,%s,%c,%d,%s}\n", key, stStudent->caName, stStudent->caIdNo, stStudent->cGender, stStudent->iAge, stStudent->caPhone);
			//break;

		}
	}else{
 
		stStudent = (stDefStudent *)caShmAddr; 
		printf("Data:{%s,%s,%c,%d,%s}\n", 
			stStudent->caName, stStudent->caIdNo, stStudent->cGender, stStudent->iAge, stStudent->caPhone);
	}	
	return 0;
}
