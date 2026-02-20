#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/utsname.h>

// 	./psx
// 	argv[0]	
// 	argc = 1

/*
	Open the directory /proc
	Open all subdirectors whose name is integer
	Inside that directory open comm file
	Display the name inside that file

*/

int main(int argc, char *argv[])
{
	char Buffer[1024] = {'\0'};
	
	getcwd(Buffer, sizeof(Buffer));
	
	printf("%s\n",Buffer);
	
	return 0;
}