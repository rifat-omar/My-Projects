#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_TRAINING 8
#define MAX_MEMBERS 4
#define NUM_TESTS 7
#define DAYS 6
#define EXERCISES 5

// -------------------- Training Status --------------------
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
char training_results[MAX_TRAINING] = {0}; // P, F, or 0

// -------------------- Member Information --------------------
char memberNames[MAX_MEMBERS][30] = {
    "Jiyeon Park", "Ethan Smith", "Helena Silva", "Liam Wilson"
};
char memberNicknames[MAX_MEMBERS][15] = {
    "Ariel", "Simba", "Belle", "Aladdin"
};

// -------------------- Fitness Data --------------------
char *testNames[NUM_TESTS] = {
    "1-Mile Run (min)", "Sprint 100m (sec)", "Push-ups 30x (min)",
    "Squats 50x (min)", "Arm Strength (min)", "Swimming 400m (min)", "Weightlifting (multiplier)"
};
float health_scores[MAX_MEMBERS][NUM_TESTS];

// -------------------- Workout Routine --------------------
char *days[DAYS] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

char *exercise_types[EXERCISES][3] = {
    {"Running", "Cycling", "Fast Walking"}, // Cardio
    {"Push-ups", "Squats", ""},             // Full-body
    {"Leg Press", "Leg Curl", ""},          // Lower-body
    {"Pull-ups", "Chin-ups", ""},           // Upper-body
    {"Plank", "Crunches", ""}               // Core
};

// Routine: member × day × exercise name
char member_routine[MAX_MEMBERS][DAYS][30];

// -------------------- Utilities --------------------
void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void displayMemberList() {
    printf("\n--- Milliways Members ---\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%d. %s (%s)\n", i + 1, memberNames[i], memberNicknames[i]);
    }
}

// -------------------- Fitness Functions --------------------
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

// -------------------- Workout Routine --------------------
void setExerciseRoutine() {
    int m, day;
    char input[30];
    displayMemberList();
    printf("Select member (1-%d): ", MAX_MEMBERS);
    scanf("%d", &m);
    m--;

    if (m < 0 || m >= MAX_MEMBERS) {
        printf("Invalid member.\n");
        return;
    }

    int coreUsed = 0;

    for (day = 0; day < DAYS; day++) {
        int valid = 0;
        printf("\n--- %s ---\n", days[day]);
        printf("Choose 2 exercises (comma-separated):\n");

        // Display available exercises
        for (int i = 0; i < EXERCISES; i++) {
            printf("%d. ", i + 1);
            for (int j = 0; j < 3 && exercise_types[i][j][0]; j++) {
                printf("%s", exercise_types[i][j]);
                if (exercise_types[i][j + 1][0]) printf(", ");
            }
            printf("\n");
        }

        char ex1[30], ex2[30];
        printf("Enter: ");
        scanf("%s,%s", ex1, ex2);

        // Validation
        int hasCardio = 0, hasStrengthOrCore = 0;
        int coreToday = 0;
        char finalRoutine[60];
        finalRoutine[0] = '\0';

        for (int e = 0; e < EXERCISES; e++) {
            for (int j = 0; j < 3 && exercise_types[e][j][0]; j++) {
                if (strcmp(ex1, exercise_types[e][j]) == 0 || strcmp(ex2, exercise_types[e][j]) == 0) {
                    if (e == 0) hasCardio = 1;
                    else if (e == 4) coreToday = 1;
                    else hasStrengthOrCore = 1;

                    strcat(finalRoutine, exercise_types[e][j]);
                    strcat(finalRoutine, " ");
                }
            }
        }

        if (!hasCardio || (!hasStrengthOrCore && !coreToday)) {
            printf("Each day must include one cardio and one strength/core exercise.\n");
            day--; continue;
        }

        if (coreToday) {
            if (coreUsed) {
                printf("Core exercises can only be used once per week.\n");
                day--; continue;
            }
            coreUsed = 1;
        }

        strcpy(member_routine[m][day], finalRoutine);
    }
    printf("Routine set for %s.\n", memberNames[m]);
}

void getExerciseRoutine() {
    char name[30];
    int found = -1;
    printf("Enter member name: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(name, memberNames[i]) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("Member not found.\n");
        return;
    }
    printf("\nWorkout Routine for %s (%s):\n", memberNames[found], memberNicknames[found]);
    for (int d = 0; d < DAYS; d++) {
        printf("%s: %s\n", days[d], member_routine[found][d]);
    }
}

// -------------------- Menu Structure --------------------
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
        printf("A. Enter Fitness Data\n");
        printf("B. View Fitness Data\n");
        printf("C. Set Basic Workout Routine\n");
        printf("D. View Basic Workout Routine\n");
        printf("Q. Return\nSelect: ");
        char input[10];
        fgets(input, sizeof(input), stdin);
        switch (toupper(input[0])) {
            case 'A': setHealth(); break;
            case 'B': getHealth(); break;
            case 'C': setExerciseRoutine(); break;
            case 'D': getExerciseRoutine(); break;
            case 'Q': return;
            default: printf("Invalid option.\n");
        }
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
        printf("Select a stage (1-8) or Q to return: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n' || toupper(input[0]) == 'Q') {
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

        if (index == 0) fitness_submenu();

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

        if (input[0] == '\n' || toupper(input[0]) == 'Q') {
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
