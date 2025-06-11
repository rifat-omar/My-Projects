#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_TRAINING 8
#define MAX_MEMBERS 4
#define NUM_TESTS 7

char training_names[MAX_TRAINING][50] = {
    "Physical Strength & Knowledge",
    "Self-Management & Teamwork",
    "Language & Pronunciation",
    "Vocal",
    "Dance",
    "Visual & Image",
    "Acting & Stage Performance",
    "Fan Communication"
};

char training_results[MAX_TRAINING] = {0}; // 'P' for pass, 'F' for fail, 0 for not attempted

// Members and nicknames from Miliways.c
char memberNames[MAX_MEMBERS][30] = {
    "Jiyeon Park", "Ethan Smith", "Helena Silva", "Liam Wilson"
};
char memberNicknames[MAX_MEMBERS][15] = {
    "Ariel", "Simba", "Belle", "Aladdin"
};

// Fitness test labels
char *testNames[NUM_TESTS] = {
    "1-Mile Run (min)", "Sprint 100m (sec)", "Push-ups 30x (min)",
    "Squats 50x (min)", "Arm Strength (min)", "Swimming 400m (min)", "Weightlifting (multiplier)"
};

// Fitness scores per member
float health_scores[MAX_MEMBERS][NUM_TESTS];

// Helper to clear buffer
void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Fitness parsing
void parseFitnessInput(int memberIndex, char input[]) {
    int i = 0, testIndex = 0;
    char temp[10];
    int tempIndex = 0;

    while (input[i] != '\0' && testIndex < NUM_TESTS) {
        if (input[i] == ',' || input[i + 1] == '\0') {
            if (input[i + 1] == '\0' && input[i] != ',') {
                temp[tempIndex++] = input[i];
            }
            temp[tempIndex] = '\0';
            sscanf(temp, "%f", &health_scores[memberIndex][testIndex]);
            testIndex++;
            tempIndex = 0;
        } else {
            temp[tempIndex++] = input[i];
        }
        i++;
    }
}

void setHealth() {
    char input[100];
    printf("\n=== Enter Fitness Data ===\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("Enter data for %s (%s) as comma-separated values:\n", memberNames[i], memberNicknames[i]);
        printf("Format: 1Mile, Sprint, PushUps, Squats, Arm, Swim, Weight\n> ");
        scanf(" %[^\n]", input);
        parseFitnessInput(i, input);
    }
    printf("Fitness data recorded.\n");
}

void getHealth() {
    int option;
    char nickname[15];
    int memberIndex = -1;

    printf("\n=== View Fitness Data ===\n");
    printf("1. Show all data\n2. Member's full data\n3. Specific test for a member\nSelect: ");
    scanf("%d", &option);

    if (option == 1) {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            printf("\nName: %s | Nickname: %s\n", memberNames[i], memberNicknames[i]);
            for (int j = 0; j < NUM_TESTS; j++) {
                printf("%s: %.2f\n", testNames[j], health_scores[i][j]);
            }
        }
    } else if (option == 2 || option == 3) {
        printf("Enter member nickname: ");
        scanf("%s", nickname);

        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(nickname, memberNicknames[i]) == 0) {
                memberIndex = i;
                break;
            }
        }

        if (memberIndex == -1) {
            printf("Nickname not found.\n");
            return;
        }

        if (option == 2) {
            printf("\nName: %s | Nickname: %s\n", memberNames[memberIndex], memberNicknames[memberIndex]);
            for (int j = 0; j < NUM_TESTS; j++) {
                printf("%s: %.2f\n", testNames[j], health_scores[memberIndex][j]);
            }
        } else {
            int testNum;
            for (int j = 0; j < NUM_TESTS; j++) {
                printf("%d. %s\n", j + 1, testNames[j]);
            }
            printf("Choose test number: ");
            scanf("%d", &testNum);

            if (testNum >= 1 && testNum <= NUM_TESTS) {
                printf("%s's %s result: %.2f\n", memberNames[memberIndex],
                       testNames[testNum - 1], health_scores[memberIndex][testNum - 1]);
            } else {
                printf("Invalid test number.\n");
            }
        }
    } else {
        printf("Invalid option.\n");
    }
}

// Original logic
int check_stage_completed(int index) {
    return training_results[index] == 'P';
}

int all_early_stages_completed() {
    return check_stage_completed(0) && check_stage_completed(1);
}

void evaluate_training(int index) {
    char input[10];
    printf("Would you like to enter the evaluation result? (Y/N): ");
    fgets(input, sizeof(input), stdin);
    if (toupper(input[0]) == 'Y') {
        printf("Did you complete the training and pass the certification? (P/F): ");
        fgets(input, sizeof(input), stdin);
        if (toupper(input[0]) == 'P') {
            training_results[index] = 'P';
            printf("Training step %d passed.\n", index + 1);
        } else {
            training_results[index] = 'F';
            printf("Training step %d failed.\n", index + 1);
        }
    }
}

void fitness_submenu() {
    int sub;
    while (1) {
        printf("\n--- Fitness Tracking Menu ---\n");
        printf("1. Enter Fitness Data\n");
        printf("2. View Fitness Data\n");
        printf("0. Return to Training Menu\nSelect: ");
        scanf("%d", &sub);
        clear_input_buffer();

        if (sub == 0) break;
        else if (sub == 1) setHealth();
        else if (sub == 2) getHealth();
        else printf("Invalid option.\n");
    }
}

void training_menu() {
    int i;
    char input[10];
    while (1) {
        printf("\n--- TRAINING MENU ---\n");
        for (i = 0; i < MAX_TRAINING; i++) {
            printf("%d. %s [%c]\n", i + 1, training_names[i],
                   training_results[i] ? training_results[i] : ' ');
        }
        printf("Select a stage (1-8) or enter Q to return: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n' || toupper(input[0]) == 'Q' || input[0] == '0') {
            break;
        }

        int choice = input[0] - '0';
        if (choice < 1 || choice > 8) {
            printf("Invalid selection.\n");
            continue;
        }

        int index = choice - 1;

        if (training_results[index] == 'P') {
            printf("Stage %d has already been completed.\n", choice);
            continue;
        }

        if (index == 0) {
            // Special Fitness Feature
            fitness_submenu();
        }

        // Restriction logic
        if (index == 1 && !check_stage_completed(0)) {
            printf("You must complete Stage 1 first.\n");
            continue;
        } else if (index > 1 && !all_early_stages_completed()) {
            printf("You must complete Stage 1 and 2 before accessing this stage.\n");
            continue;
        }

        evaluate_training(index);
    }
}

void audition_management() {
    printf("\n[AUDITION MANAGEMENT]\n- Feature under construction.\n");
}

void debut_management() {
    printf("\n[DEBUT MANAGEMENT]\n- Feature under construction.\n");
}

void main_menu() {
    char input[10];
    while (1) {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Audition Management\n");
        printf("2. Training\n");
        printf("3. Debut\n");
        printf("Enter your choice (1-3) or Q to quit: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n' || input[0] == '0' || toupper(input[0]) == 'Q') {
            printf("Exiting program...\n");
            break;
        }

        switch (input[0]) {
            case '1': audition_management(); break;
            case '2': training_menu(); break;
            case '3': debut_management(); break;
            default: printf("Invalid option. Please try again.\n");
        }
    }
}

int main() {
    main_menu();
    return 0;
}
