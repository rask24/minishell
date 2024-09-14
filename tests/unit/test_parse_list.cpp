// Copyright 2024, reasuke

#include "gtest/gtest.h"

extern "C" {
#include "ast.h"
#include "parser/parser_internal.h"
#include "token.h"
}

TEST(parse_list, OneSimplePipeline) {
  t_token_list *token_list = nullptr;

  // ls -l
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *ast = parse_list(&token_list);

  EXPECT_EQ(ast->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(ast->cmd_args->next), "-l");
  EXPECT_EQ(ast->cmd_args->next->next, nullptr);
  EXPECT_EQ(ast->redirects, nullptr);

  destroy_ast(ast);
  destroy_token_list(token_list);
}

TEST(parse_list, OneComplexPipeline) {
  t_token_list *token_list = nullptr;

  // ls -l | wc
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_PIPE, strdup("|")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("wc")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *ast = parse_list(&token_list);

  EXPECT_EQ(ast->type, AST_PIPE);

  EXPECT_EQ(ast->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(ast->left->cmd_args->next), "-l");
  EXPECT_EQ(ast->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(ast->left->redirects, nullptr);

  EXPECT_EQ(ast->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->right->cmd_args), "wc");
  EXPECT_EQ(ast->right->cmd_args->next, nullptr);
  EXPECT_EQ(ast->right->redirects, nullptr);

  destroy_ast(ast);
  destroy_token_list(token_list);
}

TEST(parse_list, OneList) {
  t_token_list *token_list = nullptr;

  // ls -l && pwd
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_AND_IF, strdup("&&")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("pwd")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  /*
  **              AND
  **             |   \
  **  COMMAND(ls -l) COMMAND (pwd)
  */
  t_ast *ast = parse_list(&token_list);

  EXPECT_EQ(ast->type, AST_AND);

  EXPECT_EQ(ast->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(ast->left->cmd_args->next), "-l");
  EXPECT_EQ(ast->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(ast->left->redirects, nullptr);

  EXPECT_EQ(ast->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->right->cmd_args), "pwd");
  EXPECT_EQ(ast->right->cmd_args->next, nullptr);
  EXPECT_EQ(ast->right->redirects, nullptr);

  destroy_ast(ast);
  destroy_token_list(token_list);
}

TEST(parse_list, MultipleLists) {
  t_token_list *token_list = nullptr;

  // ls -l && pwd > out.txt || echo hello
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_AND_IF, strdup("&&")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("pwd")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_OR_IF, strdup("||")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("echo")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("hello")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *ast = parse_list(&token_list);

  /*
  **              OR
  **             |   \
  **            AND  COMMAND(echo hello)
  **           |   \
  **  COMMAND(ls -l) REDIRECT(pwd > out.txt)
  */
  EXPECT_EQ(ast->type, AST_OR);

  EXPECT_EQ(ast->left->type, AST_AND);

  EXPECT_EQ(ast->left->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->left->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(ast->left->left->cmd_args->next), "-l");
  EXPECT_EQ(ast->left->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(ast->left->left->redirects, nullptr);

  EXPECT_EQ(ast->left->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->left->right->cmd_args), "pwd");
  EXPECT_EQ(get_cmd_arg(ast->left->right->cmd_args->next), nullptr);
  EXPECT_EQ(get_redirect_type(ast->left->right->redirects), REDIRECT_OUTPUT);
  EXPECT_EQ(get_redirect_type(ast->left->right->redirects->next),
            REDIRECT_UNKNOWN);
  EXPECT_STREQ(get_redirect_filepath(ast->left->right->redirects), "out.txt");
  EXPECT_EQ(get_redirect_filepath(ast->left->right->redirects->next), nullptr);
  EXPECT_EQ(ast->left->right->redirects->next, nullptr);

  EXPECT_EQ(ast->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(ast->right->cmd_args), "echo");
  EXPECT_STREQ(get_cmd_arg(ast->right->cmd_args->next), "hello");
  EXPECT_EQ(ast->right->cmd_args->next->next, nullptr);
  EXPECT_EQ(ast->right->redirects, nullptr);

  destroy_ast(ast);
  destroy_token_list(token_list);
}
