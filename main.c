#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int roll_a_dice(); //Global prototype to call it in other functions.
void roll_again(char, int, int, int);

char ask_roll_again();

int main() {
    //Prototypes.
    void play_computer();
    void play_user(int, int, int, int);
    int game_start(int, int);


    //set randomness seed of dice according to game start time.
    srand(time(NULL));


    //Variable definitions.
    int round_val; // Holds the data of the game length in type of rounds.
    int round_count = 1; // Holds the data of how many round has been played.
    int dice1, dice2, dice3;
    int round_point;
    int C_point; // Computer's total point.
    int P_point; // Player's total point.
    int player_val; // Holds the data of who is going to start first.

    char is_roll_again;


    //Game starts here with a welcome message.
    printf("Welcome to Crag game.\nLet's get started!\n");
    printf("\n");

    //Set game length.
    printf("How many rounds would you like to play?");
    scanf("%d", &round_val);

    // Decide who is going to start.
    player_val = game_start(dice1, dice2);


    // Main game part.
    while (round_val) {
        if (player_val == 1) { // Player starts

            // Let the player play their turn.
            play_user(dice1, dice2, dice3, round_count);
            is_roll_again = ask_roll_again();
            roll_again(is_roll_again, dice1, dice2, dice3);

            // Set round data at the end of the round.
            round_count += 1;
            round_val -= 1;
        } else if (player_val == 2) { // Computer starts
            play_computer();
        }
    }

    return 0;
}


//A function to decide which player is going to start the game by rolling two dice .
int game_start(int diceP, int diceC) {

    // Variable holds the data of the first player.
    int player;

    // Roll the dice for computer.
    diceC = roll_a_dice();
    printf("\n\nI have rolled the dice and got %d!", diceC);

    // Roll the dice for player.
    diceP = roll_a_dice();
    printf("\nI have rolled the dice for you and you got %d!", diceP);


    if (diceP > diceC)
        player = 1; // Player starts.
    else if (diceC > diceP)
        player = 2; // Computer starts.
    else {
        printf("\n\nOur dice are equal, I roll the dice again.");
        return game_start(diceP, diceC); // If there is a tie, roll again.
    }


    // Return the data of who is going to start first.
    return player;
}


// Function to let player play the game.
void play_user(int diceA, int diceB, int diceC, int round) {
    printf("\n\nROUND %d --- Your Turn\n", round);
    printf("------------------------------------\n\n");

    // Roll 3 dice for player
    diceA = roll_a_dice();
    diceB = roll_a_dice();
    diceC = roll_a_dice();

    printf("You got [Dice 1]: %d, [Dice 2]: %d, [Dice 3]: %d\n", diceA, diceB, diceC);
}


void play_computer() {

}


// Function to learn if player wants to roll again and returns the answer.
char ask_roll_again() {
    char answer;
    printf("\nShall I roll for you (Y/N)? ");
    scanf(" %c", &answer);
    return answer;
}


// Function to roll dice again if player wants.
void roll_again(char is_again, int A_dice, int B_dice, int C_dice) {
    int keep_val; // Input value about which dices are going to kept.
    int keepA = 0, keepB = 0, keepC = 0; // To mark which dice are kept.
    int wrong = 0; // Is the dice input wrong?

    if (is_again == 'Y') {
        printf("\nWhich dice do you want to keep? ");

        do {
            scanf(" %d", &keep_val);
            switch (keep_val) {
                case 1:
                    keepA = 1; // Mark the first dice to kept.
                    break;
                case 2:
                    keepB = 1; // Mark the second dice to kept.
                    break;
                case 3:
                    keepC = 1; // Mark the third dice to kept.
                    break;
                default:
                    wrong = 1;
                    fflush(stdin);
                    break;
            }
        } while (keep_val == 1);

        // Take inputs again if there is any wrong input.
        if (wrong == 1) {
            printf("\nSorry, wrong input!");
            roll_again(is_again, A_dice, B_dice, C_dice);
        }


        if (keepA == 0)
            A_dice = roll_a_dice(); // Roll the first dice again.
        if (keepB == 0)
            B_dice = roll_a_dice(); // Roll the second dice again.
        if (keepC == 0)
            C_dice = roll_a_dice(); // Roll the third dice again.

        printf("\nThese are going to be kept: %d, %d, %d", keepA, keepB, keepC);
        printf("\nNew dices are these: [Dice 1]: %d, [Dice 2]: %d, [Dice 3]: %d",
               A_dice, B_dice, C_dice);

    } else if (is_again == 'N') {
        printf("\nDo nothing...");
    } else {
        printf("\nSorry, I don't understand!");
        is_again = ask_roll_again();
        roll_again(is_again, A_dice, B_dice, C_dice);
    }
}


//Should I explain this :D
int roll_a_dice() {
    return 1 + rand() % 6; //set random in range of 1 and 6.
}
