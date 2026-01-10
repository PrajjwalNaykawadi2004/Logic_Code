#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd = 0;
    int iRet = 0;
    char Arr[] = "Jay Ganesh";  // Call Arr[] = Buffer

    fd = open("JanuaryX.txt",O_RDWR | O_CREAT, 0777);

    if(fd == -1)
    {
        printf("Unable to open file\n");
    }
    else
    {
        printf("File gets successfully opened with fd : %d\n",fd);

        iRet = write(fd,Arr,3);

        printf("%d bytes gets successfully written into the file\n",iRet);

        close(fd);
    }

    return 0;
}