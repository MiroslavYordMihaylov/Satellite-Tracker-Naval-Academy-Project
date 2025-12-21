#include "directory_options.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include "unistd.h"
#include <predict/predict.h>
#include <dirent.h>

#define MAX_LINE 100
char *retptr[100];

void case1() {
    char validate;

    printf("New orbiter?\nY/N:\n");
    scanf(" %c", &validate);

    if (validate == 'y' || validate == 'Y') {
        // predict();
        appendTo();

    } else if (validate == 'n' || validate == 'N') {
        main_menu();
        main_menu_options();
    }else {
        printf("Invalid option");
        case1();
    }
}

int get_dir() {

    char *retptr = getcwd(NULL, 1024);


    if (retptr == NULL)
    {

        printf("Get current working directory failed.\n");
        if (errno == ERANGE)
            printf("Path exceeds max buffer length.\n");
        else if (errno == ENOMEM)
            printf("Memory cannot be allocated for path.\n");

        return 1;
    }

    printf("Current working directory: \n\n%s\n", retptr);

    // Important: we need to free the dynamically allocated memory in the case
    // that _getcwd() was passed NULL as a first argument and dynamically
    // allocated space to store the path.
    free(retptr);

    return 0;
}

FILE *file;
char dir_name[100] = "my-orbiters";
char filename[100];
char buffer[MAX_LINE];
char file_path[256];

//Creating a new directory where the text files are created and stored
int appendTo() {


    char directory[PATH_MAX];
    snprintf(directory, sizeof(directory), "%s/%s", retptr, dir_name);
    mkdir(directory, S_IRWXU | S_IRWXG | S_IRWXO);

    get_dir();

    printf("Enter the name of the orbiter: ");
    scanf("%99s", filename);


    snprintf(file_path, sizeof(file_path), "%s/%s", dir_name, filename);
    file = fopen(file_path , "a");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    printf("File created successfully");

    printf("Enter 'quit' to exit.\n");
    do
    {
        fgets(buffer, MAX_LINE, stdin);
        if (strcmp(buffer, "quit\n") == 0)
            break;
        fputs(buffer, file);

    } while (true);
    fclose(file);

    //RETURN TO THE MAIN MENU ONCE YOU ARE DONE WITH THE FILE
    main_menu();
    main_menu_options();

    return 0;
}

int list_dir(void)
{
    DIR *dir;
    struct dirent *en;
    char path[PATH_MAX];

    snprintf(path, sizeof(path), "%s%s", retptr, dir_name);

    dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return -1;
    }

    while ((en = readdir(dir)) != NULL) {
        if (en->d_type == DT_REG) {
            printf("%s\n", en->d_name);
        }
    }

    closedir(dir);

    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("1.|CREATE| 2.|OPEN| 3.|DELETE| 4.|EXIT|\n");

    options();
    return 0;
}


int options() {
    int option;
    scanf("%d", &option);

    switch (option) {
        case 1:
            case1();
            break;
        case 2:
            open_option();
            predict();
            break;
        case 3:
            printf("***IN PROGRESS***\n");
            printf("***CHOOSE ANOTHER OPTION***\n");
            options();
            break;
        case 4:
            main_menu();
            main_menu_options();
            break;
            default:
            printf("Invalid option");
            options();
            break;

    }
    return 0;
}

int delete_option(){
    char validate;
    printf("Would you like to delete an orbiter?\nY/N:\n");
    scanf(" %c", &validate);

    if (validate == 'y' || validate == 'Y') {


    } else if (validate == 'n' || validate == 'N') {
        main_menu();
        main_menu_options();
    }else {
        printf("Invalid option");
        delete_option();
    }
    return 0;
}
int open_option() {
    FILE *fptr;
    printf("Enter the name of the orbiter you would like to open: ");
    scanf("%99s", filename);
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_name, filename);

    // Open a file in read mode
    fptr = fopen(file_path, "r");

    // Store the content of the file
    char myString[100];

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    // Read the content and store it inside myString
    fgets(myString, 100, fptr);
    // Print the file content
    printf("%s", myString);
    // Close the file
    fclose(file);
    return 0;
}
