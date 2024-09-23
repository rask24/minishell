// Copyright 2024, reasuke

#include "gtest/gtest.h"
#include "utils_parser.hpp"

extern "C" {
#include "ast.h"
#include "parser/parser_internal.h"
#include "token.h"
}

TEST(parse_pipeline, SimpleCommand) {
  // ls -l
  t_token_list *token_list = construct_token_list(
      {{TOKEN_WORD, "ls"}, {TOKEN_WORD, "-l"}, {TOKEN_EOF, nullptr}});

  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->cmd_args->next), "-l");
  EXPECT_EQ(node->redirects, nullptr);

  destroy_ast(node);
  destroy_token_list(token_list);
}

TEST(parse_pipeline, OnePipeline) {
  // ls -l | wc
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_WORD, "wc"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node->type, AST_PIPE);
  EXPECT_EQ(node->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args->next), "-l");
  EXPECT_EQ(node->left->redirects, nullptr);
  EXPECT_EQ(node->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->right->cmd_args), "wc");
  EXPECT_EQ(node->right->redirects, nullptr);

  destroy_ast(node);
  destroy_token_list(token_list);
}

TEST(parse_pipeline, MultiplePipelines) {
  // ls -l | wc | cat -e
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_WORD, "wc"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_WORD, "cat"},
                                                   {TOKEN_WORD, "-e"},
                                                   {TOKEN_EOF, nullptr}});

  /*
  **                    PIPE
  **                   |    \
  **                 PIPE  COMMAND (cat -e)
  **                |    \
  **   COMMAND(ls -l) COMMAND (wc)
  */
  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node->type, AST_PIPE);

  EXPECT_EQ(node->left->type, AST_PIPE);
  EXPECT_EQ(node->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->right->cmd_args), "cat");
  EXPECT_STREQ(get_cmd_arg(node->right->cmd_args->next), "-e");
  EXPECT_STREQ(get_cmd_arg(node->right->cmd_args->next->next), nullptr);

  EXPECT_EQ(node->left->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->left->cmd_args->next), "-l");
  EXPECT_STREQ(get_cmd_arg(node->left->left->cmd_args->next->next), nullptr);
  EXPECT_EQ(node->left->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->right->cmd_args), "wc");
  EXPECT_STREQ(get_cmd_arg(node->left->right->cmd_args->next), nullptr);

  destroy_ast(node);
  destroy_token_list(token_list);
}

TEST(parse_pipeline, MultiplePipelinesWithSubshells) {
  // (ls -l) | (cat -e) > out.txt
  t_token_list *token_list = construct_token_list({{TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "cat"},
                                                   {TOKEN_WORD, "-e"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out.txt"},
                                                   {TOKEN_EOF, nullptr}});

  /*
  **                PIPE
  **               |    \
  **   SUBSHELL(ls -l)  SUBSHELL(cat -e > out.txt)
  **     |                   |
  **  COMMAND(ls -l)     COMMAND(cat -e)
  */
  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node->type, AST_PIPE);

  EXPECT_EQ(node->left->type, AST_SUBSHELL);

  EXPECT_EQ(node->right->type, AST_SUBSHELL);
  EXPECT_EQ(get_redirect_type(node->right->redirects), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->right->redirects), "out.txt");
  EXPECT_EQ(node->right->redirects->next, nullptr);

  EXPECT_EQ(node->left->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->left->cmd_args->next), "-l");
  EXPECT_EQ(node->left->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->left->left->redirects, nullptr);

  EXPECT_EQ(node->right->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->right->left->cmd_args), "cat");
  EXPECT_STREQ(get_cmd_arg(node->right->left->cmd_args->next), "-e");
  EXPECT_EQ(node->right->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->right->left->redirects, nullptr);

  destroy_ast(node);
  destroy_token_list(token_list);
}

TEST(parse_pipeline, InvalidToken) {
  // ls -l |
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}

TEST(parse_pipline, InvalidTokenPipe) {
  // (ls -l ) |
  t_token_list *token_list = construct_token_list({{TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}
