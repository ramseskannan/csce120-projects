#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "Game.h"
using std::string, std::vector;

Game::Game(): players({}), suits({}), ranks({}), 
    deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename){
    // TODO: initialize suits, ranks, deck, and drawPile from the given file
    //first we check the decks in the invalid_decks folder 
    //if file cannot be openend throw std::runtime error
    std::ifstream file(filename);

    if(!file.is_open()){
        throw std::runtime_error("Cannot open file");
    }

    string line_r; //reading line
    int linNum = 0; //tracking the current line numner

    if(!std::getline(file, line_r)) {//trying to read the first line
        throw std::runtime_error("Invalid deck file format"); //error if cant read first line
    }
    linNum++;

    std::istringstream suitsStream(line_r); //creating a stream to parse throuhg suits
    string suit; //to hold each suit
    while (suitsStream >> suit){
        suits.push_back(suit);
    }

    if (suits.empty()){ //checking if any suits were read
        throw std::runtime_error("Invalid deck file format");
    }
    if (!std::getline(file, line_r)){ //trying to read the second line
        throw std::runtime_error("Invalid deck file format");
    }
    linNum++;
    std:: istringstream ranksStream(line_r); //parsing ranks
    string rank; //to hold each rank
    while (ranksStream >> rank){ //reading eacch rank from the line
        ranks.push_back(rank); //adds rank to rank vector
    }

    if (ranks.empty()){
        throw std::runtime_error("Invalid deck file format"); //throw this if no ranks
    }

    while (std::getline(file, line_r)){ //reading remainging lines which are teh cards
        linNum++;
        std::istringstream cardStream(line_r);
        string cardRank, cardSuit; //variables for the card rank and the suit

        if (!(cardStream >> cardRank >> cardSuit)) { //reading the rank and suit
            throw std::runtime_error("Invalid deck file format");
        }

        //nned this to check if there is any extra data
        string excess;
        if (cardStream >> excess){
            throw std::runtime_error("Invalid deck file format");
        }

        bool validRank = false; //this is to flag to check if the rank is vlaid
        for (const string& r : ranks) { //we loop through all the valid ranks
            if (r== cardRank){ //checking if the card rank matches!!
                validRank = true; //mark as valid
                break; //we stop searching
            }
        }
        //doing the same thing for suits
        bool validSuit = false; 
        for (const string&s : suits){
            if (s ==cardSuit){
                validSuit = true;
                break;
            }
        }

        //now checking if the rank or suit is invalid
        if (!validRank || !validSuit){
            throw std::runtime_error("Invalid deck file format");
        }
        
        try {
            Card* newCard = new Card(cardRank, cardSuit); //creaing a new card on the heap
            deck.push_back(newCard); //add card to the deck
            drawPile.insert(drawPile.begin(), newCard); //adding the card to draw pile
        } catch (const std::invalid_argument&){
            throw std::runtime_error("Invalid deck file format");
        }
        
    }
    file.close(); //closing the file

    if (suits.empty() || ranks.empty()){ //checking if they exist
        throw std::runtime_error("Invalid deck file format"); //error if missing
    }
    if (deck.size() < suits.size() || deck.size() < ranks.size()){
        throw std::runtime_error("Invalid deck file format"); //error if the deck is too short!!

    }
}


void Game::addPlayer(bool isAI){
    //we have to create a new plater and add them to the end of playeers
    //when we create a new Player objkect, remember that we are wokring with dynamic memory (new keyowrd)
    Player * newPlayer = new Player(isAI);
    players.push_back(newPlayer);
}

void Game::drawCard(Player* p){
    // If the draw pile is empty, flip the discard pile to create a new one
    //move the top card of the draw pile into the players hand
    //if the discard pile has at least two cards then print Draw pile empty flipping the discard pile
    //and the form a new draw pile by leaving ust the top card in the discard pile and flipping
    //the rest of the discard pile
    //if the draw pile is empty, and the discard contains only one card, there is nothing to draw
    //so print nothing and throw runtime error

    if (drawPile.empty()){
        if (discardPile.size() < 2){ //if the discrd pile less than 2 cards
            throw std::runtime_error("Cards to draw: None");
        }

        std::cout << "Draw pile empty, flipping the discard pile." << std::endl; //if the discard pile has at least two cards
        Card* topCard = discardPile.back(); //getting the top card of the discard pile
        discardPile.pop_back(); //removint the topcard from the discard pile

        while (!discardPile.empty()){
            Card* card = discardPile.back(); //get bottom card of disacrd
            discardPile.pop_back();
            drawPile.push_back(card);
        }

        discardPile.push_back(topCard); //put the toip card back on discard
    }
    if (drawPile.empty()){ //check if draw pile is still empty
        throw std::runtime_error("Cards to draw: None");
    }

    Card* topCard = drawPile.back(); //get top card from the draw pile
    drawPile.pop_back(); //remove card from draw pile
    p->addToHand(topCard); //adding the card to players hand
    
    
    }   

