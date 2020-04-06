//trinh064 - Nam Trinh
//cunni536 - Jessica Cunningham
//carl5362 - Conrad Carlson

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>

//file redirection
void redirect(char*filename,char* sign,int fd)
{
	if (strcmp(sign,">")==0)
	    {fd = open(filename, O_WRONLY);}
	else 
        {fd = open(filename, O_WRONLY  | O_APPEND);}
	
    if(fd< 0) 
       {printf("Error opening the file\n");} 
	dup2(fd,1);
	return;
}

//choosing local implementations of ls and wc over unix shell
void homemade(int key,char **singlecmd)
{
	char* argv= (char*) calloc(50,sizeof(char*));
	char* space=" ";
	for (int i=1;i<50;i++)
        {
            if (singlecmd[i]==NULL) 
                {break;}
            strcat(argv,singlecmd[i]); 
            if (singlecmd[i+1]==NULL)
                {break;} 
            strcat(argv,space); 
        }
	
	if (key==1)
	    {
            char *args[]={"./ls",argv,NULL}; 
       	    execvp(args[0],args);
        }
	else if (key==2)
	    {
            char *args[]={"./wc",argv,NULL}; 
       	    execvp(args[0],args); 
        }
}

//executes a command when there is no redirection
void execute(char **singlecmd)
{
	if (strcmp(singlecmd[0],"ls")==0) 
        {homemade(1,singlecmd); return; }
	if (strcmp(singlecmd[0],"wc")==0)
        {homemade(2,singlecmd); return;}

    execvp(singlecmd[0],singlecmd);
	return;
}

//executes a command whenb there is redirection
void EXECUTE(char **singlecmd)
{
	int sz;
	for(int i=1;i<50;i++)
        {if (singlecmd[i]==NULL)
            {
                sz=i;
                break;
            }
        }
	int fd;
	int flag=0;
	if (sz>2)
        {
            if ((strcmp(singlecmd[sz-2],">")==0) | (strcmp(singlecmd[sz-2],">>")==0))
                {
                    redirect(singlecmd[sz-1],singlecmd[sz-2],fd);
                    singlecmd[sz-1]=NULL;
                    singlecmd[sz-2]=NULL;
                    flag=1;
                }
	    }
	execute(singlecmd);
	
	return;
	}

//function for execution of system commands, uses forks
void executeArguments(char** parsed)
{
    pid_t pid = fork();
    
    //error checking
    if (pid ==-1){
        printf("\nForking Failed");
        return;
    }
    else if(pid == 0){
        if(execvp(parsed[0],parsed)<0){
            printf("Command execution failed");
        }
        exit(1);
    }
    else{
        //wait for the child to terminate before returning
        wait(NULL);
        return;
    }
}//displays project information
void help(){
    puts("\n***CSCI4061 PROJECT 2 SHELL***"
    "\n"
    "\nFunctionality:"
    "\n>cd"
    "\n>ls"
    "\n>wc"
    "\n>exit"
    "\n>pipe handling"
    "\n>other commands point to UNIX Shell");
    return;
}

// takes in an array of arrays of strings
// removes the pipe symbol out of the array
// counts how many pipes need to be created
int separate_pipe(char*** newargs,char* * args,int size){
	int count=0;
	int cur=0;
	
	for(int i=0;i<size;i++)
         {
            if (args[i]==NULL)
                 {break;}
             if (strcmp(args[i],"|")==0)
               {   
                    i++;
                    count++;
                    cur=i;
                }
            newargs[count][i-cur]=args[i];
		}
	return count;
	}

// Builds a pipe tree. creates file descriptors
// takes in an array from seperate pipes function
void multipipe(char*** order,int order_sz){
	if (order_sz==0)
        {
            EXECUTE(order[0]);
        }
	int fd[2];
	if(pipe(fd)<0)
        {
            exit(1);
        }
	pid_t pid=fork();
	if (pid==0)
        {
            close(fd[0]);
            dup2(fd[1],1);
            multipipe(order,order_sz-1);
            close(fd[1]);
		}
	else
        {
            wait(NULL);
            close(fd[1]);
            dup2(fd[0],0);
            EXECUTE(order[order_sz]);
            close(fd[0]);
	    }
	return;
	}

int main(){
	char* dir=(char*)malloc(1000);
	getcwd(dir, 1000);
	int status=1;
  while(status) 
  {
	  getcwd(dir, 1000);
	  char* cmd=(char*)malloc(1000);
	  char *args[50];
	  char*** new=(char***)calloc(50,sizeof(char***));
	  for (int i=0;i<50;i++)
        {
            new[i]=(char**)calloc(50,sizeof(char**));
        }
      printf("[4061-shell]%s $ ",dir);
   
  fgets(cmd,100,stdin);
  
    int oldcur=0;
    for (int args_index=0;args_index<1000;args_index++)
        {
		    char* temp_args=(char*) calloc(50,sizeof(char));
            for (int cur=0;cur<1000;cur++)
                {
                    if ( (cmd[oldcur+cur]==' ') | (cmd[oldcur+cur]=='\n') )
                        {
                            args[args_index]=temp_args;
                            oldcur=oldcur+cur+1;
                            break;
                        }
                    temp_args[cur]=cmd[oldcur+cur];
                
                }		
            
            if (cmd[oldcur-1]=='\n') 
                {
                    args[args_index+1]=NULL;
                    break;
                }
        
         }
		
	if (strcmp(args[0],"cd")==0)
        {
            chdir(args[1]); 
            goto TAG;
        }
    if (strcmp(args[0], "exit") == 0)
        {
            status=0;
            goto TAG;
        }
    int numpipe =separate_pipe(new,args,50);
	
    pid_t pid = fork();
    
    //error checking
    if (pid ==-1)
        {
            printf("\nForking Failed");
        }
    else if(pid == 0)
        {
            multipipe(new,numpipe);
        }
    else
        {
        //wait for the child to terminate before returning
        wait(NULL);
        }
   
 TAG:
    for (int i=0;i<50;i++)
        { 
            if(new[i]==NULL)
                {
                    break;
                }
            free (new[i]);
        }
    for (int i=0;i<50;i++)
        { 
            if(args[i]==NULL)
                {
                    break;
                } 
            free (args[i]);
        }
	free (cmd); // frees the allocated memory for shell loop
  } 
  free (dir); // frees memory for working directory once shell has exited
  return 0;
}