#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "base.h"

char choice, control;
char *buffer;

// KONIEC GRY
void the_end() {
    sleep(1);
    printf("Press ENTER to continue.\n");
    getchar();
    system("clear");
    printf("THE END.\n");
    wait();
    printf("Press ENTER to exit.\n");
    getchar();
    exit(0);
}

// EPILOG - WYGRANA
void go_to_epilogue_p(game_data *ptr_data) {
    save_data(ptr_data);
    system("clear");
    type_out("You're back at the museum.\nThe eccentric men are waiting for you already.\n");
    print_action("GIVE THEM THE CARBOPRISM. [a]");
    CATCH('a');
    type_out("You give the carboprism to one of the time travellers.\nThe object is reflecting the sunshine with a glittering purple luster.\nThe men seem to be very content.\n");
    type_out("> Congratulations, you have saved the world. Now it is time for us to visit the future and fix a thing or two.\n");
    wait();
    type_out("...\n");
    sleep(1);
    system("clear");
    type_out("Late evening. What are you doing here, at the gates of the museum, in the late evening?\nYou feel dizzy.\nPerhaps you got lost in your thoughts and didn't notice the passing time.\nTime to go home.\n");
    the_end();
}

// EPILOG - PRZEGRANA
void go_to_epilogue_n(game_data *ptr_data) {
    save_data(ptr_data);
    system("clear");
    type_out("...\n");
    sleep(2);
    system("clear");
    type_out("You find yourself standing in front of your house.\nYou feel uneasy for you don't remember what led you outside.\nYou open the door, sensing the weight of inevitable doom that's yet to come.\n");
    the_end();
}

// OGROD BOTANICZNY - ROZMOWA Z BRODACZEM
void talk_to_beardie(game_data *ptr_data) {
    static bool talked_to; // zmienna sprawdzajaca czy postac gracza rozmawiala juz ta postacia
    print_action("SAY: TEMPUS VOLAT, HORA FUGIT. [a]");
    CATCH('a');
    type_out("> Listen, I need some alone time.\n");
    wait();
    print_action("[ 1 ] SAY: WHAT AN ODDITY. [ 2 ] SAY: I'M SORRY.");
    CATCHM('1', '2');
    if(choice == '1') {
        type_out("< What an oddity.\n");
        if(talked_to == 0)
            change_points_value(ptr_data, -1);
    } else {
        type_out("< I'm sorry.\n");
        if(talked_to == 0)
            change_points_value(ptr_data, 1);
    }
    talked_to = 1;
    return;
}

// OGROD BOTANICZNY - ROZMOWA Z BIZNESMENKA
void talk_to_businesswoman(game_data *ptr_data) {
    static bool talked_to; // zmienna sprawdzajaca czy postac gracza rozmawiala juz ta postacia
    print_action("SAY: TEMPUS VOLAT, HORA FUGIT. [a]");
    CATCH('a');
    type_out("> What? Who are you?\n");
    wait();
    print_action("[ 1 ] SAY: NONE OF YOUR BUSINESS. [ 2 ] SAY: SORRY, I MISTOOK YOUR FOR SOMEONE ELSE.");
    CATCHM('1', '2');
    if(choice == '1') {
        type_out("< None of your business.\n");
        if(talked_to == 0)
            change_points_value(ptr_data, -1);
    } else {
        type_out("< Sorry, I mistook you for someone else.\n");
        change_points_value(ptr_data, 1);
    }
    talked_to = 1;
    return;
}

