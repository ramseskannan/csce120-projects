#include "member.h"

Member::Member(std::string firstName_,  // firstName
               std::string last_name_,  // last_name
               int id_           // id
            ) : name{}, id{} {
    //validation rules
    /*Member’s name is not empty and consists of only letters
Member’s id is an integer greater than or equal to 1000
If validation rules are not satisfied, throw a std::invalid_argument exception with the message: “Invalid <attribute>” where <attribute> is one of: “name” or “id”. 
*/
    //checking if the firstname and lastname is empty, atleast one has to be non empty
    if (firstName_.empty() && last_name_.empty()){
        throw std::invalid_argument("Invalid name");
    }

    //now we check if the first name only letters
    for (char c : firstName_){
        if (!std::isalpha(c)){
            throw std::invalid_argument("Invalid name");
        }
    }
    //now we check if the last name only letters
    for (char c : last_name_){
        if (!std::isalpha(c)){
        throw std::invalid_argument("Invalid name");
        }
    }

    //now we have to check if the members id is an integer greateer than or equal to 1000
    if (id_ < 1000){// less than 1000 invalid
        throw std::invalid_argument("Invalid id");
    }

    //this means all of the data was validated and was correct, now we can assign the values to member variabls
    name = {firstName_, last_name_};  //creating a membername with first and last
    id = id_;
}

Member::Member(MemberName membername,  // name
               int id_        // id
               ) : Member(membername.first_name, membername.last_name, id_){
        //it calls the first contructor to reuse validation logic
        //extract first and last from memberName and pass to first contructor
} 

    // TODO(student)

MemberName Member::get_name() const {
    return name; //returns the name member variable
}

int Member::get_id() const {
    return id; //returns the id member varialbe
}

//overloading operator for memeber, it prints this string Member: Name, id: ID
std::ostream& operator<<(std::ostream& os, const Member& member) {
   //we have to print member: first name last name id: Xxxxxxx
   os << "Member: " << member.get_name().first_name << " " << member.get_name().last_name << ", id: " << member.get_id();
   return os;
}
