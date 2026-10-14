#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
//these are the includes for mystring.h

class MyString {
    private:
        char* characterData;

        //how many characters are we actually using
        size_t currentLength;

        //how much space we allovated
        size_t  allocatedSpace;

    public:

        //for the npos thingin gradescope
        static const int npos = -1;
        //constructors, these are different ways to create a MyString

        MyString(); //this is the default constructor, is empty
        MyString(const char* textInput); //from a c-string
        //a copy constructor
        MyString(const MyString& other);

        //desctructor 
        ~MyString();

        MyString& operator=(const MyString& other) ;

        //this is for adding string toegether
        MyString& operator+=(const MyString& other);

        //access functions
        char& at(size_t position);
        const char& at(size_t position) const;

        //info functions
        size_t size() const;
        size_t length() const; //for the bonus
        size_t capacity() const; //for the bonus
        bool empty() const;
        char front() const;
        const char* data() const;

        //modification functions
        void clear();
        void resize(size_t newSize); //fixing the resize test
        int find(const MyString& searchTerm) const;
};

std::ostream& operator <<(std::ostream& outputStream, const MyString& text);

//non member function overloads + and ==
bool operator==(const MyString& left, const MyString& right);
MyString operator+(const MyString& left, const MyString& right); //bous
#endif