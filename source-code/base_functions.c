#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "base.h"

char title[9][255] = {
    "                    ▄▄\n", 
    "  ▄█▀▀▀█▄█         ▀███\n",
    "▄██    ▀█           ██\n",
    "▀███▄     ▄██▀██▄   ██  ▄█▀██▄ ▀███▄███\n",
    "  ▀█████▄██▀   ▀██  ██ ██   ██   ██▀ ▀▀\n",
    "▄     ▀████     ██  ██  ▄█████   ██\n",
    "██     ████▄   ▄██  ██ ██   ██   ██\n",
    "█▀█████▀  ▀█████▀ ▄████▄████▀██▄████▄\n",
    " \n"
};

// mapa swiata
const char world_map[5][5] = {
    {'X', 'X', 'X', 'X', 'X'},
    {'X', 'X', 'X', 'X', '0'}, // house
    {'X', 'X', 'X', 'X', 'X'}, 
    {'X', 'X', 'X', '1', 'X'}, // museum
    {'2', 'X', 'X', 'X', 'X'}  // garden
};

// wyswietlanie tytulu gry
void print_title() {
    char *temp = title[8];
    for(int i = 8; i > 0; i--) {
        system("clear"); 
        printf("\033[35m%s", temp);
        temp = title[i-1];
        strcat(temp, title[i]);
        usleep(100000);
    }
    printf("\n");
}

// wyswietlanie mozliwosci
void print_action(char str[]) {
    printf("\033[5m%s\n\033[0m", str);
}

// pobieranie znaku
char getch() {
    system ("/bin/stty raw");  
    char ret = getchar();
    system ("/bin/stty cooked");
    return ret;
}

// ucinanie newline
void erase_newline(char *str) {
    int length = strlen(str);
    str[length-1] = '\0';
}

// wyswietlanie tekstu litera po literze
void type_out(char str[]) {
    for(int i = 0; i < strlen(str); i++) {
        printf("%c", str[i]);
        fflush(stdout);
        usleep(40000);
    }
}

// umozliwia uzywanie imienia postaci w dialogach
void to_buffer(char buffer[], char str[], char name[]) {
    strcpy(buffer, str);
    strcat(buffer, name);
}

// zapisywanie gry
void save_data(game_data *ptr_data) {
    FILE *saved_data = fopen("data.dat", "w");
    fwrite(ptr_data, sizeof(game_data), 1, saved_data);
    fclose(saved_data);
}

// wczytywanie gry
void load_data(game_data *ptr_data) {
    FILE *saved_data = fopen("data.dat", "r+");
    if(saved_data == NULL) {  
        printf("You're playing for the first time.\n");               // funkcja najpierw sprawdza, czy plik zapisu istnieje
        printf("Game data cannot be loaded.\n");                      // i wczytuje dane tylko wtedy, gdy tak jest
    } else {
        while(fread(ptr_data, sizeof(game_data), 1, saved_data));
    }
    fclose(saved_data);
}

// inicjalizacja danych gry
void init(game_data *ptr_data) {
    char name[30];
    type_out("Please introduce yourself.\n");
    fflush(stdin);
    fgets(name, 30, stdin);     
    erase_newline(name);
    strcpy(ptr_data->name, name);                                    // imie postaci wybiera uzytkownik
    ptr_data->chara_image = Neutral;                                 // startowy wizerunek: neutralny
    ptr_data->current_x = 4;                                         // startowa lokacja: dom
    ptr_data->current_y = 1;                               
    ptr_data->player_points = 5;                                     // startowa ilosc punktow: 5 (patrz: wizerunek)
    ptr_data->progress = 0;                                          // startowy postep: 0
    ptr_data->game_result = NF;                                      // startowy wynik gry: nieukonczona
    save_data(ptr_data);
}

// rozruszanie gry
void begin(game_data *ptr_data) {
    system("clear");
    if(ptr_data->progress == 0)
        go_to_house(ptr_data);
    else if(ptr_data->progress == 0.4) 
        go_to_museum(ptr_data);
    else if(ptr_data->progress == 0.8)
        go_to_garden(ptr_data);
    else if(ptr_data->progress == 1) {
        if((ptr_data->game_result) == WON)
            go_to_epilogue_p(ptr_data);
        else
            go_to_epilogue_n(ptr_data);
    }
}

// modyfikacja punktacji
void change_points_value(game_data *ptr_data, int points) {
    if(((points > 0) && (ptr_data->player_points + points <= 10)) || ((points < 0) && (ptr_data->player_points + points >= 0)))
        ptr_data->player_points += points;
    if (ptr_data->player_points >= 0 && ptr_data->player_points <= 3)                                                        // na podstawie punktacji zmienia sie
        ptr_data->chara_image = Mean;                                                                                        // wizerunek postaci
    else if(ptr_data->player_points >=4 && ptr_data->player_points <= 6)
        ptr_data->chara_image = Neutral;
    else
        ptr_data->chara_image = Kind;
}

// poruszanie sie po swiecie
void move_around(game_data *ptr_data, char control) {
        if(control == 'd') {
            if(ptr_data->current_x == MAX_CO)
                return;
            else
                ptr_data->current_x = ptr_data->current_x + 1;
        }
        else 
        if(control == 's') {
            if(ptr_data->current_y == MAX_CO)
                return;
            else
                ptr_data->current_y = ptr_data->current_y + 1;
        }
        else
        if(control == 'a') {
            if(ptr_data->current_x == MIN_CO)
                return;
            else
                ptr_data->current_x = ptr_data->current_x - 1;
        }
        else
        if(control == 'w') {
            if(ptr_data->current_y == MIN_CO)
                return;
            else
                ptr_data->current_y = ptr_data->current_y - 1;
        }
}

// sprawdza, czy postac dotarla do celu
bool can_proceed(int x, int y, int dx, int dy) {
    if((x == dx) && (y = dy))
        return false;
    else {
        return true;
    }
}

// wyswietla kierunek, w ktorym postac ma sie udac
void print_destination(int x, int y, int dx, int dy) {
    if(x < dx && y < dy) {
        printf("Head southeast.\n");
    } else 
    if(x < dx && y > dy) {
        printf("Head northeast.\n");
    } else
    if(x < dx && y == dy) {
        printf("Head east.\n");
    } else
    if(x == dx && y < dy) {
        printf("Head south.\n");
    } else
    if(x == dx && y > dy) {
        printf("Head north.\n");
    } else
    if(x > dx && y == dy) {
        printf("Head west.\n");
    } else
    if(x > dx && y < dy) {
        printf("Head southwest.\n");
    } else
    if(x > dx && y > dy) {
        printf("Head northwest.\n");
    } else {
        printf("You've arrived at your destination.\n");
    }
}

// dramatyczna pauza
void wait() {
    usleep(600000);
}

// sterowanie postacia wg wskazowek kompasu 
void follow_compass(game_data *ptr_data, int dest_x, int dest_y) {
    char control;
    bool cp;
    do {
        cp = can_proceed(ptr_data->current_x, ptr_data->current_y, dest_x, dest_y);
        print_destination(ptr_data->current_x, ptr_data->current_y, dest_x, dest_y);
        if(!cp) {
            return;
        }
        else {
            fflush(stdin);
            control = getch();
            printf("\r%c[2K", 27);                                                                                                           
            move_around(ptr_data, control);
        }
    } while(cp);
}
