#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "token.h"
}

TEST(construct_token, CheckOneToken) {
  t_token_list *token = construct_token(TOKEN_WORD, strdup("ls"));

  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");

  destroy_token(token);
}

TEST(construct_token, CheckMultipleTokens) {
  t_token_list *list = NULL;

  // ls && cat
  t_token_list *token = construct_token(TOKEN_WORD, strdup("ls"));
  t_token_list *token1 = construct_token(TOKEN_AND_IF, strdup("&&"));
  t_token_list *token2 = construct_token(TOKEN_WORD, strdup("cat"));

  ft_lstadd_back(&list, token);
  ft_lstadd_back(&list, token1);
  ft_lstadd_back(&list, token2);

  // ls
  EXPECT_EQ(get_token_type(list), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(list), "ls");

  // &&
  EXPECT_EQ(get_token_type(list->next), TOKEN_AND_IF);
  EXPECT_STREQ(get_token_value(list->next), "&&");

  // cat
  EXPECT_EQ(get_token_type(list->next->next), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(list->next->next), "ca");

  destroy_token_list(list);
}
