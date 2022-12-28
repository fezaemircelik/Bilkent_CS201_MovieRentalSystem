//
// Created by Feza on 12/12/2022.
//

#include <iostream>
using namespace std;
#include "Sub.h"

Sub::Sub(int id, Sub * nextSub){
    this->id = id;

    next = nextSub;
};


