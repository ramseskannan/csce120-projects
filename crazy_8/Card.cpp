#include<cctype>
#include<stdexcept>
#include "Card.h"
using std::string;

Card::Card(string rank, string suit) : rank(rank), suit(suit), timesPlayed(0){
    if (rank.empty()){
        throw std:: invalid_argument("Invalid rank"); //for ranks
    }

    if (suit.empty()){
        throw std:: invalid_argument("Invalid suit"); //for suits
    }

    for (char c : rank){
        if (!std::isalnum(c)){
            throw std::invalid_argument("Invalid rank");
        } //checking if alphanumertic
    }
    
    for (char c : suit){
        if (!std::isalnum(c)){
            throw std::invalid_argument("Invalid suit");
        } //checking if alphanumertic
    }
}

 /* TODO: initialize */ 
    // TODO: implement constructor checks
    //make sure to iuntiialize all the cards attrivutes not just rnak and suit
    //throw invalid argument if rank r suit are empty

string Card::getRank(){
    // TODO: implement getter
    return rank;
}

string Card::getSuit(){
    // TODO: implement getter
    return suit;
}

int Card::getTimesPlayed(){
    // TODO: implement getter
    return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit){
    // TODO: return whether or not this card can legally be played given that the previous card
    //  played had rank currentRank and suit currentSuit
    if (rank == currentRank){ //checking if the rank matches
        return true; //card can be played
    }
    if (suit == currentSuit){ //check if the suit matches
        return true;
    }
    if (rank=="8"){
        return true; //8s can always be played in this game
    }
    return false; //card cannot be played if it doesnt pass any of these
}

//You don't need to modify this
void Card::play(){
    timesPlayed++;
}