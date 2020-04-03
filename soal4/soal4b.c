#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>

void *sum(void *arg) {
	int *n = (int *)arg;
	int x = (*n) * ((*n) + 1) / 2;
	int *pointerx = (int *)malloc(sizeof(int));
	*pointerx = x;
	pthread_exit(pointerx);
}

int main() {
	key_t key = 1234;
	int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
	int *pass;
	pass = shmat(shmid, NULL, 0);
	int i;
	int matrix[20];

	for(i=0; i<20; i++)
		matrix[i] = pass[i];

	shmdt(pass);

	printf("Matrix hasil 4a:\n");
	for(i=0; i<20; i++) {
		printf("%d ", matrix[i]);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}

	pthread_t threads[20];

	int count=0;
	int current;

	printf("Matrix hasil:\n");
	for (i=0; i<20; i++) {
		int *tmp = (int *)malloc(sizeof(int));
		tmp = &matrix[i];
		pthread_create(&threads[count++], NULL, sum, (void *)tmp);
	}

	for (i=0; i<20; i++) {
		void *k;
		pthread_join(threads[i], &k);
		int *p = (int *)k;
		printf("%d ",*p);
		if ((i + 1) % 5 == 0)
			printf("\n");
    	}
	return 0;
}
