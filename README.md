# Library-Code
Code written for Shasta College


The Library-Code was written as a response to the following prompt:

 Library Inventory Database

Write a program that maintains a list of books for a library. The program must accept commands to make insertions and deletions in this list, while simultaneously maintaining the list in alphabetical order for three string type keys: Subject, Author, and Title.

Input
1. The book information created in previous executions of this program, if any, is stored in the text file "books.txt". Each book's information is on three consecutive lines.

2. The program inputs commands from the user (keyboard) to insert, delete, list by key, and quit. You are free to implement the "user interface" part of the program as you wish, as long as it is easy to use.

Output
1. The results of each operation should be written to the screen. In addition, transaction information describing the processing of each command should be written to an output file. (For instance, for an Insert command, the output file should contain the title, author, and subject information, as well as the location where the record was inserted and the location of its entry in each ordering array.) The information in the output file should be neatly formatted and clearly labeled.

2. The "books.txt" text file should be rewritten to contain the updated book information.

Data Structures
The records containing information about each book (subject, author, and title strings) must be stored in an array. These records may be stored in consecutive array slots in the order in which they are inserted. For example, if the book information is stored in an array called bookData, bookData[0] contains information about the first book inserted, bookData[1] contains information about the second book inserted and so on.

The list must be maintained in order by title, in order by author, and in order by subject by using arrays of pointers (indexes), one for each key. For instance, suppose the key order information is stored in arrays of KeyOrderType, as described below:

typddef int[MAX_BOOKS] KeyOrderType;

titleOrder : KeyOrderType;

authorOrder : KeyOrderType;

subjectOrder : KeyOrderType;

The zero'th array slot contains the index of the first book record with the appropriate key. For example, titleOrder[0] indicates the index of the book that comes first alphabetically by title. If titleOrder[0] = 5, then bookData[5] contains the first alphabetical title. The next book, in alphabetical order by title, would be found in the bookData array at the index indicated by titleOrder[1]. For index >= 0, titleOrder[index]contains the index in bookData of the next title in the alphabetic ordering. The authorOrder and subjectOrder arrays work similarly. (The arrays may be bound together in a struct, if you wish. They are described here as separate entities only for clarity.)

