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
  const char *str = "ls |    wc>>whoami<<< (ls)) cat || echo";
  t_token_type expected_token_array[] = {
      TOKEN_WORD,          TOKEN_PIPE,          TOKEN_WORD,
      TOKEN_DGREAT,        TOKEN_WORD,          TOKEN_DLESS,
      TOKEN_LESS,          TOKEN_L_PARENTHESIS, TOKEN_WORD,
      TOKEN_R_PARENTHESIS, TOKEN_R_PARENTHESIS, TOKEN_WORD,
      TOKEN_OR_IF,         TOKEN_WORD,          TOKEN_EOF};

  const char *expected_value_array[] = {"ls", "|",   "wc", ">>",  "whoami",
                                        "<<", "<",   "(",  "ls",  ")",
                                        ")",  "cat", "||", "echo"};

  t_token_list *token = lexer(str);

  int i = 0;
  while (get_token_type(token) != TOKEN_EOF) {
    EXPECT_EQ(get_token_type(token), expected_token_array[i]);
    EXPECT_STREQ(get_token_value(token), expected_value_array[i]);
    token = token->next;
    i++;
  }
}
