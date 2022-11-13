/**
Program Name: Library
Created Date: 5/12/2022
Created By: Micah Heneveld
Acknowledgements:  Joshua Dye for guiding me on how to properly use sets
**/

#include <iostream>  //need to read input from console, and read output to the console
#include "Library.h"  //header file

using std::cin;
using std::cout;
using std::endl;

int main() 
{
  char menOp; //Stores the user's command
  Library lib; //Declare Library object
  do //do while menOp does not equal 4
  {
    cout << "What would you like to do?\n1: Add Book\n2: Delete Book\n3: List All Books\n4: Quit" << endl;  //ask user for input
    cin >> menOp;  //gets user input
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores invalid and unnersscary characters
    
    switch (menOp) //finds what the user wants
    {
      case 49: 
          lib.book_insert();
        break;
      case 50: 
          lib.book_delete();
        break;
      case 51:
          lib.book_list();
        break;
    }
  } 
  while (menOp != '4');
  lib.book_save(); //Calls function to save books to the file
  return 0;
}