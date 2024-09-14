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

  t_ast *node = parse_list(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->cmd_args->next), "-l");
  EXPECT_EQ(node->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->redirects, nullptr);

  destroy_ast(node);
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

  t_ast *node = parse_list(&token_list);

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
  t_ast *node = parse_list(&token_list);

  EXPECT_EQ(node->type, AST_AND);

  EXPECT_EQ(node->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->cmd_args->next), "-l");
  EXPECT_EQ(node->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->left->redirects, nullptr);

  EXPECT_EQ(node->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->right->cmd_args), "pwd");
  EXPECT_EQ(node->right->cmd_args->next, nullptr);
  EXPECT_EQ(node->right->redirects, nullptr);

  destroy_ast(node);
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

  t_ast *node = parse_list(&token_list);

  /*
  **              OR
  **             |   \
  **            AND  COMMAND(echo hello)
  **           |   \
  **  COMMAND(ls -l) REDIRECT(pwd > out.txt)
  */
  EXPECT_EQ(node->type, AST_OR);

  EXPECT_EQ(node->left->type, AST_AND);

  EXPECT_EQ(node->left->left->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->left->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->left->left->cmd_args->next), "-l");
  EXPECT_EQ(node->left->left->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->left->left->redirects, nullptr);

  EXPECT_EQ(node->left->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->left->right->cmd_args), "pwd");
  EXPECT_EQ(get_cmd_arg(node->left->right->cmd_args->next), nullptr);
  EXPECT_EQ(get_redirect_type(node->left->right->redirects), REDIRECT_OUTPUT);
  EXPECT_EQ(get_redirect_type(node->left->right->redirects->next),
            REDIRECT_UNKNOWN);
  EXPECT_STREQ(get_redirect_filepath(node->left->right->redirects), "out.txt");
  EXPECT_EQ(get_redirect_filepath(node->left->right->redirects->next), nullptr);
  EXPECT_EQ(node->left->right->redirects->next, nullptr);

  EXPECT_EQ(node->right->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->right->cmd_args), "echo");
  EXPECT_STREQ(get_cmd_arg(node->right->cmd_args->next), "hello");
  EXPECT_EQ(node->right->cmd_args->next->next, nullptr);
  EXPECT_EQ(node->right->redirects, nullptr);

  destroy_ast(node);
  destroy_token_list(token_list);
}

TEST(parse_list, MultipleListsWithPipeline) {
  t_token_list *token_list = nullptr;

  // ls | wc && pwd | cat -e || echo hello
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_PIPE, strdup("|")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("wc")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_AND_IF, strdup("&&")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("pwd")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_PIPE, strdup("|")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("cat")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-e")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_OR_IF, strdup("||")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("echo")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("hello")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *node = parse_list(&token_list);

  /*
  **                          0.OR
  **                       |       \
  **                     |           \
  **                   1.AND          8.CMD(echo hello)
  **                |         \
  **              |             \
  **           2.PIPE             5.PIPE
  **          |     \            |       \
  **        |         \        |           \
  **   3.CMD(ls) 4.CMD(wc)  6.CMD(pwd)   7.CMD(cat -e)
  */

  t_ast *node0 = node;
  t_ast *node1 = node0->left;
  t_ast *node2 = node0->left->left;
  t_ast *node3 = node0->left->left->left;
  t_ast *node4 = node0->left->left->right;
  t_ast *node5 = node0->left->right;
  t_ast *node6 = node0->left->right->left;
  t_ast *node7 = node0->left->right->right;
  t_ast *node8 = node0->right;

  EXPECT_EQ(node0->type, AST_OR);

  EXPECT_EQ(node1->type, AST_AND);

  EXPECT_EQ(node2->type, AST_PIPE);

  EXPECT_EQ(node3->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node3->cmd_args), "ls");
  EXPECT_EQ(node3->cmd_args->next, nullptr);
  EXPECT_EQ(node3->redirects, nullptr);

  EXPECT_EQ(node4->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node4->cmd_args), "wc");
  EXPECT_EQ(node4->cmd_args->next, nullptr);
  EXPECT_EQ(node4->redirects, nullptr);

  EXPECT_EQ(node5->type, AST_PIPE);

  EXPECT_EQ(node6->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node6->cmd_args), "pwd");
  EXPECT_EQ(node6->cmd_args->next, nullptr);
  EXPECT_EQ(node6->redirects, nullptr);

  EXPECT_EQ(node7->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node7->cmd_args), "cat");
  EXPECT_STREQ(get_cmd_arg(node7->cmd_args->next), "-e");
  EXPECT_EQ(node7->cmd_args->next->next, nullptr);
  EXPECT_EQ(node7->redirects, nullptr);

  EXPECT_EQ(node8->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node8->cmd_args), "echo");
  EXPECT_STREQ(get_cmd_arg(node8->cmd_args->next), "hello");
  EXPECT_EQ(node8->cmd_args->next->next, nullptr);
  EXPECT_EQ(node8->redirects, nullptr);

  destroy_ast(node);
  destroy_token_list(token_list);
}

TEST(parse_list, InvalidToken) {
  t_token_list *token_list = nullptr;

  // ls -l &&
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_AND_IF, strdup("&&")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *node = parse_list(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}
