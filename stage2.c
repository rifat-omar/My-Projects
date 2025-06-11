#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_TRAINEES 4
#define MAX_MENTORS 8

// ------------------ Trainee Data -------------------
char traineeNames[MAX_TRAINEES][30] = {
    "Jiyeon Park", "Ethan Smith", "Helena Silva", "Liam Wilson"
};
char traineeNicknames[MAX_TRAINEES][15] = {
    "Ariel", "Simba", "Belle", "Aladdin"
};

int traineeData[MAX_TRAINEES][2]; // [ASCII sum][Ability]

// ------------------ Mentor Struct ------------------
typedef struct {
    int id; // 1-8
    char name[30];
    int menteeIndex; // index of trainee assigned
} Mentor;

Mentor mentors[MAX_MENTORS];

// ------------------ Utility Functions ------------------
void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int parseIntMember(char *nickname) {
    int sum = 0;
    for (int i = 0; nickname[i] != '\0'; i++) {
        sum += (int)nickname[i];
    }
    return sum;
}

int getRandomAbility(int seed) {
    // Return pseudo-random value between 100 and 1000 using seed
    return 100 + (int)(fmod(seed * 3.14159, 901));
}

void initializeTrainees() {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int asciiSum = parseIntMember(traineeNicknames[i]);
        int ability = getRandomAbility(asciiSum);
        traineeData[i][0] = asciiSum;
        traineeData[i][1] = ability;
    }
}

// ------------------ Mentor Functions ------------------
void inputMentors() {
    printf("\n--- Enter Mentor Information ---\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        mentors[i].id = i + 1;
        printf("Enter name for Mentor %d: ", mentors[i].id);
        scanf(" %[^\n]", mentors[i].name);
        clear_input_buffer();  // Fixes the invalid choice issue
        mentors[i].menteeIndex = -1; // No mentee yet
    }
}

int isMentorAssigned(int mentorId) {
    return mentors[mentorId - 1].menteeIndex != -1;
}

void matchMentors() {
    printf("\n--- Matching Mentors ---\n");

    for (int i = 0; i < MAX_TRAINEES; i++) {
        int mentorId = (i % MAX_MENTORS) + 1;

        // Check if already assigned, find next available
        while (isMentorAssigned(mentorId)) {
            mentorId = (mentorId % MAX_MENTORS) + 1;
        }

        mentors[mentorId - 1].menteeIndex = i;
    }

    // Display results
    printf("\n--- Mentoring Assignments ---\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        if (mentors[i].menteeIndex != -1) {
            int t = mentors[i].menteeIndex;
            printf("Trainee #%d (%s, %s) → Mentor ID: %d (%s)\n",
                   t + 1, traineeNames[t], traineeNicknames[t],
                   mentors[i].id, mentors[i].name);
        }
    }
}

// ------------------ Main Flow ------------------
void mentoringMenu() {
    initializeTrainees();
    inputMentors();
    matchMentors();
}

int main() {
    char input[10];
    while (1) {
        printf("\n=== Training Stage 2 Menu ===\n");
        printf("A. Mentoring\nQ. Quit\nChoose an option: ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == '\n') continue;

        switch (toupper(input[0])) {
            case 'A':
                mentoringMenu();
                break;
            case 'Q':
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}
