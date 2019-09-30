#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "globals.h"


int main() {
	key_t shmkey = ftok(".", 'a');
	if(shmkey == -1) {
		fprintf(stderr, "Err in server: Cannot generate shm key (ftok: %s) \n", strerror(errno));
		exit(1);
	}
	
	int shmid = shmget(shmkey, SHMSZ, 0666 | IPC_CREAT | IPC_EXCL);
	if(shmid == -1) {
		fprintf(stderr, "Err in server: Cannot generate shm ID (shmget: %s) \n", strerror(errno));
		exit(1);
	}
	
	int* shmaddr = shmat(shmid, NULL, 0);
	if(shmaddr == (int*)-1) {
		fprintf(stderr, "Err in server: Cannot attach shm seg to server process (shmat: %s) \n", strerror(errno));
		exit(1);
	}
	
	printf("[Server started] \n");
	while(shmaddr[0] != SIG_STOP) {
		if(shmaddr[0] == SIG_EXEC) {
            printf("shmaddr[1]=%d \n", shmaddr[1]);
			shmaddr[0] = SIG_DONE;
		}
		sleep(1);
	}

	if(shmdt(shmaddr) == -1) {
		fprintf(stderr, "Err in server: Cannot detach shm seg from server process (shmdt: %s) \n", strerror(errno));
		exit(1);
	}
	
	if(shmctl(shmid, IPC_RMID, NULL) == -1) {
		fprintf(stderr, "Err in server: Cannot remove shm seg from server process (shmctl: %s) \n", strerror(errno));
		exit(1);
	}
	
	printf("[Server shutting down...] \n");
	
	
	return 0;
}
