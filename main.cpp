#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

//======================== VEHICLE ========================
class Vehicle {
protected:
    string vehicleID;
    double speed;
    int capacity;
    int currentPassengers;
    int currentStationIndex;   
    int moveInterval;          

public:
    Vehicle(string id, double sp, int cap, int interval, int startStation) {
        vehicleID = id;
        speed = sp;
        capacity = cap;
        currentPassengers = 0;
        moveInterval = interval;
        currentStationIndex = startStation;
    }

    virtual ~Vehicle() {}
    virtual void move(string stationName) = 0;

    void boardPassengers(int count) {
        int availableSeats = capacity - currentPassengers;
        int boarded = min(availableSeats, count);
        currentPassengers += boarded;

        cout << "   " << boarded << " passengers boarded " << vehicleID << endl;

        if (boarded < count) {
            cout << "   Vehicle Full! " << count - boarded << " passengers left behind.\n";
        }
    }

    void releasePassengers() {
        if (currentPassengers == 0) return;

        int leaving = rand() % (currentPassengers + 1);
        currentPassengers -= leaving;

        cout << "   " << leaving << " passengers left " << vehicleID << endl;
    }

    int getMoveInterval() { return moveInterval; }
    int getCurrentStation() { return currentStationIndex; }

    void nextStation(int totalStations) {
        currentStationIndex++;
        if (currentStationIndex >= totalStations) {
            currentStationIndex = 0;
        }
    }

    string getID() { return vehicleID; }

    virtual void displayStatus() {
        cout << "   Status -> " << vehicleID << " | Passengers : " << currentPassengers << "/" << capacity << endl;
    }
};

//======================== BUS ========================
class Bus : public Vehicle {
public:
    Bus(string id, int startStation) : Vehicle(id, 40, 50, 1, startStation) {}

    void move(string stationName) override {
        cout << "\n🚌 Bus " << vehicleID << " reached " << stationName << endl;
    }
};

//======================== EXPRESS TRAIN ========================
class ExpressTrain : public Vehicle {
public:
    ExpressTrain(string id, int startStation) : Vehicle(id, 120, 200, 2, startStation) {}

    void move(string stationName) override {
        cout << "\n🚄 Express Train " << vehicleID << " reached " << stationName << endl;
    }
};

//======================== STATION ========================
class Station {
public:
    string stationName;
    int waitingPassengers;

    Station(string name, int passengers) {
        stationName = name;
        waitingPassengers = passengers;
    }

    void spawnPassengers(int count) {
        waitingPassengers += count;
    }
};

//======================== TRANSIT ROUTE ========================
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
        cout << "\n========== " << routeName << " ==========\n";
        for (size_t i = 0; i < stations.size(); i++) {
            cout << i << ". " << stations[i].stationName 
                 << " | Waiting Passengers : " << stations[i].waitingPassengers << endl;
        }
        cout << endl;
    }
};
//======================== Simulation Engine ========================
class SimulationEngine {
private:
    TransitRoute* route;
    int currentTick;

public:
    SimulationEngine(TransitRoute* r) {
        route = r;
        currentTick = 0;
    }

    void runSimulation(int totalMinutes) {
        cout << "\n==============================";
        cout << "\n SMART TRANSIT SIMULATION";
        cout << "\n==============================\n";

        for (currentTick = 1; currentTick <= totalMinutes; currentTick++) {
            cout << "\n--------------------------------";
            cout << "\nMinute " << currentTick;
            cout << "\n--------------------------------\n";

            
            for (int i = 0; i < (int)route->stations.size(); i++) {
                int newPassengers = rand() % 5 + 1;
                route->stations[i].spawnPassengers(newPassengers);
            }

            route->displayRouteInfo();

            
            for (int i = 0; i < (int)route->activeVehicles.size(); i++) {
                Vehicle* vehicle = route->activeVehicles[i];

                if (currentTick % vehicle->getMoveInterval() != 0) {
                    continue;
                }

                int stationIndex = vehicle->getCurrentStation();
                Station &currentStation = route->stations[stationIndex];

                
                vehicle->move(currentStation.stationName);

               
                vehicle->releasePassengers();

               
                if (currentStation.waitingPassengers > 0) {
                    cout << "   Boarding from " << currentStation.stationName << endl;
                    vehicle->boardPassengers(currentStation.waitingPassengers);
                    currentStation.waitingPassengers = 0;
                } else {
                    cout << "   No passengers waiting.\n";
                }

                vehicle->displayStatus();


                vehicle->nextStation((int)route->stations.size());
            }
        }

        cout << "\n==============================";
        cout << "\n SIMULATION FINISHED";
        cout << "\n==============================\n";   
    }
};

int main() {
srand(time(0));

   
    TransitRoute greenLine("Green Line City Central");

    
    greenLine.addStation(Station("Downtown Hub", 10));
    greenLine.addStation(Station("Metro Station A", 5));
    greenLine.addStation(Station("Suburban Terminal", 2));
    greenLine.addStation(Station("City Mall", 7));
    greenLine.addStation(Station("Airport Junction", 4));


    Bus* cityBus1 = new Bus("BUS-101", 0);            // Bus starts from station 0
    ExpressTrain* bulletTrain = new ExpressTrain("TRAIN-707", 2); // Train starts from station 2
    Bus* cityBus2 = new Bus("BUS-202", 3);

   
    greenLine.assignVehicle(cityBus1);
    greenLine.assignVehicle(bulletTrain);
    greenLine.assignVehicle(cityBus2);

    SimulationEngine engine(&greenLine);

    engine.runSimulation(10);

    
    delete cityBus1;
    delete bulletTrain;
    delete cityBus2;

    
    return 0;
}
