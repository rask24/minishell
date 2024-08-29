#include "gtest/gtest.h"

extern "C" {
#include "lexer.h"
}

TEST(ft_xrealloc, CheckRealloc) {
  t_token_buffer token_buffer = {.str = (char *)malloc(1), .len = 0, .cap = 1};

  ft_xrealloc(&token_buffer);
  EXPECT_EQ(token_buffer.cap, (size_t)2);

  ft_xrealloc(&token_buffer);
  EXPECT_EQ(token_buffer.cap, (size_t)4);
}

TEST(push_back_char, CheckPushBack) {
  t_token_buffer token_buffer = {.str = (char *)malloc(1), .len = 0, .cap = 1};

  push_back_char(&token_buffer, 'l');
  push_back_char(&token_buffer, 's');
  EXPECT_STREQ(token_buffer.str, "ls");
  EXPECT_EQ(token_buffer.len, (size_t)2);
  EXPECT_EQ(token_buffer.cap, (size_t)4);
}

TEST(store_to_buffer_statefully, store_buffer) {
  t_token_buffer token_buffer = {.str = (char *)malloc(1), .len = 0, .cap = 1};

  t_token_list *token = store_to_buffer_statefully(&token_buffer, 'l');
  EXPECT_EQ(token, nullptr);

  token = store_to_buffer_statefully(&token_buffer, 's');
  EXPECT_EQ(get_token_type(token), TOKEN_WORD);
  EXPECT_STREQ(get_token_value(token), "ls");
}
