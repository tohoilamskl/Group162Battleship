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

struct navy
{
  string name;
  int xposini;
  int xposfnl;
  int yposini;
  int yposfnl;
};

struct Target
{
  int row;
  int col;
};

navy fleet[5];

struct plane
{
  string ijn[4] = {"Type 96 Carrier Attack Bomber", "B6N \"Jill\"", "B5N \"Kate\"", "B7A Ryusei \"Grace\""};
  string kms[2] = {"Fi 167", "He 115"};
  string rm[1] = {"Re.2001"};
  string uss[3] = {"TBY Sea Wolf", "TBF Avenger", "TBD Devastator"};
  string hms[3] = {"Swordfish", "Barracuda", "Vildebeest"};
};

int numofplane[5] = {4,2,1,3,3};
int plane1, plane2, planeflag;


plane bomber;

//array for storing the recon planes used by ijn, kms, rm, uss, hms respectively
string recon[5] = {"C6N Saiun \"Myrt\"","Arado Ar 196","Caproni Ca.316","Supermarine Walrus","OS2U Kingfisher"};

//array for storing the ap shells used by ijn, kms, rm, uss, hms respectively
string shell[5] = {"Type 1 AP shell", "38 cm SK C/34 AP shell", "Proiettile Perforante", "Mk. 8 APC shell", "Mk XXII BNT AP shell"};

//array for storing the radar used by ijn, kms, rm, uss, hms respectively
string radar[5] = {"Type 2 Mark 3 Model 3 Anti-Surface Fire-Control Radar", "FuMO 23 Seetakt radar", "EC 3 ter Gufo radar", "MK 37 Gun Fire Control System", "Type 279 early-warning radar"};

//array for storing the torpedos used by ijn, kms, rm, uss, hms respectively
string torpedo[5] = {"Type 93 torpedo", "21 inch torpedo", "533 mm torpedo", " 21-inch Mark 15 torpedo", "21-inch Mark VII torpedo"};

//number of storage of planes, plane 1 attack quota, plane 2 attack quota, barrage, torpedos of heavy cruiser, torpedos of submarine respectively
int spweapons[6] = {2,1,1,1,2,2};

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
void genfleet(ships uss[50], ships kms[50], ships hms[50], ships rm[50], ships ijn[50], string country, navy arr[5])
{
  string ac, bb, ca, ss, dd;
  int num, num1, num2, num3, num4;
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
    country = "the Empire of Great Japan";
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

  arr[0].name = ac;
  arr[1].name = bb;
  arr[2].name = ca;
  arr[3].name = ss;
  arr[4].name = dd;


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
    placeShip(board, 3);  //place the size-3ship
    placeShip(board, 2);  //place the size-2 ship
}

//function for validating the final coordinates of a ship when deploying, and store the ships coordinates to the player board if validated successfully
bool poschecker1(int &irow, int &icol, int &frow, int &fcol, char board[][10], int size)
{
  //check if the ship is overlapped by another ship or not
  if (board[frow][fcol] != 'O')
  {
    int flag = 0;

    //check if the ship is placed horizontally
    if (irow == frow)
    {
      //check if the final coordinates is the right of the initial coordinates, and swap them if it is not the case
      if (icol > fcol)
      {
        int temp = icol;
        icol = fcol;
        fcol = temp;
        flag = 1;
      }

      //check whether coordinates in between have been used or not
      for (int i = icol+1; i <= fcol - flag; i++)
      {

        if (board[irow][i] == 'O')
        {
          return false;
        }
      }

      //store the coordinates the ship
      for (int i = icol+1; i <= fcol - flag; i++)
      {
        board[irow][i] = 'O';
      }

      //storing the initial coordinates of the ship if the final and initial coordinates are swapped
      if (flag == 1)
      {
        board[irow][icol] = 'O';
      }
      return true;
    }
    else
    {
      //check if the final coordinates is the below the initial coordinates, and swap them if it is not the case
      if (irow > frow)
      {
        int temp = irow;
        irow = frow;
        frow = temp;
        flag = 1;

      }
      //check whether coordinates in between have been used or not
      for (int i = irow+1; i <= frow - flag; i++)
      {
        if (board[i][icol] == 'O')
        {
          cout<<i<<endl;
          return false;
        }
      }

      //store the coordinates the ship
      for (int i = irow+1; i <= frow - flag; i++)
      {
        board[i][icol] = 'O';
      }

      //storing the initial coordinates of the ship if the final and initial coordinates are swapped
      if (flag == 1)
      {
        board[irow][icol] = 'O';
      }

      return true;
    }
  }
  return false;

}

