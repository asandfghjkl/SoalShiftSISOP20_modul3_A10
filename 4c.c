#include<stdio.h>
#include<unistd.h>
#include<limits.h>
#include<dirent.h>
#include<sys/types.h> 
#include<string.h>
#include<stdlib.h>

int main(){
	char cwd[PATH_MAX];
	struct dirent *de;
	getcwd(cwd, sizeof(cwd));
	DIR *dr = opendir(cwd);
	int p[2], i; 
	if (pipe(p) < 0) 
		exit(1);
	char pass[100];
	char stop[]="stop";
	pid_t child_id;
	child_id=fork();

	if (child_id>0)
	{
		close(p[0]);
		while((de=readdir(dr))!=NULL)
		{
			strcpy(pass,de->d_name);
			if (pass[0]!='.')
			write(p[1],pass,100);

		}
		write(p[1],stop,strlen(stop)+1);
		close(p[1]);
	}
	else
	{
		close(p[1]);
		char buffer[100];
		int count=0,i=0;
		while(strcmp(buffer,stop))
		{
			read(p[0], buffer, 100);
			count++;
	
		}
		
		printf("%d\n",count-1);
		close(p[0]);

	}
	


}
