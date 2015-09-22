/* 
 * File:   Output.cpp
 * Author: Justin Trantham
 * MustangTweet
 * Handles all output based upon commands read from file
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string.h>
#include "Tweet.h"
#include "Output.h"
#include "Command.h"
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

Output::Output() {
}
//Sort the pairs based upon second value

struct sort_pred {

    bool operator()(const std::pair<string, int> &left, const std::pair<string, int> &right) {
        return left.second > right.second;
    }
};

/*
 * This will receive a Tweet object and the user being requested to search on
 * and will print the tweets and time in descending order.
 */
void Output::printTimeline(Tweet &a, string user) {
    ofstream u(outsa.c_str(), ios::app);
    int count = 0;
    u << "Command: ptl " << user << endl;
    u << endl;
    u << user << "'s timeline: " << endl;
    for (int i = 0; i < a.tweets.size(); i++) {
        if (a.tweets.at(i)->id == user) {
            count++;
            u << '\t' << "\"" << a.tweets.at(i)->tweet << "\"" << " at " << a.tweets.at(i)->time << endl;
        }
    }
    if (count == 0)
        u << '\t' << "No timeline for user " << user << " :(" << endl;
    u << "----------------------------------------------------------------" << endl;
    u << "----------------------------------------------------------------" << endl;
    u.close();
}

void Output::printActivity(Tweet& a, vector<string> d) {
    ofstream u(outsa.c_str(), ios::app);
    vector<std::pair<string, int> > s;
    map<string, int> stringCounts;

    u << "Command: lst " << endl;
    u << endl;

    for (int i = 0; i < a.tweets.size(); i++) {
        stringCounts[a.tweets.at(i)->id]++;
    }
    map<string, int>::iterator iter;
    for (iter = stringCounts.begin(); iter != stringCounts.end(); iter++) {
        s.push_back(std::make_pair(iter->first, iter->second));
    }
    sort(s.begin(), s.end(), sort_pred());
    for (int i = 0; i < s.size(); i++)
        u << '\t' << s.at(i).first << " sent " << s.at(i).second << " tweets" << endl;
    for (int i = 0; i < d.size(); i++)
        u << '\t' << d.at(i) << " sent 0 tweets" << endl;

    u << "----------------------------------------------------------------" << endl;
    u << "----------------------------------------------------------------" << endl;
    u.close();
}

void Output::printHeader() {
    ofstream u(outsa.c_str(), ios::app);

    u << " __  __           _                   _____                   _" << endl;
    u << "|  \\/  |_   _ ___| |_ __ _ _ __   __ |_   _|_      _____  ___| |_" << endl;
    u << "| |\\/| | | | / __| __/ _` | '_ \\ / _` || | \\ \\ /\\ / / _ \\/ _ \\ __|" << endl;
    u << "| |  | | |_| \\__ \\ || (_| | | | | (_| || |  \\ V  V /  __/  __/ |_" << endl;
    u << "|_|  |_|\\__,_|___/\\__\\__,_|_| |_|\\__, ||_|   \\_/\\_/ \\___|\\___|\\__|" << endl;
    u << "                                |___/                           " << endl;
    u << "----------------------------------------------------------------" << endl;
    u << "----------------------------------------------------------------" << endl;
    u.close();

}

/*
 * Print 3 friend recommendations for a user based upon their friend friendlist. 
 * If the user has no friends then it will just pick 3 that are not the user itself
 * for the possible friends.
 */
void Output::printRecommend(string user, Tweeter& b) {
    ofstream u(outsa.c_str(), ios::app);
    int counter = 0;
    vector<string> tempList;
    vector<string> tempList2;
    std::map<string, string> tempTweeters;
    std::map<string, string>::iterator sd;
    //Will get the position in the b.tweeters vector of this user to acess their
    //friendlist
    int pos = getTweeterPos(b, user);

    u << "Command: rcm " << user << endl;
    u << endl;
    for (int i = 0; i < b.tweeters.at(pos)->friendList.size(); i++) {
        tempList.push_back(b.tweeters.at(pos)->friendList.at(i));
    }
    //Check to see first if the user has any friends at all
    if (tempList.size() == 0) {
        for (int i = 0; i < b.tweeters.size(); i++) {
            if ((b.tweeters.at(i)->id != user) && (counter < 3)) {
                counter++;
                u << '\t' << b.tweeters.at(i)->id << endl;
            }
        }
        if (counter < 3)
            u << '\t' << "Ooops no more friends to be had" << endl;
    } else {
        //Store the users friend list to tempList
        for (int i = 0; i < b.tweeters.at(pos)->friendList.size(); i++) {
            tempList.push_back(b.tweeters.at(pos)->friendList.at(i));
        }
        for (int i = 0; i < tempList.size(); i++) {
            for (int j = 0; j < b.tweeters.at(getTweeterPos(b, tempList.at(i)))->friendList.size(); j++) {
                if (!checkTweeter(tempList, b.tweeters.at(getTweeterPos(b, tempList.at(i)))->friendList.at(j))) {
                    if ((b.tweeters.at(getTweeterPos(b, tempList.at(i)))->friendList.at(j) != user) && (counter < 3)) {
                        tempTweeters.insert(pair<string, string > (b.tweeters.at(getTweeterPos(b, tempList.at(i)))->friendList.at(j), ""));
                        counter++;
                    }

                }
            }
        }
        for (int i = 0; i < b.tweeters.size(); i++) {
            if (((!checkTweeter(tempList, b.tweeters.at(i)->id)) && (b.tweeters.at(i)->id != user)) && (tempTweeters.size() < 3)) {

                tempTweeters.insert(pair<string, string > (b.tweeters.at(i)->id, ""));
                counter++;
            }
        }
        for (sd = tempTweeters.begin(); sd != tempTweeters.end(); sd++) {
            tempList2.push_back((*sd).first);


        }
        for (int i = 0; i < tempList2.size(); i++)
            u << '\t' << tempList2.at(i) << endl;
        if (tempList2.size() < 3)
            u << '\t' << "Ooops no more friends to be had" << endl;
    }



    tempList2.clear();
    tempTweeters.clear();
    u << "----------------------------------------------------------------" << endl;
    u << "----------------------------------------------------------------" << endl;
    u.close();
}

