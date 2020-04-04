//main.cpp
//includes: main operation, prompt input, print board, generate random board

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>  //setw()
#include <cstdlib>  //rand(), srand(), system()
#include <ctime> //time()
#include <string> //stoi()

using namespace std;

const int boardSize = 10;
//A structure storing all the boards required
struct Boards {
    char player[boardSize][boardSize]; //Full board of player (Player see this)
    char AI[boardSize][boardSize]; //Full board of AI
    char playerViewAIBoard[boardSize][boardSize]; // AI board but in player's perspectives (Player see this)
    char AIViewPlayerBoard[boardSize][boardSize]; // player board but in AI's perspectives
};

Boards boards;

//A structure stroing all the ships of a country
struct ships
{
  string shipclass;
  string name;
};

//function for stroing all the names of all the countries' ships to the given struct
void naming(ships arr[50],string s)
{
  string filename = s +".txt";
  ifstream fin(filename.c_str());

  if (fin.fail())
  {
    cout<<"Error in opening "<<s<<endl;
    exit(1);
  }

  string sclass,x;
  while (fin >> x)
  {
    sclass = x;
    if (sclass == "ac")
      {
        for (int i = 0; i < 10; i++)
        {

          string temp;
          fin >> temp;
          if (temp == "end")
          {
            break;
          }
          arr[i].shipclass = "ac";
          arr[i].name = s +" " + temp;
        }
      }
    if (sclass == "bb")
    {
      for (int i = 10; i < 20; i++)
      {

        string temp;
        fin >> temp;
        if (temp == "end")
        {
          break;
        }
        arr[i].shipclass = "bb";
        arr[i].name = s +" " + temp;
      }
    }
    if (sclass == "ca")
    {
      for (int i = 20; i < 30; i++)
      {

        string temp;
        fin >> temp;
        if (temp == "end")
        {
          break;
        }
        arr[i].shipclass = "ca";
        arr[i].name = s +" " + temp;
      }
    }
    if (sclass == "ss")
    {
      for (int i = 30; i < 40; i++)
      {

        string temp;
        fin >> temp;
        if (temp == "end")
        {
          break;
        }
        arr[i].shipclass = "ss";
        arr[i].name = s +" " + temp;
      }
    }
    if (sclass == "dd")
    {
      for (int i = 40; i < 50; i++)
      {

        string temp;
        fin >> temp;
        if (temp == "end")
        {
          break;
        }
        arr[i].shipclass = "dd";
        arr[i].name = s +" " + temp;
      }
    }
  }
    fin.close();
}

//A function that generates the ships' names for the player's fleet by the country they inputted
void genfleet(ships uss[50], ships kms[50], ships hms[50], ships rm[50], ships ijn[50], string country)
{
  string ac,bb,ca,ss,dd;
  int num, num1, num2, num3, num4;
  srand (time(NULL));
  if (country == "us")
  {
    country = "United States";
    num = rand() % 10 + 1;
    ac = uss[num].name;
    num1 = rand() % 10 + 10;
    bb = uss[num1].name;
    num2 = rand() % 10 + 20;
    ca = uss[num2].name;
    num3 = rand() % 10 + 30;
    ss = uss[num3].name;
    num4 = rand() % 10 + 40;
    dd = uss[num4].name;
  }
  else if (country == "gb")
  {
    country = "Great Britain";
    num = rand() % 8 + 0;
    ac = hms[num].name;
    num1 = rand() % 8 + 10;
    bb = hms[num1].name;
    num2 = rand() % 10 + 20;
    ca = hms[num2].name;
    num3 = rand() % 10 + 30;
    ss = hms[num3].name;
    num4 = rand() % 10 + 40;
    dd = hms[num4].name;
  }
  else if (country == "italy")
  {
    country = "The Kingdom of Italy";
    num = rand() % 2 + 0;
    ac = rm[num].name;
    num1 = rand() % 7 + 10;
    bb = rm[num1].name;
    num2 = rand() % 7 + 20;
    ca = rm[num2].name;
    num3 = rand() % 10 + 30;
    ss = rm[num3].name;
    num4 = rand() % 10 + 40;
    dd = rm[num4].name;
  }
  else if (country == "germany")
  {
    country = "German Reich";
    num = rand() % 1 + 0;
    ac = kms[num].name;
    num1 = rand() % 4 + 10;
    bb = kms[num1].name;
    num2 = rand() % 6 + 20;
    ca = kms[num2].name;
    num3 = rand() % 4 + 30;
    ss = kms[num3].name;
    num4 = rand() % 6 + 40;
    dd = kms[num4].name;
  }
  else if (country == "japan")
  {
    country = "Empire of Great Japan";
    num = rand() % 8 + 0;
    ac = ijn[num].name;
    num1 = rand() % 10 + 10;
    bb = ijn[num1].name;
    num2 = rand() % 10 + 20;
    ca = ijn[num2].name;
    num3 = rand() % 10 + 30;
    ss = ijn[num3].name;
    num4 = rand() % 10 + 40;
    dd = ijn[num4].name;
  }

  cout<<endl<<"You have picked "<<country<<":"<<endl<<"Your aircraft carrier is: "<<ac<<endl;
  cout<<"Your battleship is: "<<bb<<endl;
  cout<<"Your heavy cruiser is: "<<ca<<endl;
  cout<<"Your submarine is: "<<ss<<endl;
  cout<<"Your destroyer is: "<<dd<<endl;

}

