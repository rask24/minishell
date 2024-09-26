// Copyright 2024, reasuke

#include "gtest/gtest.h"
#include "utils_parser.hpp"

extern "C" {
#include "parser/parser_internal.h"
#include "token.h"
}

TEST(consume_token, MultipleTokens) {
  // ls -l src
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_WORD, "src"},
                                                   {TOKEN_EOF, nullptr}});

  EXPECT_EQ(get_token_type(token_list), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token_list), "ls");
  EXPECT_TRUE(consume_token(&token_list));
  EXPECT_EQ(get_token_type(token_list), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token_list), "-l");
  EXPECT_TRUE(consume_token(&token_list));
  EXPECT_EQ(get_token_type(token_list), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token_list), "src");
  EXPECT_TRUE(consume_token(&token_list));
  EXPECT_EQ(get_token_type(token_list), TOKEN_EOF);
  EXPECT_TRUE(consume_token(&token_list));
  EXPECT_EQ(token_list, nullptr);

  destroy_token_list(token_list);
}

TEST(expect_token, MultipleTokens) {
  // ls -l src
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_WORD, "src"},
                                                   {TOKEN_EOF, nullptr}});

  EXPECT_EQ(get_token_type(token_list), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token_list), "ls");
  EXPECT_TRUE(expect_token(&token_list, TOKEN_WORD));
  EXPECT_EQ(get_token_type(token_list), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token_list), "-l");
  EXPECT_TRUE(expect_token(&token_list, TOKEN_WORD));
  EXPECT_EQ(get_token_type(token_list), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token_list), "src");
  EXPECT_TRUE(expect_token(&token_list, TOKEN_WORD));
  EXPECT_EQ(get_token_type(token_list), TOKEN_EOF);
  EXPECT_TRUE(expect_token(&token_list, TOKEN_EOF));
  EXPECT_EQ(token_list, nullptr);

  destroy_token_list(token_list);
}

TEST(consume_token, CurrentTokenIsNull) {
  t_token_list *token_list = nullptr;

  EXPECT_FALSE(consume_token(&token_list));

  destroy_token_list(token_list);
}

TEST(expect_token, CurrentTokenIsNull) {
  t_token_list *token_list = nullptr;

  EXPECT_FALSE(expect_token(&token_list, TOKEN_WORD));

  destroy_token_list(token_list);
}

TEST(expect_token, UnexpectedToken) {
  // ls > >>
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_DGREAT, ">>"},
                                                   {TOKEN_EOF, nullptr}});

  EXPECT_EQ(get_token_type(token_list), TOKEN_WORD);
  EXPECT_EQ(get_token_type(token_list->next), TOKEN_GREAT);
  EXPECT_EQ(get_token_type(token_list->next->next), TOKEN_DGREAT);
  // unexpected token
  EXPECT_FALSE(expect_token(&token_list->next->next, TOKEN_WORD));

  destroy_token_list(token_list);
}
