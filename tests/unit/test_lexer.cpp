#include "gtest/gtest.h"

extern "C" {
#include "lexer.h"
}

TEST(lexer, OneWord) {
  const char *str = "ls";

  t_token_list *token = lexer(str);
  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");
}

TEST(lexer, WordSpaceWord) {
  const char *str = "ls -l";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");

  EXPECT_EQ(get_token_type(token->next), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token->next), "-l");
}

TEST(lexer, WordTabWord) {
  const char *str = "ls\t-l";

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

  EXPECT_EQ(get_token_type(token), TOKEN_EOF);
}

TEST(lexer, EmptyString) {
  const char *str = "";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_EOF);
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

TEST(lexer, ConsecutiveQuotes) {
  const char *str = "'hello'' world'";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "'hello'' world'");
}

TEST(lexer, ConsecutiveQuotes1) {
  const char *str = "'hello''world'";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "'hello''world'");
}

TEST(lexer, ConsecutiveQuotes2) {
  const char *str = "'hello'\"world\"";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "'hello'\"world\"");
}

TEST(lexer, ConsecutiveQuotes3) {
  const char *str = "\"hello\"'world'";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "\"hello\"'world'");
}

TEST(lexer, ConsecutiveQuotes4) {
  const char *str = "'hello'' ''world'";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "'hello'' ''world'");
}

TEST(lexer, Operator) {
  const char *str = "|";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_PIPE);
  EXPECT_STREQ(get_token_value(token), "|");
}

TEST(lexer, WordsOperatorWords) {
  const char *str = "ls|wc";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");

  EXPECT_EQ(get_token_type(token->next), TOKEN_PIPE);
  EXPECT_STREQ(get_token_value(token->next), "|");

  EXPECT_EQ(get_token_type(token->next->next), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token->next->next), "wc");
}

TEST(lexer, WordsSpaceOperatorSpaceWords) {
  const char *str = "ls | wc";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");

  EXPECT_EQ(get_token_type(token->next), TOKEN_PIPE);
  EXPECT_STREQ(get_token_value(token->next), "|");

  EXPECT_EQ(get_token_type(token->next->next), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token->next->next), "wc");
}

TEST(lexer, LotsOfOperators) {
  const char *str = "ls |||||   wc>>whoami<<< (ls)) cat &&>|| echo";
  std::vector<std::pair<t_token_type, const char *>> expected_token_array = {
      {TOKEN_WORD, "ls"},         {TOKEN_OR_IF, "||"},
      {TOKEN_OR_IF, "||"},        {TOKEN_PIPE, "|"},
      {TOKEN_WORD, "wc"},         {TOKEN_DGREAT, ">>"},
      {TOKEN_WORD, "whoami"},     {TOKEN_DLESS, "<<"},
      {TOKEN_LESS, "<"},          {TOKEN_L_PARENTHESIS, "("},
      {TOKEN_WORD, "ls"},         {TOKEN_R_PARENTHESIS, ")"},
      {TOKEN_R_PARENTHESIS, ")"}, {TOKEN_WORD, "cat"},
      {TOKEN_AND_IF, "&&"},       {TOKEN_GREAT, ">"},
      {TOKEN_OR_IF, "||"},        {TOKEN_WORD, "echo"},
  };

  t_token_list *token = lexer(str);

  int i = 0;
  while (get_token_type(token) != TOKEN_EOF) {
    EXPECT_EQ(get_token_type(token), expected_token_array[i].first);
    EXPECT_STREQ(get_token_value(token), expected_token_array[i].second);
    token = token->next;
    i++;
  }
}

TEST(lexer, RealCommentOut) {
  const char *str = "ls # hello world";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");

  token = token->next;
  EXPECT_EQ(get_token_type(token), TOKEN_EOF);
}

TEST(lexer, FakeCommentOut) {
  const char *str = "ls#hello world";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls#hello");
}

TEST(lexer, Ampersand) {
  const char *str = "ls &";

  t_token_list *token = lexer(str);

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");

  EXPECT_EQ(get_token_type(token->next), TOKEN_UNKNOWN);
  EXPECT_STREQ(get_token_value(token->next), "&");
}
