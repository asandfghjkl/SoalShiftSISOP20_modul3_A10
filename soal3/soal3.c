#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[3]; 	// inisialisasi array untuk menampung thread dalam kasus ini ada 2 thread
pid_t child;
char cwd[100];

void *movefile(void *arg) {
	char *filename = (char *)arg;

	// cek ekstensi file
	int dot = '.';
        char *extension = NULL;
	extension = strrchr(filename, dot);

	char extlower[1000];
	memset(extlower, '\0', sizeof(extlower));
	if(extension) {
		extension++;
        	for(int i=0; i<strlen(extension); i++) {
                	extlower[i] = tolower(extension[i]);
        	}
	}
	else strcpy(extlower, "Unknown");

        char folderpath[1000];
        memset(folderpath, '\0', sizeof(folderpath));
	strcpy(folderpath, cwd); 	// letak file soal3.c
	strcat(folderpath, "/");
        strcat(folderpath, extlower);

	// printf("%s - %s - %s\n", filename, extlower, folderpath);

	char *argv1[] = {"mkdir", "-p", folderpath, NULL};
	char *argv2[] = {"mv", filename, folderpath, NULL};

	pthread_t id = pthread_self();
	if(pthread_equal(id,tid[0])) { 		// buat directory
		child = fork();
		if (child==0) {
		    execv("/bin/mkdir", argv1);
	    	}
	}
	else if(pthread_equal(id,tid[1])) {	// pindahkan file
        	sleep(1);
		child = fork();
        	if (child==0) {
		    execv("/bin/mv", argv2);
	    	}
	}

	return NULL;
}

int main(int argc, char *argv[]) {
	getcwd(cwd, sizeof(cwd));
	int err;
	if(argc < 2) {
		printf("argumen invalid");
		return 0;
	}
	if(strcmp(argv[1], "-f") == 0) {
		for(int i=2; i<argc; i++) {
			for(int j=0; j<2; j++) {
				err = pthread_create(&tid[j], NULL, movefile, (void *)argv[i]);
				if(err != 0) printf("\ncan't create thread : [%s]",strerror(err));
			}
			pthread_join(tid[0], NULL);
			pthread_join(tid[1], NULL);
		}
	}
	else if(strcmp(argv[1], "-d") == 0) {
	}
	return 0;
}
