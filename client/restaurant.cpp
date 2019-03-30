#include <restaurant.h>

#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <cstring>

Restaurant::RestaurantContainer* Restaurant::RestaurantList = new RestaurantContainer[MAX_RESTUARANT];
int Restaurant::restaurantCnt = 0;
int Restaurant::currentIndex = 0;

Restaurant::~Restaurant(){
    delete [] Restaurant::RestaurantList;
}

std::string Restaurant::getNameByIndex(int index){
    return Restaurant::RestaurantList[index].name;
}

Restaurant::RestaurantContainer Restaurant::getInfoByIndex(int index){
    return Restaurant::RestaurantList[index];
}

int Restaurant::findAvailable(bool type[] , bool budget[] , bool place[]){
    int countAvailable = 0;
    int available[MAX_RESTUARANT] = {0};

    for(int i = 0; i < restaurantCnt; i++){
        if( type[RestaurantList[i].type]
                && budget[RestaurantList[i].budget]
                && place[RestaurantList[i].place] ){
            available[countAvailable] = i;
            countAvailable++;
        }
    }

    if(countAvailable == 0){
        return -1;
    }

    int ans = Restaurant::randomInt(countAvailable - 1) ;
	Restaurant::currentIndex = available[ans];

    return available[ans];
}
void Restaurant::load_Csv(char filename[])
{
    std::fstream file;
    file.open(filename);
    std::string line;
    int i = 0;
    while (getline( file, line,'\n'))
    {
        std::istringstream templine(line);
        std::string data;
        getline(templine, data,',');
        Restaurant::RestaurantList[i].name = data;
        getline(templine, data,',');
        Restaurant::RestaurantList[i].budget = stoi(data.substr(1));
        getline(templine, data,',');
        Restaurant::RestaurantList[i].type = stoi(data.substr(1));
        getline(templine, data,',');
        Restaurant::RestaurantList[i].place = stoi(data.substr(1));
        getline(templine, data,',');
        Restaurant::RestaurantList[i].address = data;
        Restaurant::RestaurantList[i].index = i;
        i++;
    }
    Restaurant::restaurantCnt = i;
}
int Restaurant::randomInt(int countAvailable)
{
    std::random_device rd;

    /* 梅森旋轉演算法 */
    std::mt19937_64 generator( rd() );

    std::uniform_real_distribution< > dis(0 , countAvailable + 1) ;
    int x = dis(generator);
    return x;
}
