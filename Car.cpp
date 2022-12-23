#include <iostream>
#include "Car.h"
namespace sdds{
    Car::Car():Vehicle(){
        this->m_carWash = false;
    }
    Car::Car(const char* license,const char* makemodel): Vehicle(license,makemodel){
        this->m_carWash = false;
    }
    Car::Car(const Car& obj){
        *this = obj;
    }
    Car& Car::operator=(const Car& obj){
        Vehicle::operator=(obj);
        this->m_carWash = obj.m_carWash;
        Vehicle::setCsv(obj.isCsv());
        return *this;
    }
    Car::~Car(){
    }
    std::ostream& Car::writeType(std::ostream& ostr)const{
        if(Vehicle::isCsv()){
            ostr << "C,";
        }
        else{
            ostr << "Vehicle type: Car" << std::endl;
        }
        return ostr;
    }
    std::ostream& Car::write(std::ostream& ostr)const{
        if(Vehicle::isEmpty()){
            ostr << "Invalid Car Object" << std::endl;
        }
        else
        {
            Vehicle::write(ostr);
            if(Vehicle::isCsv()){
                ostr << this->m_carWash << std::endl;
            }
            else{
                if(this->m_carWash == true){
                    ostr << "With Carwash" << std::endl;
                }
                else{
                    ostr << "Without Carwash" << std::endl;
                }
            }
        }
        return ostr;
    }
    std::istream& Car::read(std::istream& istr){
        if(Vehicle::isCsv()){
            Vehicle::read(istr);
            istr >> this->m_carWash;
            istr.ignore(1000,'\n');
        }
        else{
            std::string flag;
            std::cout << std::endl << "Car information entry" << std::endl;
            Vehicle::read(istr);
            std::cout << "Carwash while parked? (Y)es/(N)o: ";
            istr >> flag;
            while (flag != "Y" && flag != "y" && flag != "N" && flag != "n") {
				std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				istr >> flag;
			}
            if(flag == "n" || flag == "N"){
                this->m_carWash = false;
            }
            else{
                this->m_carWash = true;
            }           
        }
        return istr;
    }
}
