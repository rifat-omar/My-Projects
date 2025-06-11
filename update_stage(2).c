#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_TRAINEES 4
#define MAX_MENTORS 8
#define MAX_MEMBERS 4
#define MAX_RESPONSES 3
#define MAX_QUESTIONS 5

// ---------- TRAINEE INFO ----------
char traineeNames[MAX_TRAINEES][30] = {
    "Jiyeon Park", "Ethan Smith", "Helena Silva", "Liam Wilson"
};
char traineeNicknames[MAX_TRAINEES][15] = {
    "Ariel", "Simba", "Belle", "Aladdin"
};
int traineeData[MAX_TRAINEES][2]; // [ASCII sum][Ability]

// ---------- MENTOR INFO ----------
typedef struct {
    int id;
    char name[30];
    int menteeIndex;
} Mentor;
Mentor mentors[MAX_MENTORS];

// ---------- TRAUMA INFO ----------
typedef struct {
    char nickname[15];
    int age;
    char trauma[100];
} Trauma;
Trauma traumaList[MAX_MEMBERS];
int traumaCount = 0;

typedef struct {
    int id;
    char question[100];
} CounselingQuestion;

CounselingQuestion questions[MAX_QUESTIONS] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

typedef struct {
    char nickname[15];
    char question[100];
    char response[101];
    int answered;
} CounselingResponse;

CounselingResponse counselingData[MAX_MEMBERS][MAX_QUESTIONS];
int sessionProgress[MAX_MEMBERS] = {0}; // How many questions answered

// ---------- UTILITIES ----------
void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int parseIntMember(char *nickname) {
    int sum = 0;
    for (int i = 0; nickname[i]; i++) sum += (int)nickname[i];
    return sum;
}

int getRandomAbility(int seed) {
    return 100 + (int)(fmod(seed * 3.14159, 901));
}

int findMemberIndex(char *nickname) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(nickname, traineeNicknames[i]) == 0) return i;
    }
    return -1;
}

void initializeTrainees() {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int asciiSum = parseIntMember(traineeNicknames[i]);
        int ability = getRandomAbility(asciiSum);
        traineeData[i][0] = asciiSum;
        traineeData[i][1] = ability;
    }
}

// ---------- MENTORING ----------
int isMentorAssigned(int mentorId) {
    return mentors[mentorId - 1].menteeIndex != -1;
}

void inputMentors() {
    printf("\n--- Enter Mentor Information ---\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        mentors[i].id = i + 1;
        printf("Enter name for Mentor %d: ", mentors[i].id);
        scanf(" %[^\n]", mentors[i].name);
        clear_input_buffer();
        mentors[i].menteeIndex = -1;
    }
}

void matchMentors() {
    printf("\n--- Matching Mentors ---\n");
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int mentorId = (i % MAX_MENTORS) + 1;
        while (isMentorAssigned(mentorId)) {
            mentorId = (mentorId % MAX_MENTORS) + 1;
        }
        mentors[mentorId - 1].menteeIndex = i;
    }

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

void mentoringMenu() {
    initializeTrainees();
    inputMentors();
    matchMentors();
}

// ---------- TRAUMA ----------
void inputTrauma() {
    while (1) {
        char nickname[15], traumaDesc[100];
        printf("Enter nickname (or Q to quit): ");
        scanf("%s", nickname);
        if (toupper(nickname[0]) == 'Q') break;

        int index = findMemberIndex(nickname);
        (index != -1) ? printf("Enter trauma description for %s: ", nickname) :
                        printf("Nickname not found. Try again.\n");

        if (index == -1) continue;

        clear_input_buffer();
        fgets(traumaDesc, sizeof(traumaDesc), stdin);
        traumaDesc[strcspn(traumaDesc, "\n")] = '\0';

        if (traumaCount >= MAX_MEMBERS) {
            printf("Maximum trauma entries reached.\n");
            break;
        }

        strcpy(traumaList[traumaCount].nickname, nickname);
        traumaList[traumaCount].age = 17 + index; // dummy age
        strcpy(traumaList[traumaCount].trauma, traumaDesc);
        traumaCount++;
    }
}

void counselingSession() {
    printf("\n--- Members with trauma ---\n");
    for (int i = 0; i < traumaCount; i++) {
        printf("%d. %s\n", i + 1, traumaList[i].nickname);
    }

    int choice;
    printf("Select member (1-%d): ", traumaCount);
    scanf("%d", &choice);
    clear_input_buffer();
    choice--;
    if (choice < 0 || choice >= traumaCount) return;

    char *nickname = traumaList[choice].nickname;
    int answered = sessionProgress[choice];

    for (int i = answered; i < answered + MAX_RESPONSES && i < MAX_QUESTIONS; i++) {
        printf("Q%d: %s\n", questions[i].id, questions[i].question);
        char response[101];
        while (1) {
            printf("Your answer: ");
            fgets(response, sizeof(response), stdin);
            if (strlen(response) > 100 || response[0] == '\n') {
                printf("Invalid. Must be 1–100 chars.\n");
                continue;
            }
            break;
        }
        response[strcspn(response, "\n")] = '\0';
        strcpy(counselingData[choice][i].nickname, nickname);
        strcpy(counselingData[choice][i].question, questions[i].question);
        strcpy(counselingData[choice][i].response, response);
        counselingData[choice][i].answered = 1;
        sessionProgress[choice]++;
    }

    printf("Counseling complete for now.\n");
}

void viewCounseling() {
    char nickname[15];
    printf("Enter nickname to view session: ");
    scanf("%s", nickname);
    int index = findMemberIndex(nickname);
    if (index == -1) {
        printf("Nickname not found.\n");
        return;
    }

    for (int i = 0; i < traumaCount; i++) {
        if (strcmp(traumaList[i].nickname, nickname) == 0) {
            printf("\n--- Session for %s ---\n", nickname);
            printf("Age: %d\n", traumaList[i].age);
            printf("Trauma: %s\n", traumaList[i].trauma);
            for (int j = 0; j < MAX_QUESTIONS; j++) {
                if (counselingData[i][j].answered) {
                    printf("\nQ: %s\nA: %s\n",
                        counselingData[i][j].question,
                        counselingData[i][j].response);
                }
            }
            return;
        }
    }

    printf("No trauma/counseling data found for this nickname.\n");
}

void traumaMenu() {
    char input[10];
    while (1) {
        printf("\n--- Trauma Management ---\n");
        printf("1. Input Trauma\n2. Start Counseling\n3. View Session\nQ. Quit\nSelect: ");
        fgets(input, sizeof(input), stdin);

        switch (toupper(input[0])) {
            case '1': inputTrauma(); break;
            case '2': counselingSession(); break;
            case '3': viewCounseling(); break;
            case 'Q': return;
            default: printf("Invalid option.\n");
        }
    }
}

// ---------- MAIN MENU ----------
int main() {
    char input[10];
    while (1) {
        printf("\n=== Training Stage 2 ===\n");
        printf("A. Mentoring\nB. Trauma Management\nQ. Quit\nSelect: ");
        fgets(input, sizeof(input), stdin);
        switch (toupper(input[0])) {
            case 'A': mentoringMenu(); break;
            case 'B': traumaMenu(); break;
            case 'Q': return 0;
            default: printf("Invalid choice.\n");
        }
    }
}
