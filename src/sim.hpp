#ifndef SIM_HPP
#define SIM_HPP

#include <vector>
#include <string>

// Declarations of the functions 
void initializeRoad(std::vector<int>& road, double density);
void updateRoad(std::vector<int>& road);
void printRoad(const std::vector<int>& road);

// Constants 
const int vmax = 5; // Maximum velocity of vehicles

#endif // SIM_HPP