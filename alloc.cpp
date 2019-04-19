#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include "alloc.h"
#include <string.h>
#include <stdlib.h>

using namespace std;

//
// Created by Laptop on 4/17/2019.
//

int alloc() {
    int height = 10;
    int width = 3;
    char rez[height][width];
    int type;
    int amountOfUnits;

    //size_t pagesize = getpagesize();
    size_t size = getFileSize("res.txt");
    int fd = open("res.txt", O_RDWR, 0);
    assert(fd != -1);

    /* shared memory file descriptor */


    size_t textsize = sizeof(rez);


    if (lseek(fd, textsize - 1, SEEK_SET) == -1) {
        close(fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
    }
    char *map = (char *) mmap(NULL, textsize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, fd, 0);
    assert(map != MAP_FAILED);

//    void *region = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, fd, 0);
//    assert(region != MAP_FAILED);


    int type0Amount = 2;
    int type1Amount = 6;
    int type2Amount = 10;
    int type3Amount = 14;
    int type4Amount = 18;

    //printf("%c",map[10]);
    int arrAmountIndexes[] = {type0Amount,type1Amount,type2Amount,type3Amount,type4Amount};

    //Write the mmapped data to stdout (= FD #1)
    write(1, map, textsize);
    printf("how many juice boxes you want kiddo?(type unit-type unit-amount)");
    while (cin >> type >> amountOfUnits) {

        char first = '0' + amountOfUnits;
        char zero = '0' + 0;
        char negativeOne = '0' + -1;
        if(type == -1){
            break;
        }
        if(map[arrAmountIndexes[type]] - amountOfUnits < '0' ) {
            printf("Error this will result in less then zero resources. Did not reserve.\n");
        }else{
            map[arrAmountIndexes[type]] = map[arrAmountIndexes[type]] - amountOfUnits;
        }
        printf("how many juice boxes you want kiddo?(type unit-type unit-amount)");

        msync(map,textsize,MS_SYNC);
        write(1, map, textsize);
    }


    //Cleanup

    int rc = munmap((void*)map, textsize);
    assert(rc == 0);
    close(fd);
    exit(0);
    return 0;
}

size_t getFileSize(const char *filename) {
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}