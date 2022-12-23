#ifndef _PARKING_H
#define _PARKING_H

#include <iostream>
/*
Final Project Milestone 2
Filename: Parking.h
Author: Rachit Chawla
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#include "Menu.h"
#include "Vehicle.h"

namespace sdds {
    const int maxSpots = 100;
    class Parking {
        private:
            char *m_filename {nullptr};
            Menu m_parkingMenu;
            Menu m_vehicleSelectionMenu;
            int m_noOfSpots;
            Vehicle* m_parkingSpots[maxSpots]{nullptr};
            int m_noOfParkedVehicles = 0;
            

            bool isEmpty();
            void parkingStatus();
            void parkVehicle();
            void returnVehicle();
            void listVehicles();
            void findVehicle();
            bool closeParking();
            bool exitParking();
            bool loadData();
            void saveData();
        public:
            Parking(const char *filename, int noOfSpots);
            ~Parking();
            Parking(const Parking& P) = delete;
            Parking& operator=(const Parking& P) = delete;
            int run();



    };
}

#endif // _PARKING_H