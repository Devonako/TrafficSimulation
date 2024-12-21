#include <iostream>
#include <vector>
#include <queue>
#include <random>

enum class Direction { North, South, East, West };
enum class LightColor { Green, Yellow, Red };

#include <iostream>
// ... (rest of the code)

// Overload the << operator to output Direction to the console
std::ostream& operator<<(std::ostream& os, Direction dir) {
    switch (dir) {
    case Direction::North: return os << "North";
    case Direction::South: return os << "South";
    case Direction::East: return os << "East";
    case Direction::West: return os << "West";
    }
    return os; // Should technically never happen, but good practice
}

// ... (rest of the code)
// Structure to represent a single car
struct Car {
    Direction direction;
    int arrivalTime;
};

// Structure to represent the intersection
struct Intersection {
    std::queue<Car> lanes[4];
    LightColor lights[4];
    int currentTime;

    Intersection() : currentTime(0) {
        // Initialize lights (North-South Green, East-West Red)
        lights[static_cast<int>(Direction::North)] = LightColor::Green;
        lights[static_cast<int>(Direction::South)] = LightColor::Green;
        lights[static_cast<int>(Direction::East)] = LightColor::Red;
        lights[static_cast<int>(Direction::West)] = LightColor::Red;
    }

    void addCar(Car car) {
        lanes[static_cast<int>(car.direction)].push(car);
    }

    void updateLights() {
        // Simplified traffic light cycle (could be made more realistic)
        int cycleTime = 70; // Total cycle time in seconds
        int phase = currentTime % cycleTime;

        if (phase < 30) {
            // North-South Green, East-West Red
            lights[static_cast<int>(Direction::North)] = LightColor::Green;
            lights[static_cast<int>(Direction::South)] = LightColor::Green;
            lights[static_cast<int>(Direction::East)] = LightColor::Red;
            lights[static_cast<int>(Direction::West)] = LightColor::Red;
        }
        else if (phase < 35) {
            // North-South Yellow, East-West Red
            lights[static_cast<int>(Direction::North)] = LightColor::Yellow;
            lights[static_cast<int>(Direction::South)] = LightColor::Yellow;
            lights[static_cast<int>(Direction::East)] = LightColor::Red;
            lights[static_cast<int>(Direction::West)] = LightColor::Red;
        }
        else if (phase < 65) {
            // East-West Green, North-South Red
            lights[static_cast<int>(Direction::East)] = LightColor::Green;
            lights[static_cast<int>(Direction::West)] = LightColor::Green;
            lights[static_cast<int>(Direction::North)] = LightColor::Red;
            lights[static_cast<int>(Direction::South)] = LightColor::Red;
        }
        else {
            // East-West Yellow, North-South Red
            lights[static_cast<int>(Direction::East)] = LightColor::Yellow;
            lights[static_cast<int>(Direction::West)] = LightColor::Yellow;
            lights[static_cast<int>(Direction::North)] = LightColor::Red;
            lights[static_cast<int>(Direction::South)] = LightColor::Red;
        }
    }

    void moveCars() {
        // Move cars if the light is green for their direction
        for (int i = 0; i < 4; ++i) {
            Direction dir = static_cast<Direction>(i);
            if (lights[i] == LightColor::Green && !lanes[i].empty()) {
                lanes[i].pop(); // Remove the car from the queue (it has passed)
            }
        }
    }

    void simulate() {
        // Initialize random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dirDist(0, 3); // For random directions
        std::uniform_int_distribution<> arrivalDist(1, 5); // For random arrival times

        while (true) {
            updateLights();
            moveCars();

            // Add new cars randomly
            if (currentTime % arrivalDist(gen) == 0) {
                Direction dir = static_cast<Direction>(dirDist(gen));
                addCar({ dir, currentTime });
            }

            // Simple text-based output (you can add more detailed output)
            std::cout << "Time: " << currentTime << std::endl;
            for (int i = 0; i < 4; ++i) {
                std::cout << "Lane " << i << " ("
                    << (static_cast<Direction>(i)) << "): "
                    << lanes[i].size() << " cars" << std::endl;
            }
            std::cout << std::endl;

            currentTime++;
            // You might want to add a delay here to slow down the simulation
        }
    }
};

int main() {
    Intersection intersection;
    intersection.simulate();
    return 0;
}