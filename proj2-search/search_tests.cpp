#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "include/search.h"

using namespace std;
using namespace testing;

TEST(CleanToken, OneLetter) {
  string token = "D";
  string res_token = "d";
  EXPECT_THAT(cleanToken(token), StrEq(res_token))
      << "token=\"" << token << "\"";

}

TEST(CleanToken, PunctInBetween) {
  string token = ",,,hi,,there,,,";
  string res_token = "hi,,there";
  EXPECT_THAT(cleanToken(token), StrEq(res_token))
      << "token=\"" << token << "\"";

}

TEST(CleanToken, NumLetter) {
  string token = ",,,223A";
  string res_token = "223a";
  EXPECT_THAT(cleanToken(token), StrEq(res_token))
      << "token=\"" << token << "\"";

}
