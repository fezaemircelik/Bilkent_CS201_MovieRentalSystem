//
// Created by Feza on 12/12/2022.
//
#include <iostream>
#include <fstream>

using namespace std;
#include "MovieRentalSystem.h"

MovieRentalSystem::MovieRentalSystem(const string movieInfoFileName, const string subscriberInfoFileName) {

    //movie ekleme kodu
    rootM = (Movie *)malloc(sizeof(Movie));
    rootM->next = (Movie *)malloc(sizeof(Movie));
    iterM = rootM;
    this->TOTALmovieCount = 0;
    bool checkerM = true;

    Movie * rootM2 = rootM;

    ifstream movieFile;
    movieFile.open(movieInfoFileName.c_str(),ios_base::in);
    if(movieFile.is_open()){
        int firstLine;
        movieFile >> firstLine;
        int movieID;
        int movieCount;

        movieFile >> movieID >> movieCount;
        //rootM showing first movie
        rootM->id = movieID;
        rootM->count = movieCount;
        rootM->totalcount = movieCount;
        rootM->returned = true;
        this->TOTALmovieCount++;

        while(movieFile >> movieID >> movieCount){
            iterM = iterM->next;
            iterM->id = movieID;
            iterM->count = movieCount;
            iterM->totalcount = movieCount;
            iterM->returned = true;
            iterM->next = (Movie *)malloc(sizeof(Movie));

            this->TOTALmovieCount++;
        }
        movieFile.close();
        //MOVIE'leri SORTLA
        int nodeCtr;
        int ctr;
        int nodeIDCopy, nodeCountCopy, nodeTotalCountCopy;
        Movie * currentNode;
        Movie * nextNode;
        for(nodeCtr = TOTALmovieCount - 2; nodeCtr>=0; nodeCtr--){
            currentNode = rootM;
            nextNode = currentNode->next;
            for(ctr = 0; ctr <= nodeCtr; ctr++){
                if(currentNode->id > nextNode->id){
                    //id
                    nodeIDCopy = currentNode->id;
                    currentNode->id = nextNode->id;
                    nextNode->id = nodeIDCopy;
                    //count
                    nodeCountCopy = currentNode->count;
                    currentNode->count = nextNode->count;
                    nextNode->count = nodeCountCopy;
                    //totalcount
                    nodeTotalCountCopy = currentNode->totalcount;
                    currentNode->totalcount = nextNode->totalcount;
                    nextNode->totalcount = nodeTotalCountCopy;

                }
                currentNode = nextNode;
                nextNode = nextNode->next;
            }
        }
        //
    }
    else{
        checkerM = false;
    }


    //subs ekleme kodu
    rootS = (Sub *)malloc(sizeof(Sub));
    rootS->next = (Sub *) malloc(sizeof (Sub));
    iterS = rootS;
    this->TOTALsubCount = 0;
    bool checkerS = true;

    ifstream  subsFile;
    subsFile.open(subscriberInfoFileName.c_str(),ios_base::in);
    if(subsFile.is_open()){
        int firstLine;
        subsFile >> firstLine;
        int subID;

        subsFile >> subID;
        //rootS showing first sub
        rootS->id = subID;
        rootS->movies = (Movie *)malloc(sizeof(Movie));
        rootS->movies->next = (Movie *)malloc(sizeof(Movie));
        rootS->moviecount = 0;
        this->TOTALsubCount++;

        while(subsFile >> subID){
            iterS = iterS->next;
            iterS->id = subID;
            iterS->next = (Sub *)malloc(sizeof(Sub));
            iterS->moviecount = 0;

            iterS->movies = (Movie *)malloc(sizeof(Movie));
            iterS->movies->next = NULL;

            this->TOTALsubCount++;
        }
        subsFile.close();

        //SUB'ları SORTLA
        int nodeCtr;
        int ctr;
        int nodeIDCopy;
        Sub * currentNode;
        Sub * nextNode;
        for(nodeCtr = TOTALsubCount - 2; nodeCtr>=0; nodeCtr--){
            currentNode = rootS;
            nextNode = currentNode->next;
            for(ctr = 0; ctr <= nodeCtr; ctr++){
                if(currentNode->id > nextNode->id){
                    //id
                    nodeIDCopy = currentNode->id;
                    currentNode->id = nextNode->id;
                    nextNode->id = nodeIDCopy;
                }
                currentNode = nextNode;
                nextNode = nextNode->next;
            }
        }
        //

    }
    else{
        checkerS = false;
    }



    if(checkerM && checkerS){
        //9 subscribers and 15 movies have been loaded
        cout << this->TOTALsubCount << " subscribers and " << this->TOTALmovieCount << " movies have been loaded" << endl;
    }
    else if(!checkerM){
        //Input file my_movies.txt does not exist
        cout << "Input file " << movieInfoFileName << " does not exist" << endl;
    }
}

