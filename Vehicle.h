#ifndef _VEHICLE_H
#define _VEHICLE_H
#include <iostream>
#include "ReadWritable.h"
#include <cstring>
namespace sdds{
    class Vehicle: public ReadWritable
    {
        protected:
        char m_licensePlate[9];
        char* m_makeModel {nullptr};
        int m_spotNum;
        bool hadModel = false;
        void setEmpty();
        bool isEmpty()const;
        const char* getMakeModel()const;
        void setMakeModel(const char* makemodel);
        public:
        Vehicle();
        Vehicle(const char* license, const char* makemodel);
        Vehicle(const Vehicle& obj);
        const char* getLicensePlate()const;
        Vehicle& operator=(const Vehicle& obj);
        void setParkingSpot(int value);
        int getParkingSpot() const;
        bool operator==(const char* license);
		bool operator==(const Vehicle& obj);
        std::ostream& write(std::ostream& ostr)const;
		virtual std::ostream& writeType(std::ostream& ostr)const = 0;
		std::istream& read(std::istream& istr);
        virtual ~Vehicle();
    };
}

#endif