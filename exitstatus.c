#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
main(){
	int pid,status,exit_status;
	if((pid=fork())<0){
        perror("fork fail");
		exit(0);
	}
	if(!pid){
        /*child process*/
		sleep(5);
		exit(5);/*use not null value exit*/
	}
	/*parent procces*/
	if(wait(&status)<0){
		perror ("wait fail");
		exit(1);
	}
	if(status & 0xFF){
       printf ("some low-roderbit not zero\n");
	}else{
       exit_status = status>>8;
	   exit_status &= 0xFF;
		printf ("Exit status from %d was %d\n",pid,exit_status );
	}
	exit(0);
}