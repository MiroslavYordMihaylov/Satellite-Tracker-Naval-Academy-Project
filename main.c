#include <stdio.h>
#include "ascii.h"
#include "directory_options.h"


int main_menu_options() {
    int option;
    scanf("%d", &option);

    switch (option) {
        case 1:
            menu_case1();
            case1();
            break;
        case 2:
            list_dir();
            break;
        case 3:
            printf("***IN PROGRESS***\n");
            printf("***CHOOSE ANOTHER OPTION***\n");
            main_menu_options();
            break;
        case 4:
            printf("See you soon :)");
            break;
        default:
            printf("Invalid option");
    }
}

int main(void) {
    main_menu();
    main_menu_options();

    return 0;
}


