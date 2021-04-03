#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_CO 4
#define MIN_CO 0
#define CATCH(c) {\
    fflush(stdin);\
    do {\
        choice = getch();\
    } while (choice != c);\
    printf("\r%c[2K", 27);\
    printf("\033[A\33[2K");\
}
#define CATCHM(a, b) {\
    fflush(stdin);\
    do {\
        choice = getch();\
    } while (choice != a && choice != b);\
    printf("\r%c[2K", 27);\
    printf("\033[A\33[2K");\
}

// lokacja postaci
typedef enum {
    House,
    Museum,
    Garden
} location; 

// wizerunek; sposob, w jaki postac jest postrzegana przez inne postacie w grze
typedef enum {
    Mean,
    Neutral,
    Kind
} image;

// wynik gry
typedef enum {
    NF, // nieukonczona
    LOST,  // przegrana
    WON   // wygrana
} result;

// dane gry (do zapisu)
typedef struct {
    char name[30];
    int player_points;
    int current_x;
    int current_y;
    image chara_image;
    double progress;
    result game_result;
} game_data;

// deklaracje funkcji
void print_title();
void print_action(char*);
char getch();
void type_out(char*);
void to_buffer(char*, char*, char*);
void save_data(game_data*);
void load_data(game_data*);
void init(game_data*);
void begin(game_data *);
void change_points_value(game_data*, int);
void move_around(game_data*, char);
void print_destination(int, int, int, int);
void wait();
void reset_cp(bool*);
void follow_compass(game_data*, int, int);

// deklaracje lokacji
void reset_choice();
void the_end();
void go_to_epilogue_p(game_data*);
void go_to_epilogue_n(game_data*);
void talk_to_beardie(game_data*);
void talk_to_businesswoman(game_data*);
void expand_dialogue(game_data*, bool*);
void go_to_garden(game_data*);
void go_to_museum(game_data*);
void go_to_house(game_data*);
