#include "MyString.h"
#include <iostream>


//ok this counts characters until null- we will use the loop style

size_t countCharsInCString(const char* text){
    size_t charCount = 0;
    //keep going until we hit the null terminator
    while (text[charCount] != '\0') {
        charCount++;
    }
    return charCount;
}

//helper to copy the chracters from source to destination
//this basically transfers howMany characters PlUS the null terminator

void transferCharacters(char* destination, const char* source, size_t howMany){
    size_t idx = 0;
    
    while (idx <= howMany){ //<= to include '0' at the end
        destination[idx] = source[idx];
        idx++;
    }
}

//size, this will return how many chracters (this does not count '0')
//this is necessary cause this does NOT count the '\0' terminator
size_t MyString::size() const {
    return currentLength;
}

size_t MyString::length() const {
    return currentLength;
}
size_t MyString::capacity() const {
    return allocatedSpace;
}

//empty- this checks if string has no characters
//this returns true if empty, false if it has any charachters
//an empty string is just '\0'
bool MyString::empty() const{
    return currentLength == 0;
}

//front - returns first character
//this doesnt check if the string is empty

char MyString::front() const {
    return characterData[0];
}

//data, this returns the raw C-string pointer
const char* MyString::data() const{
    return characterData;
}

//here are the constructors
MyString::MyString(const MyString& other){
    //copy over the size info
    currentLength = other.currentLength;
    allocatedSpace = other.allocatedSpace;
    //allocate our own space
    characterData = new char[allocatedSpace];

    //this will use the other helped function
    transferCharacters(characterData, other.characterData, currentLength);

}
//c-string constructor
MyString::MyString(const char* textInput){
    //first, the gets how long the input string is
    currentLength = countCharsInCString(textInput);
    //then we need space for all charachters plus the \0
    allocatedSpace = currentLength + 1;

    //puts the null terminator at the end first
    characterData = new char[allocatedSpace];

    //coping the data (actual data)
    characterData[currentLength] = '\0';
    //now we reverse it
    if (currentLength > 0){
        size_t position = currentLength - 1;
        while (true) {
            characterData[position] = textInput[position];
            if (position == 0) break; //this stops when weve down pos 0
            position--;// moves backwards, copying in reverse cause copied down from \0
        }
    }
}
//now we make the default contructor
//this is called when we do MyString str
MyString::MyString() {
    //allocates the mininmum space
    characterData = new char[1];
    characterData[0] = '\0';
    currentLength = 0;
    allocatedSpace = 1;
}

//destructor
MyString::~MyString(){
    delete[] characterData; //frees the character array
}

//now for the operators
//this is different from the copy constructor , this modifies an exisitng one
MyString& MyString::operator=(const MyString& other){
    //this checks it for self-assigment str = str

    if (characterData == other.characterData){
        return *this;
    }
    //deleete the old data because we are replacing it
    delete[] characterData;

    //copy the size info from other
    currentLength = other.currentLength;
    allocatedSpace = other.allocatedSpace;

    //allocate new space and copy the data
    characterData = new char[allocatedSpace];
    //use our helped to copy all characters
    transferCharacters(characterData, other.characterData, currentLength);

    //this is so we can chain assignments
    return *this; //str1 = str2 = str3
}

//plus-equals operator
MyString& MyString::operator+=(const MyString& other){

    //calculate new size needed
    size_t combinedLength = currentLength + other.currentLength;
    size_t neededSpace = combinedLength + 1;
    //do we need more space
    if (neededSpace > allocatedSpace){
        //we have to create a bigger array
        char* expandedData = new char[neededSpace];

        //copy existing content
        size_t copyIndex = 0;
        while(copyIndex < currentLength){
            expandedData[copyIndex] = characterData[copyIndex];
            copyIndex++;
        }

        //delete the old, and swithching to the new arr
        delete[] characterData;
        characterData = expandedData;
        allocatedSpace = neededSpace;
    }

    //now we append to other string to the ebnd of our string

    size_t appendPosition = 0;
    while(appendPosition < other.currentLength){
        characterData[currentLength + appendPosition] = other.characterData[appendPosition];
        appendPosition++;
    }
    //update our length and add null terminator
    currentLength = combinedLength;
    characterData[currentLength] = '\0';
    //this returns 
    return *this; //str1 += str2 += str3
}

