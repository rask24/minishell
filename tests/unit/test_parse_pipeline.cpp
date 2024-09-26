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
  ** COMMAND(ls -l) COMMAND(wc)
  */
  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node->type, AST_PIPE);

  EXPECT_EQ(node->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args->next), "-l");
  EXPECT_EQ(node->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->left->redirects, nullptr);

  EXPECT_EQ(node->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->right->cmd_args), "wc");
  EXPECT_EQ(node->right->cmd_args->next, nullptr);
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
  **            0.PIPE
  **            |    \
  **  1.CMD(ls -l)   2.PIPE
  **                |      \
  **           3.CMD(wc)  4.CMD(cat -e)
  */
  t_ast *node0 = parse_pipeline(&token_list);
  t_ast *node1 = node0->left;
  t_ast *node2 = node0->right;
  t_ast *node3 = node0->right->left;
  t_ast *node4 = node0->right->right;

  EXPECT_EQ(node0->type, AST_PIPE);

  EXPECT_EQ(node1->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node1->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node1->cmd_args->next), "-l");
  EXPECT_EQ(node1->cmd_args->next->next, nullptr);
  EXPECT_EQ(node1->redirects, nullptr);

  EXPECT_EQ(node2->type, AST_PIPE);

  EXPECT_EQ(node3->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node3->cmd_args), "wc");
  EXPECT_EQ(node3->cmd_args->next, nullptr);
  EXPECT_EQ(node3->redirects, nullptr);

  EXPECT_EQ(node4->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node4->cmd_args), "cat");
  EXPECT_STREQ(get_cmd_arg(node4->cmd_args->next), "-e");
  EXPECT_EQ(node4->cmd_args->next->next, nullptr);
  EXPECT_EQ(node4->redirects, nullptr);

  destroy_ast(node0);
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
  **               0.PIPE
  **              |     \
  **       1.SUBSHELL   4.SUBSHELL(> out.txt)
  **        |       \           |           \
  **  2.CMD(ls -l)  3.NULL  5.CMD(cat -e)  6.NULL
  */
  t_ast *node0 = parse_pipeline(&token_list);
  t_ast *node1 = node0->left;
  t_ast *node2 = node0->left->left;
  t_ast *node3 = node0->left->right;
  t_ast *node4 = node0->right;
  t_ast *node5 = node0->right->left;
  t_ast *node6 = node0->right->right;

  EXPECT_EQ(node0->type, AST_PIPE);

  EXPECT_EQ(node1->type, AST_SUBSHELL);

  EXPECT_EQ(node2->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node2->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node2->cmd_args->next), "-l");
  EXPECT_EQ(node2->cmd_args->next->next, nullptr);
  EXPECT_EQ(node2->redirects, nullptr);

  EXPECT_EQ(node3, nullptr);

  EXPECT_EQ(node4->type, AST_SUBSHELL);
  EXPECT_EQ(get_redirect_type(node4->redirects), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node4->redirects), "out.txt");
  EXPECT_EQ(node4->redirects->next, nullptr);

  EXPECT_EQ(node5->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node5->cmd_args), "cat");
  EXPECT_STREQ(get_cmd_arg(node5->cmd_args->next), "-e");
  EXPECT_EQ(node5->cmd_args->next->next, nullptr);
  EXPECT_EQ(node5->redirects, nullptr);

  EXPECT_EQ(node6, nullptr);

  destroy_ast(node0);
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
