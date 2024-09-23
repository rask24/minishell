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

  /*
  **              PIPE
  **            |     \
  ** COMMAND(ls -l)   PIPE
  **                |      \
  **            COMMAND(wc) NULL
  */
  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node->type, AST_PIPE);

  EXPECT_EQ(node->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args->next), "-l");
  EXPECT_EQ(node->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->left->redirects, nullptr);

  EXPECT_EQ(node->right->type, AST_PIPE);

  EXPECT_EQ(node->right->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->right->left->cmd_args), "wc");
  EXPECT_EQ(node->right->left->cmd_args->next, nullptr);
  EXPECT_EQ(node->right->left->redirects, nullptr);

  EXPECT_EQ(node->right->right, nullptr);

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
  **             PIPE
  **            |    \
  **   CMD(ls -l)     PIPE
  **                |      \
  **           CMD(wc)     PIPE
  **                     |     \
  **              CMD(cat -e)  NULL
  */
  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node->type, AST_PIPE);

  EXPECT_EQ(node->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args->next), "-l");
  EXPECT_EQ(node->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->left->redirects, nullptr);

  EXPECT_EQ(node->right->type, AST_PIPE);

  EXPECT_EQ(node->right->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->right->left->cmd_args), "wc");
  EXPECT_EQ(node->right->left->cmd_args->next, nullptr);
  EXPECT_EQ(node->right->left->redirects, nullptr);

  EXPECT_EQ(node->right->right->type, AST_PIPE);

  EXPECT_EQ(node->right->right->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->right->right->left->cmd_args), "cat");
  EXPECT_STREQ(get_cmd_arg(node->right->right->left->cmd_args->next), "-e");
  EXPECT_EQ(node->right->right->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->right->right->left->redirects, nullptr);

  EXPECT_EQ(node->right->right->right, nullptr);

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
  **                    PIPE
  **                 |      \
  **               |           \
  **        SUBSHELL              PIPE
  **         |                  |      \
  **  CMD(ls -l)  SUBSHELL(> out.txt)  NULL
  **                     |
  **             CMD(cat -e)
  */
  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node->type, AST_PIPE);

  EXPECT_EQ(node->left->type, AST_SUBSHELL);

  EXPECT_EQ(node->left->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->left->cmd_args->next), "-l");
  EXPECT_EQ(node->left->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->left->left->redirects, nullptr);

  EXPECT_EQ(node->left->right, nullptr);

  EXPECT_EQ(node->right->type, AST_PIPE);

  EXPECT_EQ(node->right->left->type, AST_SUBSHELL);
  EXPECT_EQ(get_redirect_type(node->right->left->redirects), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->right->left->redirects), "out.txt");
  EXPECT_EQ(node->right->left->redirects->next, nullptr);

  EXPECT_EQ(node->right->left->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->right->left->left->cmd_args), "cat");
  EXPECT_STREQ(get_cmd_arg(node->right->left->left->cmd_args->next), "-e");
  EXPECT_EQ(node->right->left->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->right->left->left->redirects, nullptr);

  EXPECT_EQ(node->right->left->right, nullptr);

  EXPECT_EQ(node->right->right, nullptr);

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
