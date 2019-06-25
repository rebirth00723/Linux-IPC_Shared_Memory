#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <strings.h>


#define BUFFSIZE 2048

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



	if((key = ftok("./", 2018)) == -1){ 
		perror("ftok error");
	}
	
	//Segement key.
	if(argc > 6 || argc == 2){
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
	//Initialization.
	memset(caShmAddr, 0, BUFFSIZE);	
	stStudent = (stDefStudent*)caShmAddr;

	if(argc > 2){
		int iIdx = 0;
		if(argc > 6){
			iIdx = 1;
		}
		printf("t");
		memcpy(stStudent->caName, argv[1+iIdx], sizeof(argv[1+iIdx]));
		memcpy(stStudent->caIdNo, argv[2+iIdx], sizeof(argv[2+iIdx]));
		stStudent->cGender = argv[3+iIdx];
		stStudent->iAge = atoi(argv[4+iIdx]);
		memcpy(stStudent->caPhone, argv[5+iIdx], sizeof(argv[5+iIdx])); 
	}else{	
		memcpy(stStudent->caName, "AMO_CHEN", 8);
		memcpy(stStudent->caIdNo, "0123456789", 10);
		stStudent->cGender = 'M';
		stStudent->iAge = 23;
		memcpy(stStudent->caPhone, "0912345678", 10);
	}
	return 0;
}
