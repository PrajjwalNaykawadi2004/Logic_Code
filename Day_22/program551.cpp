/////////////////////////////////////////////////////////////////////////
//
//  Header File Inclusion
//
/////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>      // For system calls (like clear)
#include<stdbool.h>
#include<string.h>

/////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros
//
/////////////////////////////////////////////////////////////////////////

// Maximum file size thet we allow in the project
#define MAXFILESIZE 50     // Max size of a single file
#define MAXOPENFILES 20    // Max files a process can open
#define MAXINODE 5         // Max files allowed in FS

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

#define REGULARFILE 1
#define SPECIALFILE 2

/////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros For Error Handling
//
/////////////////////////////////////////////////////////////////////////

#define ERR_INVALID_PARAMETER -1

#define ERR_NO_INODES -2

#define ERR_FILE_ALREADY_EXIST -3
#define ERR_FILE_NOT_EXIST -4

#define ERR_PERMISSION_DENIED -5

#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

#define ERR_MAX_FILES_OPEN -8

/////////////////////////////////////////////////////////////////////////
//
//  User Defined Structures
//
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    BootBlock
//  Description :       Stores information related to the boot process of
//                      CVFS and holds a short message describing system
//                      boot status
//  
/////////////////////////////////////////////////////////////////////////

struct BootBlock      
{
    char Information[100];
};

/////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    SuperBlock
//  Description :       Stores file system metadata and Tracks total and
//                      free inodes
//  
/////////////////////////////////////////////////////////////////////////

struct SuperBlock        
{
    int TotalInodes;        // Total inodes allowed
    int FreeInodes;         // Free inodes available
};

/////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    Inode
//  Description :       Represents a file in CVFS contains file name, size,
//                      type, permissions, reference count, buffer pointer
//                      and link to next inode in DILB
//  
/////////////////////////////////////////////////////////////////////////

#pragma pack(1)
struct Inode                
{
    char FileName[20];      // Name of file
    int InodeNumber;        // Unique inode number
    int FileSize;           // Max allowed size
    int ActualFileSize;     // Current used size
    int FileType;           // REGULAR/SPECIAL
    int ReferenceCount;     // No. of times opened
    int Permission;         // File permission
    char *Buffer;           // Pointer to file data
    struct Inode *next;     // Next inode in DILB
};

typedef struct Inode INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;

/////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    FileTable
//  Description :       Represents an open file in RAM and stores 
//                      read/write offsets, file mode, and pointer to 
//                      corresponding inode
//
/////////////////////////////////////////////////////////////////////////

// Structure representing an open file in RAM
struct FileTable            
{
    int ReadOffset;     // Current read position
    int WriteOffset;    // Current write position
    int Mode;           // Access mode (READ/WRITE/READWRITE)
    PINODE ptrinode;    // Pointer to inode of file
};

typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE;

/////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    UAREA
//  Description :       Stores process-level file information and contains
//                      process name and array of pointers to open file 
//                      tables (UFDT)
//  
/////////////////////////////////////////////////////////////////////////

struct UAREA                
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];      // Array of open files
};


/////////////////////////////////////////////////////////////////////////
//
//  Global variables or objects used in the project
//  
/////////////////////////////////////////////////////////////////////////

BootBlock bootobj;      // Boot info
SuperBlock superobj;    // FS metadata
UAREA uareaobj;         // Process info

PINODE head = NULL;     // Head of inode linked list (DILB)

/////////////////////////////////////////////////////////////////////////
//
//  Function Name : InitialiseUAREA
//  Description :   Initializes the UAREA structure for the process and
//                  sets process name and clears all UFDT entries
//  Author :        Prajjwal Dilip Naykawadi
//  Date :          13/01/2026
//
/////////////////////////////////////////////////////////////////////////

void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");

    int i = 0;

    for(i = 0; i < MAXOPENFILES; i++)
    {
        uareaobj.UFDT[i] = NULL;
    }
    
    printf("Marvellous CVFS : UAREA gets initialised successfully\n");
}

/////////////////////////////////////////////////////////////////////////
//
//  Function Name : InitialiseSuperBlock
//  Description :   Initializes SuperBlock with toatl and free inodes
//  Author :        Prajjwal Dilip Naykawadi
//  Date :          13/01/2026
//
/////////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("Marvellous CVFS : Super block gets initialised successfully\n");
}

