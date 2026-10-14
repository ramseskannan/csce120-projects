#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include "Cities.h"
#include "LinkedList.h"

int getRouteL(const LinkedList& schedule){
    //this function calculates and returns the total route length
    //it initaliz distance and sgtart
    int distance = 0;
    int prev = 0;

    for(unsigned i = 0; i < schedule.size(); i++){
        //loops through da cities
        int curr = schedule.at(i); //current city loc
        distance += abs(curr - prev); //add disgtance from prev
        prev = curr; //update dat ho
    }
    distance += abs(prev); //add return to HQ
    return distance; //returns the total
}

//no checkcing if duplaicate, checks if adding city at index creates consecitive duplicate
bool isDuplicate(const LinkedList& schedule, int city, unsigned index){
    if (index > 0 && schedule.at(index - 1) == city){
        return true; //checls before
    }
    if (index < schedule.size() && schedule.at(index) == city){
        return true; //checls at dat point
    }
    return false;
}
// TODO(student): implement the dispatch scheduler
int main() {

    //push, pop, add, remove, print, clear, quit
    LinkedList schedule; //first create a shcedule
    ///and input line
    std::string line; 

    while(std::getline(std::cin, line)){ //reading input line by line
        std::istringstream iss(line); //creating stream from line
        //them command and city name variables need to be there
        std::string cmd, city_name; 
        //then read command word
        iss>> cmd;

        if(cmd == "quit"){//quit and exit the loop
            break;
        }
        else if (cmd == "push"){ //push cmd
            //read rest of line (city name)
            std::getline(iss >> std::ws, city_name);
            try{
                //convert name to city valie
                int city = static_cast<int>(get_city_by_name(city_name));
                //then we check if it wont create duplicate
                if(!isDuplicate(schedule, city, 0)){
                    schedule.add(city, 0); //add to front of schedule
                }
                //catch the invalid city name and print error
            } catch (const std::invalid_argument&){
                std::cout << "Unknown city." << std::endl;
            }
        }
        else if(cmd == "pop"){
            //pop command remove the first
            //first check if dat ho empty
            if (schedule.empty()){
                std::cout << "Cannot pop from an empty schedule." << std::endl;
            } else { //this means the schedule has cities
                schedule.remove(0); //this will remove the first cityh
            }
        }
        else if (cmd== "add"){
            //READS REST OF THE LINE AS CITY NAMR
            std::getline(iss >> std::ws, city_name);
            //first error handle
            try {
                //convert city val
                int city = static_cast<int>(get_city_by_name(city_name));
                unsigned pos = schedule.size();
                for (unsigned i = 0; i < schedule.size(); i++){
                    if (schedule.at(i) > city) { //this means found city further than the new city
                        pos = i; //set insertion position
                        break; //stop searching
                    }
                }
                if (!isDuplicate(schedule, city, pos)) {
                    schedule.add(city, pos); //add the cirty at pos
                }
            } catch (const std::invalid_argument&){
                //catch the invalid city name and print error
                std::cout << "Unknown city." << std::endl;
            }
        }
        //remove , this removes specified city
        else if(cmd == "remove"){
            //first read rest of line
            std::getline(iss >> std::ws, city_name);
            try{
                int city = static_cast<int>(get_city_by_name(city_name));
                bool found = false; //track if city was found
                for (unsigned i = 0; i < schedule.size(); i++){ //this loops tjhru da schedule
                    if(schedule.at(i) == city){ //it found a matching city
                        schedule.remove(i); //remove city at index
                        found = true; //marks as found

                        //we have to check if there are two cities the same next to eachother after removing
                        if(i > 0 && i < schedule.size() && schedule.at(i-1) == schedule.at(i)){
                            schedule.remove(i);
                        }
                        else if(i == 0 && schedule.size() >= 2 && schedule.at(0) == schedule.at(1)){
                            schedule.remove(i);
                        }
                        break; //this stops searching
                    }
                }
                if (!found){
                    std::cout << get_city_name(City(city)) << " is not on the schedule." << std::endl;
                }
            } catch (const std::invalid_argument&) {
                std::cout << "Unknown city." << std::endl;
            }
        }
        else if (cmd == "print"){ //print command, display schedule
          if (schedule.empty()){
            std::cout << "The schedule is empty." << std::endl;
          } else { 
            for (unsigned i = 0; i < schedule.size(); i++){
                std::cout << get_city_name(City(schedule.at(i))) << " -> ";
            }
            std::cout << ". (" << getRouteL(schedule) << ")" << std::endl;
          }
        }
        else if (cmd == "clear"){
            schedule.clear();
        } 
        else if(!cmd.empty()){
            //this is unkown
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0; //this quits
}

