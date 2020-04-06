//trinh064 - Nam Trinh
//cunni536 - Jessica Cunningham
//carl5362 - Conrad Carlson

#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include<string.h>

// -l = num of lines
// -w = num of words
// -c = num of characters

int lineCounter(const char *str){
    int count = 0;
  //increments count for every time a newline is encountered
  for(int i = 0; str[i] != '\0'; i++){
        if( str[i] == '\n' ){
            count++;
    }
  }

    return count;
}

int wordCounter(const char *str){
    int count = 0;
    //Doesn't increment count for any spaces or newlines at beginning of file
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] == ' ' || str[i] == '\n'){
            i++;
    }
        else {
            break;
    }
  }
    //word counting begins where we left off skipping anything that isn't a word by counting each time there is whitespace between words
  for(int j = i; str[j] != '\0'; j++){
        if(str[j] == ' ' || str[j] == '\n'){
            count++;
            //Doesn't increment count if there is more than one space or newline in a row
      while(str[j] == ' ' || str[j] == '\n'){
                j++;
      }
    }
  }
  return count;
}

void wc(int mode, char* path){
    /*Feel free to change the templates as needed*/
    /*insert code here*/
    if (mode == 0) {
        
        if (path ==NULL) {
            
            //run wc on STDIN
        int lines = 0;
            int words = 0;
            int length = 0;
            char* pipeBuf=(char*)calloc(5000,sizeof(char*));
            
            fread(pipeBuf,4500, 1, stdin);
        
        //wc for piped input with no tag
      for (int i=0;i<5000;i++)
        {   
            if (pipeBuf[i]=='\0')
                {
                    words++; 
                    lines++;
                    break;
                } 
            if(pipeBuf[i]==' ')
                {   
                    words++;
                } 
            if(pipeBuf[i]=='\n')
                {
                    words++; 
                    lines++;
                } 
            length++;
        }

      printf("%d    %d    %d \n", lines, words, length);

            free(pipeBuf);
        }

        else {
            //run wc on input file
            int lines = 0;
            int words = 0;
            int length = 0;
            FILE *fp = NULL;
      fp = fopen(path, "r");
            //use fseek to move file pointer to end of file, then ftell to give position of file pointer which gives the total number of characters
            fseek(fp, 0, SEEK_END);
            length = ftell(fp);
            rewind(fp);
            char *buffer = calloc(1, length + 1);
            fread(buffer, length, 1, fp);
            lines = lineCounter(buffer);
      words = wordCounter(buffer);
      printf("%d    %d    %d\n", lines, words, length);
      fclose(fp);
            free(buffer);
        }
    }

    else if (mode == 1) {
        if (path == NULL) {
        
            
            //run wc on STDIN
        int lines = 0;
            int words = 0;
            int length = 0;
            char* pipeBuf=(char*)calloc(5000,sizeof(char*));
            
            fread(pipeBuf,4500, 1, stdin);
            
        for (int i=0;i<5000;i++)
            {
                if (pipeBuf[i]=='\0')
                    {
                        words++; 
                        lines++;
                        break;
                    } 
                if(pipeBuf[i]==' ')
                    {   
                        words++;
                    } 
                if(pipeBuf[i]=='\n')
                    {
                        words++; 
                        lines++;
                    } 
                length++;
            }
      printf("%d   \n", lines);
            free(pipeBuf);
        }

        else {
            //run wc -l on input file
            int lines = 0;
            int length = 0;
            FILE *fp = NULL;
      fp = fopen(path, "r");
            //use fseek to move file pointer to end of file, then ftell to give position of file pointer which gives the total number of characters
            fseek(fp, 0, SEEK_END);
            length = ftell(fp);
            rewind(fp);
            char *buffer = calloc(1, length + 1);
            fread(buffer, length, 1, fp);
            lines = lineCounter(buffer);
            printf("%d\n", lines);
      fclose(fp);
            free(buffer);
        }
    }

    else if (mode == 2) {
        if (path == NULL) {
            //run wc -w on STDIN
        
            
            //run wc on STDIN
        int lines = 0;
            int words = 0;
            int length = 0;
            char* pipeBuf=(char*)calloc(5000,sizeof(char*));
            
            fread(pipeBuf,4500, 1, stdin);
        
            
        for (int i=0;i<5000;i++)
            {
                if (pipeBuf[i]=='\0')
                    {
                        words++; 
                        lines++;
                        break;
                    } 
                if(pipeBuf[i]==' ')
                    {   
                        words++;
                    } 
                if(pipeBuf[i]=='\n')
                    {
                        words++; 
                        lines++;
                    } 
                length++;
            }
      printf("%d   \n", lines);
            free(pipeBuf);
        }

        else {
            //run wc -w on input file
            int words = 0;
            int length = 0;
            FILE *fp = NULL;
      fp = fopen(path, "r");
            //use fseek to move file pointer to end of file, then ftell to give position of file pointer which gives the total number of characters
            fseek(fp, 0, SEEK_END);
            length = ftell(fp);
            rewind(fp);
            char *buffer = calloc(1, length + 1);
            fread(buffer, length, 1, fp);
      words = wordCounter(buffer);
            printf("%d\n", words);
      fclose(fp);
            free(buffer);
        }
    }

    else if (mode == 3) {
        if (path == NULL) {
            
            //run wc on STDIN
        int lines = 0;
            int words = 0;
            int length = 0;
            char* pipeBuf=(char*)calloc(5000,sizeof(char*));
            
            fread(pipeBuf,4500, 1, stdin);
        
            
        for (int i=0;i<5000;i++)
            {
                if (pipeBuf[i]=='\0')
                    {
                        words++; 
                        lines++;
                        break;
                    } 
                if(pipeBuf[i]==' ')
                    {   
                        words++;
                    } 
                if(pipeBuf[i]=='\n')
                    {
                        words++; 
                        lines++;
                    } 
                length++;
            }
      printf("%d   \n", lines);
            free(pipeBuf);
        }

        else {
            //run wc -c on input file
            int length = 0;
            FILE *fp = NULL;
            fp = fopen(path, "r");
            //use fseek to move file pointer to end of file, then ftell to give position of file pointer which gives the total number of characters
            fseek(fp, 0, SEEK_END);
            length = ftell(fp);
            rewind(fp);
            printf("%d\n", length);
            fclose(fp);
        }
    }
return;
}

int main(int argc, char** argv){
   
    if(argc>2){
        if(strcmp(argv[1], "-l") == 0) {
            wc(1, argv[2]);
        }
        else if(strcmp(argv[1], "-w") == 0) {
            wc(2, argv[2]);
        }
        else if(strcmp(argv[1], "-c") == 0) {
            wc(3, argv[2]);
        }
        else {
            printf("Invalid arguments\n");
        }
        return 0;
    }
    else if (argc==2){
        if (strcmp(argv[1],"")==0){wc(0,NULL);return 0;}
         if(strcmp(argv[1], "-l") == 0) {
            wc(1, NULL);
        }
        else if(strcmp(argv[1], "-w") == 0) {
            wc(2, NULL);
        }
        else if(strcmp(argv[1], "-c") == 0) {
            wc(3, NULL);
        }
        else {
            wc(0, argv[1]);
        }
      return 0;
      }
    return 0;
}
