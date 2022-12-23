#include <iostream>
#include <cstring>
#include "Vehicle.h"
namespace sdds
{
    Vehicle::Vehicle()
    {
        this->m_licensePlate[0] = 0;
        this->m_makeModel = nullptr;
        this->m_spotNum = -1;
    }
    Vehicle::Vehicle(const char *license, const char *makemodel)
    {
        if (license != nullptr && makemodel != nullptr && strlen(license) <= 8 && strlen(makemodel) >= 2)
        {
            strcpy(this->m_licensePlate, license);
            if(this->m_makeModel != nullptr){
                delete[] this->m_makeModel;
                this->m_makeModel = nullptr;
            }
            this->m_makeModel = new char[strlen(makemodel) + 1];
            this->hadModel = true;
            strcpy(this->m_makeModel, makemodel);
            *(this->m_makeModel + strlen(makemodel)) = '\0';
            this->m_spotNum = 0;
        }
        else
        {
            setEmpty();
        }
    }
    Vehicle::Vehicle(const Vehicle& obj)
    {
        *this = obj;
    }

    Vehicle& Vehicle::operator=(const Vehicle& obj){
        if(obj.m_makeModel != nullptr && obj.m_licensePlate[0] != '\0'){ 
            strcpy(this->m_licensePlate,obj.m_licensePlate);
            if (this->m_makeModel != nullptr) {
                delete[] this->m_makeModel;
                this->m_makeModel = nullptr;
            }
            this->m_makeModel = new char[strlen(obj.m_makeModel)+1];
            this->hadModel = true;
            strcpy(this->m_makeModel,obj.m_makeModel);
            this->m_spotNum = obj.m_spotNum;
        }
        else{
            setEmpty();
        }
        return *this;
    }
    void Vehicle::setEmpty(){
        if(this->m_makeModel != nullptr && this->m_makeModel[0] != '\0'){
            delete[] this->m_makeModel;
            this->m_makeModel = nullptr;
        }
        this->m_licensePlate[0] = '\0';
        this->m_spotNum = 0;
    }
    bool Vehicle::isEmpty()const{
        return this->m_makeModel == nullptr || this->m_licensePlate[0] == '\0';
    }
    const char* Vehicle::getLicensePlate()const{
        return this->m_licensePlate;
    }
    const char* Vehicle::getMakeModel()const{
        return this->m_makeModel;
    }
    void Vehicle::setMakeModel(const char* makemodel){
        if(makemodel != nullptr && strlen(makemodel) >= 2){
            if(this->m_makeModel != nullptr){
                delete[] this->m_makeModel;
                this->m_makeModel = nullptr;
            }
            this->m_makeModel = new char[strlen(makemodel)+1];
            this->hadModel = true;
            strcpy(this->m_makeModel,makemodel);
        }
        else{
            setEmpty();
        }
    }
    void Vehicle::setParkingSpot(int value){
        if(value >= 0){
            this->m_spotNum = value;
        }
        else{
            setEmpty();
        }
    }
    int Vehicle::getParkingSpot() const
    {
        return this->m_spotNum;
    }

    bool Vehicle::operator==(const char* license){
        return strcasecmp(getLicensePlate(),license) == 0;
    }
	bool Vehicle::operator==(const Vehicle& obj){
        return strcasecmp(this->m_licensePlate,obj.m_licensePlate) == 0;
    }
    std::istream& Vehicle::read(std::istream& istr){
        setEmpty();
        if(isCsv()){
            istr >> m_spotNum;
            istr.ignore();
			istr.getline(this->m_licensePlate, 8, ',');
			for (int i = 0; i < (int) strlen(this->m_licensePlate); i++) {
				this->m_licensePlate[i] = toupper(this->m_licensePlate[i]);
			}
            char tempMakeModel[60];
            int i = 0;
            char c = 0;
            while ((c = (char)istr.get()) != ',') {
                tempMakeModel[i++] = c;
            }
            tempMakeModel[i] = '\0';
            if (this->m_makeModel != nullptr) {
                delete[] this->m_makeModel;
                this->m_makeModel = nullptr;
            }
			this->m_makeModel = new char[strlen(tempMakeModel) + 1];
            this->hadModel = true;
			strcpy(this->m_makeModel, tempMakeModel);
            this->m_makeModel[strlen(tempMakeModel)] = '\0';
        }
        else{
            std::cout << "Enter License Plate Number: ";
			std::string temp;
			std::getline(istr, temp, '\n');
			while (temp.length() > 8) {
				std::cout << "Invalid License Plate, try again: ";
				istr >> temp;
			}
			strcpy(this->m_licensePlate, temp.c_str());
			for (int i = 0; i < (int) strlen(this->m_licensePlate); i++) {
                this->m_licensePlate[i] = toupper(this->m_licensePlate[i]);
			}
			std::cout << "Enter Make and Model: ";
			std::getline(istr, temp, '\n');
			while (temp.length() > 60 || temp.length() < 2) {
				std::cout << "Invalid Make and model, try again: ";
				istr >> temp;
			}
            if (this->m_makeModel != nullptr) {
                delete[] this->m_makeModel;
                this->m_makeModel = nullptr;

            }
			this->m_makeModel = new char[temp.length() + 1];
            this->hadModel = true;
			strcpy(this->m_makeModel, temp.c_str());
		}
		if (istr.fail()) 
			setEmpty();
		return istr;
        }
        std::ostream& Vehicle::write(std::ostream& ostr)const{
            if(isEmpty()){
                ostr << "Invalid Vehicle Object" << std::endl;
            }
            else{
                writeType(ostr);
                if(isCsv()){
    			ostr << this->m_spotNum << "," << this->m_licensePlate << "," << this->m_makeModel << ",";
                }
                else{
                ostr << "Parking Spot Number: ";
				if (this->m_spotNum == 0) {
					ostr << "N/A" << std::endl;
				}
				else {
					ostr << this->m_spotNum << std::endl;
				}
				ostr << "License Plate: " << this->m_licensePlate << std::endl;
				ostr << "Make and Model: " << this->m_makeModel << std::endl;
                }
            }
            return ostr;
        }
        Vehicle::~Vehicle(){
            this->setEmpty();
        }
}