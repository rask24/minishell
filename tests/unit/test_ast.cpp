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

TEST(push_cmd_arg, OneArg) {
  t_ast *ast = construct_ast(AST_COMMAND, nullptr, nullptr);

  push_cmd_arg(ast, "ls");

  EXPECT_STREQ(get_cmd_arg(ast->cmd_args), "ls");

  destroy_ast(ast);
}

TEST(push_cmd_arg, MultipleArgs) {
  t_ast *ast = construct_ast(AST_COMMAND, nullptr, nullptr);

  push_cmd_arg(ast, "ls");
  push_cmd_arg(ast, "-l");
  push_cmd_arg(ast, "-a");

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

TEST(construct_ast, ComplexNodes) {
  t_ast *left = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_ast *right = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_ast *ast = construct_ast(AST_PIPE, left, right);

  push_cmd_arg(left, "ls");
  push_cmd_arg(left, "-l");
  push_cmd_arg(left, "-a");
  push_cmd_arg(right, "cat");
  push_cmd_arg(right, "file.txt");

  t_redirect_info *info_1 =
      construct_redirect_info(REDIRECT_INPUT, "input.txt");
  t_redirect_info *info_2 =
      construct_redirect_info(REDIRECT_OUTPUT, "output.txt");

  push_redirect_info(left, info_1);
  push_redirect_info(right, info_2);

  EXPECT_EQ(ast->type, AST_PIPE);
  EXPECT_EQ(ast->left, left);
  EXPECT_EQ(ast->right, right);

  EXPECT_STREQ(get_cmd_arg(left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(left->cmd_args->next), "-l");
  EXPECT_STREQ(get_cmd_arg(left->cmd_args->next->next), "-a");
  EXPECT_STREQ(get_cmd_arg(right->cmd_args), "cat");
  EXPECT_STREQ(get_cmd_arg(right->cmd_args->next), "file.txt");

  EXPECT_EQ(get_redirect_type(left->redirects), REDIRECT_INPUT);
  EXPECT_STREQ(get_redirect_filename(left->redirects), "input.txt");
  EXPECT_EQ(get_redirect_type(right->redirects), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filename(right->redirects), "output.txt");

  destroy_ast(ast);
}

TEST(get_cmd_arg, NullCmdArgs) {
  t_list *cmd_args = nullptr;

  EXPECT_EQ(get_cmd_arg(cmd_args), nullptr);
}

TEST(get_redirect_type, NullRedirects) {
  t_list *redirects = nullptr;

  EXPECT_EQ(get_redirect_type(redirects), REDIRECT_UNKNOWN);
}

TEST(get_redirect_filename, NullRedirects) {
  t_list *redirects = nullptr;

  EXPECT_EQ(get_redirect_filename(redirects), nullptr);
}

TEST(push_cmd_arg, InvalidNodeType) {
  t_ast *ast = construct_ast(AST_PIPE, nullptr, nullptr);

  push_cmd_arg(ast, "ls");
  EXPECT_EQ(ast->cmd_args, nullptr);
}

TEST(push_redirect_info, InvalidNodeType) {
  t_ast *ast = construct_ast(AST_PIPE, nullptr, nullptr);
  t_redirect_info *info = construct_redirect_info(REDIRECT_INPUT, "input.txt");

  push_redirect_info(ast, info);
  EXPECT_EQ(ast->redirects, nullptr);
}