//function for validating the initial coordinates of a ship when deploying
bool poschecker(int row, int col, char board[][10], int size)
{

  //check if the ship is overlapped by another ship or not
  if (board[row][col] != 'O')
  {

    //check if the left side of the of the initial coordinates has enough spaces for putting the ship
    int left = col -size;
    if (left > 0)
    {
      int flag = 0;

      //check if the any ship used one of the coordinates on the left side
      for (int i = left; i < col; i++)
      {
        if (board[row][i] == 'O')
        {
          flag = 1;
          break;
        }
      }

      //store the initial coordinates and stop the program if there is enough spaces
      if (flag == 0)
      {
        board[row][col] = 'O';
        return true;
      }
    }

    //check if the right side of the of the initial coordinates has enough spaces for putting the ship
    int right = col + size;
    if (right <= 9)
    {
      int flag = 0;

      //check if the any ship used one of the coordinates on the left side
      for (int i = col; i < right; i++)
      {
        if (board[row][i] == 'O')
        {
          flag = 1;
          break;
        }
      }

      //store the initial coordinates and stop the program if there is enough spaces
      if (flag == 0)
      {
        board[row][col] = 'O';
        return true;
      }
    }

    //check if the north side of the of the initial coordinates has enough spaces for putting the ship
    int up = row - size;
    if (up > 0)
    {
      int flag = 0;

      //check if the any ship used one of the coordinates on the north side
      for (int i = up; i < row; i++)
      {
        if (board[i][col] == 'O')
        {
          flag = 1;
          break;
        }
      }

      //store the initial coordinates and stop the program if there is enough spaces
      if (flag == 0)
      {
        board[row][col] = 'O';
        return true;
      }
    }

    //check if the south side of the of the initial coordinates has enough spaces for putting the ship
    int bot = col + size;
    if (bot <= 9)
    {
      int flag = 0;

      //check if the any ship used one of the coordinates on the south side
      for (int i = row; i < bot; i++)
      {
        if (board[i][col] == 'O')
        {
          flag = 1;
          break;
        }
      }

      //store the initial coordinates and stop the program if there is enough spaces
      if (flag == 0)
      {
        board[row][col] = 'O';
        return true;
      }
    }
    return false;
  }
  return false;
}

//function for validating the input
bool checkvalidinput(string &target)
{
  if (target.size() == 2)
  {

    //validate the format of the coordinates
    if (((target[0] >= 'A' && target[0] <= 'J') || (target[0] >= 'a' && target[0] <= 'j')) && target[1] >= '0' && target[1] <= '9')
    {

      //convert the coordinates if it is in small letter
      if (target[0] >= 'a' && target[0] <= 'j')
      {
          target[0] = target[0] - 'a' + 'A';
      }
      return true;
    }
  }

  return false;
}
//function for allowing the player to input the initial and final coordinates of each ships
void deployment(char board[][10])
{
  string pos[2] = {};
  pos[0] = "starting";
  pos[1] = "ending";


  int shipsize[5] = {4,3,2,2,1};
  cout<<endl;

  //prompt user to input coordinates of the ships
  for (int i = 0; i < 5; i++)
  {
    int j = 0;
    while (true)
    {
      cout<<"Please enter the "<<pos[j]<<" coordinates of "<<fleet[i].name<<":"<<endl;
      int invalidinput = 1;
      string target;
      getline(cin,target);

      if (checkvalidinput(target))
      {

        //validate the initial coordinates and store it, else continue to prompt user for valid input
        if (j == 0)
        {
          fleet[i].yposini = (int)target[0] - 'A';
          fleet[i].xposini = (int)target[1] - '0';

          if (poschecker(fleet[i].yposini, fleet[i].xposini, boards.player, shipsize[i]))
          {
            board[fleet[i].yposini][fleet[i].xposini] = 'O';
            j++;
            invalidinput = 0;
            printBoard();
          }
        }

        //validate the final coordinates and store it, else continue to prompt user for valid input
        else if (j == 1)
        {
          fleet[i].yposfnl = (int)target[0] - 'A';
          fleet[i].xposfnl = (int)target[1] - '0';

          if (pow(fleet[i].yposini - fleet[i].yposfnl, 2) + pow(fleet[i].xposini - fleet[i].xposfnl,2) == pow(shipsize[i],2))
          {
            if (poschecker1(fleet[i].yposini, fleet[i].xposini, fleet[i].yposfnl, fleet[i].xposfnl, boards.player, shipsize[i]))
            {
              cout<<endl;
              printBoard();
              break;
            }
          }
        }
      }

      //prompt error message if the input is invalid
      if (invalidinput == 1)
      {
        cout<<"***Invalid input! Please enter the coordinates correctly.***"<<endl;
      }
    }
  }
}

