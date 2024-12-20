// Copyright 2024, reasuke

#include "gtest/gtest.h"

extern "C" {
#include "ast.h"
}

TEST(construct_ast, OneNode) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_EQ(node->left, nullptr);
  EXPECT_EQ(node->right, nullptr);
  EXPECT_EQ(node->cmd_args, nullptr);
  EXPECT_EQ(node->redirects, nullptr);

  destroy_ast(node);
}

TEST(construct_ast, MultipleNodes) {
  t_ast *left = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_ast *right = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_ast *node = construct_ast(AST_PIPE, left, right);

  EXPECT_EQ(node->type, AST_PIPE);
  EXPECT_EQ(node->left, left);
  EXPECT_EQ(node->right, right);
  EXPECT_EQ(node->cmd_args, nullptr);
  EXPECT_EQ(node->redirects, nullptr);

  destroy_ast(node);
}

TEST(push_cmd_arg, OneArg) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);

  push_cmd_arg(node, strdup("ls"));

  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "ls");

  destroy_ast(node);
}

TEST(push_cmd_arg, MultipleArgs) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);

  push_cmd_arg(node, strdup("ls"));
  push_cmd_arg(node, strdup("-l"));
  push_cmd_arg(node, strdup("-a"));

  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->cmd_args->next), "-l");
  EXPECT_STREQ(get_cmd_arg(node->cmd_args->next->next), "-a");

  destroy_ast(node);
}

TEST(get_heredoc_fd, NullRedirects) {
  t_list *redirects = nullptr;

  EXPECT_EQ(get_heredoc_fd(redirects), -1);
}

TEST(push_redirect_info, OneRedirect) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_redirect_info *info = construct_redirect_info(REDIRECT_INPUT, "input.txt");

  push_redirect_info(node, info);

  EXPECT_EQ(get_redirect_type(node->redirects), REDIRECT_INPUT);
  EXPECT_STREQ(get_redirect_file_or_delim(node->redirects), "input.txt");

  destroy_ast(node);
}

TEST(push_redirect_info, MultipleRedirects) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_redirect_info *info_1 =
      construct_redirect_info(REDIRECT_INPUT, "input.txt");
  t_redirect_info *info_2 =
      construct_redirect_info(REDIRECT_OUTPUT, "output.txt");

  push_redirect_info(node, info_1);
  push_redirect_info(node, info_2);

  EXPECT_EQ(get_redirect_type(node->redirects), REDIRECT_INPUT);
  EXPECT_STREQ(get_redirect_file_or_delim(node->redirects), "input.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_file_or_delim(node->redirects->next), "output.txt");

  destroy_ast(node);
}

TEST(push_redirect_info, NullRedirectInfo) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);

  push_redirect_info(node, nullptr);

  EXPECT_EQ(node->redirects, nullptr);

  destroy_ast(node);
}

TEST(construct_ast, ComplexNodes) {
  t_ast *left = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_ast *right = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_ast *node = construct_ast(AST_PIPE, left, right);

  push_cmd_arg(left, strdup("ls"));
  push_cmd_arg(left, strdup("-l"));
  push_cmd_arg(left, strdup("-a"));
  push_cmd_arg(right, strdup("cat"));
  push_cmd_arg(right, strdup("file.txt"));

  t_redirect_info *info_1 =
      construct_redirect_info(REDIRECT_INPUT, "input.txt");
  t_redirect_info *info_2 =
      construct_redirect_info(REDIRECT_OUTPUT, "output.txt");

  push_redirect_info(left, info_1);
  push_redirect_info(right, info_2);

  EXPECT_EQ(node->type, AST_PIPE);
  EXPECT_EQ(node->left, left);
  EXPECT_EQ(node->right, right);

  EXPECT_STREQ(get_cmd_arg(left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(left->cmd_args->next), "-l");
  EXPECT_STREQ(get_cmd_arg(left->cmd_args->next->next), "-a");
  EXPECT_STREQ(get_cmd_arg(right->cmd_args), "cat");
  EXPECT_STREQ(get_cmd_arg(right->cmd_args->next), "file.txt");

  EXPECT_EQ(get_redirect_type(left->redirects), REDIRECT_INPUT);
  EXPECT_STREQ(get_redirect_file_or_delim(left->redirects), "input.txt");
  EXPECT_EQ(get_redirect_type(right->redirects), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_file_or_delim(right->redirects), "output.txt");

  destroy_ast(node);
}

TEST(get_cmd_arg, NullCmdArgs) {
  t_list *cmd_args = nullptr;

  EXPECT_EQ(get_cmd_arg(cmd_args), nullptr);
}

TEST(get_redirect_type, NullRedirects) {
  t_list *redirects = nullptr;

  EXPECT_EQ(get_redirect_type(redirects), REDIRECT_UNKNOWN);
}

TEST(get_redirect_file_or_delim, NullRedirects) {
  t_list *redirects = nullptr;

  EXPECT_EQ(get_redirect_file_or_delim(redirects), nullptr);
}

TEST(set_file_or_delim, NullRedirects) {
  t_list *redirects = nullptr;

  set_file_or_delim(redirects, "file.txt");
  EXPECT_EQ(redirects, nullptr);
}

TEST(set_file_or_delim, OneRedirect) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);
  t_redirect_info *info = construct_redirect_info(REDIRECT_INPUT, "input.txt");

  push_redirect_info(node, info);

  set_file_or_delim(node->redirects, strdup("file.txt"));

  EXPECT_STREQ(get_redirect_file_or_delim(node->redirects), "file.txt");

  destroy_ast(node);
}

TEST(push_cmd_arg, InvalidNodeType) {
  t_ast *node = construct_ast(AST_PIPE, nullptr, nullptr);

  push_cmd_arg(node, strdup("ls"));
  EXPECT_EQ(node->cmd_args, nullptr);
}

TEST(push_redirect_info, InvalidNodeType) {
  t_ast *node = construct_ast(AST_PIPE, nullptr, nullptr);
  t_redirect_info *info = construct_redirect_info(REDIRECT_INPUT, "input.txt");

  push_redirect_info(node, info);
  EXPECT_EQ(node->redirects, nullptr);
}

TEST(convert_cmd_args_to_array, NullCmdArgs) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);

  char **cmd_args = convert_cmd_args_to_array(node->cmd_args);

  EXPECT_EQ(cmd_args, nullptr);

  destroy_ast(node);
}

TEST(convert_cmd_args_to_array, OneArg) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);

  push_cmd_arg(node, strdup("ls"));

  char **cmd_args = convert_cmd_args_to_array(node->cmd_args);

  EXPECT_STREQ(cmd_args[0], "ls");
  EXPECT_EQ(cmd_args[1], nullptr);

  destroy_ast(node);
  ft_free_strs(cmd_args);
}

TEST(convert_cmd_args_to_array, MultipleArgs) {
  t_ast *node = construct_ast(AST_COMMAND, nullptr, nullptr);

  push_cmd_arg(node, strdup("ls"));
  push_cmd_arg(node, strdup("-l"));
  push_cmd_arg(node, strdup("-a"));

  char **cmd_args = convert_cmd_args_to_array(node->cmd_args);

  EXPECT_STREQ(cmd_args[0], "ls");
  EXPECT_STREQ(cmd_args[1], "-l");
  EXPECT_STREQ(cmd_args[2], "-a");
  EXPECT_EQ(cmd_args[3], nullptr);

  destroy_ast(node);
  ft_free_strs(cmd_args);
}
