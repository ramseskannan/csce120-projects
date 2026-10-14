// provided. do not modify. do not submit.
#pragma once

#include <stdexcept>
#include <string>

enum City {
    HQ,
    Boston,
    Hartford,
    New_York,
    Philadelphia,
    Baltimore,
    Washington_DC,
    Pittsburgh,
    Cleveland,
    Detroit,
    Chicago,
    Indianapolis,
    Nashville,
    Atlanta,
    Houston,
    Austin,
    Dallas,
    Denver,
    Albuquerque,
    Phoenix,
    Sacramento
};

/**
 * Get the string name of a City
 *
 * @param city enum City to name
 * @returns name of the City or "???" if city is unknown
 */
std::string get_city_name(City city) {
    switch (city) {
    case HQ: return "HQ";
    case Boston: return "Boston";
    case Hartford: return "Hartford";
    case New_York: return "New York";
    case Philadelphia: return "Philadelphia";
    case Baltimore: return "Baltimore";
    case Washington_DC: return "Washington, DC";
    case Pittsburgh: return "Pittsburgh";
    case Cleveland: return "Cleveland";
    case Detroit: return "Detroit";
    case Chicago: return "Chicago";
    case Indianapolis: return "Indianapolis";
    case Nashville: return "Nashville";
    case Atlanta: return "Atlanta";
    case Houston: return "Houston";
    case Austin: return "Austin";
    case Dallas: return "Dallas";
    case Denver: return "Denver";
    case Albuquerque: return "Albuquerque";
    case Phoenix: return "Phoenix";
    case Sacramento: return "Sacramento";
    default: return "???";
    }
}

/**
 * Get enum City by string name of city
 *
 * @param name the name of the city
 * @returns enum City corresponding to string name
 * @throws `std::invalid_argument` if name is unknown
 */
City get_city_by_name(const std::string& name) {
    if (name == "HQ") return City::HQ;
    if (name == "Boston") return City::Boston;
    if (name == "Hartford") return City::Hartford;
    if (name == "New York") return City::New_York;
    if (name == "Philadelphia") return City::Philadelphia;
    if (name == "Baltimore") return City::Baltimore;
    if (name == "Washington, DC") return City::Washington_DC;
    if (name == "Pittsburgh") return City::Pittsburgh;
    if (name == "Cleveland") return City::Cleveland;
    if (name == "Detroit") return City::Detroit;
    if (name == "Chicago") return City::Chicago;
    if (name == "Indianapolis") return City::Indianapolis;
    if (name == "Nashville") return City::Nashville;
    if (name == "Atlanta") return City::Atlanta;
    if (name == "Houston") return City::Houston;
    if (name == "Austin") return City::Austin;
    if (name == "Dallas") return City::Dallas;
    if (name == "Denver") return City::Denver;
    if (name == "Albuquerque") return City::Albuquerque;
    if (name == "Phoenix") return City::Phoenix;
    if (name == "Sacramento") return City::Sacramento;
    throw std::invalid_argument("no such city");
}
