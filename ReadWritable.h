#ifndef _READWRITABLE_H
#define _READWRITABLE_H
#include <iostream>
namespace sdds{
class ReadWritable{
    bool flag;
    public:
    ReadWritable();
    virtual ~ReadWritable();
    bool isCsv()const;
    void setCsv(bool value);
    virtual std::istream& read(std::istream& istr = std::cin) = 0;
    virtual std::ostream& write(std::ostream& ostr = std::cout)const = 0;
};
std::ostream& operator<<(std::ostream& ostr,const ReadWritable& obj);
std::istream& operator>>(std::istream& istr, ReadWritable& obj);
}
#endif