/////////////////////////////////////////////////////////////////////////
//
//  Function Name : CreateDILB
//  Description :   Creates a linked list of inodes (DILB) in memory
//                  and Each inode represents a file in CVFS
//  Author :        Prajjwal Dilip Naykawadi
//  Date :          13/01/2026
//
/////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for(i = 1; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        strcpy(newn->FileName,"\0");
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->FileType = 0;
        newn->ReferenceCount = 0;
        newn->Permission = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        // Link into the list
        if(temp == NULL)    // LL is empty
        {
            head = newn;
            temp = head;
        }
        else                // LL contains atleast 1 node
        {
            temp->next = newn;
            temp = temp->next;
        }
    }
    
    printf("Marvellous CVFS : DILB created successfully\n");
}

/////////////////////////////////////////////////////////////////////////
//
//  Function Name : StartAuxillaryDataInitilisation
//  Description :   It is used to call all such functions which are used
//                  to initialise auxillary data
//  Author :        Prajjwal Dilip Naykawadi
//  Date :          13/01/2026
//
/////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitilisation()
{
    strcpy(bootobj.Information,"Booting process of Marvellous CVFS is done");

    printf("%s\n",bootobj.Information);

    InitialiseSuperBlock(); 

    CreateDILB();

    InitialiseUAREA();

    printf("Marvellous CVFS : Auxillary data initialised successfully\n");
}


/////////////////////////////////////////////////////////////////////////
//
//  Function Name : DisplayHelp
//  Description :   Shows manual information for a specific command and 
//                  Prints usage and purpose on console
//  Author :        Prajjwal Dilip Naykawadi
//  Date :          14/01/2026
//
/////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("--------------------------------------------------------\n");
    printf("--------------- Marvellous CVFS Help page --------------\n");
    printf("--------------------------------------------------------\n");

    printf("man    :  It is used to display manual page\n");
    printf("clear  :  It is used to clear the terminal\n");
    printf("creat  :  It is used to create new file\n");
    printf("write  :  It is used to write the data into file\n");
    printf("read   :  It is used to read the data from the file\n");
    printf("stat   :  It is used to display statistical information\n");
    printf("unlink :  It is used to delete the file\n");
    printf("exit   :  It is used to terminated Marvellous CVFS\n");

    printf("--------------------------------------------------------\n");
}

/////////////////////////////////////////////////////////////////////////
//
//  Function Name : ManPageDisplay
//  Description :   Shows manual information for a specific command and 
//                  Prints usage and purpose on console
//  Author :        Prajjwal Dilip Naykawadi
//  Date :          14/01/2026
//
/////////////////////////////////////////////////////////////////////////

void ManPageDisplay(char Name[])
{
    if(strcmp("ls",Name) == 0)
    {
        printf("About : It is used to list the names of all files\n");
        printf("Usage : ls\n");
    }
    else if(strcmp("man",Name) == 0)
    {
        printf("About : It is used to display manual page\n");
        printf("Usage : man command_name\n");
        printf("command_name : It is the name of command\n");
    }
    else if(strcmp("exit",Name) == 0)
    {
        printf("About : It is used to terminate the shell\n");
        printf("Usage : exit\n");
    }
     else if(strcmp("clear",Name) == 0)
    {
        printf("About : It is used to clear the shell\n");
        printf("Usage : exit\n");
    }
    else
    {
        printf("No manual entry for %s\n",Name);
    }
}

/////////////////////////////////////////////////////////////////////////
//
//  Function Name : IsFileExist
//  Description :   Checks if a file with the given name exists in DILB
//                  Returns true if found, false otherwise
//  Input :         It accepts file name
//  Output :        It returns the true or false
//  Author :        Prajjwal Dilip Naykawadi
//  Date :          16/01/2026
//
/////////////////////////////////////////////////////////////////////////

bool IsFileExist(
                    char *name      // File name   
                )
{
    PINODE temp = head;
    bool bFlag = false;

    while(temp != NULL)
    {
        if((strcmp(name,temp->FileName) == 0) && (temp->FileType == REGULARFILE))
        {
            bFlag = true;
            break;
        }
        temp = temp->next;
    }

    return bFlag;
}

/////////////////////////////////////////////////////////////////////////
//
//  Function Name : CreateFile
//  Description :   Creates a new regular file with given permissions and
//                  Allocates inode, UFDT entry and memory buffer returns
//                  file descriptor or error code
//  Input :         It accepts file name and permissions
//  Output :        It returns the file descriptor
//  Author :        Prajjwal Dilip Naykawadi
//  Date :          16/01/2026
//
/////////////////////////////////////////////////////////////////////////

