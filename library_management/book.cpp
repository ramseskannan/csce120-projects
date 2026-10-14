#include "book.h"

Book::Book(std::string title_,  // title
           std::string author_first_name_,  // author_first_name
           std::string author_last_name_,  // author_last_name
           std::string isbn_,  // isbn
           bool available_         // available
         ) : title{}, author{}, isbn{}, available{} {
   // TODO(student)
   //vaildation rules : title is nto empty and consists of letters, colons, and dashes
   //authors nameis not empty and consists of only letters
   //ISBN consists of 10 or 13 digits (saved as a string, not a number)
   
   //invalid title
   if (title_.empty()){
      throw std::invalid_argument("Invalid title");
   }
   // got on error about \t \r \n \c \f
   //now checking for valid characters
    bool consists_of_letters = false; //creating a variable to tell us if title is valid or not
    for (char c : title_){
      if (std::isalpha(c)) { 
         consists_of_letters = true;
      } else if (c != ':' && c != '-' && c != ' ' &&
                 c != '\t' && c != '\r' && c != '\n' &&
                 c != '\v' && c != '\f'){
         throw std::invalid_argument("Invalid title");
      }
    }

    if (!consists_of_letters){
      throw std::invalid_argument("Invalid title");
    }
    
    //now we validate the authorsname
    //first lets check if its not empty
    if (author_first_name_.empty() && author_last_name_.empty()){
      throw std::invalid_argument("Invalid author");
    }
    
   //then we check if its only letters
   //we have to check firstname and latname seperately because we cant assign char c twice in the same loop (i think)
   for (char c: author_first_name_){
      if (!std::isalpha(c)){
         throw std::invalid_argument("Invalid author");
      }
   }
   //now for the last name
   for (char c: author_last_name_){
      if (!std::isalpha(c)){
         throw std::invalid_argument("Invalid author");
      }
   }

   //now we check the ISBN
   //the isbn consist of 10 OR 13 digits
   if (isbn_.length() != 10 && isbn_.length() != 13 ){
      throw std::invalid_argument("Invalid ISBN");
   }
   //now we have to make sure eah are a number
   for (char c : isbn_){
      if (!std::isdigit(c)){ //checking if its a digit. also reminder std is jsut namespace
         throw std::invalid_argument("Invalid ISBN");
      } 
   }

   title = title_;
   author = {author_first_name_, author_last_name_};
   isbn = isbn_;
   available = available_;
   
}

Book::Book(std::string title_,  // title
           AuthorName author_,   // author
           std::string isbn_,  // isbn
           bool available_          // available
         ) : Book(title_, author_.first_name, author_.last_name, isbn_, available_) {
   // TODO(student)
   
}

std::string Book::get_title() const {
   // TODO(student)
   return title;
}

AuthorName Book::get_author() const {
   // TODO(student)
   return author;
}

std::string Book::get_isbn() const {
   // TODO(student)
   return isbn;
}

bool Book::is_available() const {
   // TODO(student)
   return available;
}

bool Book::borrow_book() {
   // TODO(student)
   if (available){
      //the bookis avilable, so we have to mark it as borrwed
      available = false;
      return true; //success 
   }
   //the book is borrowed
   return false;
}

bool Book::return_book() {
   if (!available){
      available = true;
      return true;
   }
   return false;
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
//we have to print member: first name last name id: Xxxxxxx
   os << "title: \"" << book.get_title() << "\" by " << book.get_author().first_name << " " << book.get_author().last_name << ", isbn: " << book.get_isbn();
   return os;
}
