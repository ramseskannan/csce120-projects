#include<iostream>
#include<string>
#include "Card.h"
#include "Player.h"
#include "Game.h"
using std::string;

bool loadDeck(Game& g){
    string filename;
    std::cout << "Choose a file to load the deck from:" << std::endl;
    std::cin >> filename;
    try{
        g.loadDeckFromFile(filename);
    }
    catch(std::runtime_error const&){
        std::cout << "The file was invalid. Aborting." << std::endl;
        return false;
    }
    return true;
}

int getPlayerCount(){
    std::cout << "Enter number of players:" << std::endl;
    int numPlayers;
    while(true){
        if((!(std::cin >> numPlayers)) || numPlayers <= 0){
            if(std::cin.fail()){
                //Clear the fail flag
                std::cin.clear();
                //Remove the non-integer data from the stream
                string garbage;
                std::cin >> garbage;
            }
            std::cout << "Please enter a positive number" << std::endl;
        }
        else{
            break;
        }
    }
    return numPlayers;
}

void setupPlayers(Game& g, int numPlayers){
    for(int i=0; i < numPlayers; i++){
        std::cout << "Is player " << i << " an AI? (y/n)" << std::endl;
        char c;
        while(true){
            std::cin >> c;
            if(c == 'y'){
                g.addPlayer(true);
                break;
            }
            else{
                if(c == 'n'){
                    g.addPlayer(false);
                    break;
                }
                else{
                    std::cout << "Please enter y or n" << std::endl;
                }
            }
        }
    }
}

void setupGame(Game& g){
    int numCards;
    std::cout << "How many cards should each player start with?" << std::endl;
    while(true){
        if((!(std::cin >> numCards)) || numCards <= 0){
            if(std::cin.fail()){
                string garbage;
                std::cin.clear();
                std::cin >> garbage;
            }
            std::cout << "Please enter a positive number" << std::endl;
        }
        else{
            break;
        }
    }
    Card* c = g.deal(numCards);
    std::cout << "The initial discard is " << c->getRank() << " " << c->getSuit() << std::endl;
}

int main(){
    Game g;
    if(!loadDeck(g)){
        return 1;
    }
    int numPlayers = getPlayerCount();
    setupPlayers(g,numPlayers);
    try{
        setupGame(g);
    }
    catch(...){
        std::cout << "Too many cards dealt. Aborting";
        return 1;
    }
    int winner = g.runGame();
    if(winner != -1){
        std::cout << "Player " << winner << " wins!" << std::endl;
    }
    else{
        std::cout << "The game is a draw!" << std::endl;
    }
    std::cout << "The most played suit was " << g.mostPlayedSuit() << std::endl;
    return 0;
}