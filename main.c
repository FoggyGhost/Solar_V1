#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include "base.h"

int main() {
    game_data g_data;
    char c;
    print_title();
    sleep(3);
    do {
        system("clear");
        printf("\033[39;1mM E N U\n\033[0m");
        printf("[ 0 ] EXIT GAME\n");
        printf("[ 1 ] NEW GAME\n");
        printf("[ 2 ] LOAD GAME\n");
        c = getch();
        printf("\r%c[2K", 27); 
        switch(c) {
            case '0': 
                return 0;
            case '1': 
                init(&g_data); 
                begin(&g_data);
                break;
            case '2': 
                load_data(&g_data); 
                begin(&g_data);
                break;
            default: 
                printf("Incorrect choice.\n");
                sleep(1);
        }
    } while(c != '0' && c != '1' && c != '2');
    begin(&g_data);
    return 0;
}





