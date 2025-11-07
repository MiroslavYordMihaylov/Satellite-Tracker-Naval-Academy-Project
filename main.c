#include <stdio.h>
#include "ascii.c"
int menu(void){
    printf("                                        1. TRACK AN ORBITER\n");
    printf("                                        2.   MY SATELITES\n");
    printf("                                        3.      HELP\n");
}   

int main(void) {
    ascii();
    menu();

       

    return 0;
}
