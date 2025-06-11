#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TRAINING 8

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

void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void audition_management() {
    printf("\n[AUDITION MANAGEMENT]\n- Feature under construction.\n");
}

void debut_management() {
    printf("\n[DEBUT MANAGEMENT]\n- Feature under construction.\n");
}

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

        // Restriction logic
        if (index == 0 || index == 1) {
            if (index == 1 && !check_stage_completed(0)) {
                printf("You must complete Stage 1 first.\n");
                continue;
            }
        } else if (!all_early_stages_completed()) {
            printf("You must complete Stage 1 and 2 before accessing this stage.\n");
            continue;
        }

        evaluate_training(index);
    }
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
            case '1':
                audition_management();
                break;
            case '2':
                training_menu();
                break;
            case '3':
                debut_management();
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

int main() {
    main_menu();
    return 0;
}
