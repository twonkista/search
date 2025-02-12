#include "include/search.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string cleanRightToken(const string& token);
string cleanLeftToken(const string& token);

string cleanToken(const string& token) {
  // TODO student
  int end = token.length();  // end index

  if(token.length() == 1) {
    char new_token = tolower(token[0]);                               //bro suck me off thats how good i am
    string sds = "";
    sds += new_token;
    return sds;
  }
  else if (token == "") {
    return token;
  }

  string remo_front = cleanRightToken(token);
  string remo_back = cleanLeftToken(remo_front);
  //BRO SMDFR U PMO
  string sting = "";

  int count = 0;
  for(int i = 0; i < remo_back.length(); i++) {
    if(isalpha(remo_back[i])) {
      count++;
      sting += tolower(remo_back[i]);
    }
    else {
      sting += tolower(remo_back[i]);
    }
  }

  if (count == 0) {
    return "";
  }
  else {
    return sting;
  }
} //O(N)

string cleanRightToken(const string& token) {
  int leading =  0;

  for(char c: token) {
    if(ispunct(c)) {
      leading ++;
    }
    else {
      break;
    }
  }

  return token.substr(leading, token.length());
}

string cleanLeftToken(const string& token) {
  int trailing = token.length();
  for(int i = token.length()-1; i >= 0; --i) {
    if(ispunct(token[i])) {
      trailing--;
    }
    else {
      break;
    }
  }
  
  string remo_back = token.substr(0, trailing);
  return remo_back;
}

set<string> gatherTokens(const string& text) {
  // TODO student
  set<string> gatherWords;
  string element = "";
  for (int i = 0; i <= text.size(); i++) {
    if ((isalpha(text[i]) && i < text.size()) || (ispunct(text[i]) && i < text.size() && isalpha(text[i-1]) && i != 0 && i != text.size()-1 && isalpha(text[i+1]))) {  // alpha and not the last element or if the punctuation isnt the last or first, element and the element before is a letter
      element += tolower(text[i]);                    // add to the string
    } else if (element != "") { //too long didnt read
      gatherWords.insert(element);  // push to vector
      element = "";            // resets the element string
    }
  }
  return gatherWords;
  //micky mouse i gotta fix later
}

int buildIndex(const string& filename, map<string, set<string>>& index) {
  // TODO student
  return 0;
}

set<string> findQueryMatches(const map<string, set<string>>& index,
                             const string& sentence) {
  // TODO student
  return {};
}

void searchEngine(const string& filename) {
  // TODO student
}
