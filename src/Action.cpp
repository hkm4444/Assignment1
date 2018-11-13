//
// Created by ahikame@wincs.cs.bgu.ac.il on 11/10/18.
//

#include <Action.h>
#include "../include/Restaurant.h"
#include "../include/Action.h"
#include <string>;

BaseAction::BaseAction():errorMsg(),status(PENDING) {}

/** BaseAction class*/
ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status=COMPLETED;
}

void BaseAction::error(std::string errorMsg) {
    status=ERROR;
    this->errorMsg=errorMsg;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}


/** OpenTable class*/
OpenTable::OpenTable(int id, std::vector<Customer *> &customersList):tableId(id),customers(customersList) {}


void OpenTable::act(Restaurant &restaurant) {

    if(restaurant.getTable(tableId)== nullptr||restaurant.getTable(tableId)->isOpen())
        this->error("Table does not exist or is already open");

    for(int i=0;i<customers.size();i++)
        if(restaurant.getTable(tableId)->getCapacity()>0)
            restaurant.getTable(tableId)->addCustomer(customers[i]);

    restaurant.getTable(tableId)->openTable();
    this->complete();

}
/////// Need to be finished ////////
std::string OpenTable::toString() const {
    return std::__cxx11::string();
}

/** Order class*/
Order::Order(int id):tableId(id) {}

void Order::act(Restaurant &restaurant) {

    if(restaurant.getTable(tableId)== nullptr||restaurant.getTable(tableId)->isOpen()==false)
        this->error("Table does not exist or is not open");


    for(int i=0;i<restaurant.getTable(tableId)->getCustomers().size();i++) {

        std::vector <int> temp = restaurant.getTable(tableId)->getCustomers()[i]->order(restaurant.getMenu());
        for(int j=0;j<temp.size();j++) {
            restaurant.getTable(tableId)->addOrder(i,j,restaurant.getMenu());
            str = str + restaurant.getTable(tableId)->getCustomers()[i]->toString() + "/n";
        }
    }
    this->complete();
}


std::string Order::toString() const {
    return str;
}


/** MoveCustomer class*/
MoveCustomer::MoveCustomer(int src, int dst, int customerId):srcTable(src), dstTable(dst), id(customerId) {}

void MoveCustomer::act(Restaurant &restaurant) {

    /** Check for errors */
    if(srcTable>restaurant.getNumOfTables() || srcTable<0 ||                // If src table doesn't exist
       dstTable>restaurant.getNumOfTables() || dstTable<0 ||                // If dst table doesn't exist
       !restaurant.getTables()[srcTable]->isOpen() ||                       // If src table closed
       !restaurant.getTables()[dstTable]->isOpen() ||                       // If dst table closed
       restaurant.getTable(srcTable)->getCustomer(id) == nullptr ||         // If there is no customer with received id in the src table
       restaurant.getTable(dstTable)->getCustomers().size() == restaurant.getTable(dstTable)->getCapacity()     // If there are no seats available
            )
        this->error("Cannot move customer");
    else {
        /** Adds customer from src table and removes from dst table */
        restaurant.getTable(dstTable)->addCustomer(restaurant.getTable(srcTable)->getCustomer(id));             // Add customer to dst table
        restaurant.getTable(srcTable)->removeCustomer(id);                                                      // Remove customer from dst table

        /** Moves customer's orders from src table to dst table */
        //std::vector<OrderPair> tmpOrderList;                                                                    // Create new temp vector to store the NON deleted dishes
        for (int i=0; i<restaurant.getTable(srcTable)->getOrders().size() ; i++) {
            if (restaurant.getTable(srcTable)->getOrders()[i].first == id){
                restaurant.getTable(dstTable)->addOrder(id, restaurant.getTable(srcTable)->getOrders()[i].second.getId(), restaurant.getMenu());        // Add order at dst table
                restaurant.getTable(srcTable)->getOrders().erase(restaurant.getTable(srcTable)->getOrders().begin()+i);                               // Remove order from src table
            }
        }


        /* Update original orderList from tmpOrderList
        restaurant.getTable(srcTable)->getOrders().clear();
        for (int i=0; i<tmpOrderList.size(); i++) {
            restaurant.getTable(srcTable)->getOrders().push_back(tmpOrderList[i]);
         }
         */

        /** If table is empty after moving customer --> close table */
        if (restaurant.getTable(srcTable)->getCapacity() == 0)
            restaurant.getTable(srcTable)->closeTable();
    }


}

