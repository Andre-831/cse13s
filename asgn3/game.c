#include "game.h"
#include "randi.h"
#include "strings.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Here is an array of player names.  Given a player number i, use the
* player names like this:
*
*   player_name[i]
*
* Following this array declaration is the definition of MAX_PLAYERS.  The
* player number i can be anything from 0 to MAX_PLAYERS - 1.
*/
const char *player_name[] = {

    "Ada Lovelace",
    /*
    * 1815-1852.  Wrote the first algorithm for a computer.
    */

    "Margaret Hamilton",
    /*
    * 1936-.  While in her 20s, lead the team that wrote and tested the
    * Apollo moon program's on-board flight software. Invented the term
    * "software engineering".
    */

    "Katherine Johnson",
    /*
    * 1918-2020.  Mathematician who hand-calculated trajectories for crewed
    * spaceflights.
    */

    "Joy Buolamwini",
    /*
    * ~1989-.  MIT computer scientist who works to challenge racial and
    * gender bias in AI-based decision software.
    */

    "Grace Hopper",
    /*
    * 1906-1992.  Mathematician and computer scientist who made the first
    * machine-independent computer language.
    */

    "Adele Goldberg",
    /*
    * 1945-.  Managed the team at Xerox that developed object-oriented
    * programming and graphical user interfaces.
    */

    "Annie Easley",
    /*
    * 1933-2011.  NASA computer scientist and mathematician who developed
    * algorithms that analyze various power technologies.
    */

    "Jeannette Wing",
    /*
    * 1956-.  Led many research projects as a university professor and as a
    * vice president at Microsoft Research.
    */

    "Mary Kenneth Keller",
    /*
    * 1913-1985.  First person to earn a Ph.D. in computer science in the
    * United States.
    */

    "Megan Smith",
    /*
    * 1964-.  Vice president at Google and 3rd Chief Technology Officer of
    * the United States.
    */

    "Radia Perlman",
    /*
    * 1958-.  Computer programmer and network engineer who invented many
    * network protocols include the Spanning Tree Protocol used by network
    * bridges.
    */
};

/*
* Faces of the die are numbered 0 through 5, and each face has a symbol.
* Create an array of six Symbols that is indexed by the face number.  Then
* you can convert the roll of a die (0-5) into a Symbol by accessing the
* array like this:
*
*    Symbol sym = symbol_of_roll[roll];
*/
const Symbol symbol_of_roll[6] = {
    DOT,
    DOT,
    DOT,
    LEFT,
    CENTER,
    RIGHT,
};

int score[MAX_PLAYERS];

/*
* Purpose:      Return the letter of the Symbol according to this table:
*
*                    sym    return
*                   ------  ------
*                   DOT      '.'
*                   LEFT     'L'
*                   CENTER   'C'
*                   RIGHT    'R'
*
* Parameter:    sym - the Symbol DOT, LEFT, CENTER, or RIGHT.
*
* Returns:      a char that represents the letter of the Symbol.
*/
char letter_of_symbol(Symbol sym) {
    // Replace this comment with your source code.
    switch(sym){
        case DOT:
            return '.';
        case LEFT:
            return 'L';
        case CENTER:
            return 'C';
        case RIGHT:
            return 'R';
    }
    return 0;
}

/*
* Purpose:      Compute the minimum of two ints.
*
* Parameters:   ints a and b
*
* Returns:      a or b, whichever is smallest.
*/
int min(int a, int b) {
    // Replace this comment with your source code.
    if (a < b){
        return a;
    }
    return b;
}

/*
* Purpose:      Return the next roll of a CSE 13S die.  That is, call randi(),
*               and then convert the result into a number between 0 and 5.
*
* Parameter:    none
*
* Returns:      An int from 0 to 5 representing a die roll
*/
int rand_roll(void) {
    // Replace this comment with your source code.
    return randi() % 6;
}

/*
* Purpose:      Compute the number of the player that is to the LEFT of the
*               player with the number given in parameter "player".
*               (See Section 2 of the assignment PDF.)
*
* Parameters:   player      - player number from 0 to num_players - 1
*               num_players - the number of players in this game
*
* Returns:      int from 0 to num_players - 1
*/
int left_of(int player, int num_players) {
    // Replace this comment with your source code.
    if (player == num_players - 1){
        return 0;
    }
    return player + 1;
}

