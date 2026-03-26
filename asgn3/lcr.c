#include "game.h"
#include "strings.h"
#include "randi.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int num_players = 3;
    printf(PROMPT_NUM_PLAYERS);
    int scanf_result = scanf("%d", &num_players);

    if (scanf_result < 1 || num_players < 3 || num_players > MAX_PLAYERS) {
        printf(ERROR_INVALID_PLAYERS);
        num_players = 3;
    }

    unsigned seed = 4823;
    printf(PROMPT_SEED);
    scanf_result = scanf("%u", &seed);

    if (scanf_result < 1 || seed < 0 || seed > 999999) {
        printf(ERROR_INVALID_SEED);
        seed = 4823;
    }

    play_game(seed, num_players);




    // assert(letter_of_symbol(DOT)    == '.');
    // assert(letter_of_symbol(LEFT)   == 'L');
    // assert(letter_of_symbol(CENTER) == 'C');
    // assert(letter_of_symbol(RIGHT)  == 'R');



    // assert(min(3, 5) == 3);
    // assert(min(-1, 2) == -1);
    // assert(min(7, 7) == 7);

    // assert(left_of(0, 3) == 2);
    // assert(left_of(1, 3) == 0);
     //assert(left_of(2, 3) == 0);

    // assert(right_of(0, 3) == 1);
    // assert(right_of(1, 3) == 2);
     //assert(right_of(0, 3) == 2);

    // // rand_roll
    // randi_seed(1234);  // set a seed
    // for (int i = 0; i < 10; i++) {
    //     int roll = rand_roll();
    //     assert(roll >= 0 && roll <= 5); // ensure 0-5 range
    // }


    return 0;
}