//function to score a hit and update the map
void fire(int row, int col)
{

  //validate the coordinates
  if (row >= 0 && row < 10 && col >= 0 && col < 10)
  {
    if (boards.AI[row][col] == 'O' || boards.AI[row][col] == '@')
    {

      //if hit, mark '@'
      boards.AI[row ][col] = '@';
      boards.playerViewAIBoard[row][col] = '@';

    }
    else
    {
      boards.AI[row][col] = 'X';   //if not hit, mark 'X'
      boards.playerViewAIBoard[row ][col] = 'X';
    }

  }

}

//function for basic firing
void generalfire()
{
  string target;
  int targetRow, targetCol;
  target = playerInput();

  //convert the coordinates to digits
  targetRow = (int)target[0] - 'A';
  targetCol = (int)target[1] - '0';

  fire(targetRow, targetCol);
}

//check whether the required ship has been sunk or not
bool sunk(int num)
{
  //getting the position of the ship
  int x1 = fleet[num].xposini;
  int x2 = fleet[num].xposfnl;
  int y1 = fleet[num].yposini;
  int y2 = fleet[num].yposfnl;

  //for the case when the ship is placed vertically
  if (x1 == x2)
  {

    //check if all parts of the ship has been hit
    for (int i = y1; i <= y2; i++)
    {
      if (boards.player[i][x1] != '@')
      {
        return false;
      }
    }
  }

  //for the case when the ship is placed vertically
  else if (y1 == y2)
  {

    //check if all parts of the ship has been hit
    for (int i = x1; i <= x2; i++)
    {
      if (boards.player[y1][i] != '@')
      {
        return false;
      }
    }
  }

  //print sunk message to the player
  cout<<endl<<fleet[num].name<<"has been sunk, type anything to confirm"<<endl;
  return true;
}

//determine which country is selected
int selcountry(string country)
{
  int num = -1;
  if (country == "japan")
  {
    num = 0;
  }
  else if (country == "germany")
  {
    num = 1;
  }
  else if (country == "italy")
  {
    num = 2;
  }
  else if (country == "us")
  {
    num = 3;
  }
  else if (country == "gb")
  {
    num = 4;
  }

  return num;
}