/*
* Purpose:      Compute the number of the player that is to the RIGHT of the
*               player with the number given in parameter "player".
*               (See Section 2 of the assignment PDF.)
*
* Parameters:   player      - player number from 0 to num_players - 1
*               num_players - the number of players in this game
*
* Returns:      int from 0 to num_players - 1
*/
int right_of(int player, int num_players) {
    // Replace this comment with your source code.
    if(player == 0){
        return num_players - 1;
    }
    return player - 1;
}

/*
* Purpose:      Print all of the players' scores followed by the number of
*               chips in the pot.  The scores are in the array score[],
*               which is delcared near the top of this file.  You can
*               compute the number of chips in the pot (the game has a
*               total of 3 * num_players chips), or you can maintain the
*               pot's score in a new variable that you declare up where the
*               score[] array is.
*
*               Here is an example of the output:

Current scores:
    3 -- Ada Lovelace
    3 -- Margaret Hamilton
    3 -- Katherine Johnson
    0 -- pot

*               If you want, you can use two format strings in the file
*               string.h:  CURRENT_SCORES and SCORE_ds.  Look in strings.h
*               to see what they represent.
*
* Parameter:    num_players - an int which is the number of players.
*
* Returns:      nothing
*/
void print_scores(int num_players) {
    // Replace this comment with your source code.
    printf(CURRENT_SCORES);
    int pot = 3 * num_players;

    for(int i = 0; i < num_players; i++){
        printf(SCORE_ds,score[i],player_name[i]);
        pot -= score[i];
    }
    printf(SCORE_ds,pot,"pot");
}

/*
* Play the game.  See Section 2 of the assignment PDF for details.
*
* Write a function-header comment for this function.
* We are going to grade the comments in this function.

* purpose:
*
* Run the LCR game with the given seed and number of players. Give each player
* 3 chips and continue the game until only one player has chips left. On the current players turn,
* they roll the die up to 3 times (or less if they have less than 3 chips) and take actions based on the result of each roll.
* Dot means do nothing, Left means give a chip to the player on the left, Right means give a chip to the player on the right,
* and Center means put a chip in the pot. After each player's turn, print the scores. If a player has no chips, skip their turn.
* Game ends when only one player has chips left, and that player is declared the winner.
*
* Parameters:
*    seed - an unsigned int used to seed the random number generator.
*    num_players - an int representing the number of players in the game.
*
* Returns: nothing
*/
void play_game(unsigned seed, int num_players) {
    // Replace this comment with your source code.
    randi_seed(seed);

    //everyone starts with 3 chips
    for(int i = 0; i < num_players; i++){
        score[i] = 3;
    }
    print_scores(num_players); //initial scores

  
    int players_with_chips = num_players;
    int cur_player = 0;

    while(1){
        //check if player has chips
        if(score[cur_player] == 0){
            printf(HAS_NO_CHIPS_s,player_name[cur_player]);
            cur_player = left_of(cur_player,num_players);
            continue;
    }
    
    //player's turn message
    printf(TURN_s,player_name[cur_player]);

    int rolls = min(score[cur_player],3); // max 3 rolls
    
    for(int i =0; i < rolls; i++){ //for each roll check the result
        int roll = rand_roll();
        Symbol sym  = symbol_of_roll[roll];
        printf(ROLLS_c,letter_of_symbol(sym));

        if (sym == LEFT){
            int left_player = left_of(cur_player,num_players);
            score[cur_player]--;
            score[left_player]++;
            printf(GIVES_A_CHIP_TO_s,player_name[left_player]);
            if(score[cur_player] == 0){
                players_with_chips--;
            }
            if(score[left_player] == 1){
                players_with_chips++;
            }

        }
        else if (sym == RIGHT){
            int right_player = right_of(cur_player,num_players);
            score[cur_player]--;
            score[right_player]++;
            printf(GIVES_A_CHIP_TO_s,player_name[right_player]);
            if(score[cur_player] == 0){
                players_with_chips--;
            }
            if(score[right_player] == 1){
                players_with_chips++;
            }
        }
        else if(sym == CENTER){
            score[cur_player]--;
            printf(PUTS_A_CHIP);
            if(score[cur_player] == 0){
                players_with_chips--;
            }
        } //dot does nothing
    }
    print_scores(num_players);

    if(players_with_chips == 1){ //check for winner
        printf(ONE_PLAYER_HAS_CHIPS);
        for(int i = 0; i < num_players; i++){
            if(score[i] > 0){
                printf(WON_s,player_name[i]);
                return;
            }
        }
    }

    cur_player = left_of(cur_player,num_players); //next player's turn
}

}
