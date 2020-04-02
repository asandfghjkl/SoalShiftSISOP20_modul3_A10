#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[1000000];
pid_t child;
char cwd[1000];

void *movefile(void *arg) {
	char *filepath = (char *)arg;

	// cek ekstensi file
	int dot = '.';
        char *extension = NULL;
	extension = strrchr(filepath, dot);

	char extlower[1000];
	memset(extlower, '\0', sizeof(extlower));
	if(extension) {
		extension++;
        	for(int i=0; i<strlen(extension); i++) {
                	extlower[i] = tolower(extension[i]);
        	}
	}
	else strcpy(extlower, "Unknown");

	// simpan nama file
        int slash = '/';
        char *filename = NULL;
        filename = strrchr(filepath, slash);
        if(filename) filename++;
	else filename = filepath;

	// buat directory
	char folderpath[1000];
	strcpy(folderpath, cwd);
	strcat(folderpath, "/");
	strcat(folderpath, extlower);
	mkdir(folderpath, S_IRWXU);
        strcat(folderpath, "/");
        strcat(folderpath, filename);

	// move file
	rename(filepath, folderpath);

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
			err = pthread_create(&tid[i], NULL, movefile, (void *)argv[i]);
			if(err != 0) printf("\ncan't create thread : [%s]",strerror(err));
		}
		for(int j=2; j<argc; j++)
			pthread_join(tid[j], NULL);
	}
	else if(strcmp(argv[1], "-d") == 0) {
		int i=0;
                DIR *dir = opendir(argv[2]);
                struct dirent *tmp;
		while((dir!=NULL) && (tmp=readdir(dir))) {
                        if(strcmp(tmp->d_name, ".")==0 || strcmp(tmp->d_name, "..")==0 || strcmp(tmp->d_name, "soal3.c")==0 || strcmp(tmp->d_name, "soal3")==0 || tmp->d_type==DT_DIR) continue;

                        err = pthread_create(&tid[i], NULL, movefile, tmp->d_name);
                        if(err != 0) printf("\ncan't create thread : [%s]",strerror(err));
                        i++;
                }
                for(int j=0; j<i; j++)
                        pthread_join(tid[j], NULL);
                closedir(dir);

	}
	else if((argv[1][0]=='*') && (strlen(argv[1])==1)) {
		int i=0;
		DIR *dir = opendir(cwd);
		struct dirent *tmp;
		while((dir!=NULL) && (tmp=readdir(dir))) {
			if(strcmp(tmp->d_name, ".")==0 || strcmp(tmp->d_name, "..")==0 || strcmp(tmp->d_name, "soal3.c")==0 || strcmp(tmp->d_name, "soal3")==0 || tmp->d_type==DT_DIR) continue;
                        err = pthread_create(&tid[i], NULL, movefile, tmp->d_name);
                        if(err != 0) printf("\ncan't create thread : [%s]",strerror(err));
			i++;
		}
		for(int j=0; j<i; j++)
			pthread_join(tid[j], NULL);
		closedir(dir);
	}
	return 0;
}
