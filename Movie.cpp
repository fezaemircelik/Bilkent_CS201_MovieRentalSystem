//
// Created by Feza on 12/12/2022.
//

#include <iostream>
using namespace std;

#include "Movie.h"


Movie::Movie(int id, int count, Movie * nextMovie) {
    this->id = id;
    this->count = count;

    next = nextMovie;
}

Movie::Movie(int id, Movie * nextMovie) {
    this->id = id;
    this->count = 1;

    next = nextMovie;
}