// ROZSZERZONY DIALOG ZE STARUSZKA
void expand_dialogue(game_data *ptr_data, bool *acquired_carboprism) {
    type_out("> I have to ask you some questions before I decide that you deserve to receive the carboprism.\n");
    type_out("> Choose the option which seems more obvious to you. Of course, we never know how we would react.\n");
    type_out("> First question: your grandmother is asking you to do some grocery shopping for her. You're tired, as you just got back from work, but she's too weak to do the shopping herself, there is no one else to help and you won't have time tomorrow.\n");
    type_out("> What do you do?\n");
    print_action("[ 1 ] DO THE SHOPPING [ 2 ] FIND AN EXCUSE.");
    CATCHM('1', '2');
    if(choice == '1')
        change_points_value(ptr_data, 1);
    else
        change_points_value(ptr_data, -1);
    type_out("> Second question: you see a homeless man being bullied.\n> How do you react?\n");
    print_action("[ 1 ] INTERVENE. [ 2 ] IGNORE - HE'S A PARASITE IN THE SOCIETY.");
    CATCHM('1', '2');
    if(choice == '1')
        change_points_value(ptr_data, 1);
    else
        change_points_value(ptr_data, -1);
    type_out("> Last question: your coworker is asking you for help with her work. She's helped you many times.\n> What do you do?\n");
    print_action("[ 1 ] HELP HER. [ 2 ] IGNORE THE REQUEST.");
    CATCHM('1', '2');
    if(choice == '1')
        change_points_value(ptr_data, 1);
    else
        change_points_value(ptr_data, -1);
    if(ptr_data->chara_image != 0) {
        type_out("> You passed the test. I can trust you with this one.\n");
        wait();
        *acquired_carboprism = 1;
        printf("ACQUIRED: A CARBORPISM.\n");
        type_out("The lady leaves.\n");
    } else {
        type_out("> Sorry, I can't let you have it.\n");
        wait();
        type_out("The lady leaves.\n");
    }

}

// TRZECIA LOKACJA - OGROD BOTANICZNY
void go_to_garden(game_data *ptr_data) {
    save_data(ptr_data);
    system("clear");
    char c;
    buffer = malloc(1024);
    bool acquired_carboprism = 0; // zmienna trzymajaca informacje o tym czy postac jest w posiadaniu carboprism
    type_out("You've arrived.\nThe garden feels like home. Safe and transcendental.\nYou notice that it's difficult to breathe - the air in the greenhouse is warm and humid.\n");
    type_out("You should find the merchant.\n");
    print_action("LOOK AROUND. [a]");
    CATCH('a');
    do {
        type_out("There are are three people there. Who should you approach?\n");
        printf("[ 1 ] A SHADY CLOAK-WEARING BEARDIE.\n[ 2 ] A PROFESSIONAL-LOOKING WOMAN IN WHITE.\n[ 3 ] AN OLD LADY SITTING ON A BENCH.\n");
        c = getch();
        printf("\r%c[2K", 27);
        switch(c) {
            case '1':
                talk_to_beardie(ptr_data);
                break;
            case '2':
                talk_to_businesswoman(ptr_data);
                break;
            case '3':
                break;
            default:
                printf("Incorrect choice.\n");
                sleep(1);
        }
    } while(c != '3');
    print_action("SAY: TEMPUS VOLAT, HORA FUGIT. [a]");
    CATCH('a');
    type_out("> I haven't heard this sentence in years...\n");
    if(ptr_data->chara_image != 0)
        type_out("> May I know your name?\n");
    else
        type_out("> You seem to be a difficult type. What's your name?\n");
    print_action("[ 1 ] INTRODUCE YOURSELF. [ 2 ] DON'T INTRODUCE YOURSELF.");
    CATCHM('1', '2');
    if(choice == '1') {
        to_buffer(buffer, "< My name is ", ptr_data->name);
        type_out(strcat(buffer, ".\n"));
        free(buffer);
        change_points_value(ptr_data, 1);
    } else
        type_out("< I prefer to remain anonymous.\n");
    type_out("> And what is the thing that you need?\n");
    print_action("[ 1 ] POLITELY ASK FOR THE CARBOPRISM. [ 2 ] DEMAND FOR THE CARBOPRISM.");
    CATCHM('1', '2');
    if(choice == '1') {
        type_out("< I'm in need of the carboprism. Do you happen to own one?\n");
        if(ptr_data->chara_image == 2) {
            type_out("> Yes, I do. You can have it; I've been paid for it already and you have passed the test.\n");
            wait();
            printf("ACQUIRED: A CARBORPISM.\n");
            type_out("The lady smiles, and the goes away.\n");
            acquired_carboprism = 1;
        } else if(ptr_data->chara_image == 1) {
            type_out("> Maybe. But I'm uncertain if you are trustworthy enough to receive it.\n");
            expand_dialogue(ptr_data, &acquired_carboprism);
        } else {
            type_out("> You're not the right person to receive it anyway. I'm sorry, but I can't let you have it.\n");
            type_out("The lady goes away, looking a bit despondent.\n");
            acquired_carboprism = 0;
        }
    } else {
        type_out("< Give me the carboprism.\n");
        if(ptr_data->chara_image != 0) {
            type_out("> Would it hurt to be a bit more polite? Now, I have to make sure that I'm talking to the right person.\n");
            expand_dialogue(ptr_data, &acquired_carboprism);
        } else {
            type_out("> You've seemed suspicious since the beginning. I can't let you have it.\n");
            type_out("The lady goes away, looking a bit uneasy.\n");
            acquired_carboprism = 0;
        }
    }
    if(acquired_carboprism) {
        type_out("You're done here. You feel relieved. It wasn't such a difficult quest.\nIt's time to meet with the time travellers again.\n");
        ptr_data->progress = 1;
        ptr_data->game_result = WON;
        follow_compass(ptr_data, 3, 3);
        sleep(2);
        go_to_epilogue_p(ptr_data);
    } else {
        type_out("Frustration.\nYou don't know what will happen now.\nYou decide not to meet with the time travellers. Meeting them would only result in greater disappointment. Time to go home.\n");
        ptr_data->progress = 1;
        ptr_data->game_result = LOST;
        follow_compass(ptr_data, 4, 1);
        sleep(2);
        go_to_epilogue_n(ptr_data);
    }
}

