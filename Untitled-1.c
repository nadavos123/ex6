#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char ch;
    int length = 0;
    int dynmicLength = 0+1;
    char *str = malloc(dynmicLength*sizeof(char));
    if(str==NULL){
        exit(1);
    }    
    printf("please enter:");
    ch = getchar();
    while (ch=='\n'){//if \n entered first keep asking until 
        ch=getchar();
    }
    while (ch!='\n'){
        length++;
        if(length+1>dynmicLength){
            dynmicLength*=2;
            str = realloc(str, dynmicLength*sizeof(char));
        }    
        if(str==NULL){
            exit(1);
        }
        str[length-1]=ch;
        ch = getchar();
    }
    while(length==0){
        getchar();
    }
    str[length] = '\0';
    str = realloc(str, (length+1)*sizeof(char));
    if(str==NULL){
        exit(1);  
    }      
    printf("%s",str);
    return 0;
}
