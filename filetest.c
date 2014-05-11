#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

failure(char* s)
{
    perror(s);
    exit(1);

}
printpos(char* string,int fildes)
{
    long pos;
    if((pos=lseek(fildes,0L,1))<0L)
    {
        failure("lseek failed");
    }
    printf("%s:%ld \n",string,pos);

}
main()
{
    int fd;
    int pid;
    char buf[10];
    if((fd=open("data",O_RDONLY))<0)
    {
        failure("open failed");
    }
    read(fd,buf,10);
    printpos("Before fork",fd);
    if((pid=fork())<0)
    {

        failure("fork failed");
    }
    else if(!pid)
    {

        printpos("Child before read",fd);
        read(fd,buf,10);
        printpos("child after read",fd);
    }
    else
    {
        wait(NULL);
        printpos("parent after wait",fd);
    }

}