bool Output::checkTweeter(vector<string> list, string user) {
    bool present;
    present = find(list.begin(), list.end(), user) != list.end();
    return present;
}

int Output::getTweeterPos(Tweeter &b, string user) {
    for (int i = 0; i < b.tweeters.size(); i++) {
        if (b.tweeters.at(i)->id == user)
            return i;
    }
}

/*
 * Basic function which will print all the tweets where the word is found
 */
void Output::checkTweets(Tweet& a, string user, string word) {
    ofstream u(outsa.c_str(), ios::app);
    int wordCount = 0;
    string temp;
    string s;
    //Loop through all tweets where the userid matches
    for (int i = 0; i < a.tweets.size(); i++) {
        if ((a.tweets.at(i)->id == user)) {
            temp = a.tweets.at(i)->tweet;
            //This will remove all the punctuation marks from the end of a tweet
            if (ispunct(temp[temp.length() - 1]))
                temp[temp.length() - 1] = ' ';
            istringstream ss(temp);
            //loop through the tweet string and see if there is a match
            while (ss >> s) {
                if (s == word) {
                    u << '\t' << a.tweets.at(i)->id << "'s tweet: " << "\"" << a.tweets.at(i)->tweet << "\"" << " on " << a.tweets.at(i)->time.substr(0, 8) << " at " << a.tweets.at(i)->time.substr(10, 17) << endl;
                    wordCount++;
                }
            }
        }
    }
    if (wordCount == 0)
        printed = false;
    else
        printed = true;
    temp = "";
    s = "";
    u.close();
}

/*
 * Search all the tweets from a particular tweeters' friends for a word
 */
void Output::searchWordTweeterFriends(Tweet& a, Tweeter &b, string user, string word) {
    ofstream u(outsa.c_str(), ios::app);
    int tweeterPos = getTweeterPos(b, user);
    u << "Command: sff " << user << " " << word << endl;
    for (int i = 0; i < b.tweeters.at(tweeterPos)->friendList.size(); i++) {
        checkTweets(a, b.tweeters.at(tweeterPos)->friendList.at(i), word);
    }
    if (!printed)
        u << "no results" << endl;
    u << "----------------------------------------------------------------" << endl;
    u << "----------------------------------------------------------------" << endl;
    u.close();
}

/*
 * Print the feed for the user 
 */
void Output::printFeed(Tweeter& b, Tweet& a, string user) {
    ofstream u(outsa.c_str(), ios::app);
    //get the tweeter position of the user
    int placeAt = getTweeterPos(b, user);

    u << "Command: ptf " << " " << user << endl;
    u << endl;
    u << "User " << user << "'s friends have made these tweets: " << endl;
    //loop through that tweeter at placeAt friends list and print the tweets
    string current;
    for (int i = 0; i < b.tweeters.at(placeAt)->friendList.size(); i++) {
        current = b.tweeters.at(placeAt)->friendList.at(i);
        for (int j = 0; j < a.tweets.size(); j++) {
            if (a.tweets.at(j)->id == current) {
                u << '\t' << a.tweets.at(j)->id << "'s tweet: " << "\"" << a.tweets.at(j)->tweet << "\"" << endl;
            }
        }
    }
    u << "----------------------------------------------------------------" << endl;
    u << "----------------------------------------------------------------" << endl;
    u.close();
}

/*
 * This will search all the tweets recorded for a particular word
 */
void Output::searchAllTweets(Tweet& a, Tweeter& b, string word) {
    ofstream u(outsa.c_str(), ios::app);
    u << "Command: ssw " << " " << word << endl;
    u << endl;

    u << "The word (" << word << ") appeared in " << endl;

    for (int i = 0; i < b.tweeters.size(); i++) {
        checkTweets(a, b.tweeters.at(i)->id, word);
    }
    if (!printed)
        u << "no results" << endl;
    u << "----------------------------------------------------------------" << endl;
    u << "----------------------------------------------------------------" << endl;
    u.close();
}

/*
 * Will search all tweets of a particular tweeter for a certain and if matched
 * will print that the word was found within a tweet.
 */
void Output::searchWordTweeter(Tweet & a, string user, string word) {
    ofstream u(outsa.c_str(), ios::app);
    u << "Command: stf " << " " << user << " " << word << endl;
    u << endl;
    u << "User " << user << " has made these tweets with " << word << ":" << endl;
    checkTweets(a, user, word);
    if (!printed)
        u << "no results" << endl;
    u << "----------------------------------------------------------------" << endl;
    u << "----------------------------------------------------------------" << endl;
    u.close();
}


