/*
 * Final Project Milestone 1
 * Filename: Menu.h
 * Author: Rachit Chawla
 * -----------------------------------------------------------
 *  I have done all the coding by myself and only copied the code 
 *  that my professor provided to complete my project milestones.
 *  -----------------------------------------------------------
 *  */
#ifndef _MENU_H
#define _MENU_H

namespace sdds{
const int MAX_NO_OF_ITEMS = 10;
class MenuItem{
    char m_menuItem[51];
    MenuItem(){};
    MenuItem(const char* str);
    MenuItem(const MenuItem &obj) = delete;
    MenuItem& operator=(const MenuItem &obj) = delete;
    void display()const;
    void setItem(const char* str);
    friend class Menu;
};
class Menu{
    char m_title[51];
    MenuItem menuItems[MAX_NO_OF_ITEMS];
    int noOfItems = 0;
    int indentation = 0;
public:
    Menu() {};
    void display()const;
    Menu(const char* str,int val = 0);
    Menu(const Menu &obj)=delete;
    Menu& operator=(const MenuItem &obj) = delete;
    operator bool()const;
    bool isEmpty()const;
    Menu& operator=(const char* str);
    void add(const char* str);
    void clear();
    Menu& operator<<(const char* str);
    int run() const;
    operator int()const;
    void setIndentation(int indentation) {
        this->indentation = indentation;
    }
};

}

#endif
