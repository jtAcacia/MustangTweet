/* 
 * File:   Tweet.h
 * Author: Justin Trantham
 *
 * Created on September 21, 2012, 11:11 PM
 */

#ifndef TWEET_H
#define	TWEET_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class Tweet {
public:
    string id, time, tweet;
    std::vector<Tweet *> tweets;
    Tweet();
    Tweet(string &id, string &time, string &tweet);
    Tweet(const Tweet& orig);
    void insert(string id, string time, string tweet);
    virtual ~Tweet();
};
#endif	/* TWEET_H */

