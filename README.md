# 🚌 Public Transport Simulation System

A C++ Object-Oriented Programming project that simulates a public transportation network consisting of buses, express trains, stations, passengers, and route operations. The project demonstrates core OOP concepts such as Inheritance, Polymorphism, Abstraction, Encapsulation, and Dynamic Binding through a real-time transport simulation.

---  

## 📌 Project Overview

The system models a transportation route with multiple stations and vehicles. During each simulation cycle, stations generate new passengers, vehicles move across the route, passengers board available vehicles, and the system displays the updated transportation status.

---

## ✨ Features

- Multiple transportation modes (Bus and Express Train)
- Station-based passenger generation
- Vehicle passenger boarding system
- Route management and monitoring
- Real-time simulation engine
- Dynamic vehicle assignment
- Passenger capacity management
- Status tracking for vehicles and stations

---

## 🛠️ Technologies Used

- C++
- Object-Oriented Programming (OOP)
- Standard Template Library (STL)

---

## 🎯 OOP Concepts Implemented

### Encapsulation
Data members such as vehicle speed, capacity, passenger count, and vehicle ID are protected within classes and accessed through member functions.

### Inheritance
`Bus` and `ExpressTrain` inherit from the abstract `Vehicle` base class.

### Polymorphism
The `move()` function is declared as a pure virtual function and implemented differently by each vehicle type.

### Abstraction
The abstract `Vehicle` class defines common vehicle behavior while hiding implementation details.

### Dynamic Binding
Vehicle objects are handled using base-class pointers (`Vehicle*`) and resolved at runtime.

---

## 🏗️ Class Structure

### Vehicle (Abstract Base Class)
- Vehicle ID
- Speed
- Capacity
- Passenger Management
- Virtual Movement Behavior

### Bus
- Inherits from Vehicle
- Simulates city transportation

### ExpressTrain
- Inherits from Vehicle
- Simulates high-speed rail transportation

### Station
- Stores station information
- Manages waiting passengers
- Generates new passengers dynamically

### TransitRoute
- Manages stations
- Assigns vehicles
- Displays route information

### SimulationEngine
- Controls the entire simulation
- Updates stations and vehicles each minute
- Handles passenger boarding

---

## ⚙️ Simulation Workflow

1. Create a transport route.
2. Add stations to the route.
3. Assign vehicles (Bus and Express Train).
4. Start the simulation engine.
5. Generate passengers at stations.
6. Move vehicles along the route.
7. Board waiting passengers.
8. Display vehicle and station status.
9. Repeat for the specified simulation duration.

---

## 📂 Project Structure

```text
Public_Transport_Simulation System/
│
├── main.cpp
├── README.md
```

---

## 🚀 How to Run

### Compile

```bash
g++ main.cpp -o simulation
```

### Execute

```bash
./simulation
```

---

## ▶️ Sample Output

```text
==============================
 SMART TRANSIT SIMULATION
==============================

--------------------------------
Minute 1
--------------------------------

========== Green Line City Central ==========
0. Downtown Hub | Waiting Passengers : 13
1. Metro Station A | Waiting Passengers : 8
2. Suburban Terminal | Waiting Passengers : 6
3. City Mall | Waiting Passengers : 11
4. Airport Junction | Waiting Passengers : 9


🚌 Bus BUS-101 reached Downtown Hub
   Boarding from Downtown Hub
   13 passengers boarded BUS-101
   Status -> BUS-101 | Passengers : 13/50

🚌 Bus BUS-202 reached City Mall
   Boarding from City Mall
   11 passengers boarded BUS-202
   Status -> BUS-202 | Passengers : 11/50
   ```

## 📚 Learning Outcomes

- Object-Oriented Programming Design
- Inheritance and Polymorphism
- Abstract Classes and Virtual Functions
- Dynamic Memory Allocation
- STL Vectors
- Simulation-Based Modeling

---
