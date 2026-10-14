#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "rank_functions.h"

// load data from standard input into a vector
//   input format := <time> <country> <number> <name>
//   examples:
//     32.7 AUS 81 Piastri
//     36.5 NED 1  Verstappen
//   rank should be initialized to 0 for each driver
// returns a vector of drivers, or an empty vector if any input is invalid
std::vector<driver> load_driver_data() {
    std::vector<driver> drivers;

    //intialize these before because you are passing it throguh (last name will be after)
    //initializiang time, countrym number, and name
    double time;
    std::string country; //its not just one letter 
    int number;
    

    //ok now we have to read the file/input from start to end. 
    //using a while loop we will interate through it and find the 4 values from cin (unless a wrong entry is found!)
    //this is time, country, number, and lastname
    //only passing valid ones
    while (std::cin >> time >> country >> number){ //originally i had lastname, but if i do that it doesnt let lastnames with spcaes go through
        std::string lastname; //its not just one letter, have to use string
        std::getline(std::cin, lastname); //this will take eveyrthing after number (its in the parameter)
        if (!lastname.empty() && std::isspace(lastname[0])){
            lastname = lastname.substr(1);
        }
        lastname = trim(lastname);
        //validating time
        if (time <= 0){
            return {}; //has to be positive
        }
        //validating country
        if (country.length() != 3 ||
            !std::isupper(country[0]) || !std::isalpha(country[0]) ||
            !std::isupper(country[1]) || !std::isalpha(country[1]) ||
            !std::isupper(country[2]) || !std::isalpha(country[2])){ //as we saw in the examples, the country name is jsut 3 letters
            
            return {}; //the country input is invalid
        }
        //checking if its a valid number
        if (number < 0 || number > 99) { //[0, 99] is the range, if not in range its invalid  
            return {}; 
        }

        int count = 0;
        //checking if this is a valid last name
        for (char c : lastname){
            if (!std::isalpha(c) && c!= ' '){
                return {}; //this happens if its not a letter os space
            }
            if (std::isalpha(c)){  
                count++; //counting the valid letters
            }
        }
        if (count < 2){ //checking if the last name is less than 2 letters (invalid)
            return {};
        }
            //so after checking the 4 inputs, and ONLY IF THEY ALL PASS time to add the driver
        driver d {}; //initializes it
        d.time = time;
        d.country = country;
        d.number = number;
        d.rank = 0; //set the rank to 0 for now. the next function will fix this
        d.lastname = lastname;
        drivers.push_back(d); //added the (checked) driver to the drivers vector
            
    }
    return drivers; //only returns the vector with valud drivers!
}


// returns a copy of the input vector with ranks set based on the time for each driver.
//   the fastest/minimum time is ranked 1
// the order of the elements in the vector should not be changed
std::vector<driver> set_rankings(std::vector<driver> drivers) { //drivers is the vector we are passing
    //this loops through each driver
    for (size_t i = 0; i < drivers.size(); ++i){ //use size_t to iterate through vectors as size can change
        int r = 1; //it has to start from 1 (rank)
        //no we compare it to every other driver in the drivers vector (checked ones)
        for (size_t j = 0; j < drivers.size(); j++){ //use size_t to iterate through vectors as size can change
            if (drivers[j].time < drivers [i].time){
                r++; //incresing it the driver we compare it to has a shorter time!
            }
        }
        drivers[i].rank = r; //GIVING THAT DRIVER THEIR RANK!!!!!! :D
    }

    return drivers;
}

// returns a copy of the input string with whitespace removed from the front and back
std::string trim(std::string str) {
    // TODO(student)
    if (str.empty()){ //if the string passed is just empty, return an empty string back
        return "";
    } 
    //this also has to be size_t cause size can change and ur using to interate through
    size_t first = 0; //index of the first not space characters. number/char/etc
    //this will move the "first" forward while we are looking for spaces
    while (first < str.size() && std::isspace(str[first])) {
        first ++;
    }

    //finds the index of the last letter/number/char in the str
    //this also has to be size_t cause size can change and ur using to interate through
    size_t last = str.size();
    //this will move "last" backward while we are looking for spaces still
    while (last > first && std::isspace(str[last -1])){
        last--;
    }
    return str.substr(first, last-first);
}

// print the results of the race
void print_results(const std::vector<driver>& drivers) {
    // get the fastest time
    double best_time;
    for (const driver& driver : drivers) {
        if (driver.rank == 1) {
            best_time = driver.time;
            break;
        }
    }

    std::cout << "Final results!";
    std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
    for (unsigned rank = 1; rank <= drivers.size(); rank++) {
        for (const driver& driver : drivers) {
            if (driver.rank == rank) {
                std::string rank_str = "["+std::to_string(rank)+"]";
                std::cout << std::setw(4) << std::left << rank_str << " " << driver.time << " " << std::setw(15) << std::left << driver.lastname << " (" << driver.country << ") +" << (driver.time - best_time) << std::endl;
            }
        }
    }
}
