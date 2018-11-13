//
// Created by deanta@wincs.cs.bgu.ac.il on 11/9/18.
//
#include <iostream>
#include "../include/Customer.h"
#include <string>
#include <Customer.h>

/** Customer class*/
Customer::Customer(std::string c_name, int c_id):name(c_name),id(c_id), orderNumber(0),str() {      // orderNumber should be a counter and NOT get just 0 value ???
    std:: vector<int> order;
    std:: string toString();
}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}



/** VegetarianCustomer class*/
VegetarianCustomer::VegetarianCustomer(std::string name, int id) : Customer(name,id) {}

std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu) {

    std::vector<int> orderList;
    std::string orderName;
    int i=0;

    /**find the first veg dish in the menu*/
    while(i<menu.size()) {

        if (menu[i].getType() == VEG) {
            orderList.push_back(menu[i].getId());
            orderName=menu[i].getName();
            i = menu.size();
            str = str + this->getName() + " ordered " + orderName + "/n";
            }
        i++;
    }

    /**find the expensive beverage dish in the menu*/
    int idOfTheExpBvG = -1;
    for(int j=0;j<menu.size();j++){
        if(menu[i].getType()==BVG) {
            if (idOfTheExpBvG == -1)
                idOfTheExpBvG = i;
            else if(menu[i].getPrice()>menu[idOfTheExpBvG].getPrice())
                idOfTheExpBvG = i;
        }
    }
    if(idOfTheExpBvG != -1){
        orderList.push_back(idOfTheExpBvG);
        orderName = menu[idOfTheExpBvG].getName();
        str = str + this->getName() + " ordered " + orderName + "/n";
    }

    this->orderNumber++;
    return orderList;
}

std::string VegetarianCustomer::toString() const {
    return str;
}

/** CheapCustomer class*/
CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {}


std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu) {

    std::vector<int> orderList;
    std::string orderName;
    int idOfTheChpDish = -1;

    if(this->orderNumber==1)
        return orderList;

/**find the cheapest dish in the menu*/
    for(int i=0;i<menu.size();i++){
        if(idOfTheChpDish == -1)
            idOfTheChpDish = i;
        else if(menu[i].getPrice()<menu[idOfTheChpDish].getPrice())
            idOfTheChpDish = i;
    }

    if(idOfTheChpDish != -1){
        orderList.push_back(idOfTheChpDish);
        orderName = menu[idOfTheChpDish].getName();
        str = str + this->getName() + " ordered " + orderName + "/n";
    }
    this->orderNumber++;
    return orderList;
}

std::string CheapCustomer::toString() const {
    return str;
}



/** SpicyCustomer class*/
SpicyCustomer::SpicyCustomer(std::string name, int id) : Customer(name, id) {}


std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu) {

    std::vector<int> orderList;
    std::string orderName;
    int idOfTheSpcDish = -1;
    int idOfTheChpBvg = -1;

    /**find the most expensive spicy dish in the menu*/
    if(this->orderNumber == 0) {
        for (int i = 0; i < menu.size(); i++) {
            if (menu[i].getType() == SPC)
                if (idOfTheSpcDish == -1)
                    idOfTheSpcDish = i;
                else if (menu[i].getPrice() > menu[idOfTheSpcDish].getPrice())
                    idOfTheSpcDish = i;
        }
    }
    if (idOfTheSpcDish == -1){
        orderList.push_back(idOfTheSpcDish);
        orderName = menu[idOfTheSpcDish].getName();
        str = str + this->getName() + " ordered " + orderName + "/n";
        this->orderNumber++;
        return orderList;
    }

    /**find the cheapest non-alcoholic beverage in the menu*/
    for(int i=0;i<menu.size();i++){
        if(menu[i].getType()==BVG)
            if(idOfTheChpBvg == -1)
                idOfTheChpBvg = i;
            else if(menu[i].getPrice()<menu[idOfTheChpBvg].getPrice())
                idOfTheChpBvg = i;
    }
    if (idOfTheChpBvg == -1){
        orderList.push_back(idOfTheChpBvg);
        orderName = menu[idOfTheChpBvg].getName();
        str = str + this->getName() + " ordered " + orderName + "/n";
        this->orderNumber++;
        return orderList;
    }

    return orderList;
}

std::string SpicyCustomer::toString() const {
    return str;
}



/** AlchoholicCustomer class*/
AlchoholicCustomer::AlchoholicCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu) {

    std::vector<int> orderList;
    std::vector<Dish> alcoholMenu;
    std::string orderName;


    /**find all the alcoholic beverages in the menu*/
    for(int i=0;i<menu.size();i++)
        if(menu[i].getType()==ALC)
            alcoholMenu.push_back(menu[i]);

    /**sort the alcoholic beverages in the alcohol menu*/
    for(int i=0;i<alcoholMenu.size();i++)
        for(int j=0;j<alcoholMenu.size();j++)
            if(alcoholMenu[i].getPrice()>alcoholMenu[j].getPrice())
                std::swap(alcoholMenu[i],alcoholMenu[j]);

    /**find the next alcoholic beverage in the menu*/
    if(alcoholMenu.size() > orderNumber){
        orderList.push_back(alcoholMenu[orderNumber].getId());
        orderName = alcoholMenu[orderNumber].getName();
        str = str + this->getName() + " ordered " + orderName + "/n";
        this->orderNumber++;
        return orderList;
    }

    return orderList;
}

std::string AlchoholicCustomer::toString() const {
    return str;
}























