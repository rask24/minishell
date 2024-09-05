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

  destroy_ast(ast);
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

  destroy_ast(ast);
}

TEST(push_cmd_args, OneArg) {
  t_ast *ast = construct_ast(AST_COMMAND, nullptr, nullptr);

  push_cmd_args(ast, "ls");

  EXPECT_STREQ(get_cmd_arg(ast->cmd_args), "ls");

  destroy_ast(ast);
}

TEST(push_cmd_args, MultipleArgs) {
  t_ast *ast = construct_ast(AST_COMMAND, nullptr, nullptr);

  push_cmd_args(ast, "ls");
  push_cmd_args(ast, "-l");
  push_cmd_args(ast, "-a");

  EXPECT_STREQ(get_cmd_arg(ast->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(ast->cmd_args->next), "-l");
  EXPECT_STREQ(get_cmd_arg(ast->cmd_args->next->next), "-a");

  destroy_ast(ast);
}

TEST(push_redirect_info, OneRedirect) {
  t_ast *ast = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_redirect_info *info = construct_redirect_info(REDIRECT_INPUT, "input.txt");

  push_redirect_info(ast, info);

  EXPECT_EQ(get_redirect_type(ast->redirects), REDIRECT_INPUT);
  EXPECT_STREQ(get_redirect_filename(ast->redirects), "input.txt");

  destroy_ast(ast);
}

TEST(push_redirect_info, MultipleRedirects) {
  t_ast *ast = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_redirect_info *info_1 =
      construct_redirect_info(REDIRECT_INPUT, "input.txt");
  t_redirect_info *info_2 =
      construct_redirect_info(REDIRECT_OUTPUT, "output.txt");

  push_redirect_info(ast, info_1);
  push_redirect_info(ast, info_2);

  EXPECT_EQ(get_redirect_type(ast->redirects), REDIRECT_INPUT);
  EXPECT_STREQ(get_redirect_filename(ast->redirects), "input.txt");
  EXPECT_EQ(get_redirect_type(ast->redirects->next), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filename(ast->redirects->next), "output.txt");

  destroy_ast(ast);
}
