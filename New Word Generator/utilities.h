#include <iostream>
using namespace std;
#include <cstring>
#include <string>
#include <time.h>
#include <fstream>

const int MAX_CHAR = 256;
const int BOX_WIDTH = 72;

// Input Utilities
//
void takeInput(int& input, const string& prompt);
void takeInput(double& input, const string& prompt);
void takeInput(char& input, const string& prompt);
void takeInput(char input[], const string& prompt);

// Error Handling
//
void cinErrorCheck(bool& errorFlag);
void checkNext(bool& errorFlag);
void invalidEntry(const bool& errorFlag);
bool quitCheck(const char input[]);
bool quitCheck(const char& input);

// Cstring Utilities
//
// Cstring General Output
void printCstring(const char cString[]);
int compareCstringToLowercase(const char cString1[], const char cString2[]);
//
// Cstring Copy
void copyCstring(const char sourceCstring[], char destinationCstring[]);
int compareChar(const char& char1, const char& char2);
//
// Cstring manipulation
void cStringToLowercase(char cString[], const int stringLength);
bool cStringToInt(const char input[], int& output);
void stringCopy(char destination[], const int& stringLength, const char source[]);

// Design Tools
void printCharacters(const int& width, const string& designCharacter);
void headerBox(const string& message);
void alertBoxTwoLines(const string& line1, const string& line2);
void questionBox(char inputBuffer[], const string& message);