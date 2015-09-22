/* 
 * File:   Output.h
 * Author: Justin Trantham *
 * Created on September 23, 2012, 9:54 AM
 */

#ifndef OUTPUT_H
#define	OUTPUT_H
#include "Tweet.h"
#include "Tweeter.h"
#include <fstream>
using namespace std;
class Output {
public:
    Output();
    string outsa;
    bool printed;
    void searchWordTweeter(Tweet &a, string user, string word);
    void printTimeline(Tweet &a, string user);
    void printFeed(Tweeter &b, Tweet &a, string user);
    void searchAllTweets(Tweet& a, Tweeter& b, string word);
    void printFeed(Tweet & a, string user);
    void printRecommend(string user, Tweeter &b);
    void searchWordTweeterFriends(Tweet &a, Tweeter &b,string user,string word);
    void printActivity(Tweet& a, vector<string> d);
    void printHeader();
    int getTweeterPos(Tweeter &b,string user);
    void possibleFriends(string user, Tweeter& b, vector<string> &temp, vector<string> &temp2);
    void closeFile();
    bool checkTweeter(vector<string> list,string user);
    void checkTweets(Tweet& a, string user, string word);
};

#endif	