std::string MoveCustomer::toString() const {
    return std::__cxx11::string();
}


/** Close class*/
Close::Close(int id):tableId(id) {}

void Close::act(Restaurant &restaurant) {

    int bill=0;

    if(restaurant.getTable(tableId)== nullptr||restaurant.getTable(tableId)->isOpen()==false)
        this->error("Table does not exist or is not open");

    for(int i=0;i<restaurant.getTable(tableId)->getOrders().size();i++)
    {
        bill = bill + restaurant.getTable(tableId)->getOrders()[i].second.getPrice();
    }

    auto tableIdS = std::to_string(tableId);
    auto billS = std::to_string(bill);

    /** delete the order list and the customer list*/
    for(int i=0;i<restaurant.getTable(tableId)->getCustomers().size();i++)
        delete(restaurant.getTable(tableId)->getCustomers()[i]);
    for(int i=0;i<restaurant.getTable(tableId)->getOrders().size();i++)
        restaurant.getTable(tableId)->getOrders().pop_back();

    str = "Table " + tableIdS + "was closed. Bill " + billS + "NIS";
    this->complete();
}

std::string Close::toString() const {
    return str;
}

/** CloseAll class*/
CloseAll::CloseAll() {}

void CloseAll::act(Restaurant &restaurant) {

    for(int i=0;i<restaurant.getTables().size();i++)
        if(restaurant.getTables()[i]->isOpen()) {
            Close toClose(i);
            toClose.act(restaurant);
            restaurant.getTables()[i]->closeTable();
            str = str + toClose.toString() + "/n";
        }
    this->complete();
}

std::string CloseAll::toString() const {
    return str;
}

/** PrintMenu class*/
PrintMenu::PrintMenu() {}

void PrintMenu::act(Restaurant &restaurant) {

    for (int i = 0; i < restaurant.getMenu().size(); i++) {

        /** convert dish type to string */
        std::string dishType;
        DishType temp = restaurant.getMenu()[i].getType();
        if (temp == VEG)
            dishType = "VEG";
        if (temp == ALC)
            dishType = "ALC";
        if (temp == BVG)
            dishType = "BVG";
        if (temp == SPC)
            dishType = "SPC";

        /** convert dish price to string */
        auto billS = std::to_string(restaurant.getMenu()[i].getPrice());
        str = str + restaurant.getMenu()[i].getName() + " " + dishType + " " + billS + +"NIS" + "/n";
    }
    this->complete();
}

std::string PrintMenu::toString() const {
    return str;
}

/** PrintTableStatus class*/
PrintTableStatus::PrintTableStatus(int id):tableId(id) {}

void PrintTableStatus::act(Restaurant &restaurant) {

    int currBill = 0;
    auto tableIdS = std::to_string(tableId);
    auto isOpenS = std::to_string(restaurant.getTables()[tableId]->isOpen());
    str = "Table " + tableIdS + " status: " + isOpenS + "/n";

    /** check if the table is open */
    if (restaurant.getTables()[tableId]->isOpen() & restaurant.getTables()[tableId]->getCustomers().size() != 0) {

        /** print customers list */
        str = str + "Customers: /n";
        for (int i = 0; i < restaurant.getTables()[tableId]->getCustomers().size(); i++) {
            auto customerIdS = std::to_string(i);
            str = str + customerIdS + restaurant.getTables()[tableId]->getCustomers()[i]->getName() + "/n";
        }

        /** print orders list */
        str = str + "Orders: /n";
        for (int i = 0; i < restaurant.getTables()[tableId]->getOrders().size(); i++) {

            currBill = currBill + restaurant.getTables()[tableId]->getOrders()[i].second.getPrice();
            auto dishPriceS = std::to_string(restaurant.getTables()[tableId]->getOrders()[i].second.getPrice());
            auto customerIdS = std::to_string(restaurant.getTables()[tableId]->getOrders()[i].first);
            str = str + restaurant.getTables()[tableId]->getOrders()[i].second.getName() + " " + dishPriceS + " " +
                  customerIdS + "/n";
        }

        /** print current bill list */
        auto currBillS = std::to_string(currBill);
        str = str + "Current bill: " + currBillS + "NIS" + "/n";
    }
}


std::string PrintTableStatus::toString() const {
    return str;
}


PrintActionsLog::PrintActionsLog() {

}

void PrintActionsLog::act(Restaurant &restaurant) {

}

std::string PrintActionsLog::toString() const {
    return std::__cxx11::string();
}

