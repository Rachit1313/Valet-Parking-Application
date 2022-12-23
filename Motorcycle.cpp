#include <iostream>
#include "Motorcycle.h"
namespace sdds{
    Motorcycle::Motorcycle():Vehicle(){
        this->m_hasSideCar = false;
    }
    Motorcycle::Motorcycle(const char* license,const char* makemodel): Vehicle(license,makemodel){
        this->m_hasSideCar = false;
    }
    Motorcycle::Motorcycle(const Motorcycle& obj){
        *this = obj;
    }
    Motorcycle& Motorcycle::operator=(const Motorcycle& obj){
        Vehicle::operator=(obj);
        this->m_hasSideCar = obj.m_hasSideCar;
        Vehicle::setCsv(obj.isCsv());
        return *this;
    }
    Motorcycle::~Motorcycle(){
    }
    std::ostream& Motorcycle::writeType(std::ostream& ostr)const{
        if(Vehicle::isCsv()){
            ostr << "M,";
        }
        else{
            ostr << "Vehicle type: Motorcycle" << std::endl;
        }
        return ostr;
    }
    std::ostream& Motorcycle::write(std::ostream& ostr)const{
        if(Vehicle::isEmpty()){
            ostr << "Invalid Motorcycle Object" << std::endl;
        }
        else
        {
            Vehicle::write(ostr);
            if(Vehicle::isCsv()){
                ostr << this->m_hasSideCar << std::endl;
            }
            else{
                if(this->m_hasSideCar == true){
                    ostr << "With Sidecar" << std::endl;
                }
            }
        }
        return ostr;
    }
    std::istream& Motorcycle::read(std::istream& istr){
        if(Vehicle::isCsv()){
            Vehicle::read(istr);
            istr >> this->m_hasSideCar;
            istr.ignore(1000,'\n');
        }
        else{
            std::string flag;
            std::cout << std::endl << "Motorcycle information entry" << std::endl;
            Vehicle::read(istr);
            std::cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
            istr >> flag;
            while (flag != "Y" && flag != "y" && flag != "N" && flag != "n") {
				std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				istr >> flag;
			}
            if(flag == "n" || flag == "N"){
                this->m_hasSideCar = false;
            }
            else{
                this->m_hasSideCar = true;
            }           
        }
        return istr;
    }
}
