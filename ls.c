//trinh064 - Nam Trinh
//cunni536 - Jessica Cunningham
//carl5362 - Conrad Carlson

#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include <stdbool.h>
#include <dirent.h>
 

void ls(char *path, bool recurse_flag) {
	 if (path==NULL)
        {printf("No path!"); return;}
	 struct dirent **namelist;
           int n;
           n = scandir(path, &namelist, NULL, alphasort);
           if (n == -1) {
               return;
           }
            if (n == 2) {
			printf("%s \n\n",path);
               return;
           }    
           printf("%s \n",path);
          for (int i=2;i<n;i++) {
               printf("%s  ",namelist[i]->d_name);
            
           }
           printf("\n\n");
           if (!recurse_flag){return;}
          // recursively find file names in the directory and its sub directories
          for (int i=2;i<n;i++) {
			  char  childpath[300];
			  sprintf(childpath,"%s/%s",path,namelist[i]->d_name);
			  free(namelist[i]);
			  ls(childpath, recurse_flag);
			  }
        free(namelist);
	return;
}

int main(int argc, char *argv[])
{
	if(argc < 2)
		{ // No -R flag and no path name
			ls(NULL, false);
		} 
	
	else if(strcmp(argv[1], "-R") == 0) 
		{
			if(argc == 2) 
				{ // only -R flag
					ls(NULL, true);
				} 
			else{ // -R flag with some path name
				ls(argv[2], true);
				}
		}
	else { // no -R flag but path name is given
    	ls(argv[1], false);
  }
	return 0;
}
