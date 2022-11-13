#define EXTRA_LOG

#include "Library.h"

using std::ifstream; //Allows input file access
using std::ofstream; //Allows output file access
using std::cin; //Allows for user input
using std::cout; //Allows for output to the console
using std::cerr; //used for error messages
using std::set;  //Allows for the use of set
using std::endl;  //Allows for the use of endl

/**
Auto function to sort by title, author, or subject
**/
auto compareTitles = [](Book *lhs, Book *rhs) //Sorts by title of the book
{
  return lhs->title < rhs->title;
};

auto compareAuthors = [](Book *lhs, Book *rhs) //Sorts by book author
{
  return lhs->author < rhs->author;
};

auto compareSubject = [](Book *lhs, Book *rhs) //Sorts by book subject
{
  return lhs->subject < rhs->subject;
};

//Set is used for the sorted lists
set<Book *, decltype(compareTitles)> ByTitle(compareTitles);
set<Book *, decltype(compareAuthors)> ByAuthor(compareAuthors);
set<Book *, decltype(compareSubject)> BySubject(compareSubject);



void Library::book_load()  //Reads in the input file and creates the lists
{
    ifstream inFile;  //declare input file
    inFile.open("BookIven.txt");  //open the input file

    count = 0;  //variable that keeps track of current book count

    book_clear(); //clears all previous lists

    if (!inFile.is_open()) //makes sure input file can be read
    {
        cerr << "ERROR!!!\nUnable to open 'BookIven.txt'." << "\n";
        exit(0);
    }

    Book book;  //declares book object

     /**
     while loop that runs while the input file reads data into book's title, author, and subject variables
     **/
    while (getline(inFile, book.title), getline(inFile, book.author), getline(inFile, book.subject))
    {
        books[count] = book; //inserts the book into the list

        /**
        sorts book into the sorted lists by passing a reference
        **/
        ByTitle.insert(&books[count]);
        ByAuthor.insert(&books[count]);
        BySubject.insert(&books[count]);

        library_log << book.title << " has been added.\n";  //outputs to the log what book has been added
        shelf_coords = 0;
        for (auto const& bo : ByTitle)
        {
            if (bo->title == book.title)
                break;
            ++shelf_coords;
        }
#ifdef EXTRA_LOG
        library_log << "\tInserted " << book.title << " at location " << shelf_coords;  //outputs to the log where the book has been added
        shelf_coords = 0;
        for (auto const& bo : ByAuthor)
        {
            if (bo->title == book.title)
                break;
            ++shelf_coords;
        }
        library_log << "\n\tInserted " << book.author << " at location " << shelf_coords;  //outputs to the log where the author's name has been added
        shelf_coords = 0;
        for (auto const& bo : BySubject)
        {
            if (bo->title == book.title)
                break;
            ++shelf_coords;
        }
        library_log << "\n\tInserted " << book.subject << " at location " << shelf_coords << "\n\n";  //outputs to the log where the book's subject has been added
#endif
        ++count;
    }
    inFile.close();  //closes the input file
}

void Library::book_clear()  //clears book listing
{ 
  ByTitle.clear();
  ByAuthor.clear();
  BySubject.clear();
}


int Library::title_search(const string &title)  //searches for book by its title
{  
  for (int b = 0; b < count; b++)
    if (books[b].title == title) return b;

  return -1;
}

Library::Library() //constructor that opens log and runs the book_load() function
{
  library_log.open("Log.txt");
  book_load();
}