// DRUGA LOKACJA - MUZEUM HISTORII NATURALNEJ
void go_to_museum(game_data *ptr_data) {
    save_data(ptr_data);
    system("clear");
    type_out("As you arrive at the museum, your eyes witness the marvels of nature.\nGiant skeletons of ancient creatures, dainty fossils and curious pictures, all dimly lit by the soft strokes of the afternoon light\ncoming through gothic stainted glass windows.\nAnd then you hear, loud and clear...\n");
    wait();
    type_out("HOLOGRAPHIC NIGHT IN THE MESOZOIC!\n");
    wait();
    type_out("Is it truly what you were waiting for?\n");
    wait();
    type_out("No... you're sure that you were supposed to meet someone here.\nWhat a shame that you didn't note down whom.\nThough it seems that they have already found you.\n");
    wait();
    buffer = malloc(1024);
    to_buffer(buffer, "> Good afternoon, ", ptr_data->name);
    type_out(strcat(buffer, "!\n"));
    free(buffer);
    print_action("[ 1 ] SAY: GOOD AFTERNOON. [ 2 ] SAY NOTHING.");
    CATCHM('1', '2');
    if(choice == '1')
        type_out("< Good afternoon.\n");
    else {
        type_out("< ...\n");
        change_points_value(ptr_data, -1);
    }
    type_out("You've been greeted by a group of men dressed in tweed suits. This kind of garment had gone out of fashion even before you were born...\n");
    type_out("Now you remember. You've met them already.\nThe time travellers.\nIt was an accident, you didn't mean to discover such a great secret.\nBut you did, you saw them, and now you have to help them.\n");
    type_out("> We know that you may feel a bit perplexed. But do not worry, as soon as we are finished here, you will not remember a thing. Everything will go back to normal.\n");
    print_action("ASK ABOUT YOUR JOB. [a]");
    CATCH('a');
    type_out("> We need you to get only one thing: a carboprism.\n> We cannot get it personally as we cannot let ourselves known.\n> Obtaining this device will not be easy. You will have to talk to a merchant in the Botanical Garden. Be wary, it will not be easy to recognise who is the merchant.\n");
    print_action("ACCEPT REQUEST. [a]");
    CATCH('a');
    type_out("> To make sure that you are talking to the merchant, say `tempus volat, hora fugit`. Now, off you go.\n");
    follow_compass(ptr_data, 0, 4);
    ptr_data->progress = 0.8;
    sleep(2);
    go_to_garden(ptr_data);
}

// PIERWSZA LOKACJA - DOM
void go_to_house(game_data *ptr_data) {
    type_out("You're here. In the safety of your room.\nThe sun shines brightly through your window and allows you to notice a forgotten piece of paper laying on your desk.\n");
    wait();
    print_action("PICK IT UP. [a]");
    CATCH('a');
    type_out("The note reads...\n12 JUNE 2078\n3 PM\nAT NATURAL HISTORY MUSEUM\nOh, it's today!\nBut what was supposed to happen there?\nYou should find out...\nBut first, you'll need this.\n");
    wait();
    printf("ACQUIRED: A GLIMMERING COMPASS.\n");
    type_out("Follow the directions the compass gives you.\n");
    follow_compass(ptr_data, 3, 3);
    ptr_data->progress = 0.4;
    sleep(2);
    go_to_museum(ptr_data);
}







