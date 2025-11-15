#include <stdio.h>

void ascii(void) {
    static const char* banner =
        "            _       _ _ _         _                  _    _                             _                 \n"
        "           | |     | (_) |       | |                | |  (_)                           | |                \n"
        "  ___  __ _| |_ ___| |_| |_ ___  | |_ _ __ __ _  ___| | ___ _ __   __ _   ___ _   _ ___| |_ ___ _ __ ___  \n"
        " / __|/ _` | __/ _ \\ | | __/ _ \\ | __| '__/ _` |/ __| |/ / | '_ \\ / _` | / __| | | / __| __/ _ \\ '_ ` _ \\ \n"
        " \\__ \\ (_| | ||  __/ | | ||  __/ | |_| | | (_| | (__|   <| | | | | (_| | \\__ \\ |_| \\__ \\ ||  __/ | | | | |\n"
        " |___/\\__,_|\\__\\___|_|_|\\__\\___|  \\__|_|  \\__,_|\\___|_|\\_\\_|_| |_|\\__, | |___/\\__, |___/\\__\\___|_| |_| |_|\n"
        "                                                                   __/ |       __/ |                      \n"
        "                                                                  |___/       |___/                       \n";
    printf("%s", banner);
    printf("Welcome to the SATELITE TRACKING SYSTEM. A terminal app which allows you to track the location of any orbiter\n");
    printf("\n");

}

int menu(void){
    printf("                                        1. TRACK AN ORBITER\n");
    printf("                                        2.   MY SATELITES\n");
    printf("                                        3.      HELP\n");
    return 0;
}

int main(void) {
    ascii();
    menu();

    return 0;
}