//function for squadron feature
void squadron(string country)
{

  //check if the aircraft carrier is sunk
  if (sunk(0))
  {
    string sth;
    cin>>sth;
  }

  //check if the aircraft carrier is out of planes
  else if (spweapons[0] == 0)
  {
    cout<<endl<<"Out of planes to form attack squadrons or reconnaissance! Type anything to confirm"<<endl;
    string sth;
    cin>>sth;
  }
  else
  {
    int num = selcountry(country);
    cout<<endl<<"***"<<fleet[0].name<<" REPORTING***"<<endl;
    cout<<radar[num]<<" OPERATIVE"<<endl;

    //to randomize the plane for attack squadron once
    if(planeflag == 0)
    {
      plane1 = rand() % numofplane[num];
      planeflag = 1;
    }

    string s = " ready to go";

    //getting the mode for planes
    cout<<endl<<"***AWAITING ORDERS***"<<endl;
    cout<<"To launch assault, type \"1\""<<endl<<"To conduct reconnaissance, type \"2\""<<endl;

    while (true)
    {
      string plane;
      cin>>plane;

      //for attacking
      if (plane == "1")
      {
        if (spweapons[1] == 1)
        {

          //picking a plane for different country
          cout<<endl;
          if (num == 0)
          {
            cout<<bomber.ijn[plane1]<<s;
          }
          else if (num == 1)
          {
            cout<<bomber.kms[plane1]<<s;
          }
          else if (num == 2)
          {
            cout<<bomber.rm[plane1]<<s;
          }
          else if (num == 3)
          {
            cout<<bomber.hms[plane1]<<s;
          }
          else if (num == 4)
          {
            cout<<bomber.uss[plane1]<<s;
          }

          cout<<endl<<endl<<"***AWAITING ASSUALT COORDINATES***"<<endl;
          cout<<"Please enter the center coordinates of the attack zone with a \"+\" pattern"<<endl;

          //getting the center coordinates of the hit zone
          string center;
          cin>>center;

          //validating the coordinates
          while (!(checkvalidinput(center)))
          {
            cout<<"Invalid coordinates! Please input valid coordinates"<<endl;
            getline(cin, center);
          }

          int centerRow, centerCol;
          centerRow = (int)center[0] - 'A';
          centerCol = (int)center[1] - '0';

          //storing all the coordinates of the hit zone to targets[]
          Target targets[5];

          targets[0].row = centerRow -1;
          targets[0].col = centerCol;

          for (int i = 0; i < 3; i++)
          {
            targets[i+1].row = centerRow;
            targets[i+1].col = centerCol-1+i;
          }

          targets[4].row = centerRow +1;
          targets[4].col = centerCol;

          //firing on the hit zone
          for (int i = 0; i < 5; i++)
          {
            fire(targets[i].row, targets[i].col);
          }
          spweapons[1] = 0;
          spweapons[0] -=1;
        }
        else
        {
          cout<<"Out of planes to form attack squadron! Please type anything to confirm"<<endl;
          string sth;
          cin>>sth;
        }
        break;
      }

      //for recon mode
      else if (plane == "2")
      {
        if (spweapons[2] == 1)
        {
          cout<<endl<<recon[num]<<s<<endl;
        }

        cout<<endl<<"***AWAITING RECONNAISSANCE COORDINATES***"<<endl;
        cout<<"Please enter the center coordinates of the recon zone with a \"X\" pattern"<<endl;

        //getting the center coordinates of the recon zone
        string center;
        cin>>center;

        //validating the coordinates
        while (!(checkvalidinput(center)))
        {
          cout<<"Invalid coordinates! Please input valid coordinates"<<endl;
          getline(cin, center);
        }

        int centerRow, centerCol;
        centerRow = (int)center[0] - 'A';
        centerCol = (int)center[1] - '0';

        //storing the coordinates of the recon zone
        Target targets[5];

        int j = 0;
        for (int i = 0; i < 2; i++)
        {
          targets[i].row = centerRow - 1;
          targets[i].col = centerCol - 1 + j + i;
          j++;
        }

        targets[2].row = centerRow;
        targets[2].col = centerCol;

        j = 0;
        for (int i = 0; i < 2; i++)
        {
          targets[i+3].row = centerRow + 1;
          targets[i+3].col = centerCol - 1 + j + i;
          j++;
        }

        char row[10] = {'A','B','C','D','E','F','G','H','I','J'};

        int flag = 0;

        //scanning on the given zone
        for (int i = 0; i < 5; i++)
        {

          //if hostile found
          if (boards.AI[targets[i].row][targets[i].col] == 'O')
          {
            cout<<endl<<"ENEMY SPOTTED IN "<<row[targets[i].row]<<targets[i].col<<endl;
            boards.playerViewAIBoard[targets[i].row][targets[i].col] = '!';
            flag = 1;
          }

          //if no hostile found
          else
          {
            boards.AI[targets[i].row][targets[i].col] = 'X';   //if not hit, mark 'X'
            boards.playerViewAIBoard[targets[i].row][targets[i].col] = 'X';
          }
        }

        cout<<endl<<"***RECONNAISSANCE COMPLETED***"<<endl;
        if (flag == 0)
        {
          cout<<"NO HOSTILE SPOTTED"<<endl;
        }
        cout<<endl<<"Please type anything to confirm"<<endl;
        string sth;
        cin>>sth;
        break;
      }
      else
      {
        cout<<"Invalid command, please type as instructed above"<<endl;
      }
    }
  }
}

