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

char *tle_line_1;
char *tle_line_2;

void new_orbiter_options() {
    char validate;

    printf("New orbiter? Y/N?\n");
    scanf(" %c", &validate);

    if (validate == 'y' || validate == 'Y') {
        create_option();
    } else if (validate == 'n' || validate == 'N') {
        main_menu();
        main_menu_options();
    } else {
        printf("Invalid option");
        new_orbiter_options();
    }
}

FILE *file;
char dir_name[100] = "my-orbiters";

char buffer[MAX_LINE];
char file_path[256];
char filename[100];


int create_option() {
    char data[MAX_LINE][MAX_LEN];
    char directory[PATH_MAX];
    char cwd[PATH_MAX]; // Local buffer for current directory

    // Get current working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("Failed to get current directory.\n");
        return 1;
    }


    snprintf(directory, sizeof(directory), "%s/%s", cwd, dir_name);


    if (mkdir(directory, S_IRWXU | S_IRWXG | S_IRWXO) != 0 && errno != EEXIST) {
        printf("Failed to create directory: %s\n", strerror(errno));
        return 1;
    }

    printf("Enter the name of the orbiter: ");
    scanf("%99s", filename);

    snprintf(file_path, sizeof(file_path), "%s/%s", directory, filename);

    // Try to open in read mode to check if it exists
    FILE *test_file = fopen(file_path, "r");
    if (test_file != NULL) {
        fclose(test_file); // Close the test file

        char overwrite;
        printf("Warning: '%s' already exists!\n", filename);
        printf("Overwrite? (Y/N): ");
        scanf(" %c", &overwrite);

        if (!(overwrite == 'y' || overwrite == 'Y')) {
            printf("Orbiter creation cancelled.\n");
            create_option();
            return 0;
        }
    }
    //consumes the first empty line at the start of the file
    getchar();

    snprintf(file_path, sizeof(file_path), "%s/%s", directory, filename);
    file = fopen(file_path, "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

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

    printf("Full TLE:");
    for (int i = 0; i < line; i++) {
        printf("%s", data[i]);
    }
    printf("\n");

    // Store TLE lines - use strdup to allocate memory
    tle_line_1 = strdup(data[0]);
    tle_line_2 = strdup(data[1]);

    new_orbiter();

    char validate_save;
    printf("Would you like to save this orbiter for future tracking? Y/N?\n");
    scanf(" %c", &validate_save);

    if (validate_save == 'y' || validate_save == 'Y') {
        printf("Orbiter created successfully!\n");
    } else if (validate_save == 'n' || validate_save == 'N') {
        snprintf(file_path, sizeof(file_path), "%s/%s/%s", cwd, dir_name, filename);
        if (remove(file_path) != 0) {
            perror("");
        }
    } else {
        printf("Invalid option");
        snprintf(file_path, sizeof(file_path), "%s/%s/%s", cwd, dir_name, filename);
        if (remove(file_path) != 0) {
            perror("");
        }
    }
    //Return to the main menu once you are done
    main_menu();
    main_menu_options();

    return 0;
}

int list_dir(void) {
    DIR *dir;
    struct dirent *en;
    char path[PATH_MAX];
    char cwd[PATH_MAX];

    // Get current directory
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("Failed to get current directory.\n");
        return -1;
    }

    snprintf(path, sizeof(path), "%s/%s", cwd, dir_name);

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

int delete_option() {
    char validate;
    char filename[100];
    char file_path_full[PATH_MAX];
    char cwd[PATH_MAX];

    printf("Which orbiter would you like to delete?\n");
    scanf("%s", filename);

    // Get current directory
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("Failed to get current directory.\n");
        return 1;
    }

    snprintf(file_path_full, sizeof(file_path_full), "%s/%s/%s", cwd, dir_name, filename);

    // Try to open the file to check if it exists
    FILE *test_file = fopen(file_path_full, "r");
    if (test_file == NULL) {
        printf("Orbiter '%s' does not exist.\n", filename);
        list_dir();
    }
    fclose(test_file); // Close the file since we were just checking

    printf("Are you sure you would like to delete %s? Y/N: ", filename);
    scanf(" %c", &validate);

    if (validate == 'y' || validate == 'Y') {
        if (remove(file_path_full) != 0) {
            perror("Error deleting file");
        } else {
            printf("%s deleted.\n", filename);
        }
    } else if (validate == 'n' || validate == 'N') {
        open_option();
    } else {
        printf("Invalid option\n");
        delete_option();
    }

    return 0;
}

int open_option() {
    char data[MAX_LINE][MAX_LEN];
    char file_path_full[PATH_MAX];
    char cwd[PATH_MAX];

    printf("Enter the name of the orbiter you would like to open:\n");
    scanf("%99s", filename);

    // Get current directory
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("Failed to get current directory.\n");
        return 1;
    }

    snprintf(file_path_full, sizeof(file_path_full), "%s/%s/%s", cwd, dir_name, filename);

    // Store the content of the file
    file = fopen(file_path_full, "r");

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
        "\n------------------------------------------------------------------------------------------------------------------\n");

    // Free old TLE data if it exists
    if (tle_line_1) free(tle_line_1);
    if (tle_line_2) free(tle_line_2);

    // Store new TLE data
    tle_line_1 = strdup(data[0]);
    tle_line_2 = strdup(data[1]);

    new_orbiter();

    //Return to the main menu once you are done
    main_menu();
    main_menu_options();
    return 0;
}

int new_orbiter() {
    int timer;
    printf("How many seconds would you like to predict this object for?\n");
    scanf("%d", &timer);
    printf("\n");

    // Check if TLE data exists
    if (!tle_line_1 || !tle_line_2) {
        fprintf(stderr, "TLE data not loaded!\n");
        main_menu();
        main_menu_options();
        return 1;
    }

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

    for (int i = 0; i < timer; i++) {
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

    printf("Predicted orbiter for %d seconds!\n", timer);

    // Free TLE memory after use
    if (tle_line_1) {
        free(tle_line_1);
        tle_line_1 = NULL;
    }
    if (tle_line_2) {
        free(tle_line_2);
        tle_line_2 = NULL;
    }

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
