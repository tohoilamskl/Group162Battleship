#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "displayGameHistory.h"
using namespace std;

//structure for storing and sorting all game records (for dynamic array)
struct GameRecords {
  int won;
  int totalMoveUsed;
  string gameName;
  string playerName;
  string country;
  string date;
  GameRecords* next;
};

//function to print all game records history
void printAllRecords(GameRecords* &head){
  GameRecords* current = head;

  system("CLS");

  cout << "Rank  Player Name    Game Name   Country Result Move         Date" << endl;
  cout << "---- ------------ ------------ --------- ------ ---- ------------" << endl;

  for(int i = 1; current!=NULL; i++){
    cout << setw(4) << i << " " << setw(12) << current->playerName << " " << setw(12) << current->gameName << " ";
    cout << setw(9) << current->country << " " << setw(6) << ((current->won) ? "Won" : "Lose") << " ";
    cout << setw(4) << current->totalMoveUsed << " " << setw(12) << current->date << endl;
    current = current->next;
  }
  current = new GameRecords;
  delete current;
}

//function to sort and store the game history records in order of (win, then lose), then (ascending order of amount of moves used)
void newGameRecord(GameRecords* &head, string line, int size){
  int wonInt, movesInt;
  string won, move, gameName, playerName, date, country;
  bool newRecordInserted = false;

  //store all information of this record into a temporary dynamic array of data
  cout << line << endl;
  istringstream iss(line);
  iss >> won >> move >> playerName >> gameName >> country >> date;
  wonInt = stoi(won);
  movesInt = stoi(move);

  GameRecords* temp = new GameRecords;
  GameRecords* current = head;
  GameRecords* data = new GameRecords;
  data->won = wonInt;
  data->totalMoveUsed = movesInt;
  data->playerName = playerName;
  data->gameName = gameName;
  data->country = country;
  data->date = date;
  data->next = NULL;

  //store records into the dynamic array in a specific order
  if(head == NULL || (wonInt > head->won || (wonInt == head->won && movesInt <= head->totalMoveUsed))){
    temp = head;
    data->next = temp;
    head = data;
    newRecordInserted = true;
  }
  else{
    while (current->next != NULL){
      if (wonInt > current->next->won || (wonInt == current->next->won && movesInt <= current->next->totalMoveUsed)){
        data->next = current->next;
        current->next = data;

        newRecordInserted = true;
        break;
      }
      current = current->next;
    }
  }
  if(!newRecordInserted){
    current->next = data;
  }

  temp = new GameRecords;
  current = new GameRecords;
  data = new GameRecords;
  delete temp;
  delete current;
  delete data;
}

//function to access file "Game_History.txt", extracting all game history records
void showGameRecord(){
  int size = 0;
  string input, line;
  GameRecords* head = NULL;

  ifstream fin;
  fin.open("Game_History.txt");
  if(fin.fail()){
    cout << "Failed opening file!" << endl;
    exit(1);
  }

  //loop until all records in the file have been optained, and stored in a dynamic array structure
  while(getline(fin, line)){
    newGameRecord(head, line, size);
  }
  fin.close();

  printAllRecords(head);

  cout << endl << "Q to quit: ";
  getline(cin, input);

}