//function for the barrage feature
void barrage(string country)
{

  //check if the battleship is sunk
  if (sunk(1))
  {
    string sth;
    getline(cin,sth);
  }

  //check if the battleship is out of shells
  else if (spweapons[3] == 0)
  {
    cout<<endl<<"Out of shells for performing barrage! Type anything to confirm"<<endl;
    string sth;
    getline(cin,sth);
  }
  else
  {
    int num = selcountry(country);
    cout<<endl<<"***"<<fleet[1].name<<" REPORTING***"<<endl;
    cout<<radar[num]<<" OPERATIVE"<<endl;
    cout<<shell[num]<<" ARMED"<<endl;
    cout<<"Ready to launch, input center coordinates of a 3x3 grid"<<endl;

    //getting the center coordinates of the hit zone
    string center;
    getline(cin, center);

    //validating the coordinates
    while (!(checkvalidinput(center)))
    {
      cout<<"Invalid coordinates! Please input valid coordinates"<<endl;
      getline(cin, center);
    }


    int centerRow, centerCol;
    centerRow = (int)center[0] - 'A';
    centerCol = (int)center[1] - '0';

    //storing all the coordinates of the hit zone to targets[]
    Target targets[9];

    //for the first row
    for (int i = 0; i < 3; i++)
    {
      targets[i].row = centerRow -1;
      targets[i].col = centerCol -1 +i;
    }

    //for the second row
    for (int i = 0; i < 3; i++)
    {
      targets[i+3].row = centerRow;
      targets[i+3].col = centerCol-1+i;
    }

    //for the third row
    for(int i = 0; i < 3; i++)
    {
      targets[i+6].row = centerRow+1;
      targets[i+6].col = centerCol-1 +i;
    }

    //fire according to the coordinates
    for (int i = 0; i < 9; i++)
    {
      fire(targets[i].row, targets[i].col);
    }

    spweapons[3] = 0;
  }
}

//function for the cruiser feature
void cruiser(string country)
{

  //check if the heavy cruiser is sunk
  if (sunk(2))
  {
    string sth;
    getline(cin,sth);
  }

  //check if the heavy cruiser is out of torpedos
  else if (spweapons[4] == 0)
  {
    cout<<endl<<"Out of torpedos to perform strike! Type anything to confirm"<<endl;
    string sth;
    getline(cin,sth);
  }
  else
  {
    int num = selcountry(country);
    cout<<endl<<"***"<<fleet[2].name<<" REPORTING***"<<endl;
    cout<<radar[num]<<" OPERATIVE"<<endl;
    cout<<torpedo[num]<<" ARMED"<<endl;
    cout<<"Ready to launch, input center coordinates of a 1x3 or 3x1 grid"<<endl;

    //getting the center coordinates of the torpedo
    string center;
    getline(cin, center);

    //validating the coordinates
    while (!(checkvalidinput(center)))
    {
      cout<<"Invalid coordinates! Please input valid coordinates"<<endl;
      getline(cin, center);
    }

    //getting the firing mode
    cout<<endl<<"***INPUT TORPEDO MODE***"<<endl<<"For horizontal mode, type \"h\""<<endl<<"For vertical mode, type \"v\""<<endl;
    char mode;
    cin>>mode;

    int centerRow, centerCol;

    centerRow = (int)center[0] - 'A';
    centerCol = (int)center[1] - '0';

    //getting the coordinates of the hit zone
    Target targets[3];
    while (true)
    {
      if (mode == 'h')
      {
        for (int i = 0; i < 3; i++)
        {
          targets[i].row = centerRow;
          targets[i].col = centerCol -1 + i;
        }
        break;
      }
      else if (mode == 'v')
      {
        for (int i = 0; i < 3; i++)
        {
          targets[i].row = centerRow -1 + i;
          targets[i].col = centerCol;
        }
        break;
      }
      else
      {
        cout<<"Invalid mode! Please input as instructed above"<<endl;
      }
    }

    //firing on the hit zone
    for (int i = 0; i < 3; i++)
    {
      fire(targets[i].row, targets[i].col);
    }

    spweapons[4] -= 1;
  }
}

