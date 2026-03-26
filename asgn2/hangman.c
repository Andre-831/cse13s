#include "hangman_strings.h"

/*
* Purpose:          Determine whether a char is lower-case.
*
*                   For this assignment only, YOU MAY NOT USE islower().  I
*                   want you to get experience in comparing character
*                   values.  So you will write code that checks whether c
*                   is between 'a' and 'z'.
*
* Parameter:        c   - A character.  Literally any byte value 0 to 255.
*
* Return value:     1 (true) if c is a lower-case letter (between 'a' and 'z').
*                   0 (false) otherwise.
*/
bool is_lowercase_letter(char c) {
    return (c >= 'a' && c <= 'z'); 
                  // Replace these lines with your source code.
                  // Remember, for this assignment only, YOU MAY NOT USE islower().
                  // I want you to get experience in comparing character values.
}


/*
* Purpose:          Determine whether a string contains a character.
*
*                   To determine whether the string contains the given
*                   character, you may use strlen() and a "for" loop, or
*                   you may use strchr().  Use the commands "man 3 strlen"
*                   and "man 3 strchr" to read more about these functions.
*                   Look near the end of the man page for "RETURN VALUE"
*                   for the best summary.
*
* Parameters:       string  - the string to search within
*                   ch      - the character to search for
*
* Return value:     1 if the string contains the character.
*                   0 otherwise
*/
bool string_contains_character(const char *string, char ch) {
    return strchr(string,ch) != NULL; // Replace this line with your source code.
}


/*
* Purpose:          Determine whether the length and contents of a secret
*                   are valid.  As described in the assignment PDF, valid
*                   secrets have a length that is no more than MAX_LENGTH
*                   (which already is defined for you in
*                   hangman_strings.h), and they must consist of only
*                   lower-case letters and the three punctuation characters
*                   '-', '\'', and ' '.
*
*                   Use strlen() to confirm that the length of the secret
*                   does not exceed MAX_LENGTH.  If it does, use printf()
*                   and MSG_LONG_SECRET_d to print an error and return
*                   false.  (Look in hangman_strings.h to see what
*                   MSG_LONG_SECRET_d represents.)
*
*                   Using a "for" loop, verify that all of the secret's
*                   characters are valid.  That is, that they are
*                   lower-case letters and the three kinds of punctuation.
*                   If any of the characters is illegal, then use printf()
*                   and MSG_INVALID_CHAR_c to print an error and return
*                   false.  (Look in hangman_strings.h to see what
*                   MSG_LONG_SECRET_d represents.)
*
*                   Hint:  You can test that a character of the string is
*                   punctuation using individual "==" comparisions, or you
*                   can use your function string_contains_character() and
*                   the string "punctuation" (which is defined for you in
*                   hangman_strings.h).
*
* Parameter:        secret  - A string that represents the secret to test.
*
* Return Value:     If the secret is valid, then return true.
*                   Otherwise return false.
*/
bool is_valid_secret(const char *secret) {

    //check if length is valid
    if (strlen(secret) > MAX_LENGTH){
        printf(MSG_LONG_SECRET_d, MAX_LENGTH);
        return false;
    }

    for (int i = 0; i < strlen(secret); i++){
        char c = secret[i];
        //check if char is valid
        if (!is_lowercase_letter(c) && !string_contains_character(punctuation, c)){
            printf(MSG_INVALID_CHAR_c, c);
            return false;
        }
    }
    return true; // Replace this line with your source code.
}


/*
* Purpose:          Prompt for and return a character.  If the character is
*                   '\n' (end of line), then get another character.
*
* Parameter:        None.
*
* Return value:     A character.
*/
char prompt_for_and_read_character(void) {
    //               1. Use printf() and MSG_PROMPT to print the prompt.

    //               2. Create a do-while loop.

    //               3. In the body of the loop use getchar() to read an
    //                  int.  (The function is called getchar(), but it
    //                  also might return EOF, and so we need to store
    //                  its return value in an int.)

    //               4. In the condition of the do-while loop check if
    //                  the character is '\n'.  Stay in the loop if it is.

    //               5. If the character is EOF, then call exit(0).

    //               6. Return the character.

    int ch;
    printf(MSG_PROMPT);
    do{
        ch = getchar();

        if (ch == EOF){
            exit(0);
        }

    } while(ch == '\n');
    return (char) ch; // Replace this line with your source code.
}


