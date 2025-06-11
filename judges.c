#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_INPUT 1024
#define REQUIRED_FIELDS 7

char judges_array[MAX_JUDGES][MAX_INPUT];

int count_fields(const char *str) {
    int count = 1;
    const char *p = str;
    while (*p) {
        if (*p == ',') count++;
        p++;
    }
    return count;
}

void trim_spaces(char *str) {
    int i, j = 0;
    char buffer[MAX_INPUT];
    for (i = 0; str[i]; i++) {
        if (!(str[i] == ' ' && str[i + 1] == ' ')) {
            buffer[j++] = str[i];
        }
    }
    buffer[j] = '\0';
    strcpy(str, buffer);
}

int main() {
    char project_name[100];
    int num_judges = 0;
    int selected_members = 0;
    int i = 0;

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");

    printf("Participating Project: ");
    fgets(project_name, sizeof(project_name), stdin);
    project_name[strcspn(project_name, "\n")] = '\0'; // Remove newline

    printf("Total Number of Judges: ");
    scanf("%d", &num_judges);

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);

    getchar(); // consume newline

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", num_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    while (i < num_judges) {
        printf("Judge %d: ", i + 1);
        fgets(judges_array[i], MAX_INPUT, stdin);
        judges_array[i][strcspn(judges_array[i], "\n")] = '\0'; // Remove newline

        if (count_fields(judges_array[i]) != REQUIRED_FIELDS) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue;
        }

        trim_spaces(judges_array[i]);
        i++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char choice;
    printf("\"Should we check the judge information?\" ");
    scanf(" %c", &choice);

    if (choice != 'Y') {
        printf("Exiting program.\n");
        return 0;
    }

    printf("\n[%s] Should we check the judge information? %c\n", project_name, choice);
    printf("####################################\n");
    printf("#        Display Judge Data        #\n");
    printf("####################################\n");

    for (i = 0; i < num_judges; i++) {
        printf("[Judge %d]\n", i + 1);
        char *token;
        int field = 0;
        char buffer[MAX_INPUT];
        strcpy(buffer, judges_array[i]);

        token = strtok(buffer, ",");

        while (token != NULL) {
            switch (field) {
                case 0: printf("Name: %s\n", token); break;
                case 1: printf("Gender: %s\n", token); break;
                case 2: printf("Affiliation: %s\n", token); break;
                case 3: printf("Title: %s\n", token); break;
                case 4: printf("Expertise: %s\n", token); break;
                case 5: printf("Email: %s\n", token); break;
                case 6: printf("Phone: %s\n", token); break;
            }
            field++;
            token = strtok(NULL, ",");
        }
        printf("-----------------------------------\n");
    }

    return 0;
}
