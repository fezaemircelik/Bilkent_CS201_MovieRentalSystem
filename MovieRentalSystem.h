//
// Created by Feza on 12/12/2022.
//

#ifndef HW3_MOVIERENTALSYSTEM_H
#define HW3_MOVIERENTALSYSTEM_H

#endif //HW3_MOVIERENTALSYSTEM_H
#include <iostream>
using namespace std;

#include "Sub.h"

class MovieRentalSystem {
public:
    MovieRentalSystem( const string movieInfoFileName,
                       const string subscriberInfoFileName );
    ~MovieRentalSystem();
    void removeMovie( const int movieId );
    void addMovie( const int movieId, const int numCopies );
    void removeSubscriber( const int subscriberId );
    void rentMovie( const int subscriberId, const int movieId );
    void returnMovie( const int subscriberId, const int movieId );
    void showMoviesRentedBy( const int subscriberId ) const;
    void showSubscribersWhoRentedMovie( const int movieId ) const;
    void showAllMovies() const;
    void showAllSubscribers() const;
private:
    int TOTALmovieCount;
    int TOTALsubCount;

    Movie * rootM ;
    Movie * iterM;

    Sub * rootS;
    Sub * iterS;
};
