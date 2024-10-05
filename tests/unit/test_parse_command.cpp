// Copyright 2024, reasuke

#include "gtest/gtest.h"
#include "utils_parser.hpp"

extern "C" {
#include "ast.h"
#include "parser/parser_internal.h"
#include "token.h"
}

TEST(parse_command, SimpleCommand) {
  // ls -l
  t_token_list *token_list = construct_token_list(
      {{TOKEN_WORD, "ls"}, {TOKEN_WORD, "-l"}, {TOKEN_EOF, nullptr}});

  t_ast *node = parse_command(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->cmd_args->next), "-l");
  EXPECT_EQ(node->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->redirects, nullptr);

  destroy_ast(node);
  destroy_token_list(token_list);
}

TEST(parse_command, OneSubshell) {
  // (ls -l)
  t_token_list *token_list = construct_token_list({{TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_command(&token_list);

  /*
  **  SUBSHELL
  **     |
  **  COMMAND(ls -l)
  */
  EXPECT_EQ(node->type, AST_SUBSHELL);
  EXPECT_EQ(node->redirects, nullptr);

  EXPECT_EQ(node->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args->next), "-l");
  EXPECT_EQ(node->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->left->redirects, nullptr);

  destroy_ast(node);
  destroy_token_list(token_list);
}

TEST(parse_command, OneSubshellWithOneRedirect) {
  // (ls -l) > out.txt
  t_token_list *token_list = construct_token_list({{TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out.txt"},
                                                   {TOKEN_EOF, nullptr}});

  /*
  **  SUBSHELL(> out.txt)
  **     |
  **  COMMAND(ls -l)
  */
  t_ast *node = parse_command(&token_list);

  EXPECT_EQ(node->type, AST_SUBSHELL);
  EXPECT_STREQ(get_redirect_file_or_delim(node->redirects), "out.txt");
  EXPECT_EQ(get_redirect_type(node->redirects), REDIRECT_OUTPUT);

  EXPECT_EQ(node->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args->next), "-l");
  EXPECT_EQ(node->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->left->redirects, nullptr);

  EXPECT_EQ(node->right, nullptr);

  destroy_ast(node);
  destroy_token_list(token_list);
}

TEST(parse_command, OneSubsellWithMultipleRedirects) {
  // (ls -l) > out1.txt >> out2.txt
  t_token_list *token_list = construct_token_list({{TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out1.txt"},
                                                   {TOKEN_DGREAT, ">>"},
                                                   {TOKEN_WORD, "out2.txt"},
                                                   {TOKEN_EOF, nullptr}});

  /*
  ** SUBSHELL(> out1.txt >> out2.txt)
  **     |
  **  COMMAND(ls -l)
  */
  t_ast *node = parse_command(&token_list);

  EXPECT_EQ(node->type, AST_SUBSHELL);
  EXPECT_STREQ(get_redirect_file_or_delim(node->redirects), "out1.txt");
  EXPECT_EQ(get_redirect_type(node->redirects), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_file_or_delim(node->redirects->next), "out2.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next), REDIRECT_APPEND);
  EXPECT_EQ(node->redirects->next->next, nullptr);

  EXPECT_EQ(node->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args->next), "-l");
  EXPECT_EQ(node->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->left->redirects, nullptr);

  EXPECT_EQ(node->right, nullptr);

  destroy_ast(node);
  destroy_token_list(token_list);
}

TEST(parse_command, MultipleSubshells) {
  // ((ls -l))
  t_token_list *token_list = construct_token_list({{TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_EOF, nullptr}});

  /*
  **  SUBSHELL
  **     |
  **  SUBSHELL
  **     |
  **  COMMAND(ls -l)
  */
  t_ast *node = parse_command(&token_list);

  EXPECT_EQ(node->type, AST_SUBSHELL);
  EXPECT_EQ(node->redirects, nullptr);

  EXPECT_EQ(node->left->type, AST_SUBSHELL);
  EXPECT_EQ(node->left->redirects, nullptr);

  EXPECT_EQ(node->right, nullptr);

  EXPECT_EQ(node->left->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->left->cmd_args->next), "-l");
  EXPECT_EQ(node->left->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->left->left->redirects, nullptr);

  EXPECT_EQ(node->left->right, nullptr);

  destroy_ast(node);
  destroy_token_list(token_list);
}

TEST(parse_command, UnclosedParenthesis) {
  // (ls -l
  t_token_list *token_list = construct_token_list({{TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_command(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}

TEST(parse_command, InvalidTokenPipe) {
  // (ls -l | )
  t_token_list *token_list = construct_token_list({{TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_command(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}

TEST(parse_command, InvalidTokenRedirect) {
  // (ls -l ) >
  t_token_list *token_list = construct_token_list({{TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_command(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}
