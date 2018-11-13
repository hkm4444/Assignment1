//
// Created by deanta@wincs.cs.bgu.ac.il on 11/9/18.
//
#include <iostream>
#include <fstream>
#include "../include/Restaurant.h"
#include <sstream>
#include <string>
#include <Restaurant.h>

#include "Table.h"
#include "Dish.h"

Restaurant::Restaurant(): open(false), totalBill(0), numOfTables(0) {}

Restaurant::Restaurant(const std::string &configFilePath) {
    using namespace std;
    ifstream file(configFilePath);
        if (file.is_open()) {
            string str;

             /**get number of tables */
            getline(file, str);
            getline(file, str);
            int numOfTables = stoi(str);   /**convert string to int, int should be deleted*/

             /**insert the capacities of tables*/
            getline(file, str);
            getline(file, str);
            stringstream ss(str);
            while( ss.good() )
            {
                string substr;
                getline( ss, substr, ',' );
                tables.push_back(new Table(stoi(substr)));
            }

            /**insert the dishes to the menu*/
            getline(file, str);
            int i=0;
            while(file.good())
            {
                getline(file, str);
                stringstream ss(str);

                string name;                /**get dish name*/
                getline( ss, name, ',' );

                string type;                /**get dish type*/
                getline( ss,type, ',' );

                string priceS;               /**get dish price*/
                int price;
                getline( ss,priceS, ',' );
                price = stoi(priceS);

                menu.push_back(Dish(i,name,price,convert(type))); /// check if the type is good for the class dish
                i++;
            }
        }
    }

void Restaurant::start() {

    std:: string input;
    this->open = true;
    std::cout << "Restaurant is now open!";
    std::cin >>input;
    std::string firstWord = input.substr(0, input.find(" "));
    std::string secondWord;
    std::string ThirdWord;


    if(firstWord == "open" | firstWord == "order" | firstWord == "move" | firstWord=="close" | firstWord == "status"){
        secondWord = getline(input)


    }


    //actionsLog.push_back()



























}

int Restaurant::getNumOfTables() const {
    return this->numOfTables;
}

Table *Restaurant::getTable(int ind) {
    if(tables.size()<ind|ind<0)
        return nullptr;
    return *tables[ind];
}

const std::vector<BaseAction *> &Restaurant::getActionsLog() const {         /**should be completed*/
    return <#initializer#>;
}

std::vector <Dish> &Restaurant::getMenu() {
    return this->menu;
}

DishType Restaurant::convert(const std::string &str) {
    if (str == "VEG")
        return VEG;
    if (str == "SPC")
        return SPC;
    if (str == "BVG")
        return BVG;
    if (str == "ALC")
        return ALC;
}

/**Rule Of Five*/

/** Destructor*/
Restaurant:: ~ Restaurant(){

    for(int i=0;i<tables.size();i++)
        delete(tables[i]);

    for(int i=0;i<menu.size();i++)
        delete(menu[i]);

    for(int i=0;i<actionsLog.size();i++)
        delete(actionsLog[i]);
}

/** Copy Constructor*/
Restaurant::Restaurant(const Restaurant &other):open(other.open),numOfTables(other.numOfTables),totalBill(other.totalBill) {

    for(int i=0;i<other.tables.size();i++)
        tables.push_back(other.tables[i]);

    for(int i=0;i<other.menu.size();i++)
        menu.push_back(other.menu[i]);

    for(int i=0;i<other.actionsLog.size();i++)
        actionsLog.push_back(other.actionsLog[i]);
}


// Assignment operator must return a value and implement 4 rules as described in practical session 3    ??????????????????
/** Copy Assignment*/
Restaurant &Restaurant::operator=(const Restaurant &other) {

    /** delete this*/
    for(int i=0;i<tables.size();i++)
        delete(tables[i]);

    for(int i=0;i<menu.size();i++)
        delete(menu[i]);

    for(int i=0;i<actionsLog.size();i++)
        delete(actionsLog[i]);

    /** copy other to this*/
    this->open=other.open;
    this->numOfTables=other.numOfTables;
    this->totalBill=other.totalBill;

    for(int i=0;i<other.tables.size();i++)
        tables.push_back(other.tables[i]);

    for(int i=0;i<other.menu.size();i++)
        menu.push_back(other.menu[i]);

    for(int i=0;i<other.actionsLog.size();i++)
        actionsLog.push_back(other.actionsLog[i]);

    return *this;
}

/** Move Constructor*/
Restaurant::Restaurant(const Restaurant &&other) {

    /** copy other to this*/
    this->open=other.open;
    this->numOfTables=other.numOfTables;
    this->totalBill=other.totalBill;

    for(int i=0;i<other.tables.size();i++)
        tables.push_back(other.tables[i]);

    for(int i=0;i<other.menu.size();i++)
        menu.push_back(other.menu[i]);

    for(int i=0;i<other.actionsLog.size();i++)
        actionsLog.push_back(other.actionsLog[i]);

    /**delete pointers of other*/
    other.tables = nullptr;
    other.menu = nullptr;
    other.actionsLog = nullptr;
}


// Assignment operator must return a value and implement 4 rules as described in practical session 3    ??????????????????
/** Move Assignment*/
Restaurant &Restaurant::operator=(const Restaurant &&other) {

    /** delete this*/
    for(int i=0;i<tables.size();i++)
        delete(tables[i]);

    for(int i=0;i<menu.size();i++)
        delete(menu[i]);

    for(int i=0;i<actionsLog.size();i++)
        delete(actionsLog[i]);

    /** copy other to this*/
    this->open=other.open;
    this->numOfTables=other.numOfTables;
    this->totalBill=other.totalBill;

    for(int i=0;i<other.tables.size();i++)
        tables.push_back(other.tables[i]);

    for(int i=0;i<other.menu.size();i++)
        menu.push_back(other.menu[i]);

    for(int i=0;i<other.actionsLog.size();i++)
        actionsLog.push_back(other.actionsLog[i]);

    /**delete pointers of other*/
    other.tables = nullptr;
    other.menu = nullptr;
    other.actionsLog = nullptr;

    return *this;
}

std::vector<Table *> &Restaurant::getTables() {
    return this->tables;
}