//function for the sub feature
void sub(string country)
{

  //check if the submarine is sunk
  if (sunk(3))
  {
    string sth;
    getline(cin,sth);
  }
  else
  {
    int num = selcountry(country);
    cout<<endl<<"***"<<fleet[3].name<<" REPORTING***"<<endl;
    cout<<"PERISCOPE DEPTH AND STABLE"<<endl;

    //check the if there are any torpedo left
    if (spweapons[5] == 0)
    {
      cout<<torpedo[num]<<" DEPLEPTED"<<endl;

    }
    else
    {
      cout<<torpedo[num]<<" ARMED"<<endl;
    }
    cout<<endl<<"***AWAITING ORDERS***"<<endl;

    //getting the mode for operation
    cout<<"To launch torpedo, type \"torpedo\""<<endl<<"To perform scanning, type \"scanning\""<<endl;


    while (true)
    {
      string plan;
      getline(cin,plan);
      //if torpedo is chosen
      if (plan == "torpedo")
      {
        //check if the submarine is out of torpedos
        if (spweapons[5] == 0)
        {
          cout<<endl<<"Out of torpedos to perform strike! Type anything to confirm"<<endl;
          string sth;
          getline(cin,sth);
        }
        else
        {
          cout<<endl<<"***ENTER FIRING PATTERN***"<<endl<<"To fire the torpedo horizontally, type \"h\""<<endl<<"To fire the torpedo vertically, type \"v\""<<endl;

          char mode;
          cin>>mode;

          //validating the mode
          while (true)
          {
            if (mode != 'h' && mode != 'v')
            {
              cout<<"Invalid mode! Please input as instructed above"<<endl;
              cin>>mode;
            }
            else
            {
              break;
            }
          }

          //getting the starting point of the torpedo
          cout<<endl<<"Input the starting point the torpedo's course which is a point along the edge"<<endl;
          string center;
          cin>>center;

          //validating the coordinates
          while (!(checkvalidinput(center)))
          {
            cout<<"Invalid coordinates! Please input valid coordinates"<<endl;
            getline(cin, center);
          }

          int centerRow, centerCol;

          centerRow = (int)center[0] - 'A';
          centerCol = (int)center[1] - '0';

          //firing the torpedo horizontally
          if (mode == 'h')
          {

            //firing the torpedo from the right side of the map
            if (centerCol == 9)
            {
              for (int i = 0; i < 10; i++)
              {
                fire(centerRow, 9-i);
                if (boards.AI[centerRow][9-i] == '@')
                {
                  break;
                }
              }
            }

            //firing the torpedo from the left side of the map
            else
            {
              for (int i = 0; i < 10; i++)
              {
                fire(centerRow, i);
                if (boards.AI[centerRow][i] == '@')
                {
                  break;
                }
              }
            }
          }

          //firing the torpedo vertically
          else
          {

            //firing the torpedo from the south side of the map
            if (centerRow == 9)
            {
              for (int i = 0; i < 10; i++)
              {
                fire(9-i, centerCol);
                if (boards.AI[9-i][centerCol] == '@')
                {
                  break;
                }
              }
            }

            //firing the torpedo from the north side of the map
            else
            {
              for (int i = 0; i < 10; i++)
              {
                fire(i, centerCol);
                if (boards.AI[i][centerCol] == '@')
                {
                  break;
                }
              }
            }
          }
        spweapons[5] -= 1;
        }
        break;
      }

      //if scanning mode is chosen
      else if (plan == "scanning")
      {

        //getting the center coordinates of the scanning zone
        cout<<"Please enter the center coordinates of a 3x3 grid"<<endl;
        string center;
        cin>>center;

        //validating the coordinates
        while (!(checkvalidinput(center)))
        {
          cout<<"Invalid coordinates! Please input valid coordinates"<<endl;
          getline(cin, center);
        }

        int centerRow, centerCol;
        centerRow = (int)center[0] - 'A';
        centerCol = (int)center[1] - '0';

        //storing all the coordinates of the scanning zone to targets[]
        Target targets[9];

        //for the first row
        for (int i = 0; i < 3; i++)
        {
          targets[i].row = centerRow -1;
          targets[i].col = centerCol -1 +i;
        }

        //for the second row
        for (int i = 0; i < 3; i++)
        {
          targets[i+3].row = centerRow;
          targets[i+3].col = centerCol-1+i;
        }

        //for the third row
        for(int i = 0; i < 3; i++)
        {
          targets[i+6].row = centerRow+1;
          targets[i+6].col = centerCol-1 +i;
        }

        //scanning the zone
        int flag = 0;
        for (int i = 0; i < 9; i++)
        {

          //if AI vessel found in the zone
          if (boards.AI[targets[i].row][targets[i].col] == 'O')
          {
            cout<<"***SONAR SWEEP DETECTS ENEMY VESSEL --- PRECISE LOCATION UNCONFIRMED***"<<endl;
            flag = 1;
            break;
          }
        }

        //if no AI vessel are found in the zone
        if (flag == 0)
        {
          cout<<"***SONAR SWEEP CONFIRMS NO HOSTILE IN SELECTED WATERS***"<<endl;
        }

        cout<<"Type anything to confirm"<<endl;
        string sth;
        cin>>sth;
        break;
      }
      else
      {
        cout<<"Invalid command, please type as instructed above"<<endl;
      }
    }
  }
}