int CreateFile(
                    char *name,         // Name of new file
                    int permission      // Permission of that file
                )
{
    PINODE temp = head;
    int i = 0;

    printf("Total number of Inodes remaining : %d\n",superobj.FreeInodes);
    
    // If name is missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If the permission value is wrong
    // permission -> 1 -> READ
    // permission -> 2 -> WRITE
    // permission -> 3 -> READ + WRITE
    if(permission < 1 || permission >3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If the Inodes are full
    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }

    // If file is already present
    if(IsFileExist(name) == true)
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    // Search Empty Inode
    while(temp != NULL)
    {
        if(temp->FileType == 0)
        {
            break;
        }
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("There is no Inode\n");
        return ERR_NO_INODES;
    }

    // Search for Empty UFDT entry
    // Note : 0,1,2 are reserved
    for(i = 3; i < MAXOPENFILES; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }
    
    // UFDT is full
    if(i == MAXOPENFILES)
    {
        return ERR_MAX_FILES_OPEN;
    }

    // Allocate memory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

    // Initialise File table
    uareaobj.UFDT[i]->ReadOffset = 0;
    uareaobj.UFDT[i]->WriteOffset = 0;
    uareaobj.UFDT[i]->Mode = permission;

    // Connect File table with Inode
    uareaobj.UFDT[i]->ptrinode = temp;

    // Initialise elements of Inode
    strcpy(uareaobj.UFDT[i]->ptrinode->FileName,name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permission;

    // Allocate memory for files data
    uareaobj.UFDT[i]->ptrinode->Buffer = (char*)malloc(MAXFILESIZE);

    superobj.FreeInodes--;

    return i;   // File descriptor
}

/////////////////////////////////////////////////////////////////////////
//
//  Entry Point function of the project
//
/////////////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    char Command[5] [20] = {{'\0'}};
    int iCount = 0;
    int iRet = 0;

    StartAuxillaryDataInitilisation();

    printf("--------------------------------------------------------\n");
    printf("--------- Marvellous CVFS started successfully ---------\n");
    printf("--------------------------------------------------------\n");

    // Infinite Listening Shell
    while(1)        // Shell loop
    {
        fflush(stdin);

        strcpy(str,"");

        printf("\nMarvellous CVFS : > ");
        fgets(str,sizeof(str),stdin);

        iCount = sscanf(str,"%s %s %s %s %s",Command[0],Command[1],Command[2],Command[3],Command[4]);

        fflush(stdin);

        if(iCount == 1)
        {
            // Marvellous CVFS : > exit
            if(strcmp("exit",Command[0]) == 0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
            }
            // Marvellous CVFS : > ls
            else if(strcmp("ls",Command[0]) == 0)
            {
                printf("Inside ls\n");
            }
            // Marvellous CVFS : > help
            else if(strcmp("help",Command[0]) == 0)
            {
                DisplayHelp();
            }
            // Marvellous CVFS : > clear
            else if(strcmp("clear",Command[0]) == 0)
            {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif 
            }
        }  // End of else if 1
        else if(iCount == 2)
        {   
            // Marvellous CVFS : > man ls
            if(strcmp("man",Command[0]) == 0)
            {
                ManPageDisplay(Command[1]);
            }
        }  // End of else if 2
        else if(iCount == 3)
        {
            // Marvellous CVFS : > creat Ganesh.txt 3
            if(strcmp("creat",Command[0]) == 0)
            {
                iRet = CreateFile(Command[1],atoi(Command[2]));

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Unable to create the file as parameters are invalid\n");
                    printf("Please refer to man page\n");
                }

                if(iRet == ERR_NO_INODES)
                {
                    printf("Error : Unable to create file as there is no inode\n");
                }

                if(iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("Error : Unable to create file because the file is already present\n");
                }

                if(iRet == ERR_MAX_FILES_OPEN)
                {
                    printf("Error : Unable to create file\n");
                    printf("Max opened files limit reached\n");
                }

                printf("File gets successfully created with FD %d\n",iRet);
            }
        }// End of else if 3
        else if(iCount == 4)
        {

        } // End of else if 4
        else
        {
            printf("Command not found\n");
            printf("Please refer help option to get more information\n");
        } // End of else
    } // End of while

    return 0; // End of main
}