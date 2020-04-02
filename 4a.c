#include<stdio.h> 
#include<pthread.h> 
#include<unistd.h> 
#include<stdlib.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
  
void *mult(void* arg) 
{ 
    int *data = (int *)arg; 
    int k = 0, i = 0; 
      
    int x = data[0]; 
    for (i = 1; i <= x; i++) 
           k += data[i]*data[i+x]; 
      
    int *p = (int*)malloc(sizeof(int)); 
         *p = k; 
      

    pthread_exit(p); 
} 
  

int main() 
{ 
    int r1=4,c1=2,r2=2,c2=5,i,j,k; 
    int matA[r1][c1];  
    int matB[r2][c2];  
      

    for (i = 0; i < r1; i++)  
            for (j = 0; j < c1; j++)  
                   matA[i][j] = rand() % 20+1;  
            

    for (i = 0; i < r2; i++)  
	{
	for (j = 0; j < c2; j++)  
        matB[i][j] = rand() % 20+1;  

	}
 
      
    int max = r1*c2; 
      
      
        
    pthread_t *threads; 
    threads = (pthread_t*)malloc(max*sizeof(pthread_t)); 
      
    int count = 0; 
    int* data = NULL; 
    for (i = 0; i < r1; i++) 
        for (j = 0; j < c2; j++) 
               { 
                 
  
            data = (int *)malloc((20)*sizeof(int)); 
            data[0] = c1; 
      
            for (k = 0; k < c1; k++) 
                data[k+1] = matA[i][k]; 
      
            for (k = 0; k < r2; k++) 
                data[k+c1+1] = matB[k][j]; 
               

                pthread_create(&threads[count++], NULL,mult, (void*)(data)); 
                  
                    } 
      int result[max];
    printf("Matriks hasil:\n"); 
    for (i = 0; i < max; i++)  
    { 
      void *k; 
        

      pthread_join(threads[i], &k); 
             
            
          int *p = (int *)k; 
      printf("%d ",*p); 
      if ((i + 1) % c2 == 0) 
          printf("\n"); 
	result[i]= *p;
    } 

	key_t key = 1234;
	int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
	int *pass;pass=shmat(shmid, NULL, 0);
	
	for(i=0;i<max;i++) pass[i]=result[i];
	shmdt(pass);
	
} 
