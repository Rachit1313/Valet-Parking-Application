#ifndef _MOTORCYCLE_H
#define _MOTORCYCLE_H
#include "Vehicle.h"
namespace sdds{
class Motorcycle: public Vehicle{
    bool m_hasSideCar;
    public:
    Motorcycle();
    Motorcycle(const char* license,const char* makemodel);
    Motorcycle(const Motorcycle& obj);
    Motorcycle& operator=(const Motorcycle& obj);
    ~Motorcycle();
    std::ostream& writeType(std::ostream& ostr)const;
    std::ostream& write(std::ostream& ostr)const;
    std::istream& read(std::istream& istr);
};
}
#endif