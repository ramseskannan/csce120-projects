#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "book.h"
#include "member.h"
#include "library.h"
#include "lms_utilities.h"

int read_list_of_books(Library& library, const std::string& filename) {
   // TODO(student)
   //trying to open the file
   std::ifstream f(filename);
   if (!f){
      throw std::runtime_error("Cannot open " + filename);
   }

   // now we count for how many books we add succesffully
   int books_add = 0;
   //the text file consisits of lines of text, 3:
   //titlem author first and last name isbn
   //the parameterized constructors for the Book class check if the arguements are correct.

   std::string titlel, authorLine, isbn; //variavles to store the three lines for each book
   //line 1: title
   //line 2: author first and last name
   //line 3: ISBN

   //now we read the book (the 3 lines)
   while (std::getline(f, titlel)){
      //checkingif the title is empty
      if (titlel.empty()) continue;

      //reading the auhtor line (first and last which is seperated by a space)
      if(!std::getline(f, authorLine)) break;

      //reading the ISBN line, has to be 10 or 13 digits and A STRING
      if(!std::getline(f, isbn)) break;
      
      //we have to get the first and last name seperatly
      std::istringstream author_stream(authorLine);
      std::string first_name, lastname;
      author_stream >> first_name >> lastname;

      //also if the constructor throws an exception, we catch it, ignore the book that caused it and go to next book 

      //now we try to create and add the book and we have to fall the library.add_book() to add the book into library
      try {
         library.add_book(Book(titlel, first_name, lastname, isbn));
         books_add++;
      } catch(...){
         //this silenty ignores all the invalid books
      }
   }
      return books_add; //we have to return the total # of valid books added
}


int read_list_of_members(Library& library, const std::string& filename) {
   //in this one we load the member data from a tet file into a librayr
   //the name of the test file is given by a string argument
   //if the text file cant be opened we throw a runtime error
   std::ifstream f(filename);
   if(!f){
      throw std::runtime_error("Cannot open " + filename);
   }

   //keep track of registered members
   int members_reg = 0;
   //the text files consists of member names
   //first, space, last ---> in each line
   std::string lines;

   //we are also assigned ID, in the doc it says we have to start from 1000
   int id_assign = 1000;

   while(std::getline(f, lines)){
      //skipping blank lines
      if (lines.empty()) continue;

      //we have to parse it to get first space and last
      //we also need to assign ID
      std::istringstream stream(lines);
      std::string first_name, last_name;

      stream >> first_name >> last_name;

      //now we attempt to create and register the member and calling the function library.register_member()
      try {
         library.register_member(Member(first_name, last_name, id_assign));
         members_reg++;
         id_assign++; //incremmeitng the ID for the next member
      } catch(...){
         //ignore invalid member data the ID is not incrememnted because it wasnt valid!
      }
   }

   return members_reg; //returning the number of memebers added
}

int read_list_of_borrowed_books(Library& library, const std::string& filename) {

   //opening the file, if cannot open file throw an error
   std::ifstream f(filename);
   if (!f){
      throw std::runtime_error("Cannot open " + filename);
   }
   //tracking borrowing books
   int borrowing_books = 0;
   //text file has ISBN and member ID
   std::string lines;

   while(std::getline(f, lines)){
      //skip empty lines
      if (lines.empty()) continue;

      //getting the ISBN and member ID
      std::istringstream stream(lines);
      std::string isbnBook;
      int id_of_borrower;

      stream >> isbnBook >> id_of_borrower;

      //attempting to borrow the book
      //borrow_book vaildates ISBN and member ID
      std::string msg; //this will store success or error mesg
      if (library.borrow_book(isbnBook, id_of_borrower, msg)){
         borrowing_books++;
      }
      //so here if the borrow failsm it will continue to nexxt one discretly
   }
   return borrowing_books; //returning the number of book sborrowed 
}

int read_list_of_returned_books(Library& library, const std::string& filename) {
   // TODO(student)
   //opening the file, if cannot open file throw an error
   std::ifstream f(filename);
   if (!f){
      throw std::runtime_error("Cannot open " + filename);
   }

   //cputning the books that get returned succesfully:
   int returned_books = 0;
   //the text files consists of ISBN number in each line 10 or 13 digits remember
   std::string isbnL;

   while(std::getline(f, isbnL)){
      if (isbnL.empty()) continue;

      //creating a return status message
      std::string message;
      //now we attempt to store the book with the correspondibng ISBN
      //calling library.return_book()
      if (library.return_book(isbnL, message))
         returned_books++;
   }

   return returned_books; //returning the number of books returned
}
