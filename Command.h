/* 
 * File:   Command.h
 * Author: Justin Trantham
 * 
 * Created on September 22, 2012, 5:05 PM
 */

#ifndef COMMAND_H
#define	COMMAND_H
#include <fstream>
#include <map>
#include <vector>
using namespace std;

class Command {
public:
    Command();
    void performCommands(ifstream &commands);
    void setTweeters(ifstream &input);
    void setTweets(ifstream &tweets);
    ~Command();
private:
    int numberTweeters;
    int numberTweets;
    string tweetersInput, tweetsInput, outputData;
};

#endif	/* COMMAND_H */