//accessing functions

//at nonconst - this accesses a character at a spefici position
//allows modifictation
//returns a reference so we can change the charachter
char& MyString::at(size_t position){
    //apparently there needs to be out of range thrown for certain cases
    if (position >= currentLength){
        throw std::out_of_range("its out of range");
    }
    return characterData[position];
}

//AT const - access a character in a const MyString
//this is only readable
//returns a const reference, WE CANNOT CHANGE IT
const char& MyString::at(size_t position) const {
    //same thing for this one, throwing out of range
    if (position >= currentLength){
        throw std::out_of_range("its out of range");
    }
    return characterData[position];

}

//modifications functions
//clear - this will empty the string
//we are going to reset the string by putting \0 at the start

void MyString::clear() {
    //resets it
    characterData[0] = '\0'; //makes empty string
    currentLength = 0; //lenght is 0
}

void MyString::resize(size_t newSize){
    //checking if we nee to create more space
    if (newSize + 1 > allocatedSpace){
        //we need to resize the array
        size_t newCapacity =  newSize + 1; //+1 for the \0
        char* newData = new char[newCapacity];

        //now copy the exisitng characthers
        for (size_t i = 0; i < currentLength; i++){
            newData[i] = characterData[i];
        }
        //now filling the rest with null 
        for (size_t i = currentLength; i < newSize; i++){
            newData[i] = '\0';
        }
            //adding the final null terminator 
            newData[newSize] = '\0';

            //now we delete the old array
            delete[] characterData;
            //assign the new one
            characterData = newData;
            allocatedSpace = newCapacity;
            currentLength = newSize;
        }
        else if(newSize < currentLength){
            //shrinking, 
            characterData[newSize] = '\0';
            currentLength = newSize;
        }
        else if (newSize > currentLength){
            //growing but there is space, so we fill with nulls
            for (size_t i = currentLength; i < newSize; i++){
                characterData[i] = '\0';
            }
            characterData[newSize] = '\0';
            currentLength = newSize;
        }
        //so if the newsize -- currentlenght then we do nothing
    }

//FIND this will search for substring
//this returns the index where searchTerm is found
int MyString::find(const MyString& searchTerm) const{

    //if searching for an empty string, we return 0
    if(searchTerm.currentLength == 0){
        return 0;
    }

    //now if search term is longer than us, we cant find it
    if (searchTerm.currentLength > currentLength){
        return -1;
    }

    //checks each possible starting position
    size_t maxStartPos = currentLength - searchTerm.currentLength;

    //this tries each possible starting position
    for(size_t startPos = 0; startPos <= maxStartPos; startPos++){
        //checl if the match starts here
        bool foundMatch = true;
        size_t checkPos = 0;
        //we compare character by charachter
        while(checkPos < searchTerm.currentLength && foundMatch){
            if (characterData[startPos + checkPos] != searchTerm.characterData[checkPos]){
                foundMatch = false; //no match
            }
            checkPos++;
        }
        //if there is a match
        if(foundMatch){
            return startPos; //we return where we found it
        }
    }
    return -1; //none is found
}

//now for the non memebr function
//output operator
std::ostream& operator<<(std::ostream& outputStream, const MyString& text){
    outputStream << text.data();
    return outputStream;
}

bool operator==(const MyString& left, const MyString& right){

    //if they are different lenghths, it cannot be equal
    if (left.size() != right.size()){
        return false;
    }

    //now we compare it by each of the characthers
    for (size_t i = 0; i < left.size(); i++){
        if (left.at(i) != right.at(i)){
            return false; //this means we found a different character between both
        }
    }

    //if all characters match
    return true;
}

//
MyString operator+(const MyString& left, const MyString& right){ //bonus
    //create a copy of the left string
    MyString result(left);

    //add the right string to it
    result += right;

    //return the combined result
    return result;
} 


