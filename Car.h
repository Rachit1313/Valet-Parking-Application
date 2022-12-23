#ifndef _CAR_H
#define _CAR_H
#include "Vehicle.h"
namespace sdds{
    class Car : public Vehicle{
        bool m_carWash;
        public:
        Car();
        Car(const char* license,const char* makemodel);
        Car(const Car& obj);
        Car& operator=(const Car& obj);
        ~Car();
        std::ostream& writeType(std::ostream& ostr)const;
        std::ostream& write(std::ostream& ostr)const;
        std::istream& read(std::istream& istr);

    };
}
#endif