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

TEST(consume_token, CurrentTokenIsNull) {
  t_token_list *token_list = nullptr;

  EXPECT_FALSE(consume_token(&token_list));

  destroy_token_list(token_list);
}

TEST(handle_parse_status, ParseSuccess) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_ast *result = handle_parse_status(node, PARSE_SUCCESS);

  EXPECT_EQ(result, node);

  destroy_ast(result);
}

TEST(handle_parse_status, ParseFailure) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_ast *result = handle_parse_status(node, PARSE_FAILURE);

  EXPECT_EQ(result, nullptr);
}

TEST(handle_parse_status, ParseAbort) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);

  t_ast *result = handle_parse_status(node, PARSE_ABORT);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->type, AST_ABORT);
  EXPECT_EQ(result->left, nullptr);
  EXPECT_EQ(result->right, nullptr);

  destroy_ast(result);
}

TEST(handle_parse_status, ComplexTreeHandling) {
  t_ast *left = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_ast *right = construct_ast(AST_PIPE, nullptr, nullptr);
  t_ast *node = construct_ast(AST_AND, left, right);

  t_ast *result = handle_parse_status(node, PARSE_ABORT);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->type, AST_ABORT);
  EXPECT_EQ(result->left, nullptr);
  EXPECT_EQ(result->right, nullptr);

  destroy_ast(result);
}
