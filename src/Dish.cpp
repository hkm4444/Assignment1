//
// Created by deanta@wincs.cs.bgu.ac.il on 11/9/18.
//
#include <iostream>
#include <Dish.h>
#include  "../include/Dish.h"

Dish::Dish(int d_id, std::string d_name, int d_price, DishType d_type): id(d_id),name(d_name),price(d_price),type(d_type) {}

int Dish::getId() const {
    return id;
}

std::string Dish::getName() const {
    return name;
}

int Dish::getPrice() const {
    return price;
}

DishType Dish::getType() const {
    return type;
}

/**Rule Of Five*/

/** Destructor*/
Dish::~Dish() {
    delete this;
}
/** Copy Constructor*/
Dish::Dish(const Dish &other): id(other.id),name(other.name),type(other.type),price(other.price) {}


/** Move Constructor*/
Dish::Dish(const Dish &&other): id(other.id),name(other.name),type(other.type),price(other.price){}

/** Copy Assignment*/
Dish &Dish::operator=(const Dish &other){}

/** Move Assignment*/
Dish &Dish::operator=(const Dish &&other) {}
