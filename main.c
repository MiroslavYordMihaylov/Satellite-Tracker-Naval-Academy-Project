#include <stdio.h>
#include "ascii.h"
#include "directory_options.h"

int main_menu_options() {
    int option;
    scanf("%d", &option);

    switch (option) {
        case 1:
            menu_case1();
            new_orbiter_options();
            break;
        case 2:
            list_dir();
            break;
        case 3:
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


