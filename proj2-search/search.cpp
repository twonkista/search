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

string cleanToken(const string& token) {
  // TODO student
  string res = "";           // result string
  int count_punct = 0;       // number of punctuation
  int start = 0;             // start index
  int end = token.length();  // end index
  // increment start and end so that it exclused leading and trailing
  // punctuation
  // for loop to add all the elements to res
  for (int i = start; i < end; i++) {
    if (isalpha(token[i])) {
      count_punct++;
      res += tolower(token[i]);
    } else if (isdigit(token[i])) {
      res += token[i];
    }
  }
  // if count of letters is 0
  if (count_punct == 0) {
    return "";
  } else {
    return res;
  }
}

set<string> gatherTokens(const string& text) {
  // TODO student
  return {};
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
