//
// Created by deanta@wincs.cs.bgu.ac.il on 11/9/18.
//


#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    ifstream file("config1.txt");
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
            cout << stoi(substr);
            //tables.push_back(new Table(stoi(substr)));
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

            cout << name << " " << price << " " << type;
            //menu.push_back(Dish(i,name,price,convert(type))); /// check if the type is good for the class dish
            i++;
        }
    }
}