MovieRentalSystem::~MovieRentalSystem() {

}

void MovieRentalSystem::addMovie(const int movieId, const int numCopies) {
    this->iterM = rootM;
    bool alreadyExists = false;
    if(iterM->id == movieId){
        alreadyExists = true;
    }
    for(int i = 0; i < TOTALmovieCount ;i++){
        this->iterM = this->iterM->next;
        if(iterM->id == movieId){
            alreadyExists = true;
        }
    }
    if(alreadyExists){
        cout << "Movie " << movieId << " already exists" << endl;
    }
    else{
        this->iterM->id = movieId;
        this->iterM->count = numCopies;
        iterM->totalcount = numCopies;
        this->iterM->next = (Movie *) malloc(sizeof(Movie));

        cout << "Movie " << movieId << " has been added" << endl;

        this->TOTALmovieCount++;
        //MOVIE'leri SORTLA
        int nodeCtr;
        int ctr;
        int nodeIDCopy, nodeCountCopy, nodeTotalCountCopy;
        Movie * currentNode;
        Movie * nextNode;
        for(nodeCtr = TOTALmovieCount - 2; nodeCtr>=0; nodeCtr--){
            currentNode = rootM;
            nextNode = currentNode->next;
            for(ctr = 0; ctr <= nodeCtr; ctr++){
                if(currentNode->id > nextNode->id){
                    //id
                    nodeIDCopy = currentNode->id;
                    currentNode->id = nextNode->id;
                    nextNode->id = nodeIDCopy;
                    //count
                    nodeCountCopy = currentNode->count;
                    currentNode->count = nextNode->count;
                    nextNode->count = nodeCountCopy;
                    //totalcount
                    nodeTotalCountCopy = currentNode->totalcount;
                    currentNode->totalcount = nextNode->totalcount;
                    nextNode->totalcount = nodeTotalCountCopy;
                }
                currentNode = nextNode;
                nextNode = nextNode->next;
            }
        }
        //
    }



}

void MovieRentalSystem::removeMovie(const int movieId) {
    Movie * temp = rootM;
    Movie * deleter = rootM;
    bool doesntExist = true;
    bool missedMovies = false;
    //birinciyse
    if(temp->id == movieId){
        if(temp->count != temp->totalcount){
            missedMovies = true;
        }else{
            rootM = temp->next;

            doesntExist = false;

            this->TOTALmovieCount--;
        }
    }
    else{//birinci değilse
        for(int i = 0; i < TOTALmovieCount; i++){
            if(temp->next->id == movieId){
                if(temp->next->count != temp->next->totalcount){
                    missedMovies = true;
                    i = TOTALmovieCount + 10;
                }
                else{
                    deleter = temp->next;
                    temp->next = temp->next->next;

                    i = TOTALmovieCount + 10;

                    doesntExist = false;

                    this->TOTALmovieCount--;
                }
            }
            else{
                temp = temp->next;
                deleter = deleter->next;
            }
        }
    }


    if(missedMovies){
        cout << "Movie " << movieId << " cannot be removed -- at least one copy has not been returned" << endl;
    }
    else if(doesntExist){
        cout << "Movie " << movieId << " does not exist" << endl;
    }
    else{
        cout << "Movie " << movieId << " has been removed" << endl;
    }
}

