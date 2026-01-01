/*
Student: Samuel Meyer
About: This program utilizes process functions in order to implement a more extensive grep command
this was a pretty difficult assignment and the testing for it was rather annoying as well
I found that the assignment took concepts from the previous two assignments and expanded upon them 
the first one teaching about what grep did and how to implement it 
the second on teaching more about directory navigation and the like
this one sort of fusing the topics together and creating a mesh of the two that searches directories and looks for specific file types and then 
in those file types searching for a specific pattern given by the user
*/
#include"utils.h"

int isTxtFile(const char *file);
void search(const char *dirPath, char *pattern, char **flags, int numFlags, int *file_cnt);

//this is a helper method which takes the length of the file being checked and checks if its
//file type is of type .txt
int isTxtFile(const char *file)
{
    int length = strlen(file);
    
    if(length < 4)
    {
        return 0;
    }
    
    return strcmp(file + length - 4, ".txt") == 0;
}

//This is a recursviely implemented searching algorithm that searches directories and reconstructs the 
//file path to be printed in the grep_extended method
//this function uses the fork and execvp functions in C in order to shorten up the searching algorithms
void search(const char *dirPath, char *pattern, char **flags, int numFlags, int *file_cnt)
{
    DIR *path = opendir(dirPath);
    
    //safely checking to see if the directory we are opening was done successfully 
    if(path == NULL)
    {
        return;
    }
    
    struct dirent *entry;
    //while loop that does the searching
    while((entry = readdir(path)) != NULL)
    {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        
        char finPath[1024];
        strcpy(finPath, dirPath);
        strcat(finPath, "/");
        strcat(finPath, entry->d_name);
        
        DIR *check = opendir(finPath);
        //a point in which we have found a new branch for the file directory we are searching and therefor
        //need to search it as well for any of our target file types
        if(check != NULL)
        {
            closedir(check);
            search(finPath, pattern, flags, numFlags, file_cnt);
        }
        else
        {
            //this section checks if its a .txt file and does the nitty gritty of doing the grep command and seraching
            //for the chars we are looking for 
            if(isTxtFile(entry->d_name))
            {
                (*file_cnt)++;
                
                pid_t pid = fork();
                
                if(pid < 0)
                {
                    perror("fork failed");
                    closedir(path);
                    exit(1);
                }
                else if(pid == 0)
                //this is the child process that does the execvp command using grep
                {
                    char *args[6 + numFlags];
                    int arg_index = 0;
                    
                    args[arg_index++] = "grep";
                    args[arg_index++] = pattern;
                    args[arg_index++] = finPath;
                    
                    for(int i = 0; i < numFlags; i++)
                    {
                        args[arg_index++] = flags[i];
                    }
                    
                    args[arg_index] = NULL;
                    
                    execvp("grep", args);
                    
                    perror("execvp failed");
                    exit(1);
                }
            }
        }
    }
    
    closedir(path);
}
//tha main() implementation of our program
void grep_extended(int argc, char *argv[])
{
    //checks for valid arguments
    if(argc < 5)
    {
        usage_message();
        return;
    }

    
    char *pattern = argv[1];
    char *directory = argv[2];
    
    DIR *direct = opendir(directory);
    //checks if the opendir() command work correctly 
    if(direct == NULL)
    {
        usage_message();
        return;
    }
    closedir(direct);
    
    char *flags[10];
    int num_flags = 0;
    int hasC = 0, hasH = 0;
    //checking for the flags 
    for(int i = 3; i < argc; i++)
    {
        if(strcmp(argv[i], "-c") == 0)
        {
            hasC = 1;
            flags[num_flags++] = argv[i];
        }
        else if(strcmp(argv[i], "-H") == 0)
        {
            hasH = 1;
            flags[num_flags++] = argv[i];
        }
        else if(strcmp(argv[i], "-i") == 0)
        {
            flags[num_flags++] = argv[i];
        }
        else
        {
            usage_message();
            return;
        }
    }
    //incase the user provided no -C and no -H flags 
    if(!hasC || !hasH)
    {
        usage_message();
        return;
    }
    
    int filecnt = 0;
    search(directory, pattern, flags, num_flags, &filecnt);
    //this section does the actual printing portion of the program and prints the file path and when its done 
    //doing all of its searching 
    int stat;
    for(int i = 0; i < filecnt; i++)
    {
        wait(&stat);
    }
    
    printf("Finished searching all the .txt files\n");
    printf("Total .txt files searched: %d\n", filecnt);
}