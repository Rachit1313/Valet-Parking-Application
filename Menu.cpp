/*
Final Project Milestone 1
Filename: Menu.cpp
Author: Rachit Chawla
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#include <iostream>
#include <cstring>
#include "Menu.h"

namespace sdds
{
    MenuItem::MenuItem(const char *str)
    {
        if (str == nullptr)
        {
            this->m_menuItem[0] = '\0';
        }
        else
        {
            strncpy(this->m_menuItem, str, 51);
        }
    }
    void MenuItem::display() const
    {
        if (this->m_menuItem[0] != '\0')
        {
            std::cout << this->m_menuItem << std::endl;
        }
    }
    void Menu::display() const
    {
        if (*this && this->noOfItems > 0)
        {
            if(indentation != 0){
            std::cout.width(indentation * 4);
            std::cout << " ";
            }
            std::cout << m_title << std::endl;
            for (int i = 0; i < MAX_NO_OF_ITEMS && i < this->noOfItems; i++)
            {
                if(indentation != 0){
                std::cout.width(indentation * 4);
                std::cout << " ";
                }
                std::cout << i + 1 << "- ";
                menuItems[i].display();
            }
            if(indentation != 0){
            std::cout.width(indentation * 4);
            std::cout << " ";
            }
            std::cout << "> ";
        }
        else if (this->m_title[0] == '\0')
        {
            std::cout << "Invalid Menu!" << std::endl;
        }
        else if (this->noOfItems == 0)
        {
            if(indentation != 0){
            std::cout.width(indentation * 4);
            std::cout << " ";
            }
            std::cout << m_title << std::endl;
            std::cout << "No Items to display!" << std::endl;
        }
    }

    Menu::Menu(const char *str, int val)
    {
        if (str == nullptr)
        {
            this->m_title[0] = '\0';
        }
        else
        {
            strncpy(this->m_title, str, 51);
        }
        this->indentation = val;
    }
    Menu::operator bool() const
    {
        return this->m_title[0] != '\0';
    }
    bool Menu::isEmpty() const
    {
        return !(*this);
    }
    Menu& Menu::operator=(const char *str)
    {
        if (str == nullptr)
        {
            this->m_title[0] = '\0';
        }
        else
        {
            strncpy(this->m_title, str, 51);
        }
        return *this;
    }
    void MenuItem::setItem(const char *str)
    {
        if (str == nullptr) {
            this->m_menuItem[0] = '\0';
        }
        else {
            strncpy(this->m_menuItem, str, 51);
        }
    }
    void Menu::add(const char *str)
    {
        if (str == nullptr)
        {
            this->m_title[0] = '\0';
        }
        else if (*this && this->noOfItems < MAX_NO_OF_ITEMS)
        {
            this->menuItems[this->noOfItems++].setItem(str);
        }
    }
    void Menu::clear()
    {
        this->m_title[0] = '\0';
        for (int i = 0; i < noOfItems; i++)
        {
            menuItems[i].setItem(nullptr);
        }
        this->noOfItems = 0;
    }
    Menu &Menu::operator<<(const char *str)
    {
        add(str);
        return *this;
    }
    int Menu::run() const
    {
        int input = -1;
        this->display();
        if (this->noOfItems == 0 || this->isEmpty())
        {
            input = 0;
        }
        else
        {
            while(input == -1){
            std::cin >> input;
            if (std::cin.fail())
            {
                std::cout << "Invalid Integer, try again: ";
                std::cin.clear();
                std::cin.ignore(1024, '\n');
                input = -1;
            }
            else if (input > this->noOfItems || input < 1)
            {
                std::cout << "Invalid selection, try again: ";
                input = -1;
            }
            }
        std::cin.ignore(256, '\n');
        }
        return input;
    }
    Menu::operator int()const{
        return this->run();
    }
}