void MovieRentalSystem::removeSubscriber(const int subscriberId) {
    Sub* temp = rootS;
    Sub* deleter = rootS;
    bool doesntExist = true;
    bool haveMovies = false;

    Movie * iterSM = temp->movies;
    //birinciyse
    if(temp->id == subscriberId){
        while(iterSM->id > 0){
            if(!iterSM->returned){
                haveMovies = true;
            }
            iterSM = iterSM->next;
        }
        if(haveMovies){

        }
        else{
            rootS = temp->next;

            doesntExist = false;

            this->TOTALsubCount--;
        }
    }
    else{//birinci değilse
        for(int i = 0; i < TOTALsubCount; i++){
            if(temp->next->id == subscriberId){
                iterSM = temp->next->movies;
                while(iterSM->id > 0){
                    if(!iterSM->returned){
                        haveMovies = true;
                    }
                    iterSM = iterSM->next;
                }
                if(!haveMovies){
                    deleter = temp->next;
                    temp->next = temp->next->next;

                    i = TOTALsubCount + 10;

                    doesntExist = false;

                    this->TOTALsubCount--;
                }
            }
            else{
                temp = temp->next;
                deleter = deleter->next;
            }
        }
    }

    if(haveMovies){
        cout << "Subscriber " << subscriberId << " cannot be removed -- at least one movie has not been returned" << endl;
    }
    else if (doesntExist){
        cout << "Subscriber " << subscriberId << " does not exist" << endl;
    }
    else{
        cout << "Subscriber " << subscriberId << " has been removed" << endl;
    }
}

void MovieRentalSystem::rentMovie(const int subscriberId, const int movieId) {
    //iterator ayarlayıcı (SUB)
    this->iterS = this->rootS;
    bool subExists = false;
    for(int i = 0; i < this->TOTALsubCount; i++){
        if(iterS->id == subscriberId){
            i = TOTALsubCount + 10;
            subExists = true;
        }
        else{
            iterS = iterS->next;
        }
    }

    //iterator ayarlayıcı (MOVIE)
    this->iterM = this->rootM;
    bool movieExists = false;
    for(int i = 0; i < this->TOTALmovieCount; i++){
        if(iterM->id == movieId){
            i = TOTALmovieCount + 10;
            movieExists = true;
        }
        else{
            iterM = iterM->next;
        }
    }

    bool copy = true;
    if(movieExists){    //movie var mı yok mu kontrol ediyor
        if(iterM->count == 0){
            copy = false;
        }
    }
    if(!movieExists && !subExists){
        cout << "Subscriber " << subscriberId << " and movie " << movieId << " do not exist" << endl;
    }
    else if(!subExists){     //sub var mı yok mu kontrol ediyor
        cout << "Subscriber " << subscriberId << " does not exist" << endl;
    }



    if(subExists){
        if(movieExists && copy){
            Movie * iterSM = iterS->movies;
            bool checker = true;
            while(iterSM->id > 0 ){
                iterSM = iterSM->next;
            }
            iterSM->id = movieId;
            iterSM->returned = false;   //
            iterSM->next = (Movie *) malloc(sizeof (Movie));

            //movie nin eksilmesi lazım
            iterM->count--;

            cout << "Movie " << movieId << " has been rented by subscriber " << subscriberId << endl;

            iterS->moviecount++;

        }
        else if(!movieExists){
            cout << "Movie " << movieId << " does not exist" << endl;
        }
        else{
            cout << "Movie " << movieId << " has no available copy for renting" << endl;
        }
    }
}

void MovieRentalSystem::returnMovie(const int subscriberId, const int movieId) {
    //iterator ayarlamaca (SUB)
    this->iterS = rootS;
    bool subExists = false;

    for(int i = 0; i < this->TOTALsubCount; i++){
        if(iterS->id == subscriberId){
            i = TOTALsubCount + 10;
            subExists = true;
        }
        else{
            iterS = iterS->next;
        }
    }

    //iterator ayarlamaca (SUB'un MOVIE'si)
    Movie * iterSM = iterS->movies;
    bool movieExists = false;

    while(iterSM->id > 0 && iterSM->id != movieId){  //movie bulana kadar devam
        if(iterSM->returned){
            while(iterSM->returned){
                iterSM = iterSM->next;
            }
        }
        else{
            iterSM = iterSM->next;
            while(iterSM->returned){
                iterSM = iterSM->next;
            }
        }
    }
    if(iterSM->id == movieId){
        movieExists = true;
    }

    //if(iterSM->returned){
    //    Movie * temp  = iterSM;
    //    bool checker = true;
    //    while(temp->id > 0 && checker){
    //        if(temp->id == movieId && !temp->returned){
    //            iterSM = temp;
    //            checker = false;
    //        }
    //    }
    //}


    bool notReturned = true;
    //geri vermiş mi kontrol et
    if(iterSM->returned){
        notReturned = false;
    }

    if(!subExists){
        cout << "Subscriber " << subscriberId << " does not exist" << endl;
    }
    if(subExists){
        if(movieExists && notReturned){
            iterSM->returned = true;

            //movie'i ana iteratöründen returnle
            this->iterM = rootM;
            for(int i = 0; i < this->TOTALmovieCount; i++){
                if(this->iterM->id == movieId){
                    i = TOTALmovieCount + 10;
                }
                else{
                    iterM = iterM->next;
                }
            }
            iterM->count++;

            iterS->moviecount--;
            cout << "Movie " << movieId << " has been returned by subscriber " << subscriberId << endl;
        }
        else if(!movieExists){
            cout << "No rental transaction for subscriber " << subscriberId << " and movie " << movieId << endl;
        }
        else{
            cout << "No rental transaction for subscriber " << subscriberId << " and movie " << movieId << endl;
        }
    }
    else{
        cout << "No rental transaction for subscriber " << subscriberId << " and movie " << movieId << endl;
    }
}

