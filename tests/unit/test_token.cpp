#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "../include/token.h"
}

TEST(CheckToken, Check_token_list) {
  t_token_list *list = construct_token_list();

  // ls && cat
  t_token *token = construct_token(strdup("ls"), TOKEN_WORD);
  t_token *token1 = construct_token(strdup("&&"), TOKEN_AND_IF);
  t_token *token2 = construct_token(strdup("cat"), TOKEN_WORD);

  push_back_token(&list, token);
  push_back_token(&list, token1);
  push_back_token(&list, token2);

  t_token *current = (t_token *)list->content;
  EXPECT_STREQ(current->value, "ls");
  EXPECT_EQ(current->type, TOKEN_WORD);

  EXPECT_EQ(ft_lstsize(list), 3);

  destroy_token_list(list);
}
