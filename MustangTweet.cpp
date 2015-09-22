/* 
 * File:   MustangTweet.cpp
 * Author: Justin Trantham
 * Main driver class to run Mustang Tweet depends on command line input of 
 * commands.input file.
 * 
 * Created on September 21, 2012, 11:11 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include "Command.h"
#include "Tweet.h"

using namespace std;

int main(int argc, char *argv[]) {
    //commands input file
    ifstream commands(argv[1]);
    Command j;   
    //Perform all the commands from file
    j.performCommands(commands);
    //Cleanup
    j.~Command();
}


