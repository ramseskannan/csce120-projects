#include <iostream>
#include <sstream>
#include "library.h"
#include "lms_utilities.h"

void Library::add_book(Book new_book) {
   //adds a book to the vector of books
   books.push_back(new_book);
   //its unsorted
   
}

void Library::register_member(Member newMember) { //adds a member to the vector of memebrs
   members.push_back(newMember);
   //memberss should be unsorted, but it adds to end of vector so pushbacl
   
}

bool Library::borrow_book(const std::string& isbn , int m_id, std::string& error_message) {
   //attemps to lend a book from the library to a member
   //checks if the book is availble and if the ISB is in the library catalog
   bool found_book = false;
   Book* book_wanted = nullptr;

   for(auto& book : books){
      if (book.get_isbn() == isbn){
         found_book = true;
         book_wanted = &book;
         break; //we found it so we stop searching, thats why we break
      }
   }
//it checks if the book is available and if the ISBN is in the library catalog 

   //the purpose of this if if the book is not found, we return immedeitly
   if (!found_book){
      error_message = "Book ISBN: " + isbn + " not available";
      return false;
   }
   //if the book is nto available, return immedetly
   if(!book_wanted->is_available()){
      error_message = "Book ISBN: " + isbn + " not available";
      return false;
   }

   //now we check if the memebr ID is registered
   bool member_true = false;
   Member* member_checking = nullptr;

   for (auto& member : members){
      if (member.get_id() == m_id){
         member_true = true;
         member_checking = &member;
         break; //stop searching the member once we found them
      }
   }

   //now we check if the member is registered
   if (!member_true){
      error_message = "Member " + std::to_string(m_id) + " not found";
      return false;
   }

   //now if all the above condition are satistifed, then this message is provided
   book_wanted->borrow_book(); //this marks the book as unavailable

   //this is the mesage using overloaded operators
   std::ostringstream oss;
   oss << *member_checking << " borrowed " << *book_wanted;
   error_message = oss.str();

   return true; //this means that everything was validated and it aws a success

   
}

bool Library::return_book(const std::string& isbn, std::string& error_message) {
   // TODO(student)
   //this method attemps to reutrn a book to the library, 
   //first we check if the book is unavailable and if the ISB is in the library catalog
   bool found_book = false;
   Book * book_to_return = nullptr;

   for(auto& book : books){
      if (book.get_isbn() == isbn){
         found_book = true;
         book_to_return = &book;
         break;
      }
   }  
   
   //now we check if the book is not found in the catalog
   if(!found_book){
      error_message = "Book ISBN: " + isbn + " not found";
      return false;
   }

   //now check if the book is already unabailbe, it was borred. like if its already available, it cannot be returned
   if(book_to_return->is_available()){
      error_message = "Book ISBN: " + isbn + " still available (cannot be returned)";
      return false;
   }

   //return the book so now it becomes avaialbe
   book_to_return->return_book();

   //now we have to create the success messge that the book was returend (in the requiremetns)
   std::ostringstream oss;
   oss << "Book \"" << book_to_return->get_title() << "\" returned"; //book to return is the title of the boook
   error_message = oss.str();
   return true;
}
void Library::display_available_books(std::ostream& os) {
   // TODO(student)
   // use the ostream parameter, NOT std::cout

   for(const auto& book : books){
      if (book.is_available()){
         os << book << std::endl;
      }
   }
}

void Library::display_library_members(std::ostream& os) {
   // TODO(student)
   // use the ostream parameter, NOT std::cout
   //display all the registered members 
   for(const auto& member : members){
      os << member << std::endl;
   
   }
}

bool Library::is_book_available(const std::string& isbn) {
   //this cbecks if a book is available with a given ISBN

   for(const auto& book : books){
      if (book.get_isbn() == isbn){
         return book.is_available();
      }
   }
   return false; //this means if the book is not found in the catalog
}