//function for allowing player to pick which advanced weapon
void advancedweapons(string country)
{
  printBoard();

  cout<<endl<<"To use regular rounds, type \"ap\""<<endl;
  cout<<"To launch "<<fleet[0].name<<"'s torpedo bomber squadron, type \"plane\""<<endl;
  cout<<"To launch "<<fleet[1].name<<"'s barrage, type \"barrage\""<<endl;
  cout<<"To launch "<<fleet[2].name<<"'s torpedo, type \"cruiser\""<<endl;
  cout<<"To launch "<<fleet[3].name<<"'s torpedo, type \"sub\""<<endl;
  while(true)
  {
    string mode;
    getline(cin,mode);

    if (mode == "ap")
    {
      generalfire();
      break;
    }
    else if (mode == "plane")
    {
      squadron(country);
      break;
    }
    else if (mode == "barrage")
    {
      barrage(country);
      break;
    }
    else if (mode == "cruiser")
    {
      cruiser(country);
      break;
    }
    else if (mode == "sub")
    {
      sub(country);
      break;
    }
    else if (mode == "q")
    {
      break;
    }
    else
    {
      cout<<"***INVALID ORDER, PLEASE RETRY INPUTTING ORDERS AS INSTRUCTED ABOVE***"<<endl;
    }
  }
}

int main() {
    ships uss[50], kms[50], hms[50], rm[50], ijn[50];

    naming(uss,"USS");
    naming(kms,"KMS");
    naming(hms,"HMS");
    naming(rm,"RM");
    naming(ijn,"IJN");

    srand(time(NULL));

    int flag = 0;
    printBoard();
    cout<<"To play as the United States, type \"us\""<<endl;
    cout<<"To play as Great Britain, type \"gb\""<<endl;
    cout<<"To play as German Reich, type \"germany\""<<endl;
    cout<<"To play as the Kingdom of Italy, type \"italy\""<<endl;
    cout<<"To play as the Empire of Great Japan, type \"japan\""<<endl<<endl;
    string country;

    while (true)
    {
      getline(cin,country);
      if (!(country == "us" || country == "gb" || country == "germany" || country == "italy" || country == "japan"))
      {
        cout<<"***Invalid country name inputted! Please enter the country name according to the above instructions***"<<endl;
        continue;
      }
      else
      {
        break;
      }
    }

    genfleet(uss, kms, hms, rm, ijn, country, fleet);
    deployment(boards.player);
    generateRandomBoard(boards.AI);

    while (true) {
      cout<<"AWAITING ORDER"<<endl;
      cout<<"To fire regualr rounds, type \"ap\""<<endl;
      cout<<"To use special weapons, type \"aw\""<<endl;
      cout<<"To quit the game, type \"q\""<<endl;

      string mode;
      getline(cin,mode);
      if (mode == "ap")
      {
        generalfire();
      }
      else if (mode == "aw")
      {
        advancedweapons(country);
      }
      else if (mode == "Q" || mode == "q")
      {
          break;
      }
      else
      {
        cout<<"***INVALID ORDER, PLEASE RETRY INPUTTING ORDERS AS INSTRUCTED ABOVE***"<<endl;
      }
        tempPrintBoard();
    }
    return 0;
}