Card* Game::deal(int numCards){
    // TODO: Flip the top card of the draw pile to be the initial discard
    // then deal numCards many cards to each player
    //we first form a starting discard pile bu discarding the top card of the draw pile
    //then deal cards from the top of the deck to players hands one at a time (use draw card method
    ////you should nto catch any exceptions thrown by drawCard
    //that is if you are unable to draw enough cards for all players
    //deal should allow the exception thrown by drawCard ti continuie being thrown
    //each playters should get their first card before second
    //return the intitially discarded card
    if (drawPile.empty()){
        throw std::runtime_error("No cards to deal"); //give error if no cards to deal
    }

    //getting that intitial discard
    Card* first_discard = drawPile.back();
    drawPile.pop_back();
    discardPile.push_back(first_discard); //adding the card to discard pile

    for (size_t i = 0; i < static_cast<size_t>(numCards); i++){ //looping numCards times
        for (Player* player : players) { //loop through each player
            drawCard(player); //using the fucntion reqiureing, give one card to  player
        }
    }
    return first_discard; //returning the first intiial discard card
}

string Game::mostPlayedSuit(){
    // TODO: Return the suit which has been played the most times
    // if there is a tie, choose any of the tied suits
    //we have to figure out how may times each suit has been pplayed by adding up the timesPlayer values for all cards of that suit
    //return the suit that ahs been played the most times
    //in case of a tie, return any of the tied suits
    //remember the deck contains all cards in teh game, whether they arein the draw pile, discard pile ,or players hand
    //im going to use a string...
    string MaxSuit = suits[0];
    int maxCount = 0; //intiialzing the max count

    for (const string& suit : suits){ //for each suit
        int count = 0; //count for the current suit

        for (Card* card : deck){ //checking al lthe cards
            if (card->getSuit() == suit){ //if the card matches the current suit
                count += card->getTimesPlayed();
            }
        }
        if (count > maxCount){
            maxCount = count;
            MaxSuit = suit; //upadting the max suit. if one is equal it jsut keeps the one that got delcared max first
        }
     }
     return MaxSuit; //returning the maxSuit

}

int Game::runGame(){
    // TODO: Run the game and return the number of the winning player
    int currentPlayer = 0; //start with player 0
    string currentRank = discardPile.back()->getRank(); //this getst ehr ank of the top discard card
    string currentSuit = discardPile.back()->getSuit(); //this getst he suit of the top discard card

    while(true){ //game loop until someonen wins the game
        std::cout << "Player " << currentPlayer << "'s turn!" <<std::endl; //announce3s wwhos turns it is

        Player* player = players[currentPlayer]; //points to current player

        //we have to ask player wehich card to play (null if drawing)
        Card* playedCard = player->playCard(suits, currentRank, currentSuit);

        if (playedCard != nullptr) { //player is played a card
            if(playedCard->getRank() == "8"){ //checks if the card is an 8
                //if the player chooses new suits, updates current suits for 8s
                //currentSuit = playedCard->getSuit(); //get the suit the player chose
                currentRank = "8"; //updating the current rank to 8
                //announces the suit change
                std::cout << "Player " << currentPlayer << " plays " << playedCard->getRank() << " " << playedCard->getSuit() << " and changes the suit to " << currentSuit << "." << std::endl;             
            } else {
                std::cout << "Player " << currentPlayer << " plays " << playedCard->getRank() << " " << playedCard->getSuit() << "." << std::endl;
                currentRank = playedCard->getRank(); //updating the current rnak
                currentSuit = playedCard->getSuit(); //updating the current suit
            }
            //adds the card to the end of the discard pile (top)
            discardPile.push_back(playedCard);

        } else { //player is going to draw a card
            try {
                drawCard(player); //draws a card and adds it to that players ahnd
                std::cout << "Player " << currentPlayer << " draws a card." << std::endl;

            }catch (const std::runtime_error & e){ //catch exception if no cards are available to draw
                std::cout << "Player " << currentPlayer << " cannot draw a card." << std::endl;
                return -1; //returns -1 for tied game
            }
        }
        if (player->getHandSize() == 0){ //checls if player has no cards left
            return currentPlayer; //return winners index
        }

        currentPlayer = (currentPlayer + 1) % players.size(); //move to the next player!!!!
    }
}


//Destructor--Deallocates all the dynamic memory we allocated
//You shouldn't touch this
Game::~Game(){
    for (unsigned int i = 0; i < deck.size(); i++){
        delete deck.at(i);
    }
    for (unsigned int i = 0; i < players.size(); i++) {
        delete players.at(i);
    }
}