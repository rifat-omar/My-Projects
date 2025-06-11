#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_QUESTIONS 10
#define MAX_TRAINEES 4
#define QUIZ_SIZE 5
#define PASS_SCORE 80

// ---------- Struct Definitions ----------
typedef struct {
    int id;
    char question[100];
    char answer[50];
} Question;

typedef struct {
    int id;
    char result; // 'O' or 'X'
} Answer;

typedef struct {
    char name[30];
    char nickname[15];
    char nationality[20];
    int score;
    char passed[5]; // "PASS" or "FAIL"
} Trainee;

// ---------- Global Variables ----------
Question questionBank[MAX_QUESTIONS] = {
    {1, "What is 'Hello' in Korean?", "Annyeong"},
    {2, "What is 'Thank you' in Korean?", "Gamsahamnida"},
    {3, "What is 'Yes' in Korean?", "Ne"},
    {4, "What is 'No' in Korean?", "Aniyo"},
    {5, "What is 'I love you' in Korean?", "Saranghae"},
    {6, "What is 'Sorry' in Korean?", "Mianhamnida"},
    {7, "What is 'Delicious' in Korean?", "Masisseoyo"},
    {8, "What is 'Goodbye' in Korean?", "Annyeonghi gaseyo"},
    {9, "What is 'Please' in Korean?", "Juseyo"},
    {10, "What is 'Excuse me' in Korean?", "Shillehamnida"}
};

Trainee trainees[MAX_TRAINEES] = {
    {"Jiyeon Park", "Ariel", "Korean", 0, ""},
    {"Ethan Smith", "Simba", "USA", 0, ""},
    {"Helena Silva", "Belle", "Brazil", 0, ""},
    {"Liam Wilson", "Aladdin", "Canada", 0, ""}
};

Answer answerSheet[QUIZ_SIZE];

// ---------- Function Declarations ----------
int selectRandomTaker();
void serveRandomQuiz(int traineeIndex);
void delaySeconds(int sec);
void toUpperCase(char *str);

// ---------- Main Quiz Function ----------
void testKoreanLang() {
    srand(time(NULL));
    int takerIndex = selectRandomTaker();
    if (takerIndex == -1) return;
    serveRandomQuiz(takerIndex);
}

int selectRandomTaker() {
    int hour = time(NULL) % MAX_TRAINEES;
    int attempts = 0;
    while (strcmp(trainees[hour].nationality, "Korean") == 0) {
        hour = (hour + 1) % MAX_TRAINEES;
        if (++attempts > MAX_TRAINEES) {
            printf("No eligible trainee for the quiz.\n");
            return -1;
        }
    }
    printf("Welcome, %s, to the Korean quiz session!\n", trainees[hour].name);
    return hour;
}

void delaySeconds(int sec) {
    time_t start = time(NULL);
    while (time(NULL) - start < sec);
}

void serveRandomQuiz(int traineeIndex) {
    int asked[QUIZ_SIZE] = {0};
    int score = 0;

    printf("Quiz will begin in 30 seconds. Please wait...\n");
    delaySeconds(1); // Use 1 for demo instead of 30

    for (int i = 0; i < QUIZ_SIZE; ) {
        int qid = rand() % MAX_QUESTIONS;
        int alreadyAsked = 0;
        for (int j = 0; j < i; j++) {
            if (asked[j] == qid) {
                alreadyAsked = 1;
                break;
            }
        }
        if (alreadyAsked) continue;

        asked[i] = qid;
        printf("Q%d: %s\n> ", i + 1, questionBank[qid].question);

        char userAnswer[50];
        fgets(userAnswer, sizeof(userAnswer), stdin);
        userAnswer[strcspn(userAnswer, "\n")] = '\0';

        answerSheet[i].id = questionBank[qid].id;
        toUpperCase(userAnswer);
        toUpperCase(questionBank[qid].answer);

        if (strcmp(userAnswer, questionBank[qid].answer) == 0) {
            answerSheet[i].result = 'O';
            score += 20;
        } else {
            answerSheet[i].result = 'X';
        }
        i++;
    }

    // Update trainee struct
    trainees[traineeIndex].score = score;
    strcpy(trainees[traineeIndex].passed, score >= PASS_SCORE ? "PASS" : "FAIL");

    // Print results
    printf("\n--- Answer Sheet ---\n");
    for (int i = 0; i < QUIZ_SIZE; i++) {
        printf("Q%d: %c\n", answerSheet[i].id, answerSheet[i].result);
    }
    printf("Total Score: %d\nStatus: %s\n",
           trainees[traineeIndex].score,
           trainees[traineeIndex].passed);
}

void toUpperCase(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = toupper(str[i]);
        }
    }
}

// ---------- Main Entry ----------
int main() {
    char input;
    while (1) {
        printf("\n--- Language & Pronunciation Training ---\n");
        printf("A. Korean Quiz\nQ. Quit\nSelect: ");
        scanf(" %c", &input);
        getchar();

        switch (toupper(input)) {
            case 'A': testKoreanLang(); break;
            case 'Q': return 0;
            default: printf("Invalid option.\n");
        }
    }
}
