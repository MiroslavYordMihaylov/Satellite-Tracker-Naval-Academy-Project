#include "directory_options.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include "unistd.h"
#include <predict/predict.h>
#include <dirent.h>
#include <math.h>

#define MAX_LINE 100
#define MAX_LEN 1000
char *retptr[100];

char *tle_line_1;
char *tle_line_2;

void new_orbiter_options() {
    char validate;

    printf("New orbiter?\nY/N:\n");
    scanf(" %c", &validate);

    if (validate == 'y' || validate == 'Y') {
        appendTo();
    } else if (validate == 'n' || validate == 'N') {
        main_menu();
        main_menu_options();
    } else {
        printf("Invalid option");
        new_orbiter_options();
    }
}

int get_dir() {
    char *retptr = getcwd(NULL, 1024);


    if (retptr == NULL) {
        printf("Get current working directory failed.\n");
        if (errno == ERANGE)
            printf("Path exceeds max buffer length.\n");
        else if (errno == ENOMEM)
            printf("Memory cannot be allocated for path.\n");

        return 1;
    }

    // printf("Current working directory: \n\n%s\n", retptr);

    // Important: we need to free the dynamically allocated memory in the case
    // that _getcwd() was passed NULL as a first argument and dynamically
    // allocated space to store the path.
    free(retptr);

    return 0;
}

FILE *file;
char dir_name[100] = "my-orbiters";

char buffer[MAX_LINE];
char file_path[256];
char filename[100];

//Creating a new directory where the text files are created and stored
int appendTo() {
    char data[MAX_LINE][MAX_LEN];
    char directory[PATH_MAX];


    snprintf(directory, sizeof(directory), "%s/%s", retptr, dir_name);
    mkdir(directory, S_IRWXU | S_IRWXG | S_IRWXO);
    mkdir(directory, S_IRWXU | S_IRWXG | S_IRWXO);

    get_dir();

    printf("Enter the name of the orbiter: ");
    scanf("%99s", filename);
    //consumes the first empty line at the start of the file
    getchar();


    snprintf(file_path, sizeof(file_path), "%s/%s", dir_name, filename);
    file = fopen(file_path, "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    printf("Orbiter created successfully!\n");

    int count = 0;

    do {
        if (count == 0)
            printf("TLE1:\n");
        else if (count == 1)
            printf("TLE2:\n");

        fgets(buffer, MAX_LINE, stdin);

        fputs(buffer, file);
        count++;
    } while (count < 2);


    fclose(file);

    file = fopen(file_path, "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    int line = 0;

    while (!feof(file) && !ferror(file))
        if (fgets(data[line], MAX_LEN, file) != NULL) {
            line++;
        }

    fclose(file);

    // Print out all the rows of our 2D array that were used to store a line from
    // the file, as indicated by 'line' which lets us know how many lines we've
    // read from the file.

    for (int i = 0; i < line; i++) {
        printf("%s", data[i]);
    }
    tle_line_1 = data[0];
    tle_line_2 = data[1];

    new_orbiter();

    //RETURN TO THE MAIN MENU ONCE YOU ARE DONE WITH THE FILE
    main_menu();
    main_menu_options();

    return 0;
}

int list_dir(void) {
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

    printf(
        "------------------------------------------------------------------------------------------------------------------\n");
    printf("1.|CREATE| 2.|OPEN| 3.|DELETE| 4.|EXIT|\n");

    options();
    return 0;
}


int options() {
    int option;
    scanf("%d", &option);

    switch (option) {
        case 1:
            new_orbiter_options();
            break;
        case 2:
            open_option();
            break;
        case 3:
            delete_option();
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

int delete_option() {
    char validate;
    char filename[100];
    printf("Which orbiter would you like to delete?\n");
    scanf("%s", filename);

    printf("Are you sure you would like to delete%s? Y/N", filename);
    scanf(" %c", &validate);

    if (validate == 'y' || validate == 'Y') {
        snprintf(file_path, sizeof(file_path), "%s/%s", dir_name, filename);
        if (remove(file_path) != 0) {
            // if there was an error, output the error number and message
            fprintf(stderr, "Errno: %d\n", errno);
            perror("Error msg");

            // if to delete was successful, inform the user the file was deleted
        } else printf("%s deleted.\n", filename);
        main_menu();
        main_menu_options();
    } else if (validate == 'n' || validate == 'N') {
        open_option();
    } else {
        printf("Invalid option");
        delete_option();
    }
    return 0;
}


int open_option() {
    char data[MAX_LINE][MAX_LEN];

    printf("Enter the name of the orbiter you would like to open: ");
    scanf("%99s", filename);
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_name, filename);

    // Open a file in read mode

    // Store the content of the file
    file = fopen(file_path, "r");

    if (file == NULL) {
        printf("There is no such orbiter.\n");
        open_option();
    }
    int line = 0;

    while (!feof(file) && !ferror(file))
        if (fgets(data[line], MAX_LEN, file) != NULL) {
            line++;
        }


    fclose(file);

    // Print out all the rows of our 2D array that were used to store a line from
    // the file, as indicated by 'line' which lets us know how many lines we've
    // read from the file.

    printf(
        "--------------------------------------------------------TLE--------------------------------------------------------\n");
    for (int i = 0; i < line; i++) {
        printf("%s", data[i]);
    }
    printf(
        "------------------------------------------------------------------------------------------------------------------\n");
    tle_line_1 = data[0];
    tle_line_2 = data[1];


    new_orbiter();
    return 0;
}


int new_orbiter() {
    // Create orbit object
    predict_orbital_elements_t *iss = predict_parse_tle(tle_line_1, tle_line_2);
    if (!iss) {
        fprintf(stderr, "Failed to initialize orbit from tle!");
        exit(1);
    }

    // Create observer object
    predict_observer_t *obs = predict_create_observer("Me", 63.9 * M_PI / 180.0, 10.9 * M_PI / 180.0, 0);
    if (!obs) {
        fprintf(stderr, "Failed to initialize observer!");
        exit(1);
    }

    while (true) {
        printf("%s\n", filename);

        predict_julian_date_t curr_time = predict_to_julian(time(NULL));

        // Predict
        struct predict_position iss_orbit;
        predict_orbit(iss, &iss_orbit, curr_time);
        printf("lat=%f, lon=%f, alt=%f\n", iss_orbit.latitude * 180.0 / M_PI, iss_orbit.longitude * 180.0 / M_PI,
               iss_orbit.altitude);

        // Observe
        struct predict_observation iss_obs;
        predict_observe_orbit(obs, &iss_orbit, &iss_obs);
        printf("azi=%f (rate: %f), ele=%f (rate: %f)\n", iss_obs.azimuth * 180.0 / M_PI,
               iss_obs.azimuth_rate * 180.0 / M_PI, iss_obs.elevation * 180.0 / M_PI,
               iss_obs.elevation_rate * 180.0 / M_PI);

        // Apparent elevation
        double apparent_elevation = predict_apparent_elevation(iss_obs.elevation);
        printf("Apparent elevation: %.2f\n\n", apparent_elevation * 180.0 / M_PI);

        //Sleep
        fflush(stdout);
        usleep(1000000);
    }


    // Free memory
    predict_destroy_orbital_elements(iss);
    predict_destroy_observer(obs);

    main_menu_options();
    main_menu();

    return 0;
}


