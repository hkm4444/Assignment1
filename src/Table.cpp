#include "../include/Table.h"
#include <iterator>
#include <iostream>
#include <Table.h>


Table::Table(int t_capacity) {
    capacity = t_capacity;
    open = false;
}

int Table::getCapacity() const {
    return capacity;
}

void Table::addCustomer(Customer *customer) {
    customersList.push_back(customer);
    capacity--;
}

void Table::removeCustomer(int id) {
    for (int i=0; i<customersList.size(); i++) {
        if (customersList[i]->getId() == id) {
            customersList.erase(customersList.begin() + i - 1);
            capacity++;
        }

    }
}

Customer *Table::getCustomer(int id) {
    for (int i=0; i<customersList.size(); i++) {
        if (customersList[i]->getId() == id)
            return customersList[i];
    }
    return nullptr;
}

std::vector<Customer *> &Table::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Table::getOrders() {
    return orderList;
}

void Table::addOrder(int costemerId,int dishId, const std::vector<Dish> &menu) {

    orderList.push_back(OrderPair(costemerId,menu[dishId]));


}

/////// Need to be finished ////////
void Table::order(const std::vector<Dish> &menu) {

}


void Table::openTable() {
    this->open = true;
}

void Table::closeTable() {
    this->open = false;

}

int Table::getBill() {
    int i(0), totalBill(0);
    while (i < orderList.size()) {
        totalBill = totalBill + orderList[i].second.getPrice();
        i++;
    }

    return totalBill;
}

bool Table::isOpen() {
    return open;
}