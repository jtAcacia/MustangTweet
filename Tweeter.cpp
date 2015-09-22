/* 
 * File:   Tweeter.cpp
 * Author: Justin Trantham
 * Creates a tweeter object read from file containing id,first and last name
 * and list of friends
 * 
 * Created on September 21, 2012, 11:11 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "Tweeter.h"
using namespace std;
Tweeter::Tweeter(){}
Tweeter::Tweeter(string id1, string first1, string last1, vector<string> friends) {
    id = id1;
    first = first1;
    last = last1;
    friendList = friends;
}
void Tweeter::insert(string id1, string first1, string last1, vector<string> friends){
    tweeters.push_back(new Tweeter(id1,first1,last1,friends));
}



