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

  t_ast *ast = parse_pipeline(&token_list);

  EXPECT_EQ(ast->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(ast->cmd_args->next), "-l");
  EXPECT_EQ(ast->redirects, nullptr);

  destroy_ast(ast);
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

  t_ast *ast = parse_pipeline(&token_list);

  EXPECT_EQ(ast->type, AST_PIPE);
  EXPECT_EQ(ast->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(ast->left->cmd_args->next), "-l");
  EXPECT_EQ(ast->left->redirects, nullptr);
  EXPECT_EQ(ast->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->right->cmd_args), "wc");
  EXPECT_EQ(ast->right->redirects, nullptr);

  destroy_ast(ast);
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

  t_ast *ast = parse_pipeline(&token_list);

  EXPECT_EQ(ast->type, AST_PIPE);

  EXPECT_EQ(ast->left->type, AST_PIPE);
  EXPECT_EQ(ast->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->right->cmd_args), "cat");
  EXPECT_STREQ(get_cmd_arg(ast->right->cmd_args->next), "-e");
  EXPECT_STREQ(get_cmd_arg(ast->right->cmd_args->next->next), nullptr);

  EXPECT_EQ(ast->left->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->left->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(ast->left->left->cmd_args->next), "-l");
  EXPECT_STREQ(get_cmd_arg(ast->left->left->cmd_args->next->next), nullptr);
  EXPECT_EQ(ast->left->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->left->right->cmd_args), "wc");
  EXPECT_STREQ(get_cmd_arg(ast->left->right->cmd_args->next), nullptr);

  destroy_ast(ast);
  destroy_token_list(token_list);
}

TEST(parse_pipeline, InvalidToken) {
  t_token_list *token_list = nullptr;

  // ls -l |
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_PIPE, strdup("|")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *ast = parse_pipeline(&token_list);

  EXPECT_EQ(ast, nullptr);

  destroy_token_list(token_list);
}