//Function to print both your board, and opponent's board in your perspectives
void printBoard() {
    system("CLS"); //clear screen
    cout << setw(30) << "Opponent's Board" << setw(52) << "Your Board" << endl;
    cout << "     0   1   2   3   4   5   6   7   8   9                 0   1   2   3   4   5   6   7   8   9  \n";
    cout << "   +---+---+---+---+---+---+---+---+---+---+             +---+---+---+---+---+---+---+---+---+---+\n";
    for (int i = 0; i < boardSize; i++) {
        //Printing your opponent's board (in your perspective)
        cout << " " << (char)('A' + i);
        for (int j = 0; j < boardSize; j++) {
            cout << " | " << boards.playerViewAIBoard[i][j];
        }
        cout << " |          ";

        //Printing your own board
        cout << " " << (char)('A' + i);
        for (int j = 0; j < boardSize; j++) {
            cout << " | " << boards.player[i][j];
        }
        cout << " |\n";
        cout << "   +---+---+---+---+---+---+---+---+---+---+             +---+---+---+---+---+---+---+---+---+---+\n";
    }
}

//TEMPORARY PRINT BORAD FUNCTION (For developing stage only) (Will print all 4 boards)  (DELETE BEFORE SUBMISSION!!!!!!!!!!!)
void tempPrintBoard() {
    system("CLS"); //clear screen
    cout << "                                          YOUR Perspective                                  |                                       AI Perspective\n";
    cout << "               Opponent's Board                                  Your Board                 |                  AI Board                                     Your Board\n";
    cout << "     0   1   2   3   4   5   6   7   8   9        0   1   2   3   4   5   6   7   8   9     |     0   1   2   3   4   5   6   7   8   9        0   1   2   3   4   5   6   7   8   9  \n";
    cout << "   +---+---+---+---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+---+---+---+   |   +---+---+---+---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+---+---+---+\n";
    for (int i = 0; i < boardSize; i++) {
        //Printing your opponent's board (in your perspective)
        cout << " " << (char)('A' + i);
        for (int j = 0; j < boardSize; j++) {
            cout << " | " << boards.playerViewAIBoard[i][j];
        }
        cout << " | ";

        //Printing your own board
        cout << " " << (char)('A' + i);
        for (int j = 0; j < boardSize; j++) {
            cout << " | " << boards.player[i][j];
        }
        cout << " |   |";

        cout << " " << (char)('A' + i);
        for (int j = 0; j < boardSize; j++) {
            cout << " | " << boards.AI[i][j];
        }
        cout << " | ";

        cout << " " << (char)('A' + i);
        for (int j = 0; j < boardSize; j++) {
            cout << " | " << boards.AIViewPlayerBoard[i][j];
        }
        cout << " |\n";
        cout << "   +---+---+---+---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+---+---+---+   |   +---+---+---+---+---+---+---+---+---+---+    +---+---+---+---+---+---+---+---+---+---+\n";
    }
}

