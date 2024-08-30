#include "gtest/gtest.h"

extern "C" {
#include "lexer.h"
}

TEST(lexer, CheckTokenWord) {
  const char *str = "ls";

  t_token_list *token = lexer(str);
  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");
}

// TEST(lexer, CheckTokenWords) {
//   const char *str = "ls -l";

//   t_token_list *token = lexer(str);

//   EXPECT_EQ(get_token_type(token), TOKEN_WORD);
//   EXPECT_STREQ(get_token_value(token), "ls");

//   EXPECT_EQ(get_token_type(token->next), TOKEN_WORD);
//   EXPECT_STREQ(get_token_value(token->next), "-l");
// }
