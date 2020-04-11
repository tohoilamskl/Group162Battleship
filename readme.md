# Group162Battleship

## Group: 162
## Game: Battleship Remastered
### Members:
1. To Hoi Lam 3035667455
2. Ng Chun Hei 3035690634

### Game description:
* A turn-based strategy game where you will be guessing the coordinates of the AI's ships. If you guessed all the positions of the AI's ships first, you win. Otherwise, you lose.

###  Game rules:
* Each side has a 10x10 board and 5 classes of ships to put on it:
    * an Aircraft carrier which takes up 5 spaces,
    * a battleship which takes up 4 spaces,
    * a heavy cruiser which takes up 3 spaces,
    * a submarine which takes up 3 spaces,
    * a destroyer which takes up 2 spaces.


* On your turn, you can fire a single shot/special weapon to score a hit or a miss, or performing a reconnaissance.

* The winner is the player who is first to sink all ships in the enemy fleet.

### Game features:
* Randomly generate a board for both AI and player (Requirement 1)

* The game will records all the previous game history into a txt file (Requirement 4)
    * Recording your name, win/lose, number of moves used
    * When the program extract game history from the txt file, it will store in a dynamic memory, and the program will use a linked list to sort the records from least moves used to most moves used (Requirement 3)


* The program can also save the unfinished game into a txt file, and you can resume the game on another time (Requirement 4)

* Then the program can retrieve the records from the txt file into a data structure, for displaying the records (Requirement 2)

* Codes to display the boards, and codes to display the game records will be in a different file than the main program codes (requirement 5)

* An AI for computer's moves
