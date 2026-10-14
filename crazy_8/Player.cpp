#include<iostream>
#include<sstream>
#include "Player.h"
using std::vector, std::string, std::size_t;


Player::Player(bool isAI) : isAI(isAI), hand({}) /* TODO: initialize */ {
}
void Player::addToHand(Card* c){
    // TODO: Add the card c to the player's hand
    //add the given card to this players hand
    //the hand should be ordered from least recently added to most
    //recently added
    hand.push_back(c); //adding the card to the back of the hand vector
}
size_t Player::getHandSize(){
    // TODO: Implement getter
    return hand.size(); //reutnring the # of cards in hand
}
std::string Player::getHandString(){
    // TODO: Implement getter
    //returns a string rep of the players ahnd
    //cars should be listed from the front of the hand to the back (new)
    //the rank and suit of the card should be speerated by a space
    //consective cards should be seprated by a comma nad soace
    string players_hand = "";
    for (size_t i = 0; i < hand.size(); i++){
        players_hand += hand[i]->getRank(); //add rank to string
        players_hand+= " "; //adding the space
        players_hand += hand[i]->getSuit();
        if (i < hand.size()- 1){ //check if not the last card
            players_hand += ", "; 
        }
    }
    return players_hand; //returnign the formatting string
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit){
    // TODO: Choose a card to play and return the chosen card. Update currentRank and currentSuit.
    //choose a card to play, remove it from the playters hand and return it
    //make sure to incrememnt the cards timesPlayed and to update the current rank and suit
    //ifthe player chooses not to play a card return nullmptr to indicate that they are drawing a car
    //
    //if the player is AI
    if (isAI){
        for (size_t i = 0; i < hand.size(); i++){ //loop trough hand
            if (hand[i]->canBePlayed(currentRank, currentSuit)){
                Card * cardPlay = hand[i]; //getting the card
                hand.erase(hand.begin() + i); //removing the card from hand
                currentRank = cardPlay->getRank();
                currentSuit = cardPlay->getSuit();
                if(currentRank == "8"){
                    currentSuit = cardPlay->getSuit();
                }
                cardPlay->play();
                return cardPlay;
            }
        }
        //no playtable card
        return nullptr;
    } else {//if the plater is human!!!!
        std::cout << "Your hand contains: " << getHandString() << std::endl;
        std::cout << "The next card played must be a " << currentRank << " or " << currentSuit << std::endl;
        std::cout<< "What would you like to play? (enter \"draw card\" to draw a card)" << std::endl;
        while(true) { //loop until valid card draw}
            string input; //holds the user inpout
            std::getline(std::cin, input); //reading the entire line
            if (input == "draw card"){ //check if the player wants to draw
                return nullptr; //this indicates draw
                }
            std::istringstream inputStream(input); //creating a stream to parse input
            //initialiozes variavles
            string rank;
            string suit;
            //forget this- we have to read the input
            if(!(inputStream >> rank >> suit)){
                std::cout << "That's not a card you have. Try again." << std::endl;
                continue; //go back to the top
            }
            bool found = false;
            size_t cardIndex = 0;
            for (size_t i = 0; i < hand.size(); i++){
                if(hand[i]->getRank() == rank && hand[i]->getSuit() ==suit){
                    found = true;
                    cardIndex = i;
                    break;
                }   
            }
            if(!found){
                std::cout << "That's not a card you have. Try again." << std::endl;
                continue; //this just continues iunstead of recurison
            }
            Card* cardToPlay = hand[cardIndex]; //get the card
            if (!cardToPlay->canBePlayed(currentRank, currentSuit)){ //checking if the card can be played}
                std::cout << "You can't play that card. Try again." <<std::endl;
                continue; //no recurison
            }
            hand.erase(hand.begin() + cardIndex); //thie removes the card from hand
            cardToPlay->play(); //iuncrememnts the timesplayed
            if(cardToPlay->getRank() == "8"){
                //if the card is an 8
                std::cout << "What suit would you like to declare?" << std::endl;
                while(true){
                    //looping for suit slection
                    string newSuit; //what the player will declare
                    std::getline(std::cin, newSuit); //reads the suit the user inouts
                    //now we have to check that that is a valid suitin the deck
                    bool ValidS = false;
                    for (const string& s : suits){
                        if (s == newSuit){ //loops through the valid suits
                            ValidS = true; //this checks if it matches
                            break; //stops searching after valid suit found
                        }
                    }
                    if(!ValidS) { //if the suit is not valid
                        std::cout << "That's not a suit in this deck. Try again." << std::endl;
                        continue;
                    }
                    currentRank = "8"; //updates the current rank to 8
                    currentSuit = newSuit; //updates to the chosen suit
                    break; //exit the suit loop
                }

            } else {
                currentRank = cardToPlay->getRank();
                currentSuit = cardToPlay->getSuit();

            }

            return cardToPlay;

        }

    }

}
