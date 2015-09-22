/* 
 * File:   Tweeter.h
 * Author: Justin Trantham
 *
 * Created on September 21, 2012, 11:11 PM
 */

#ifndef TWEETER_H
#define	TWEETER_H
#include <map>
using namespace std;

class Tweeter {
public:
    std::vector<std::string> friendList;
    std::string id, first, last;
    std::vector<Tweeter *> tweeters;
    Tweeter();
    Tweeter(std::string id1, std::string first1, std::string last1, std::vector<std::string> friends);
    void insert(string id1, string first1, string last1, vector<string> friends);
};

#endif	/* TWEETER_H */

