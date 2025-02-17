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
  //int end = token.length();  // end index

  if(token.length() == 1) {
    if(isalpha(token[0])) {
      char new_token = tolower(token[0]);                               
      string sds = "";
      sds += new_token;
      return sds;
    }
    else {
      return "";
    }
  }
  else if (token == "") {
    return token;
  }

  string remo_front = cleanRightToken(token);
  string remo_back = cleanLeftToken(remo_front);

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

  return token.substr(leading);
}

string cleanLeftToken(const string& token) {
  int trailing = token.length();
  for(int i = token.length()-1; i >= 0; i--) {
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
  for(int i = 0; i < text.length(); i++) {
    if(!isspace(text[i])){
      element += text[i];
    }
    else {
      gatherWords.insert(cleanToken(element));
      element = "";
    }
  }
  gatherWords.insert(cleanToken(element));
  gatherWords.erase("");
  return gatherWords;
}

int buildIndex(const string& filename, map<string, set<string>>& index) {
  // TODO student
  
  ifstream infile(filename);
  if(!infile.is_open()){
    return 0;
  }
  string url;
  int url_count = 0;
  string base;

  while(!infile.eof()) {
    getline(infile, url);
    getline(infile, base);
    if(!infile.fail()) {
      string sentence = cleanToken(base);
      set <string> words = gatherTokens(sentence);
      for(auto word: words) {
          index[word].insert(url);
      }
      url_count++;
    }
  }
  return url_count;
}

set<string> findQueryMatches(const map<string, set<string>>& index,
                             const string& sentence) {
  // TODO student
  map<string,set<string>> copy = index; //copy of index map
  vector<string> word_list; // list of words
  string word = "";
  set<string> resultant; //resultant set

  //iterate through sentence
  for(int i = 0; i < sentence.length(); i++) {
    if(isalpha(sentence[i]) || sentence[i] == '+' || sentence[i] == '-') {
      word += tolower(sentence[i]);
    }
    else if(word != "") {
      word_list.push_back(word);
      word = "";
    }
  }

  if (!word.empty()) { 
    word_list.push_back(word); 
  }

  for(int j = 0; j < word_list.size(); j++) { //iterate through the vector of words
    string search = ""; // the term for the word
    if(word_list[j][0] == '+'|| word_list[j][0] == '-') {
      search = word_list[j].substr(1); //just the word
    }
    else {
      search = word_list[j];
    }

    set<string> search_res = copy[search]; // only the values of the key

    set<string> temp;
    if(word_list[j][0] == '+') {
      set_intersection(resultant.begin(), resultant.end(), search_res.begin(), search_res.end(), inserter(temp, temp.begin()));
      resultant = temp;
    }
    else if(word_list[j][0] == '-') {
      set_difference(resultant.begin(), resultant.end(), search_res.begin(), search_res.end(), inserter(temp, temp.begin()));
      resultant = temp;
    }
    else {
      set_union(resultant.begin(), resultant.end(), search_res.begin(), search_res.end(), inserter(temp, temp.end()));
      resultant = temp;
    }
  }

  return resultant;
}

void searchEngine(const string& filename) {
  // TODO student
  map<string, set<string>> index;
  int indexSize = buildIndex(filename,index);
  if(indexSize == 0) {
    cout << "Invalid filename." << endl;
    cout<<"Stand by while building index..."<<endl;
    cout<<"Indexed 0 pages containing 0 unique terms"<<endl;
  }
  else {
    cout<<"Stand by while building index..."<<endl;
    cout << "Indexed ";
    cout << to_string(indexSize);
    cout << " pages containing "; 
    cout << index.size(); 
    cout << " unique terms" << endl;
  }
  while(true) {
    cout << "Enter query sentence (press enter to quit): ";
    string command;
    getline(cin, command);
    if (command == "") {
      break;
    }
    set<string> result = findQueryMatches(index, command);
    cout << "Found "+ to_string(result.size()) + " matching pages" << endl;
    for(auto i: result) {
      cout << i << endl;
    }
  }
  cout << "Thank you for searching!";
}
