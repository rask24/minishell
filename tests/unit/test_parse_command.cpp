// Copyright 2024, reasuke

#include <string>

#include "gtest/gtest.h"

extern "C" {
#include "ast.h"
#include "parser/parser_internal.h"
#include "token.h"
}

TEST(parse_command, SimpleCommand) {
  t_token_list *token_list = nullptr;

  // ls -l
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

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
  t_token_list *token_list = nullptr;

  // (ls -l)
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_L_PARENTHESIS, strdup("(")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_R_PARENTHESIS, strdup(")")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

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
  t_token_list *token_list = nullptr;

  // (ls -l) > out.txt
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_L_PARENTHESIS, strdup("(")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_R_PARENTHESIS, strdup(")")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *node = parse_command(&token_list);

  /*
  **  SUBSHELL(> out.txt)
  **     |
  **  COMMAND(ls -l)
  */
  EXPECT_EQ(node->type, AST_SUBSHELL);
  EXPECT_STREQ(get_redirect_filepath(node->redirects), "out.txt");
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
  t_token_list *token_list = nullptr;

  // (ls -l) > out1.txt >> out2.txt
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_L_PARENTHESIS, strdup("(")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_R_PARENTHESIS, strdup(")")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out1.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_DGREAT, strdup(">>")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out2.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  /*
  ** SUBSHELL(> out1.txt >> out2.txt)
  **     |
  **  COMMAND(ls -l)
  */
  t_ast *node = parse_command(&token_list);

  EXPECT_EQ(node->type, AST_SUBSHELL);
  EXPECT_STREQ(get_redirect_filepath(node->redirects), "out1.txt");
  EXPECT_EQ(get_redirect_type(node->redirects), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects->next), "out2.txt");
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
  t_token_list *token_list = nullptr;

  // ((ls -l))
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_L_PARENTHESIS, strdup("(")));
  ft_lstadd_back(&token_list,

                 construct_token(TOKEN_L_PARENTHESIS, strdup("(")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_R_PARENTHESIS, strdup(")")));
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_R_PARENTHESIS, strdup(")")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

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
  t_token_list *token_list = nullptr;

  // (ls -l
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_L_PARENTHESIS, strdup("(")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_AND_IF, strdup("&&")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  ::testing::internal::CaptureStderr();

  t_ast *node = parse_command(&token_list);

  std::string err_msg = ::testing::internal::GetCapturedStderr();

  EXPECT_EQ(node, nullptr);
  EXPECT_STREQ(err_msg.c_str(),
                   "minishell: unexpected token near `newline'\n");

  destroy_token_list(token_list);
}

TEST(parse_command, InvalidTokenPipe) {
  t_token_list *token_list = nullptr;

  // (ls -l | )
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_L_PARENTHESIS, strdup("(")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_PIPE, strdup("|")));
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_R_PARENTHESIS, strdup(")")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  ::testing::internal::CaptureStderr();

  t_ast *node = parse_command(&token_list);

  std::string err_msg = ::testing::internal::GetCapturedStderr();

  EXPECT_EQ(node, nullptr);
  EXPECT_STREQ(err_msg.c_str(), "minishell: unexpected token near `)'\n");

  destroy_token_list(token_list);
}

TEST(parse_command, InvalidTokenRedirect) {
  t_token_list *token_list = nullptr;

  // (ls -l ) >
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_L_PARENTHESIS, strdup("(")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list,
                 construct_token(TOKEN_R_PARENTHESIS, strdup(")")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  ::testing::internal::CaptureStderr();

  t_ast *node = parse_command(&token_list);

  std::string err_msg = ::testing::internal::GetCapturedStderr();

  EXPECT_EQ(node, nullptr);
  EXPECT_STREQ(err_msg.c_str(),
                   "minishell: unexpected token near `newline'\n");

  destroy_token_list(token_list);
}
