//
// Created by Feza on 12/12/2022.
//

#ifndef HW3_SUB_H
#define HW3_SUB_H

#endif //HW3_SUB_H

#include <iostream>

#include "Movie.h"

using namespace std;


class Sub{
public:
    Sub(int id, Sub * nextSub);
    Sub * next;
    int id;
    Movie * movies;
    int moviecount;
private:
};