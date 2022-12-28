//
// Created by Feza on 12/12/2022.
//

#ifndef HW3_MOVIE_H
#define HW3_MOVIE_H

#endif //HW3_MOVIE_H

#include <iostream>
using namespace std;


class Movie{
public:
    Movie(int id, int count, Movie * nextMovie);
    Movie(int id, Movie * nextMovie);
    Movie * next;
    int id;
    int count;
    bool returned;

    int totalcount;
private:
};
