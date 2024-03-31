/*
 * Ata Berke Yargıç - 2638328
 * CNG 140 Assignment-1 (Crag Game)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global prototypes to call them in other functions.
int roll_a_dice();

int roll_again(char);

int score_table(int, int, int);

void scoresheet(int, int, int);

char ask_roll_again();

int main() {
    //Function prototypes.
    int play_computer();
    int play_user();
    int game_start(int, int);


    //set randomness seed of dice according to game start time.
    srand(time(NULL));


    //Variable definitions.
    int round_val = 0; // Holds the data of the game length in type of rounds.
    int round_count = 1; // Holds the data of how many round has been played.
    int dice1, dice2, dice3;
    int round_point = 0;
    int C_point = 0; // Computer's total point.
    int P_point = 0; // Player's total point.
    int player_val; // Holds the data of who is going to start first.
    int roll_this; // Value of the dice that is going to rolled again.
    char is_roll_again; // Holds the data of does the user wants to reroll or not.


    //Game starts here with a welcome message.
    printf("Welcome to Crag game.\nLet's get started!\n");
    printf("\n");

    //Set game length.
    printf("How many rounds would you like to play?");
    scanf("%d", &round_val);
    fflush(stdin); // To prevent errors happened because of the multiple inputs.

    // Decide who is going to start.
    player_val = game_start(dice1, dice2);


    // Main game part.
    while (round_val) {
        if (player_val == 1) { // Player starts
            printf("\n\nROUND %d --- Your Turn\n", round_count);
            printf("======================================================");

            round_point = play_user(); // User plays.
            P_point += round_point; // Calculate total score.
            printf("\n\nYour Score: %d Total Score: %d", round_point, P_point);

            printf("\n\nROUND %d --- My Turn\n", round_count);
            printf("======================================================");

            round_point = play_computer(); // Computer plays.
            C_point += round_point; // Calculate total score.
            printf("\nMy Score: %d Total Score: %d", round_point, C_point);

            scoresheet(P_point, C_point, round_count);

            // Update round data at the end of the round.
            round_count += 1;
            round_val -= 1;
        } else if (player_val == 2) { // Computer starts
            printf("\n\nROUND %d --- My Turn\n", round_count);
            printf("======================================================");

            round_point = play_computer(); // Computer plays.
            C_point += round_point; // Add round's point to computer's total points.
            printf("\nMy Score: %d Total Score: %d", round_point, C_point);

            printf("\n\nROUND %d --- Your Turn\n", round_count);
            printf("======================================================");

            round_point = play_user(); // User plays.
            P_point += round_point; // Add round's point to player's total points.
            printf("\n\nYour Score: %d Total Score: %d", round_point, P_point);

            scoresheet(P_point, C_point, round_count); /* Display score sheet at the end of
                                                                                    the each round*/

            // Set round data at the end of the round.
            round_count += 1;
            round_val -= 1;
        }
    }

    if (C_point > P_point)
        printf("\nI AM THE WINNER!!");
    else if (P_point > C_point)
        printf("\nYOU ARE THE WINNER!!");
    else
        printf("\nTIE!!");

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


// Function to roll dice for the player.
int play_user() {
    int dice_sum, roll, is_roll_again;
    int diceA, diceB, diceC;

    // Roll 3 dice for player
    diceA = roll_a_dice();
    diceB = roll_a_dice();
    diceC = roll_a_dice();

    printf("\n\nYou got => [Dice 1]: %d, [Dice 2]: %d, [Dice 3]: %d", diceA, diceB, diceC);

    // Ask if user wants to reroll the dice.
    is_roll_again = ask_roll_again();
    roll = roll_again(is_roll_again);

    // If user wants to reroll a dice, roll that.
    if (roll == 1) {
        diceA = roll_a_dice();
        printf("\nYou got => [Dice 1]: %d, [Dice 2]: %d, [Dice 3]: %d", diceA, diceB, diceC);
    } else if (roll == 2) {
        diceB = roll_a_dice();
        printf("\nYou got => [Dice 1]: %d, [Dice 2]: %d, [Dice 3]: %d", diceA, diceB, diceC);
    } else if (roll == 3) {
        diceC = roll_a_dice();
        printf("\nYou got => [Dice 1]: %d, [Dice 2]: %d, [Dice 3]: %d", diceA, diceB, diceC);
    }

    dice_sum = score_table(diceA, diceB, diceC);

    return dice_sum;
}


