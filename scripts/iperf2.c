#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<fcntl.h>
#include<time.h>
#include<sys/wait.h>
#include<string.h>
#define BUFSIZE 50
int main(){

	int child_pid;
	int status,wait_pid;
	volatile static int ap1, ap2, ap3;
	ap1 = -1;
	ap2 = -1;
	ap3 = -1;
	volatile static char prevMAC[BUFSIZE] = "\n";
	volatile char *MAC1 = "B8:27:EB:6C:F0:84\n";
	volatile char *MAC2 = "B8:27:EB:75:C1:31\n";
	volatile char *MAC3 = "B8:27:EB:CC:AA:D5\n";
	while(1){

	child_pid = fork();
	if(child_pid == 0){
	char *cmd = "iwconfig wlan0 | egrep \"Access Point: \" | awk \'{print $6}\'";
	char MAC[BUFSIZE];
	FILE *fp;
	if((fp=popen(cmd,"r")) == NULL){
		printf("Error cant open popen for the given command\n");
	}
	while(fgets(MAC,BUFSIZE, fp) != NULL){
	}
	pclose(fp);
	printf("RESULT:%s", MAC);
	if (strcmp(MAC, "\n") != 0 && strcmp(MAC, (const char*) prevMAC) != 0) {
		if(strcmp((const char*) prevMAC, (const char*) MAC1) == 0){
			ap1 = 0;
		}
		else if(strcmp((const char*) prevMAC, (const char*) MAC2) == 0){
			ap2 = 0;
		}
		else if(strcmp((const char*) prevMAC, (const char*) MAC3) == 0){
			ap3 = 0;
		}
	}

	// Determine port number
	char port[10] = "5201";
       	if (strcmp(MAC, (const char*) MAC1) == 0) {
		strcpy(port, "6001");
	} else if (strcmp(MAC, (const char*) MAC2) == 0) {
		strcpy(port, "6002");
	} else if (strcmp(MAC, (const char*) MAC3) == 0) {
		strcpy(port, "6003");
	}
	printf("%s\n", port);	

	int fd = open("/home/pi/WirelessProject/iperftcp.log", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

	dup2(fd,1);
	dup2(fd,2);
	time_t rawtime;
        time(&rawtime);
	char *time_str = ctime(&rawtime);
	time_str[strlen(time_str)-1] = '\0';
	printf("%s\n", time_str);
	fflush(stdout);
	close(fd);
	char *args[]={"iperf3", "-c", "nprabhalmac.wifi.local.cmu.edu", "-p", port, "-t","5", 0};
	char *env[] = {0};
	if (strcmp(MAC, "\n") != 0) {
		memcpy((void*) prevMAC, (void*) MAC, BUFSIZE);
	}
	execve("/usr/bin/iperf3",args,env);
	printf("EXEC failed \n");
	exit(-1);
	}
	sleep(7);
	kill(child_pid,SIGKILL);
	wait(NULL);
}
}

