#include <iostream>
#include "alloc.h"
//
// Created by Laptop on 4/17/2019.
//

int main() {
    alloc();
    return 0;
    //when you enter no for the provider kill both prov and reporter
    //can check how many processes are waiting for semaphore
    //man page of semctl GETNCNT returns value of semcnt
    // as the number of processes waiting for sem value
    //ipcs gives all semaphores
}

int provider(){

}

int reporter(){

}