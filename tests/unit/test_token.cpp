#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "token.h"
}

TEST(CheckToken, CheckOneToken) {
  t_token_list *token = construct_token(TOKEN_WORD, strdup("ls"));

  t_token *current = (t_token *)token->content;
  EXPECT_STREQ(current->value, "ls");
  EXPECT_EQ(current->type, TOKEN_WORD);

  destroy_token(token);
}

  t_token_list *list = NULL;

  // ls && cat
  t_token_list *token = construct_token(TOKEN_WORD, strdup("ls"));
  t_token_list *token1 = construct_token(TOKEN_AND_IF, strdup("&&"));
  t_token_list *token2 = construct_token(TOKEN_WORD, strdup("cat"));

  ft_lstadd_back(&list, token);
  ft_lstadd_back(&list, token1);
  ft_lstadd_back(&list, token2);

  t_token *current = (t_token *)list->content;
  EXPECT_STREQ(current->value, "ls");
  EXPECT_EQ(current->type, TOKEN_WORD);

  EXPECT_EQ(ft_lstsize(list), 3);

  destroy_token_list(list);
}
