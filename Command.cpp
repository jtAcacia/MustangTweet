/*
 * File:   Command.cpp
 * Author: Justin Trantham
 * Will read from commands file and then will call the function necessary to
 * complete that command.
 *
 * Created on September 22, 2012, 5:05 PM
 */

#include "Command.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include "Tweet.h"
#include "Tweeter.h"
#include "Output.h"
#include <map>
using namespace std;
Tweet a;
Tweeter b;
Output outs;
std::map<string, string> tempTweeters;
std::map<string, string>::iterator sd;
std::vector<string> temp;
vector<string> temp2;
Command::Command() {}
Command::~Command() {
    //Clear contents of vector<Tweeter *>
    while (!b.tweeters.empty())delete b.tweeters.back(), b.tweeters.pop_back();
    //Clear contents of vector<Tweet *>
    while (!a.tweets.empty())delete a.tweets.back(), a.tweets.pop_back();
    temp.clear();
    temp2.clear();
}

/*
 * Will sort the tweets based upon timestamp
 */
bool sortTimes(Tweet * i, Tweet * j) {
    return (i->time < j->time);
}

/*
 * Will read from the commands file and will call the functions to perform those
 * commands
 */
void Command::performCommands(std::ifstream& commands) {
    string currentCommand;
    //Read from commands input file word for word
    while (commands >> currentCommand) {
        if (currentCommand == "rtw") {
            commands >> tweetersInput;
            ifstream tweeterInput(tweetersInput.c_str());
            setTweeters(tweeterInput);
        }
        if (currentCommand == "rtt") {
            commands >> tweetsInput;
            ifstream tweetInput(tweetsInput.c_str());
            setTweets(tweetInput);
        }
        if (currentCommand == "out") {
            commands >> outputData;
            std::ofstream ofs(outputData.c_str());
            ofs.clear();
            outs.outsa = outputData;
            outs.printHeader();
        }
        if (currentCommand == "ptl") {
            commands >> currentCommand;
            outs.printTimeline(a, currentCommand);
        }
        if (currentCommand == "sff") {
            string tempWord;
            commands >> currentCommand;
            commands >> tempWord;
            outs.searchWordTweeterFriends(a, b, currentCommand, tempWord);
        }
        if (currentCommand == "stf") {
            string tempWord;
            commands >> currentCommand;
            commands >> tempWord;
            outs.searchWordTweeter(a, currentCommand, tempWord);
        }
        if (currentCommand == "ssw") {
            commands >> currentCommand;
            outs.searchAllTweets(a, b, currentCommand);
        }
        if (currentCommand == "ptf") {
            commands >> currentCommand;
            outs.printFeed(b, a, currentCommand);
        }
        if (currentCommand == "rcm") {
            commands >> currentCommand;
            outs.printRecommend(currentCommand, b);
        }
        if (currentCommand == "lst") {
            outs.printActivity(a, temp2);
        }
    }

    //close the commands input file
    commands.close();
}

/*
 * Will read from the tweetersInput file and create Tweeter objects stored in a
 * vector that has the userId, first and last name and the friends associated
 * with that tweeter.
 */

void Command::setTweeters(std::ifstream &tweeters) {
    string line;
    getline(tweeters, line);
    numberTweeters = atoi(line.c_str());
    getline(tweeters, line);
    string userId, first, last;
    //holds the friends attached for each tweeter
    std::vector<std::string> friends;
    int counter = 0;
    string tokens;
    string second;

    //reads in the userId, first name and last name
    for (int abc = 0; abc < numberTweeters; abc++) {
        //counter to keep track of the number of vertical bars
        counter = 0;
        istringstream sss(line);
        while (getline(sss, tokens, '|')) {
            if (counter == 0)
                userId = tokens;
            if (counter == 1)
                first = tokens;
            if (counter == 2)
                last = tokens;
            if (counter > 2) {
                second = tokens;
            }
            counter++;
        }

        //stringstream to read in the friends
        istringstream j(second);
        //store the friends for each tweeter into the friends vector
        while (getline(j, second, ',')) {
            friends.push_back(second);
        }
        second = "";
        counter = 0;
        //create a new Tweeter object with userId,first,last and friendslist
        b.insert(userId, first, last, friends);
        //clear the temp. friend list for each tweeter
        friends.clear();
        getline(tweeters, line);
    }
    //close the tweeters input file
    tweeters.close();
    friends.clear();
}

/*
 * Reads from the tweetInput file and creates vector of Tweet objects
 */
void Command::setTweets(std::ifstream &tweets) {
    string userId, time, tweet, line, tokens;
    getline(tweets, line);
    numberTweets = atoi(line.c_str());
    getline(tweets, line);
    //Counter used for keeping track of the vertical bars
    int counter = 0;
    //Read and store all the tweets from the file
    for (int abc = 0; abc < numberTweets; abc++) {
        istringstream sss(line);
        //tokens based on vertical bars
        while (getline(sss, tokens, '|')) {
            if (counter == 0)
                userId = tokens;
            if (counter == 1)
                time = tokens;
            if (counter == 2)
                tweet = tokens;
            counter++;
        }
        tempTweeters.insert(pair<string, string > (userId, ""));
        counter = 0;
        //create a Tweet object with userId, time and tweet
        a.insert(userId, time, tweet);
        getline(tweets, line);
        userId = "";
        time = "";
        tweet = "";
    }
    for (sd = tempTweeters.begin(); sd != tempTweeters.end(); sd++) {
        temp.push_back((*sd).first);
    }
    //check to see which tweeters didn't make any tweets and store them into temp2
    //Will store the tweeters that didn't make any tweets
    bool isPresent = false;
    for (int i = 0; i < b.tweeters.size(); i++) {
        isPresent = (std::find(temp.begin(), temp.end(), b.tweeters.at(i)->id) != temp.end());
        if (!isPresent)
            temp2.push_back(b.tweeters.at(i)->id);
    }
    //sort the tweets based upon timestamp
    sort(a.tweets.begin(), a.tweets.end(), sortTimes);
    //clear contents of tempTweeters
    tempTweeters.clear();
    //close the tweets input file
    tweets.close();
}
