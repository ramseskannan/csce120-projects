#include <stdexcept>
#include "LinkedList.h"

// TODO(student): implement a linked list

//purpose: create a default constructor. this will intialize an empty list
LinkedList::LinkedList() : head{nullptr}{}

//purpose: destructor, this will free all the allocated memory
LinkedList::~LinkedList(){
    clear();
    
}

//purpose: this will remove all the nodes from the list
void LinkedList::clear(){
    Node* current_node = head; //start at head

    //traverse and delete each ndoe
    while (current_node != nullptr) { //this will loop until end of list
        Node* next_node = current_node->next; //this saves the next pointer
        delete current_node; //deletes the current node
        current_node = next_node; //then moves to the next node
    }
    head = nullptr; //tos sets the head to nill
}

//now we make the copy constructor, this creates a deep copy (this was on the exam, rule of 3)
LinkedList::LinkedList(const LinkedList& other) : head{nullptr}{
    if (other.head != nullptr){
        //copy the first node
        head = new Node(other.head->value); //this creates the first node
        Node* my_node = head; //Pointer to track position in new list
        Node* their_node = other.head->next; //this makes the pointer to track position in the new list
        
        //copy remaining nodes one by one
        while(their_node != nullptr){ //this loops through the list
            my_node->next = new Node(their_node->value); //create new node
            my_node = my_node->next; //this moves forward in the new list
            their_node = their_node->next; //moves forward in the other listq}}
        }
    }
}

//this is the copy assignment operator, this will replace the current listwith a copy of a another
//purpose: replace the list with a copy of the other list 
LinkedList& LinkedList::operator=(const LinkedList& other){
    //first we have to check for self assignmnet
    if(this != &other){ //make sure not assigning to self
        clear(); //deletes the existing nodes

        if (other.head != nullptr){ //this checks if the other list is not empty
            //copy the first node
            head = new Node(other.head->value); //this creates the first node
            Node* my_node = head; //Pointer to track position in new list
            Node* their_node = other.head->next; //this makes the pointer to track position in the new list
            
            //copy remaining nodes one by one
            while(their_node != nullptr){ //this loops through the list
                my_node->next = new Node(their_node->value); //create new node
                my_node = my_node->next; //this moves forward in the new list
                their_node = their_node->next; //moves forward in the other listq}}
            }
        }
    }
    return *this; //return reference to this objkect
}

//then we check if the list contains no elements
//purpose to test if the list is empty
bool LinkedList::empty() const{
    return (head == nullptr); //true if head is null
}

//count and return the number of elemnts in the list

//purpose is to get the number of items in the list
unsigned LinkedList::size() const{
    unsigned total = 0; //intialize counter
    Node* current_node = head; //start at the head of the list

    //then traverse the list and count the nodes
    while (current_node != nullptr){ //loop until the end of it
        total++; //incremement counter
        current_node = current_node->next; //move to the next node
    }

    return total; //return count
}


//purpose: access the value at the given index
//throws std::: out of range if the index is out of bounds
int LinkedList::at(unsigned index) const{
    Node* current_node = head; //start athead
    unsigned position = 0; //this initializes the position counter

    //now we traverse to the desired index
    while(current_node != nullptr && position < index){ // loop it until the end of the index
        current_node = current_node->next; //move to the next node
        position++; //incremement ht eposition
    }

    //this is the index out of bounds
    if(current_node == nullptr){ //
        throw std::out_of_range("index out of bounds");
    }
    return current_node->value; //reutrn value at index
}

//purpose: acceoss the first item in the list
//throw std::out_of_range if the list is empty
int LinkedList::front() const{
    if(empty()) { //check if the list is empty first
        //throw exception
        throw std::out_of_range("list is empty"); 
    }
    return head->value; //reutnr the first value
}

//next is the modifiers

//purpose: add a value at the given index, throw std::out_of_range if the index is out of bounds

void LinkedList::add(int value, unsigned index){

    //first case: insert at the beginning
    if (index == 0){ //check if inserting at front
        Node* new_node = new Node(value, head); 
        head = new_node; //update the head to new node
        return; 
    }
    //start at the head
    Node* current_node = head; 
    unsigned position = 0; //initalize position counter

    //then we find the node just before the point we have to insert it 
    while (current_node != nullptr && position < index - 1){
        current_node = current_node->next; //moves to the next node
        position++; //incremments the position
    }

    //couldnt reach the insertion point, the index is invalid
    if(current_node == nullptr){ //check if the index was out of bounds
        throw std::out_of_range("index out of bounds");
    }

    //create new node and link it into the list
    Node* new_node = new Node(value, current_node->next); //create a new node
    //then link the previous node to new node
    current_node->next = new_node; 
}

//purpose: remove the value at the given index, throw out of range if the index out of bounds
void LinkedList::remove(unsigned index){
    //first we check if the list is empty
    if(head == nullptr) { //check for an empty list
        throw std::out_of_range("index out of bounds");
    }

    //removing the first elemnt
    if(index == 0) { //this is the check
        Node* old_head = head; //save current head
        head = head->next; //update head to next node
        delete old_head; //delete old head
        return;
    }

    //now for other cases
    Node* current_node = head; //start at head
    unsigned position = 0; //initalize pos counter

    //then we find the node of the one just before the one we have to remove
    while(current_node->next != nullptr && position < index - 1){
        current_node = current_node->next; //move to next node
        position++; //incrememnt pos

    }

    //if the node cannot be reached before removal point, then the index is valid
    if (current_node->next == nullptr){ //check if index was out of bounds
        throw std::out_of_range("index out of bounds");
    }

    //now we unlink the node and delete it
    Node* node_delete = current_node->next; //saveing node to delete
    current_node->next = node_delete->next;
    delete node_delete;


}