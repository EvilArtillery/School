#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char* type;
static int check_type(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf){
    if(FTW_D == tflag) return 0;
    
    char* pos = strrchr(fpath, '.');
    if(NULL == pos){
        return 0;
    }

    if(0 == strcmp(pos, type)){
        printf("\x1b[93m%-40s\x1b[0m\n", fpath);
    }
    
    return 0;
}


int main(int argc, char *argv[]){
    if (argc > 3){
        printf("\x1b[91mError! Too much arguments!\x1b[0m\n");
        return 0;
    }
    if (argc < 3){
        printf("\x1b[91mError! Too few arguments!\x1b[0m\n");
        return 0;
    }

    type = malloc(sizeof(char) * strlen(argv[2]));
    if(!sscanf(argv[2], "%s", type)){
        printf("\x1b[91mError!\x1b[0m\n");
        return -1;
    }


    if (nftw(argv[1], check_type, 20, 0) == -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
    return 1;
}