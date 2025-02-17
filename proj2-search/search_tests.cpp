#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "include/search.h"

using namespace std;
using namespace testing;

TEST(CleanToken, OneChar) {
  ASSERT_THAT(cleanToken("A"), StrEq("a"));
  ASSERT_THAT(cleanToken("+"), StrEq(""));
  ASSERT_THAT(cleanToken("B"), StrEq("b"));
}

TEST(CleanToken, PunctStartEnd) {
  ASSERT_THAT(cleanToken(",,hithere,,"), StrEq("hithere"));
  ASSERT_THAT(cleanToken("!!!!youfool!!!"), StrEq("youfool"));
  ASSERT_THAT(cleanToken("...ethan..."), StrEq("ethan"));
}

TEST(CleanToken, PunctInMiddle) {
  ASSERT_THAT(cleanToken("hi,,there"), StrEq("hi,,there"));
  ASSERT_THAT(cleanToken("yeat.....andcart"), StrEq("yeat.....andcart"));
  ASSERT_THAT(cleanToken("New..York..City"), StrEq("new..york..city"));
}

TEST(CleanToken, MiddleStart) {
  ASSERT_THAT(cleanToken(",,,hi,(&%(7)@($)),there"), StrEq("hi,(&%(7)@($)),there"));
  ASSERT_THAT(cleanToken(",,,you!!!fool"), StrEq("you!!!fool"));
  ASSERT_THAT(cleanToken(",,,make...files"), StrEq("make...files"));
}

TEST(CleanToken, MiddleEnd) {
  ASSERT_THAT(cleanToken("hi,(&%(7)@($)),there,,,"), StrEq("hi,(&%(7)@($)),there"));
  ASSERT_THAT(cleanToken("you!!!fool,,,"), StrEq("you!!!fool"));
  ASSERT_THAT(cleanToken("make...files,,,"), StrEq("make...files"));
}

TEST(GatherTokens, LeadingSpaces) {
  string token = "   hi how are you?";
  set<string> res_set = {"hi", "how", "are","you"};
  ASSERT_THAT(gatherTokens(token), ContainerEq(res_set));
  token = "     hi how are you?";
  ASSERT_THAT(gatherTokens(token), ContainerEq(res_set));
  token = "   where are my birkenstocks?";
  res_set = {"where", "are", "my","birkenstocks"};
  ASSERT_THAT(gatherTokens(token), ContainerEq(res_set));
}

TEST(GatherTokens, TrailingSpaces) {
  string token = "hi how are you?   ";
  set<string> res_set = {"hi", "how", "are","you"};
  ASSERT_THAT(gatherTokens(token), ContainerEq(res_set));
  token = "hi how are you?       ";
  ASSERT_THAT(gatherTokens(token), ContainerEq(res_set));
  token = "where are my birkenstocks?       ";
  res_set = {"where", "are", "my","birkenstocks"};
  ASSERT_THAT(gatherTokens(token), ContainerEq(res_set));
}

TEST(GatherTokens, SpacesInBetween) {
  string token = "hi   how     are      you?";
  set<string> res_set = {"hi", "how", "are","you"};
  ASSERT_THAT(gatherTokens(token), ContainerEq(res_set));
  token = "new      york     city";
  res_set = {"new", "york", "city"};
  ASSERT_THAT(gatherTokens(token), ContainerEq(res_set));
  token = "four   five   six   train   east     harlem";
  res_set = {"four", "five", "six", "train", "east", "harlem"};
  ASSERT_THAT(gatherTokens(token), ContainerEq(res_set));
}

