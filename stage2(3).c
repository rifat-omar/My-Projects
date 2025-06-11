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
int sessionProgress[MAX_MEMBERS] = {0};

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
    for (int i = 0; i < MAX_TRAINEES; i++) {
        traineeData[i][0] = parseIntMember(traineeNicknames[i]);
        traineeData[i][1] = getRandomAbility(traineeData[i][0]);
    }
    inputMentors();
    matchMentors();
}

// ---------- TRAUMA ----------
void inputTrauma() {
    while (1) {
        char nickname[15], traumaDesc[100];
        printf("Enter nickname (or Q to quit): ");
        scanf("%s", nickname);
        clear_input_buffer();
        if (toupper(nickname[0]) == 'Q') break;

        int index = findMemberIndex(nickname);
        if (index == -1) {
            printf("Nickname not found.\n");
            continue;
        }

        printf("Enter trauma description for %s: ", nickname);
        fgets(traumaDesc, sizeof(traumaDesc), stdin);
        traumaDesc[strcspn(traumaDesc, "\n")] = '\0';

        if (traumaCount >= MAX_MEMBERS) {
            printf("Max trauma entries reached.\n");
            break;
        }

        strcpy(traumaList[traumaCount].nickname, nickname);
        traumaList[traumaCount].age = 17 + index;
        strcpy(traumaList[traumaCount].trauma, traumaDesc);
        traumaCount++;
    }
}

void counselingSession() {
    if (traumaCount == 0) {
        printf("No trauma entries yet.\n");
        return;
    }

    for (int i = 0; i < traumaCount; i++) {
        printf("%d. %s\n", i + 1, traumaList[i].nickname);
    }

    int choice;
    printf("Choose a member: ");
    scanf("%d", &choice);
    clear_input_buffer();

    if (choice < 1 || choice > traumaCount) return;
    choice--;

    char *nickname = traumaList[choice].nickname;
    int answered = sessionProgress[choice];

    for (int i = answered; i < MAX_QUESTIONS && i < answered + MAX_RESPONSES; i++) {
        printf("Q: %s\n", questions[i].question);
        char response[101];
        while (1) {
            printf("Your answer: ");
            fgets(response, sizeof(response), stdin);
            if (strlen(response) > 100 || response[0] == '\n') {
                printf("Invalid. Try again.\n");
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
}

void viewCounseling() {
    char nickname[15];
    printf("Enter nickname to view: ");
    scanf("%s", nickname);
    clear_input_buffer();
    int index = findMemberIndex(nickname);
    if (index == -1) {
        printf("Nickname not found.\n");
        return;
    }

    for (int i = 0; i < traumaCount; i++) {
        if (strcmp(traumaList[i].nickname, nickname) == 0) {
            printf("Nickname: %s\nAge: %d\nTrauma: %s\n",
                   traumaList[i].nickname, traumaList[i].age, traumaList[i].trauma);
            for (int j = 0; j < MAX_QUESTIONS; j++) {
                if (counselingData[i][j].answered) {
                    printf("\nQ: %s\nA: %s\n", counselingData[i][j].question, counselingData[i][j].response);
                }
            }
            return;
        }
    }
    printf("No responses found.\n");
}

void traumaMenu() {
    char input[10];
    while (1) {
        printf("\n--- Trauma Management ---\n1. Input Trauma\n2. Counseling\n3. View Session\nQ. Back\nChoice: ");
        fgets(input, sizeof(input), stdin);
        switch (toupper(input[0])) {
            case '1': inputTrauma(); break;
            case '2': counselingSession(); break;
            case '3': viewCounseling(); break;
            case 'Q': return;
            default: printf("Invalid.\n");
        }
    }
}

// ---------- EASTER EGG ----------
typedef struct {
    char keyword[8];
    char message[300];
} EasterEgg;

EasterEgg arthurEgg = {
    "specter",
    "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. The past Arthur was a ghost of dogmatism and stubbornness."
};

void charToBinary(char c, char *bin) {
    for (int i = 7; i >= 0; i--) {
        bin[7 - i] = (c & (1 << i)) ? '1' : '0';
    }
    bin[8] = '\0';
}

int isRightChar(char *expectedReversedBin, char userChar) {
    char originalBin[9];
    char reversedBin[9];

    // Convert userChar to binary
    charToBinary(userChar, originalBin);

    // Reverse the binary string of userChar
    for (int i = 0; i < 8; i++) {
        reversedBin[i] = originalBin[7 - i];
    }
    reversedBin[8] = '\0';

    // Now compare with the already-reversed binary
    return strcmp(reversedBin, expectedReversedBin) == 0;
}


int isEasterEgg(char *input) {
    return strcmp(input, arthurEgg.keyword) == 0;
}

void find_easter_egg() {
    printf("\n<<Arthur's Easter Egg>>\n");
    char *key = arthurEgg.keyword;
    char binValues[7][9];

    for (int i = 0; i < 7; i++) {
        charToBinary(key[i], binValues[i]);
    }

    printf("Enter characters that match the reversed binary:\n");
    char input[8];

    for (int i = 6; i >= 0; i--) {
        printf("Binary %d: %s\n", 6 - i + 1, binValues[i]);
        char userChar;
        scanf(" %c", &userChar);
        clear_input_buffer();
        if (!isRightChar(binValues[i], userChar)) {
            printf("Incorrect. Try again.\n");
            i++;
            continue;
        }
        input[6 - i] = userChar;
    }
    input[7] = '\0';

    if (isEasterEgg(input)) {
        printf("\n##Easter Egg Discovered!$$\n");
        printf("%s\n", arthurEgg.message);
    } else {
        printf("Keyword mismatch.\n");
    }
}

// ---------- MAIN MENU ----------
int main() {
    char input[20];
    while (1) {
        printf("\n=== Training Stage 2 ===\n");
        printf("Enter 'Arthur' for Easter Egg or A. Mentoring, B. Trauma Management, Q. Quit\nSelect: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "Arthur") == 0) {
            find_easter_egg();
        } else {
            switch (toupper(input[0])) {
                case 'A': mentoringMenu(); break;
                case 'B': traumaMenu(); break;
                case 'Q': return 0;
                default: printf("Invalid choice.\n");
            }
        }
    }
}
