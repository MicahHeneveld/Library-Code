#pragma once

#include "Book.h"
#include <algorithm> 
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

class Library
{
 private:
  int count; //the number of books in the unsorted array
  static constexpr int MAX_BOOKS = 1000; 
  int shelf_coords; //maps location of book placement
  Book books[MAX_BOOKS];  //maximum number of books that can be stored in the library
  std::ofstream library_log; //file name of log printed when program is finished running
 

  /**
  Reads books in from the input file and stores them into lists
  **/
  void book_load();
  /**
  Function to clear all sorted lists
  **/
  void book_clear(); 
  /**
  Fuction to search by title
  **/
  int title_search(const string &title); 

 public:


  /**
  Constructor function.  Runs the book_load function after opening up the log
  **/
  Library(); 

  /**
  Gets Book info from the user through the console, then sorts that book into
  the correct position on each of the lists
  **/
  void book_insert(); 

  /**
  Gets a unwanted Book's name from the user and deletes it
  **/
  void book_delete(); 

  /**
  Asks how the user would like their books printed, and prints them accordingly
  **/
  void book_list(); 

  /**
  Writes the data to the output file
  **/
  void book_save(); 
};