TEST(BuildIndex, TinyTxt) {
  string filename = "data/tiny.txt";
  map<string, set<string>> expectedIndex = {
      {"eggs", {"www.shoppinglist.com"}},
      {"milk", {"www.shoppinglist.com"}},
      {"fish", {"www.shoppinglist.com","www.dr.seuss.net"}},
      {"bread", {"www.shoppinglist.com"}},
      {"cheese", {"www.shoppinglist.com"}},
      {"red", {"www.rainbow.org",{"www.dr.seuss.net"}}},
      {"gre-en", {"www.rainbow.org"}},
      {"orange", {"www.rainbow.org"}},
      {"yellow", {"www.rainbow.org"}},
      {"blue", {"www.rainbow.org","www.dr.seuss.net"}},
      {"indigo", {"www.rainbow.org"}},
      {"violet", {"www.rainbow.org"}},
      {"one", {"www.dr.seuss.net"}},
      {"two", {"www.dr.seuss.net"}},
      {"i'm", {"www.bigbadwolf.com"}},
      {"not", {"www.bigbadwolf.com"}},
      {"trying", {"www.bigbadwolf.com"}},
      {"to", {"www.bigbadwolf.com"}},
      {"eat", {"www.bigbadwolf.com"}},
      {"you", {"www.bigbadwolf.com"}},
  };
  map<string, set<string>> studentIndex;
  int studentNumProcesed = buildIndex(filename, studentIndex);

  string indexTestFeedback =
      "buildIndex(\"" + filename + "\", ...) index incorrect\n";
  EXPECT_THAT(studentIndex, ContainerEq(expectedIndex)) << indexTestFeedback;

  string retTestFeedback =
      "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
  EXPECT_THAT(studentNumProcesed, Eq(4)) << retTestFeedback;
}

TEST(BuildIndex, InvalidFile) {
  string filename = "ethan.txt";
  map<string, set<string>> expected;
  int count = buildIndex(filename, expected);
  EXPECT_TRUE(expected.empty());
}

map<string, set<string>> INDEX = {
    {"hello", {"example.com", "uic.edu"}},
    {"there", {"example.com"}},
    {"according", {"uic.edu"}},
    {"to", {"uic.edu"}},
    {"all", {"example.com", "uic.edu", "random.org"}},
    {"known", {"uic.edu"}},
    {"laws", {"random.org"}},
    {"of", {"random.org"}},
    {"mohan", {"mohan.org","uic.edu"}},
    {"dizzler",{"uic.edu","random.org"}},
    {"desai", {"luckydsgamingcafe.com"}},
    {"dating", {"luckydsgamingcafe.com", "random.org"}},
    {"aviation", {"random.org"}},
    {"a", {"uic.edu", "random.org"}},
    {"no", {"uic.edu"}},
};

TEST(FindQueryMatches, FirstItemNoExist) {
  set<string> expected;

  expected = {"uic.edu","random.org"};
  EXPECT_THAT(findQueryMatches(INDEX, "ethan known to aviation"),
              ContainerEq(expected));
  
  expected = {"random.org","luckydsgamingcafe.com"};
  EXPECT_THAT(findQueryMatches(INDEX, "harsh desai laws of dating"),
              ContainerEq(expected));
}

TEST(FindQueryMatches, LaterItemNoExist) {
  set<string> expected;

  expected = {"uic.edu"};
  EXPECT_THAT(findQueryMatches(INDEX, "dizzler +mohan -aura"),
              ContainerEq(expected));
  
  expected = {"mohan.org","uic.edu"};
  EXPECT_THAT(findQueryMatches(INDEX, "known to all +greatest mohan"),
              ContainerEq(expected));

  expected = {"random.org","uic.edu"};
  EXPECT_THAT(findQueryMatches(INDEX, "laws of no play according to dizzler"),
              ContainerEq(expected));
}

// TEST(FindQueryMatches, LongCombinedQueries) {
//   set<string> expected;

//   expected = {"example.com"};
//   EXPECT_THAT(findQueryMatches(INDEX, "there laws aviation -to +hello"),
//               ContainerEq(expected));

//   expected = {};
//   EXPECT_THAT(findQueryMatches(INDEX, "all -all +all"), ContainerEq(expected));

//   expected = {"example.com", "uic.edu", "random.org"};
//   EXPECT_THAT(findQueryMatches(INDEX, "all -all +all all"),
//               ContainerEq(expected));
// }