#include <stdio.h>
#include <stdlib.h>

void clear_screen() {
    printf("\033[H\033[J"); // ANSI escape code to clear screen
}

void display_splash_screen(const char *name, const char *date) {
    clear_screen();
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) printf("*"); // Left triangle
        for (int j = 0; j < 90; j++) printf(" ");
        for (int j = 5 - i; j > 0; j--) printf("*"); // Right triangle
        printf("\n");
    }
    printf("                                        [Magrathea ver 0.1]                              \n");
    printf("          Magrathea, where a shining planet is created in a wasteland with no grass,     \n");
    printf("  a place where unseen potential is discovered and gems are polished by the hands of experts, \n");
    printf("                                       Welcome to Magrathea.                             \n");
    for (int i = 5; i > 0; i--) {
        for (int j = i; j > 0; j--) printf("*"); // Left inverted triangle
        for (int j = 0; j < 90; j++) printf(" ");
        for (int j = 6 - i; j > 0; j--) printf("*"); // Right inverted triangle
        printf("\n");
    }
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[User]: %s                                   [Execution Time]: %s\n", name, date);
    printf("=============================================================================================================\n");
}

int main() {
    char name[50], date[11];
    printf("[Please enter the current date in the \"yyyy-mm-dd\" format]: ");
    scanf("%10s", date);
    printf("[Please enter your name]: ");
    scanf("%49s", name);
    
    printf("**The input has been processed successfully.**\n");
    for (volatile int i = 0; i < 300000000; i++); // Simple delay without including sleep.h
    
    display_splash_screen(name, date);
    return 0;
}
