#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class Vehicle {
protected:
    string vehicleID;
    double speed;
    int capacity;
    int currentPassengers;

public:
    Vehicle(string id, double maxSpeed, int cap) {
        vehicleID = id;
        speed = maxSpeed;
        capacity = cap;
        currentPassengers = 0;
    }

    virtual ~Vehicle() {}

    virtual void move() = 0;

    void boardPassengers(int count) {
        currentPassengers = min(capacity, currentPassengers + count);
    }

    void releasePassengers() {
        currentPassengers = 0;
    }

    string getID() {
    return vehicleID;
}

    virtual void displayStatus() {
        cout << "Vehicle [" << vehicleID << "] | Speed: " << speed
             << " km/h | Passengers: " << currentPassengers << "/" << capacity << endl;
    }
};

class Bus : public Vehicle {
public:
    Bus(string id) : Vehicle(id, 40.0, 50) {}

    void move() override {
        cout << " Bus " << vehicleID << " is navigating city streets (making frequent stops)." << endl;
    }
};

class ExpressTrain : public Vehicle {
public:
    ExpressTrain(string id) : Vehicle(id, 120.0, 200) {}

    void move() override {
        cout << "⚡ Express Train " << vehicleID << " is flying down the dedicated tracks!" << endl;
    }
};



class Station {
public:
    string stationName;
    int waitingPassengers;

  
    Station(string name, int initialPassengers) {
        stationName = name;
        waitingPassengers = initialPassengers;
    }

   
    void spawnPassengers(int count) {
        waitingPassengers += count;
    }
};


class TransitRoute {
public:
    string routeName;
    vector<Station> stations;        
    vector<Vehicle*> activeVehicles; 
   
    TransitRoute(string name) {
        routeName = name;
    }

    
    void addStation(Station s) {
        stations.push_back(s);
    }

    
    void assignVehicle(Vehicle* v) {
        activeVehicles.push_back(v);
    }

    
    void displayRouteInfo() {
        cout << "\n--- Route: " << routeName << " ---" << endl;
        cout << "Stations: ";
        for (int i = 0; i < stations.size(); i++) {
            cout << stations[i].stationName << " (" << stations[i].waitingPassengers << " waiting)";
            if (i < stations.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
};



class SimulationEngine {
public:
    TransitRoute* route;
    int currentTick; // Keeps track of simulated minutes passed

    SimulationEngine(TransitRoute* r) {
        route = r;
        currentTick = 0;
    }

    
    void runSimulation(int totalMinutes) {
        cout << "\n=== STARTING SMART TRANSIT SIMULATION ===" << endl;

        for (int i = 0; i < totalMinutes; i++) {
            currentTick++;
            cout << "\n⏱️ [Minute " << currentTick << "]" << endl;

            
            for (int s = 0; s < route->stations.size(); s++) {
                route->stations[s].spawnPassengers(rand() % 5 + 1); // Adds 1 to 5 new people
            }
            route->displayRouteInfo();

           
            for (int v = 0; v < route->activeVehicles.size(); v++) {
                Vehicle* currentVehicle = route->activeVehicles[v];
                
                
                currentVehicle->move();

                
                for (int s = 0; s < route->stations.size(); s++) {
                    if (route->stations[s].waitingPassengers > 0) {
                        int peopleToBoard = route->stations[s].waitingPassengers;
                        
                        cout << "   [Boarding] " << peopleToBoard << " passengers entering " << currentVehicle->getID() << endl;
                        
                        currentVehicle->boardPassengers(peopleToBoard);
                        route->stations[s].waitingPassengers = 0; // Station is now cleared
                        break; 
                    }
                }
                
                
                currentVehicle->displayStatus();
            }
        }
        cout << "\n=== SIMULATION COMPLETE ===" << endl;
    }
};


int main() {
   
    srand(time(0));

    
    TransitRoute greenLine("Green Line City Central");

    greenLine.addStation(Station("Downtown Hub", 10));
    greenLine.addStation(Station("Metro Station A", 5));
    greenLine.addStation(Station("Suburban Terminal", 2));

   
    Bus* cityBus = new Bus("BUS-101");
    ExpressTrain* bulletTrain = new ExpressTrain("TRAIN-707");

    
    greenLine.assignVehicle(cityBus);
    greenLine.assignVehicle(bulletTrain);

    
    SimulationEngine engine(&greenLine);

    
    engine.runSimulation(3);

    
    delete cityBus;
    delete bulletTrain;

    return 0;
}
