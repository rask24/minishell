// Copyright 2024, reasuke

#include "gtest/gtest.h"

extern "C" {
#include "ast.h"
}

TEST(construct_ast, OneNode) {
  t_ast *ast = construct_ast(AST_COMMAND, nullptr, nullptr);

  EXPECT_EQ(ast->type, AST_COMMAND);
  EXPECT_EQ(ast->left, nullptr);
  EXPECT_EQ(ast->right, nullptr);
  EXPECT_EQ(ast->cmd_args, nullptr);
  EXPECT_EQ(ast->redirects, nullptr);
}

TEST(construct_ast, MultipleNodes) {
  t_ast *left = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_ast *right = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_ast *ast = construct_ast(AST_PIPE, left, right);

  EXPECT_EQ(ast->type, AST_PIPE);
  EXPECT_EQ(ast->left, left);
  EXPECT_EQ(ast->right, right);
  EXPECT_EQ(ast->cmd_args, nullptr);
  EXPECT_EQ(ast->redirects, nullptr);
}

TEST(push_cmd_args, OneArg) {
  t_ast *ast = construct_ast(AST_COMMAND, nullptr, nullptr);

  push_cmd_args(ast, "ls");

  EXPECT_STREQ(get_cmd_arg(ast->cmd_args), "ls");
}

TEST(push_cmd_args, MultipleArgs) {
  t_ast *ast = construct_ast(AST_COMMAND, nullptr, nullptr);

  push_cmd_args(ast, "ls");
  push_cmd_args(ast, "-l");
  push_cmd_args(ast, "-a");

  EXPECT_STREQ(get_cmd_arg(ast->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(ast->cmd_args->next), "-l");
  EXPECT_STREQ(get_cmd_arg(ast->cmd_args->next->next), "-a");
}
