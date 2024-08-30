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

TEST(lexer, CheckTokenWords) {
  const char *str = "ls -l";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");

  EXPECT_EQ(get_token_type(token->next), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token->next), "-l");
}

TEST(lexer, ManySpaces) {
  const char *str = "ls    -l";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");

  EXPECT_EQ(get_token_type(token->next), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token->next), "-l");
}

TEST(lexer, SpacesAfterWord) {
  const char *str = "ls -l  ";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");

  EXPECT_EQ(get_token_type(token->next), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token->next), "-l");
}

TEST(lexer, SpacesBeforeWord) {
  const char *str = "    ls -l";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");

  EXPECT_EQ(get_token_type(token->next), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token->next), "-l");
}

TEST(lexer, OnlySpaces) {
  const char *str = "    ";

  t_token_list *token = lexer(str);

  EXPECT_EQ(token, nullptr);
}

TEST(lexer, SingleQuote) {
  const char *str = "echo 'hello world'";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "echo");

  EXPECT_EQ(get_token_type(token->next), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token->next), "'hello world'");
}

TEST(lexer, DoubleQuote) {
  const char *str = "echo \"hello world\"";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "echo");

  EXPECT_EQ(get_token_type(token->next), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token->next), "\"hello world\"");
}

TEST(lexer, MixedQuote) {
  const char *str = "echo \"wendy's burger\" 'apple' is yummy ";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "echo");

  EXPECT_EQ(get_token_type(token->next), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token->next), "\"wendy's burger\"");

  EXPECT_EQ(get_token_type(token->next->next), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token->next->next), "'apple'");
}

TEST(lexer, QuoteInsideString) {
  const char *str = "e\"ch\"o";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "e\"ch\"o");
}

TEST(lexer, QuoteInsideQuote) {
  const char *str = "e'\"ch\"'o";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "e'\"ch\"'o");
}