//Function to prompt player input, with input validation
string playerInput() {
    string target;
    int targetRow, targetCol;
    bool validInput;

    //Input validation
    while (true) {
        validInput = false;

        //Prompt input
        cout << "Please choose a target ('q' to quit): ";
        getline(cin, target);

        if (target.length() <= 2) {
            //check whether the player input Q or not (TODO: allow player input other command if have)
            if (target.length() == 1 && (target[0] == 'Q' || target[0] == 'q')) {
                validInput = true;
                return target;
            }
            if (((target[0] >= 'A' && target[0] <= 'J') || (target[0] >= 'a' && target[0] <= 'j')) && target[1] >= '0' && target[1] <= '9') {
                if (target[0] >= 'a' && target[0] <= 'j') {
                    target[0] = target[0] - 'a' + 'A';
                }
                validInput = true;
            }
        }

        if (validInput == true) {
            targetRow = (int)target[0] - 'A';
            targetCol = (int)target[1] - '0';
            if (boards.playerViewAIBoard[targetRow][targetCol] == 'X' || boards.playerViewAIBoard[targetRow][targetCol] == '@') { //TODO: if target is equal to attacked and is ship sign
                cout << "Invalid Input! " << target[0] << target[1] << " already attacked, please choose a non-attacked location!\n";
                validInput == false;
                continue;
            }
            else {
                return target;
            }
        }
        cout << "Invalid Input! Please input a character from 'A' to 'Z' followed by an integer 1 - 9! (Nothing in between)\n";
    }


    return target;
}

//Function to place each ship into the board (Randomly)
void placeShip(char board[][10], int size) {
    bool vertical = rand() % 2; //true = vertical;, false = horizontal
    bool invalidPlacement = true;
    int rowStart, colStart, row, col;

    if (vertical) {  //if place vertically
        while (invalidPlacement) {
            invalidPlacement = false;

            //randomly place ship
            rowStart = rand() % (10 - size);
            col = rand() % 10;
            //Check whether this position overlaps with other ships or not
            for (int i = rowStart; i < rowStart + size; i++) {
                if (board[i][col] == 'O') {
                    invalidPlacement = true;
                    break;
                }
            }
        }
        for (int i = rowStart; i < rowStart + size; i++) {
            board[i][col] = 'O'; //place ship
        }
    }
    else {  //if place horizontally
        while (invalidPlacement) {
            invalidPlacement = false;

            //randomly place ship
            colStart = rand() % (10 - size);
            row = rand() % 10;
            //Check whether this position overlaps with other ships or not
            for (int i = colStart; i < colStart + size; i++) {
                if (board[row][i] == 'O') {
                    invalidPlacement = true;
                    break;
                }
            }
        }
        for (int i = colStart; i < colStart + size; i++) {
            board[row][i] = 'O'; //place ship
        }
    }
}

//Function to generate random board (randomly put the ships into the board)
void generateRandomBoard(char board[][10]) {
    placeShip(board, 5);  //place the size-5 ship
    placeShip(board, 4);  //place the size-4 ship
    placeShip(board, 3);  //place the size-3 ship
    placeShip(board, 2);  //place the size-2 ship
}

int main() {
    string target;
    int targetRow, targetCol;
    ships uss[50], kms[50], hms[50], rm[50], ijn[50];

    naming(uss,"USS");
    naming(kms,"KMS");
    naming(hms,"HMS");
    naming(rm,"RM");
    naming(ijn,"IJN");

    srand(time(NULL));

    generateRandomBoard(boards.player);
    generateRandomBoard(boards.AI);

    int flag = 0;
    printBoard();
    cout<<"To play as the United States, type \"us\" "<<endl;
    cout<<"To play as Great Britain, type \"gb\" "<<endl;
    cout<<"To play as German Reich, type \"germany\" "<<endl;
    cout<<"To play as the Kingdom of Italy, type \"italy\" "<<endl;
    cout<<"To play as the Empire of Great Japan, type \"japan\" "<<endl<<endl;
    string country;
    getline(cin,country);
    genfleet(uss, kms, hms, rm, ijn, country);



    while (true) {

        target = playerInput();


        //if player enters q/Q, it quits
        if (target[0] == 'Q' || target[0] == 'q') {
            break;
        }
        targetRow = (int)target[0] - 'A';
        targetCol = (int)target[1] - '0';
        if (boards.AI[targetRow][targetCol] == 'O') {  //if hit, mark '@'
            boards.AI[targetRow][targetCol] = '@';
            boards.playerViewAIBoard[targetRow][targetCol] = '@';
        }
        else {
            boards.AI[targetRow][targetCol] = 'X';   //if not hit, mark 'X'
            boards.playerViewAIBoard[targetRow][targetCol] = 'X';
        }

        printBoard();
    }




    return 0;
}