/*
* See Section 2 of the assignment PDF.
*
* Write a function-header comment for this function.
* We are going to grade the comments in this function.

* Purpose:          
*   Run the hangman game for the given secret phrase. displaying the art,
*   current guessed phrase, eliminated letters after each guess, tracking
*   mistkaes, and determining win or loss.


* how to use: 
* Parameters:   secret  - The secret phrase to guess.

    void run_hangman(const char *secret)
    -secret: a valid all secret phrase with lowercase letters and  certain punctuation allowed
    (letters, space, hyphen, apostrophe)
    -prints game progress and result, no return value

* Return value:  none
*
*
*Organization:
*   -build hidden version of the secret phrase in guess[] with underscores for letters
*   -use elminated[] array to track incorrect guesses and mistake count to track number 
*    of wrong guesses/display hangman art
*   -Loop: prompt for character, validate input, update guess or eliminated letters, check win/lose conditions
*   -printed updated art, phrase and eliminated letters after each guess
*   -end game when player wins (all letters guessed) or loses (LOSING_MISTAKE reached)
*   
*       
*/
void run_hangman(const char *secret) {
    // Replace this line with your source code.
    int len = strlen(secret);
    char guess[MAX_LENGTH + 1] = {0};
    int mistake_count = 0;
    int eliminated[256]  = {0}; // array to track eliminated letters

    // build hidden phrase
    for(int i = 0; i < len; i++){
        char c = secret[i];
        if (is_lowercase_letter(c)){
            guess[i] = '_';
        }else{
            guess[i] = c;
        }
    }
    guess[len] = '\0';
    
        printf("%s\n", arts[mistake_count]);
        printf("    Phrase: %s\n", guess);
        printf("Eliminated: \n\n");

    while(1){
        //check win condition, if theres no more '_' in guess

        if (strchr(guess,'_') == NULL){
            printf(MSG_WIN_s, secret);
            return;
        }
        //check lose condition
        if (mistake_count >= LOSING_MISTAKE){
            printf(MSG_LOSE_s, secret);
            return;
        }

        //get character from user
        char c = prompt_for_and_read_character();

        //check if char is valid or has already been guessed
        if(!is_lowercase_letter(c) || string_contains_character(guess, c) || eliminated[c]){
            continue;
            }

        //reveal psositions of correct guess
        if (string_contains_character(secret, c)){
            for(int i = 0; i < len; i++){
                if (secret[i] == c){
                    guess[i] = c;
                }
            }
        }
        //add to wrong guesses and increment mistake count
        else{
            eliminated[c] = 1;
            mistake_count++;
        }
        printf("%s\n", arts[mistake_count]);
        printf("    Phrase: %s\n", guess);
        printf("Eliminated: ");
        for(char c = 'a'; c <= 'z'; c++){
            if(eliminated[c]){
                printf("%c",c);
            }
        }
        printf("\n\n");

    }
}



/*
* Purpose:          Run the hangman game.
*
*                     1. Check the value of argc to confirm that the user
*                        runs hangman with a "secret" on the command line.
*                        If the user puts the wrong number of arguments on
*                        the command line, then using printf() and
*                        MSG_WRONG_NUM_ARGS to report an error, and then
*                        "return 1".
*                     2. Call is_valid_secret().  If the function
*                        returns false, then "return 1;".
*                     3. Call run_hangman(secret).
*                     4. Return 0.
*
* Parameters:       argc    - The number of command-line arguments from main().
*                   argv    - An array of strings from main().
*
* Return value:     0 if no error.  1 otherwise.
*/
int main(int argc, char **argv) {
    
    if(argc != 2){
        printf("%s", MSG_WRONG_NUM_ARGS);
        return 1;
    }
    
    
    if (!is_valid_secret(argv[1])){
        return 1;
    }

    run_hangman(argv[1]);

    return 0; // Replace this line with your source code.
}
