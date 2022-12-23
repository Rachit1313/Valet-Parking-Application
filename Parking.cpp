/*
Final Project Milestone 2
Filename: Parking.cpp
Author: Rachit Chawla
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#include <iostream>
#include <cstring>
#include <cctype>
#include "Parking.h"
#include <fstream>
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Utils.h"

namespace sdds {
    bool Parking::isEmpty()
    {
        return this->m_filename == nullptr;
    }

    void Parking::parkingStatus()
    {
        std::cout << "****** Valet Parking ******" << std::endl;
        std::cout << "*****  Available spots: ";
        std::cout.width(4);
        std::cout.setf(std::ios::left);
        std::cout << this->m_noOfSpots << " *****" << std::endl;
    }

    void Parking::parkVehicle()
    {
        if (this->m_noOfSpots < 1) {
            std::cout << "Parking is full" << std::endl;
        }
        else {
            int selection = this->m_vehicleSelectionMenu.run();
            
            // User selects to cancel
            if (selection == 3) {
                std::cout << "Parking cancelled" << std::endl;
            } 
            else {
                Vehicle *v = nullptr;
                if (selection == 1)
                    v = new Car();
                else if (selection == 2)
                    v = new Motorcycle();
                
                v->setCsv(false);
                v->read(std::cin);

                bool parked = false;
                for (int i = 0; !parked && i < this->m_noOfParkedVehicles + this->m_noOfSpots; ++i) {
                    if (this->m_parkingSpots[i] == nullptr) {
                        v->setParkingSpot(i + 1);
                        this->m_parkingSpots[i] = v;
                        parked = true;
                        this->m_noOfSpots -= 1;
                        this->m_noOfParkedVehicles += 1;
                    }
                }
                std::cout << std::endl << "Parking Ticket" << std::endl;
                v->write(std::cout);
                std::cout << std::endl;

            }
            std::cout << "Press <ENTER> to continue....";
            std::cin.get();
            std::cin.ignore();
        }
    }

    void Parking::returnVehicle()
    {
        std::cout << "Return Vehicle" << std::endl;

        char licensePlate[10];
        std::cout << "Enter License Plate Number: ";
        do {
            std::cin >> licensePlate;
            std::cout << std::endl;
            if (strlen(licensePlate) < 1 || strlen(licensePlate) > 8) {
                std::cin.ignore(1024, '\n');
                std::cout << "Invalid License Plate, try again: ";
            }
        } while (!(strlen(licensePlate) >= 1 && strlen(licensePlate) <= 8));

        bool found = false;
        for (int i = 0; !found && i < this->m_noOfParkedVehicles; ++i) {
            if (this->m_parkingSpots[i] != nullptr) {
                if (sdds::compareCaseInsensitiveString(this->m_parkingSpots[i]->getLicensePlate(), licensePlate) == 0) {
                    found = true;
                    
                    std::cout << "Returning:" << std::endl;
                    this->m_parkingSpots[i]->setCsv(false);
                    this->m_parkingSpots[i]->write(std::cout);
        std::cout << std::endl;
                    delete this->m_parkingSpots[i];
                    this->m_parkingSpots[i] = nullptr;
                    this->m_noOfSpots += 1;
                    this->m_noOfParkedVehicles -= 1;
                }
            }
        }
        if (!found) {
    for (unsigned i = 0; i < strlen(licensePlate); i++) {
        licensePlate[i] = toupper(licensePlate[i]);
    }
            std::cout << "License plate " << licensePlate << " Not found" << std::endl << std::endl;
        }
            std::cout << "Press <ENTER> to continue....";
            std::cin.get();
            std::cin.ignore();
    }

    void Parking::listVehicles()
    {
        std::cout << "*** List of parked vehicles ***" << std::endl;
        for (int i = 0; i <= this->m_noOfParkedVehicles; ++i) {
            if (this->m_parkingSpots[i] != nullptr) {
                this->m_parkingSpots[i]->setCsv(false);
                this->m_parkingSpots[i]->write(std::cout);
                std::cout << "-------------------------------" << std::endl;
            }
        }
       std::cout << "Press <ENTER> to continue....";
       std::cin.ignore();
    }

    void Parking::findVehicle()
    {
        std::cout <<  "Vehicle Search" << std::endl;

        char licensePlate[10];
        std::cout << "Enter Licence Plate Number: ";
        do {
            std::cin >> licensePlate;
            std::cout << std::endl;
            if (strlen(licensePlate) < 1 || strlen(licensePlate) > 8) {
                std::cin.ignore(1024, '\n');
                std::cout << "Invalid License Plate, try again: ";
            }
        } while (!(strlen(licensePlate) >= 1 && strlen(licensePlate) <= 8));

        bool found = false;
        for (int i = 0; !found && i < this->m_noOfParkedVehicles; ++i) {
            if (this->m_parkingSpots[i] != nullptr) {
                if (sdds::compareCaseInsensitiveString(this->m_parkingSpots[i]->getLicensePlate(), licensePlate) == 0) {
                    std::cout << "Vehicle found:" << std::endl;
                    this->m_parkingSpots[i]->setCsv(false);
                    this->m_parkingSpots[i]->write(std::cout);
                    found = true;
                    std::cout << std::endl;
                }
            }
        }
        if (!found) {
    for (unsigned i = 0; i < strlen(licensePlate); i++) {
        licensePlate[i] = toupper(licensePlate[i]);
    }
            std::cout << "License plate " << licensePlate << " Not found" << std::endl << std::endl;
 }
            std::cout << "Press <ENTER> to continue....";
            std::cin.get();
            std::cin.ignore();
    }

    bool Parking::closeParking()
    {
        bool flag = false;


        if (this->m_noOfParkedVehicles == 0) {
            std::cout << "Closing Parking" << std::endl; 
            flag = true;
        }
        else {
            char selection;
            std::cout << "This will Remove and tow all remaining vehicles from the parking!" << std::endl;
            std::cout << "Are you sure? (Y)es/(N)o: ";
            do{
                std::cin >> selection;
                if(selection == 'y' || selection == 'Y'){
                    std::cout << "Closing Parking" << std::endl;
                    for (int i = 0; i < this->m_noOfParkedVehicles + this->m_noOfSpots; ++i) {
                        if (this->m_parkingSpots[i] != nullptr) {
                            std::cout << std::endl << "Towing request" << std::endl;
                            std::cout << "*********************" << std::endl;
                            this->m_parkingSpots[i]->setCsv(false);
                            this->m_parkingSpots[i]->write(std::cout);

                            delete this->m_parkingSpots[i];
                            this->m_parkingSpots[i] = nullptr;
                            this->m_noOfSpots += 1;
                            this->m_noOfParkedVehicles -= 1;
                        }
                    }
                    flag = true;
                }
                else if(selection == 'n' || selection == 'N'){
                    flag = false;
                }
                else{
                    std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
                }
            }while(selection != 'y' && selection != 'Y' && selection != 'n' && selection != 'N');
        }
        return flag;
    }

    bool Parking::exitParking()
    {
        char selection;
        bool flag = false;
        std::cout << "This will terminate the program!" << std::endl;
        std::cout << "Are you sure? (Y)es/(N)o: ";
        do{
            std::cin >> selection;
            if(selection == 'y' || selection == 'Y'){
            std::cout << "Exiting program!" << std::endl;
                flag = true;
            }
            else if(selection == 'n' || selection == 'N'){
                flag = false;
            }
            else{
                std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
            }
        }while(selection != 'y' && selection != 'Y' && selection != 'n' &&  selection != 'N');
        return flag;
    }

    bool Parking::loadData()
    {
        bool flag = false;
        if (!isEmpty()) {
            flag = true;

            std::ifstream file(this->m_filename);

            bool vehicleSet = false;
            int ch;
            Vehicle *v = nullptr;
            while (!file.eof() && this->m_noOfSpots > 0) {
                ch = file.get();
                file.ignore();
                if (ch == 'M') {
                    v = new Motorcycle();
                    vehicleSet = true;
                } else if (ch == 'C') {
                    v = new Car();
                    vehicleSet = true;
                } else
                    break;

                if (vehicleSet) {
                    v->setCsv(true);
                    v->read(file);
                    if (file.fail()) {
                        flag = false;
                        break;
                    }
                    else {
                        if (this->m_parkingSpots[v->getParkingSpot() - 1] == nullptr) {
                            this->m_parkingSpots[v->getParkingSpot() - 1] = v;
                            this->m_noOfParkedVehicles += 1;
                            this->m_noOfSpots -= 1;
                        }
                        v = nullptr;
                    }
                }
            }

            file.close();
        }
        return flag;
    }

    void Parking::saveData()
    {
        if (!isEmpty()) {
            std::ofstream file(this->m_filename);

            if (file) {
                for (int i = 0; i < this->m_noOfParkedVehicles + this->m_noOfSpots; ++i) {
                    if (this->m_parkingSpots[i] != nullptr) {
                        this->m_parkingSpots[i]->setCsv(true);
                        this->m_parkingSpots[i]->write(file);
                    }
                }
            }
            file.close();
        }
    }

    Parking::Parking(const char *filename,int noOfSpots)
    {
        if (filename == nullptr || *filename == '\0') {
            std::cout << "Error in data file" << std::endl;
            this->m_filename = nullptr;
            for(int i= 0;i< maxSpots;i++){
                m_parkingSpots[i] = nullptr;
            }
        }
        else if(noOfSpots < 10 || noOfSpots > maxSpots){
            if (this->m_filename != nullptr){
            delete[] m_filename;}
            this->m_filename = nullptr;
            for(int i= 0;i< maxSpots;i++){
                m_parkingSpots[i] = nullptr;
            }
        }   
        else {
            this->m_filename = new char[strlen(filename) + 1];
            strcpy(this->m_filename, filename);
            m_filename[strlen(filename)] = '\0'; 
            this->m_noOfSpots = noOfSpots;
            if (this->loadData()) {
                this->m_parkingMenu = "Parking Menu, select an action:";
                m_parkingMenu << "Park Vehicle" << "Return Vehicle" << "List Parked Vehicles" << "Find Vehicle" << "Close Parking (End of day)" << "Exit Program";

                this->m_vehicleSelectionMenu = "Select type of the vehicle:";
                this->m_vehicleSelectionMenu << "Car" << "Motorcycle" << "Cancel";
                this->m_vehicleSelectionMenu.setIndentation(1);
            }
            else {
                std::cout << "Error in data file" << std::endl;
                if (this->m_filename != nullptr)
                    delete[] m_filename;
                this->m_filename = nullptr;
                for(int i= 0;i< maxSpots;i++){
                m_parkingSpots[i] = nullptr;
            }
            }   
        }
    }

    Parking::~Parking()
    {
        this->saveData();
	if (this->m_filename != nullptr)
		delete[] m_filename;
        for (int i = 0; i < this->m_noOfParkedVehicles + this->m_noOfSpots; ++i) {
            if (this->m_parkingSpots[i] != nullptr)
                delete this->m_parkingSpots[i];
        }
    }

    int Parking::run()
    {
        if (!this->isEmpty()) {
            int selection = 0;

            do {
                this->parkingStatus();
                selection = m_parkingMenu.run();

                switch (selection) {
                    case 1 : this->parkVehicle();   break; 
                    case 2 : this->returnVehicle(); break; 
                    case 3 : this->listVehicles();  break; 
                    case 4 : this->findVehicle();   break; 
                    case 5 : if (this->closeParking()) selection = -1; break;
                    case 6 : if (this->exitParking())  selection = -1; break;
                    default : break;
                }

            } while (selection != -1);
        }
        return this->isEmpty();
    }



}
