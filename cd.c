//trinh064 - Nam Trinh
//cunni536 - Jessica Cunningham
//carl5362 - Conrad Carlson

#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>

void cd(char* arg){
    char s[100];
	if (arg == NULL)
    {
        fprintf(stderr, "you must pass a valid path name to ""cd""\n" );
    }
    else{
        if(chdir(arg)!=0)
        {
            perror("error");
        }
    }
    printf("%s\n",arg);
    printf("%s\n", getcwd(s, 100));
    chdir(arg);
    printf("%s\n", getcwd(s, 100));
}

int main(int argc, char** argv){

	if(argc<2){
		printf("Pass the path as an argument\n");
		return 0;

	}
	cd(argv[1]);
	return 1;
}
