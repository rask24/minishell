// Copyright 2024, reasuke

#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "ast.h"
#include "parser/parser_internal.h"
#include "token.h"
}

TEST(parse_pipeline, SimpleCommand) {
  t_token_list *token_list = nullptr;

  // ls -l
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->cmd_args->next), "-l");
  EXPECT_EQ(node->redirects, nullptr);

  destroy_ast(node);
  destroy_token_list(token_list);
}

TEST(parse_pipeline, OnePipeline) {
  t_token_list *token_list = nullptr;

  // ls -l | wc
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_PIPE, strdup("|")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("wc")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

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
  t_token_list *token_list = nullptr;

  // ls -l | wc | cat -e
  /*
  **                    PIPE
  **                   |    \
  **                 PIPE  COMMAND (cat -e)
  **                |    \
  **   COMMAND(ls -l) COMMAND (wc)
  */
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_PIPE, strdup("|")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("wc")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_PIPE, strdup("|")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("cat")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-e")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

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
  t_token_list *token_list = nullptr;

  // (ls -l) | (cat -e) > out.txt
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_L_PARENTHESIS, strdup("(")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_R_PARENTHESIS, strdup(")")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_PIPE, strdup("|")));
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_L_PARENTHESIS, strdup("(")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("cat")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-e")));
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_R_PARENTHESIS, strdup(")")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

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
  t_token_list *token_list = nullptr;

  // ls -l |
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_PIPE, strdup("|")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}

TEST(parse_pipline, InvalidTokenPipe) {
  t_token_list *token_list = nullptr;

  // (ls -l ) |
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_L_PARENTHESIS, strdup("(")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_R_PARENTHESIS, strdup(")")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_PIPE, strdup("|")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *node = parse_pipeline(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}
