// Copyright 2024, reasuke

#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "libft.h"
#include "parser.h"
#include "parser/parser_internal.h"
#include "token.h"
}

TEST(consume_token, MultipleTokens) {
  t_token_list *token_list = nullptr;

  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("src")));

  EXPECT_EQ(get_token_type(token_list), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token_list), "ls");
  EXPECT_EQ(consume_token(&token_list, TOKEN_WORD), true);
  EXPECT_EQ(get_token_type(token_list), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token_list), "-l");
  EXPECT_EQ(consume_token(&token_list, TOKEN_WORD), true);
  EXPECT_EQ(get_token_type(token_list), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token_list), "src");
  EXPECT_EQ(consume_token(&token_list, TOKEN_WORD), true);
  EXPECT_EQ(token_list, nullptr);

  destroy_token_list(token_list);
}