void MovieRentalSystem::showMoviesRentedBy(const int subscriberId) const {
    //iterator ayarlamaca SUB
    Sub * tempIterS = rootS;
    bool subExists = false;
    for(int i = 0; i < this->TOTALsubCount; i++){
        if(tempIterS->id == subscriberId){
            subExists = true;
            i = TOTALsubCount + 10;
        }
        else{
            tempIterS = tempIterS->next;
        }
    }

    if(subExists){
        Movie * iterSM = tempIterS->movies;

        bool checker = false;
        //daha önce film aldı mı?
        if(iterSM->id > 0){
            checker = true;
        }

        //daha önce film aldıysa
        if(checker){
            cout << "Subscriber " << subscriberId << " has rented the following movies:" << endl;
            iterSM = tempIterS->movies;
            while(iterSM->id > 0){
                if(iterSM->returned){
                    cout << iterSM->id << " returned" << endl;
                }
                else{
                    cout << iterSM->id << " not returned" << endl;
                };
                iterSM = iterSM->next;
            }
        }
        else{
            cout << "Subscriber " << subscriberId << " has not rented any movies" << endl;
        }

    }
    else{
        cout << "Subscriber " << subscriberId << " does not exist" << endl;
    }

}

void MovieRentalSystem::showSubscribersWhoRentedMovie(const int movieId) const {
    //movie'nin var olup olmadığını kontrol et
    Movie * tempIterM = rootM;
    bool movieExists = false;
    for(int i = 0; i < this->TOTALmovieCount; i++){
        if(tempIterM->id == movieId){
            movieExists = true;
            i = TOTALmovieCount + 10;
        }
        else{
            tempIterM = tempIterM->next;
        }
    }
    //
    if(movieExists){
        Sub * tempIterS = rootS;
        Movie * tempIterSM;
        bool checker = false;

        for(int i = 0; i < this->TOTALsubCount; i++){
            tempIterSM = tempIterS->movies;
            while(tempIterSM->id > 0){
                if(tempIterSM->id == movieId){
                    checker = true;
                }
                tempIterSM = tempIterSM->next;
            }
            tempIterS = tempIterS->next;
        }

        if(!checker){
            cout << "Movie " << movieId << " has not been rented by any subscriber" << endl;
        }
        else{
            cout << "Movie " << movieId << " has been rented by the following subscribers:" << endl;

            tempIterS = rootS;
            tempIterSM = tempIterS->movies;

            for(int i = 0; i < this->TOTALsubCount; i++){
                tempIterSM = tempIterS->movies;
                while(tempIterSM->id > 0){
                    if(tempIterSM->id == movieId){
                        if(tempIterSM->returned){
                            cout << tempIterS->id << " returned" << endl;
                        }
                        else{
                            cout << tempIterS->id << " not returned" << endl;
                        }
                    }
                    tempIterSM = tempIterSM->next;
                }
                tempIterS = tempIterS->next;
            }
        }
    }
    else{
        cout << "Movie " << movieId << " does not exist" << endl;
    }

}

void MovieRentalSystem::showAllMovies() const {
    cout << "Movies in the movie rental system:" << endl;
    Movie * newIter = this->rootM;
    for(int i = 0; i < this->TOTALmovieCount;i++){
        cout << newIter->id << " " << newIter->totalcount << endl;
        newIter = newIter->next;
    }
}

void MovieRentalSystem::showAllSubscribers() const {
    cout << "Subscribers in the movie rental system:" << endl;
    Sub * newIter = this->rootS;
    for(int i = 0; i < this->TOTALsubCount; i++){
        cout << newIter->id << endl;
        newIter = newIter->next;
    }
}
