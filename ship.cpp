#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  ifstream fin;
  fin.open("ship.txt");
  string x;
  int count;
  if (fin.fail()) {
		cout << "Error in file opening!"<< endl;
  	exit(1);
   }


  while (getline(fin,x))
  {
    for (int i = 0; i < 60; i++)
    {
      if (x[i] == '1')
      {
        cout<<"#";
      }
      else
      {
        cout<<" ";
      }
    }
    cout<<endl;

  }
  fin.close();

  return 0;
}