void Library::book_insert()  //inserts a user given book into the lists
{
    if (count >= MAX_BOOKS)  //makes sure the max amount of books hasn't been reached
    {
        cerr << "ERROR: This library is filled to the brim!"
             << "\n";
        return;
    }
    Book book;  //declare book object

    cout << "Enter the Book's Title: "; //get book title from user
    getline(cin, book.title);
    cout << "Enter the Book's Author: "; //get book author from user
    getline(cin, book.author);
    cout << "Enter the Book's Subject: "; //get book subject from user
    getline(cin, book.subject);

    /**
    Makes sure the user input is valid
    **/
    if (book.title.empty() || book.author.empty() || book.subject.empty())
    {
        cerr << "ERROR: A book needs a Title, Author, and Subject."
             << "\n";
        return;
    }

    if (title_search(book.title) >= 0)
    {
        cerr << "ERROR: It appears that book is already in the library."
             << "\n";
        return;
    }
    books[count] = book;  //book added to the list
    
    /**
    book added to the sorted lists
    **/
    ByTitle.insert(&books[count]);
    ByAuthor.insert(&books[count]);
    BySubject.insert(&books[count]);

    cout << book.title << " has been added.";  //let user know book has been added through the console
    library_log << book.title << " has been added.\n";  //let user know the book has been added through the log
    
    shelf_coords = 0;  //sort book by title
    for (auto const& bo : ByTitle)
    {
        if (bo->title == book.title)
            break;
        ++shelf_coords;
    }
#ifdef EXTRA_LOG
    library_log << "\tInserted " << book.title << " at location " << shelf_coords;  //let user know where the book title was inserted through the log
    shelf_coords = 0;

    for (auto const& bo : ByAuthor)  //sort book by author
    {
        if (bo->title == book.title)
            break;
        ++shelf_coords;
    }
    library_log << "\n\tInserted " << book.author << " at location " << shelf_coords;  //let user know where the book's author was inserted through the log
    shelf_coords = 0;

    for (auto const& bo : BySubject)  //sort book by subject
    {
        if (bo->title == book.title)
            break;
        ++shelf_coords;
    }
    library_log << "\n\tInserted " << book.subject << " at location " << shelf_coords << "\n\n"; //let user know where the book's subject was inserted through the log
#endif

    ++count; 
}

void Library::book_delete()  //deletes unwanted book from the list
{
    string title;  //name of unwanted book
    cout << "Book's title:  " << endl;;  //ask user for the name of the book
    getline(cin, title);  //get input from user
    int index = title_search(title);  //searches for book

    if (index == -1)  //makes sure the input is valid
    {
        cerr << "ERROR: The book mentioned does not exist."
             << "\n";
        return;
    }

    for (int b = index; b < count - 1; ++b) books[b] = books[b + 1]; //decreases book count
    --count;

    book_clear();  //clears book
    for (int b = 0; b < count; b++)
    {
        ByTitle.insert(&books[b]);
        ByAuthor.insert(&books[b]);
        BySubject.insert(&books[b]);
    }

    /**
    output to he console and log that the book has been deleted
    **/
    cout << "The book known as '" << title << "' has been deleted.\n\n";
    library_log << "The book known as '" << title << "' has been deleted.\n\n";
}


void Library::book_list()  //list books according to the user's wishes
{
    if (count == 0)  //makes sure there are books to list
    {
        cerr << "ERROR: This library lacks books."
            << "\n";
        return;
    }
    cout << "\nHow would you like to sort the books?\n1:  Title\n2:  Author\n3:  Subject" << endl;  //asks user how they want their books listed
    char menOp;  //stores user input
    cin >> menOp;  //gets user input
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores additional characters

    switch (menOp) //switch that asks the user how they wish to print out the books
    {
        
    case 49: //Prints by Title first
        cout << "\nPrinting by title\n\n";
        library_log << "\nPrinted to console by title.\n";
        for (auto const& bo : ByTitle)
        {
            cout << "\t" << bo->title << "\n";  //pointer returns the title
            cout << "\t" << bo->author << "\n";  //pointer returns the author
            cout << "\t" << bo->subject << "\n\n";  //pointer returns the subject
        }
        break;

    case 50: //Prints by Author first
        cout << "\nPrinting by author\n\n";
        library_log << "\nPrinted to console by author.\n";
        for (auto const& bo : ByAuthor)
        {
            cout << "\t" << bo->author << "\n";  //pointer returns the author
            cout << "\t" << bo->title << "\n";  //pointer returns the title
            cout << "\t" << bo->subject << "\n\n";  //pointer returns the subject
        }
        break;

    case 51: //Prints by Subject first
        cout << "\nPrinting by subject\n\n";
        library_log << "\nPrinted to console by subject.\n\n";
        for (auto const& bo : BySubject)
        {
            cout << "\t" << bo->subject << "\n";  //pointer returns the subject
            cout << "\t" << bo->author << "\n";  //pointer returns the author
            cout << "\t" << bo->title << "\n\n";  //pointer returns the title
        }
        break;
    
    default:cerr << "ERROR: invalid option.\n";  //handles invalid input
    }
}

void Library::book_save()  //prints data to the same file that was used for the input
{ 
  ofstream outfile("BookIven.txt");
  cout << "\nQuit successful, saved progress\n";
  library_log << "\nUser exited program, books saved successfully.";
  
  
  for (auto const &bo : ByTitle) //prints library to file
  {
    outfile << bo->title << "\n";
    outfile << bo->author << "\n";
    outfile << bo->subject << "\n";
  }

  outfile.close();  //closes output file
}