#include <iostream>
#include "rank_functions.h"

int main() {
    // TODO(student): create and load driver data into a vector of drivers using load_driver_data()
    std::vector<driver> driver_data = load_driver_data(); //creating a loading driver data into a dector of drivers using the function in .cpp

    // TODO(student): if loading driver data failed,
    //                1) print "Bad input" to standard output
    //                2) exit the program by returning 1
    if (driver_data.empty()){ //checking if the dricer data failed!
        std::cout << "Bad input" << std::endl; //print "bad input"
        return 1; //exit the program by returning 1
    }

    // TODO(student): set the rankings of the drivers using set_rankings()

    driver_data = set_rankings(driver_data); //passing the driver data to the set rankings


    // TODO(student): print the results using print_results()
    print_results(driver_data); 

    return 0;
}
