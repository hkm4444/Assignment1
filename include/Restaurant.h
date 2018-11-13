#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"


class Restaurant{
public:
    Restaurant();
    Restaurant(const std::string &configFilePath);
    void start();
    int getNumOfTables() const;
    Table* getTable(int ind);
    const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Dish>& getMenu();

    virtual ~Restaurant();
    Restaurant(const Restaurant &other);
    Restaurant(const Restaurant &&other);
    Restaurant& operator=(const Restaurant &other);
    Restaurant& operator=(const Restaurant &&other);
    std::vector<Table*>& getTables();                   // Returns a reference to a vector which contains pointers to objects of type Table


private:
    bool open;
    int numOfTables;        // Is needed ??
    double totalBill;       // Is needed ??
    std::vector<Table*> tables;
    std::vector<Dish> menu;
    std::vector<BaseAction*> actionsLog;
    std::vector<std::string> actionslist;
    DishType convert(const std::string &str);
};

#endif