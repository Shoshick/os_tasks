#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main(){
    printf("Real User ID = %d\n", getuid());
    printf("Effective User ID = %d\n\n", geteuid());
    FILE *fp;
    if((fp=fopen("file.txt", "r"))==NULL){
        perror("You do not have permission to read this file\n");
        return 0;
    }
    fclose(fp);
    return 0;
}