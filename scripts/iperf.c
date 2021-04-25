#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<fcntl.h>
#include<time.h>
#include<sys/wait.h>
#include<string.h>
int main(){

	int child_pid;
	int status,wait_pid;
	while(1){

	child_pid = fork();
	if(child_pid == 0){
	int fd = open("/home/pi/WirelessProject/iperftcp.log", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	dup2(fd,1);
	dup2(fd,2);
	time_t rawtime;
        time(&rawtime);
	char *time_str = ctime(&rawtime);
	time_str[strlen(time_str)-1] = '\0';
	printf("%s\n", time_str);
	close(fd);
	char *args[]={"iperf3", "-c", "ec2-18-210-17-65.compute-1.amazonaws.com", "-t","5", 0};
	char *env[] = {0};
	execve("/usr/bin/iperf3",args,env);
	printf("EXEC failed \n");
	exit(-1);
	}
	sleep(6);
	kill(child_pid,SIGKILL);
	wait(NULL);
}
}