int play_computer() {
    int dice_sum, roll, is_roll_again;
    int diceA, diceB, diceC;

    // Roll 3 dice for computer.
    diceA = roll_a_dice();
    diceB = roll_a_dice();
    diceC = roll_a_dice();

    printf("\nI rolled them and I got");
    printf("\n=> [Dice 1]: %d, [Dice 2]: %d, [Dice 3]: %d\n", diceA, diceB, diceC);

    // Determine when the computer wants to reroll dice.
    if (diceA == 4 && diceB == 5 && diceC != 6) {
        diceC = roll_a_dice();
        printf("\nRolled dice 3!");
        printf("\n=> [Dice 1]: %d, [Dice 2]: %d, [Dice 3]: %d\n", diceA, diceB, diceC);
    } else if (diceA == 4 && diceC == 6 && diceB != 5) {
        diceB = roll_a_dice();
        printf("\nRolled dice 2!");
        printf("\n=> [Dice 1]: %d, [Dice 2]: %d, [Dice 3]: %d\n", diceA, diceB, diceC);
    } else if (diceB == 5 && diceC == 6 && diceA != 4) {
        diceA = roll_a_dice();
        printf("\nRolled dice 1!");
        printf("\n=> [Dice 1]: %d, [Dice 2]: %d, [Dice 3]: %d\n", diceA, diceB, diceC);
    }

    dice_sum = score_table(diceA, diceB, diceC); // Calculate the computer's points at the end of the round.

    return dice_sum;
}


// Function to learn if player wants to roll again and returns the answer.
char ask_roll_again() {
    char answer;
    printf("\nShall I roll for you (Y/N)?");
    scanf(" %c", &answer);
    fflush(stdin);
    return answer;
}


// Function to roll dice again if player wants.
int roll_again(char is_again) {
    int x, y; // Variables to mark two kept dice.
    int reroll; // Variable to return the value of unkept dice.

    if (is_again == 'Y' || is_again == 'y') { // If user wants to reroll the dice, return the data of that dice.
        printf("\nWhich ones do you want to keep?");
        scanf("%d %d", &x, &y);
        fflush(stdin); // Clean the buffer to prevent errors if user enters more than 2 input and take first 2.

        if (x == 1 && y == 2) // If user choose 1 and 2, keep 3
            reroll = 3;
        else if (x == 1 && y == 3) // If user choose 1 and 3, keep 2
            reroll = 2;
        else if (x == 2 && y == 3) // If user choose 2 and 3, keep 1
            reroll = 1;
        else { // Error handling for dice input.
            printf("Sorry, wrong input!");
            reroll = roll_again(is_again);
        }
    } else if (is_again == 'N' || is_again == 'n') { // If user don't want to reroll a dice, return 0.
        return 0;
    } else { // Error handling for yes/no question.
        printf("Sorry, I don't understand!");
        is_again = ask_roll_again();
        reroll = roll_again(is_again);
    }

    return reroll;
}


// A function to calculate scores according to the scoring table.
int score_table(int diceA, int diceB, int diceC) {
    int dice_sum; // Variable for the score

    if ((diceA == diceB || diceA == diceC || diceB == diceC) && (diceA + diceB + diceC) == 13) {
        dice_sum = 50;
        printf("\nCrag!!");
    } else if ((diceA + diceB + diceC) == 13) {
        dice_sum = 26;
    } else if (diceA == diceB && diceA == diceC) {
        dice_sum = 25;
    } else if (diceA == 1 && diceB == 2 && diceC == 3) {
        dice_sum = 20;
    } else if (diceA == 4 && diceB == 5 && diceC == 6) {
        dice_sum = 20;
    } else if (diceA == 1 && diceB == 3 && diceC == 5) {
        dice_sum = 20;
    } else if (diceA == 2 && diceB == 4 && diceC == 6) {
        dice_sum = 20;
    } else
        dice_sum = diceA + diceB + diceC;

    return dice_sum;
}


// A function to display total score at the end of the each round.
void scoresheet(int player_total, int computer_total, int round) {
    printf("\n\n\nOur scoreboard after round %d:", round);
    printf("\n=============================");
    printf("\nMy score     Your score");
    printf("\n%d%14d", computer_total, player_total);
    printf("\n\n");
}


//Should I explain this :D
int roll_a_dice() {
    return 1 + rand() % 6; //set random in range of 1 and 6.
}
