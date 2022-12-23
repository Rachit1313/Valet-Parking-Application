#include "ReadWritable.h"
#include <iostream>
namespace sdds{
ReadWritable::ReadWritable(){
    this->flag = false;
}
bool ReadWritable::isCsv()const{
    return this->flag;
}
void ReadWritable::setCsv(bool value){
    this->flag = value;
}
ReadWritable::~ReadWritable(){
}
std::ostream& operator<<(std::ostream& ostr,const ReadWritable& obj) {
    obj.write(ostr);
    return ostr;
}
std::istream& operator>>(std::istream& istr, ReadWritable& obj){
    obj.read(istr);
    return istr;
}
}