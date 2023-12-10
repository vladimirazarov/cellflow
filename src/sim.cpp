/* 
 * sim.cpp
 * 
 * Description : Simulation of traffic flow using cellular automata.
 * 
 * Author : Vladimir Azarov
 * 
 */

#include "sim.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <numeric>
#include <algorithm>
#include "sim.hpp"

// Function to initialize the road state
void initializeRoad(std::vector<int> &road, double density)
{
    for (int i = 0; i < road.size(); ++i)
    {
        // Random number between 0 and 1
        double randomNum = std::rand() / (double)RAND_MAX;

        // Check if this random number is less than density
        if (randomNum < density)
        {
            // If yes, generate a random initial speed for the vehicle
            int initialSpeed = std::rand() % (vmax + 1);

            // Save this speed in the array
            road[i] = initialSpeed;
        }
        else
        {
            // If not, set the cell to -1, indicating it's empty
            road[i] = -1;
        }
    }
}

// Function to update the road state
void updateRoad(std::vector<int> &road)
{
    // Acceleration and deceleration
    for (int i = 0; i < road.size(); ++i)
    {
        if (road[i] >= 0)
        {
            // Acceleration
            road[i] = std::min(road[i] + 1, vmax);

            // Measure the distance to the next vehicle
            int distance = 0;
            while (road[(i + distance + 1) % road.size()] == -1 && distance < road[i])
            {
                distance++;
            }

            // Deceleration if the vehicle is too close to the vehicle in front
            if (distance < road[i])
            {
                road[i] = distance;
            }
        }
    }

    // Random deceleration
    for (int i = 0; i < road.size(); ++i)
    {
        if (road[i] > 0 && (std::rand() / (double)RAND_MAX) < 0.5)
        {
            road[i]--;
        }
    }

    // Vehicle movement
    std::vector<int> newRoad(road.size(), -1);
    for (int i = 0; i < road.size(); ++i)
    {
        if (road[i] >= 0)
        {
            newRoad[(i + road[i]) % road.size()] = road[i];
        }
    }
    road = newRoad;
}

// Function to print the road state
void printRoad(const std::vector<int> &road)
{
    for (int i = 0; i < road.size(); ++i)
    {
        if (road[i] == -1)
        {
            std::cout << ".";
        }
        else
        {
            std::cout << road[i];
        }
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    // Check the number of arguments
    if (argc != 5)
    {
        std::cerr << "Usage: " << argv[0] << " <mode> <roadLength> <density> <iterations>\n";
        std::cerr << "Modes: 1 - For fixed density, diagram will be displayed, 2- Average flow and densities will be sent to stdout (for all densities <0, 1>, with step 0.00005).  \n";
        return 1;
    }

    int mode;
    int roadLength, iterations;
    double density;

    // Parse mode selection
    std::istringstream(argv[1]) >> mode;

    // Convert arguments to numbers
    std::istringstream(argv[2]) >> roadLength;
    std::istringstream(argv[3]) >> density;
    std::istringstream(argv[4]) >> iterations;

    // Check if the values are within a valid range
    if (density < 0.0 || density > 1.0 || roadLength <= 0 || iterations <= 0)
    {
        std::cerr << "Invalid argument values.\n";
        return 1;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Initialize the random number generator

    std::vector<int> road(roadLength, -1); // Create and initialize the road

    if (mode == 1)
    {
        // Mode 1: Print road only
        initializeRoad(road, density);
        for (int t = 0; t < iterations; ++t)
        {
            updateRoad(road);
            printRoad(road); // Print the road state
        }
    }
    else if (mode == 2)
    {
        // Mode 2: Full simulation without printing road
        for (double density = 0.0; density < 1.0; density += 0.00005)
        {
            initializeRoad(road, density);

            int totalSpeed = 0;     // Total speed of all vehicles
            int totalDensity = 0;   // Total vehicle density

            // Simulation loop
            for (int t = 0; t < iterations; ++t)
            {
                updateRoad(road);

                // Record vehicle flow (using speed)
                totalSpeed += std::accumulate(road.begin(), road.end(), 0, [](int total, int v) {
                    return total + (v > 0 ? v : 0);
                });

                // Record vehicle density
                totalDensity += std::count_if(road.begin(), road.end(), [](int v) { return v != -1; });
            }

            double averageFlow = static_cast<double>(totalSpeed) / iterations;                       // Average flow
            double averageDensity = static_cast<double>(totalDensity) / (roadLength * iterations);  // Average density

            // Print average density and flow for the given density
            std::cout << averageFlow << " " << averageDensity << std::endl;
        }
    }
    else
    {
        std::cerr << "Invalid mode selected.\n";
        return 1;
    }

    return 0;
}