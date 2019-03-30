#ifndef RESTAURANT_H
#define RESTAURANT_H

const int MAX_RESTUARANT = 1000;

#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <cstring>

class Restaurant
{
public:
    struct RestaurantContainer{
        std::string name;
        int place;
        int type;
        int budget;
        std::string address;
        int index;
    };
    static Restaurant::RestaurantContainer* RestaurantList;
    static const int TYPE_OPTIONS_NUM = 14;
    static const int BUDGET_OPTIONS_NUM = 4;
    static const int PLACE_OPTIONS_NUM = 6;
    static std::string getNameByIndex(int index);
    static Restaurant::RestaurantContainer getInfoByIndex(int index);
    static int findAvailable(bool type[] , bool budget[] , bool place[]);
    static void load_Csv(char filename[]);
	static int currentIndex;
    ~Restaurant();
private:

    static int restaurantCnt;
    static int randomInt(int countAvailable);
};

#endif // RESTAURANT_H
