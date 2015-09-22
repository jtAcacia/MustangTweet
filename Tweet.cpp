/* 
 * File:   Tweet.cpp
 * Author: Justin Trantham
 * Will create a tweet object based upon reading from file which contains id,
 * timestamp, and the tweet
 * 
 * Created on September 21, 2012, 11:11 PM
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "Tweet.h"
using namespace std;

Tweet::Tweet() {
}

Tweet::Tweet(string &id1, string &time1, string &tweet1) {
    id = id1;
    time = time1;
    tweet = tweet1;
}

void Tweet::insert(string id, string time, string tweet) {
    tweets.push_back(new Tweet(id, time, tweet));

}

Tweet::~Tweet() {
}

