// Copyright 2024, reasuke

#include "gtest/gtest.h"
#include "utils_parser.hpp"

extern "C" {
#include "ast.h"
#include "parser/parser_internal.h"
#include "token.h"
}

TEST(parse_list, OneSimplePipeline) {
  // ls -l
  t_token_list *token_list = construct_token_list(
      {{TOKEN_WORD, "ls"}, {TOKEN_WORD, "-l"}, {TOKEN_EOF, nullptr}});

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
  // ls -l | wc
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_WORD, "wc"},
                                                   {TOKEN_EOF, nullptr}});

  /*
  **             PIPE
  **            |    \
  **   CMD(ls -l)   CMD(wc)
  */
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
  // ls -l && pwd
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_AND_IF, "&&"},
                                                   {TOKEN_WORD, "pwd"},
                                                   {TOKEN_EOF, nullptr}});

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
  // ls -l && pwd > out.txt || echo hello
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_AND_IF, "&&"},
                                                   {TOKEN_WORD, "pwd"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out.txt"},
                                                   {TOKEN_OR_IF, "||"},
                                                   {TOKEN_WORD, "echo"},
                                                   {TOKEN_WORD, "hello"},
                                                   {TOKEN_EOF, nullptr}});

  /*
  **              OR
  **             |   \
  **            AND  COMMAND(echo hello)
  **           |   \
  **  COMMAND(ls -l) REDIRECT(pwd > out.txt)
  */
  t_ast *node = parse_list(&token_list);

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
  // ls | wc && pwd | cat -e || echo hello
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_WORD, "wc"},
                                                   {TOKEN_AND_IF, "&&"},
                                                   {TOKEN_WORD, "pwd"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_WORD, "cat"},
                                                   {TOKEN_WORD, "-e"},
                                                   {TOKEN_OR_IF, "||"},
                                                   {TOKEN_WORD, "echo"},
                                                   {TOKEN_WORD, "hello"},
                                                   {TOKEN_EOF, nullptr}});

  /*
  **                    0.OR
  **                  /     \
  **                /         \
  **               1.AND    8.CMD(echo hello)
  **             /        \
  **            /            \
  **          2.PIPE           5.PIPE
  **          /    \          |        \
  **    3.CMD(ls) 4.CMD(wc) 6.CMD(pwd) 7.CMD(cat -e)
  */
  t_ast *node0 = parse_list(&token_list);
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

  destroy_ast(node0);
  destroy_token_list(token_list);
}

TEST(parse_list, ListsWithSubshells) {
  // (ls -l | cat) && (pwd | wc)
  t_token_list *token_list = construct_token_list({{TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_WORD, "cat"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_AND_IF, "&&"},
                                                   {TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "pwd"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_WORD, "wc"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_EOF, nullptr}});

  /*
  **                     0.AND
  **                  /         \
  **                /             \
  **              /                 \
  **        1.SUBSHEL               6.SUBSHELL
  **           |     \                 |    \
  **         2.PIPE  5.NULL         7.PIPE  10.NULL
  **       |       \                |      \
  **  3.CMD(ls -l) 4.CMD(cat)  8.CMD(pwd) 9.CMD(wc)
  */
  t_ast *node0 = parse_list(&token_list);
  t_ast *node1 = node0->left;
  t_ast *node2 = node0->left->left;
  t_ast *node3 = node0->left->left->left;
  t_ast *node4 = node0->left->left->right;
  t_ast *node5 = node0->left->right;
  t_ast *node6 = node0->right;
  t_ast *node7 = node0->right->left;
  t_ast *node8 = node0->right->left->left;
  t_ast *node9 = node0->right->left->right;
  t_ast *node10 = node0->right->right;

  EXPECT_EQ(node0->type, AST_AND);

  EXPECT_EQ(node1->type, AST_SUBSHELL);

  EXPECT_EQ(node2->type, AST_PIPE);

  EXPECT_EQ(node3->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node3->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node3->cmd_args->next), "-l");
  EXPECT_EQ(node3->cmd_args->next->next, nullptr);
  EXPECT_EQ(node3->redirects, nullptr);

  EXPECT_EQ(node4->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node4->cmd_args), "cat");
  EXPECT_EQ(node4->cmd_args->next, nullptr);
  EXPECT_EQ(node4->redirects, nullptr);

  EXPECT_EQ(node5, nullptr);

  EXPECT_EQ(node6->type, AST_SUBSHELL);

  EXPECT_EQ(node7->type, AST_PIPE);

  EXPECT_EQ(node8->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node8->cmd_args), "pwd");
  EXPECT_EQ(node8->cmd_args->next, nullptr);
  EXPECT_EQ(node8->redirects, nullptr);

  EXPECT_EQ(node9->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node9->cmd_args), "wc");
  EXPECT_EQ(node9->cmd_args->next, nullptr);
  EXPECT_EQ(node9->redirects, nullptr);

  EXPECT_EQ(node10, nullptr);

  destroy_ast(node0);
  destroy_token_list(token_list);
}

TEST(parse_list, ListsInSubshell) {
  // (ls -l && pwd) && ((echo hello) || cat)
  t_token_list *token_list = construct_token_list({{TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_AND_IF, "&&"},
                                                   {TOKEN_WORD, "pwd"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_AND_IF, "&&"},
                                                   {TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "echo"},
                                                   {TOKEN_WORD, "hello"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_OR_IF, "||"},
                                                   {TOKEN_WORD, "cat"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_EOF, nullptr}});

  /*
  **                      0.AND
  **                  /           \
  **                /               \
  **              /                   \
  **       1.SUBSHELL                 5.SUBSHELL
  **           |                          |
  **         2.AND                       6.OR
  **       |       \                  |        \
  **  3.CMD(ls -l)  4.CMD(pwd)  7.SUBSHELL      \
  **                            |                \
  **                          8.CMD(echo hello)   9.CMD(cat)
  */
  t_ast *node0 = parse_list(&token_list);
  t_ast *node1 = node0->left;
  t_ast *node2 = node0->left->left;
  t_ast *node3 = node0->left->left->left;
  t_ast *node4 = node0->left->left->right;
  t_ast *node5 = node0->right;
  t_ast *node6 = node0->right->left;
  t_ast *node7 = node0->right->left->left;
  t_ast *node8 = node0->right->left->left->left;
  t_ast *node9 = node0->right->left->right;

  EXPECT_EQ(node0->type, AST_AND);

  EXPECT_EQ(node1->type, AST_SUBSHELL);

  EXPECT_EQ(node2->type, AST_AND);

  EXPECT_EQ(node3->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node3->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node3->cmd_args->next), "-l");
  EXPECT_EQ(node3->cmd_args->next->next, nullptr);
  EXPECT_EQ(node3->redirects, nullptr);

  EXPECT_EQ(node4->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node4->cmd_args), "pwd");
  EXPECT_EQ(node4->cmd_args->next, nullptr);
  EXPECT_EQ(node4->redirects, nullptr);

  EXPECT_EQ(node5->type, AST_SUBSHELL);

  EXPECT_EQ(node6->type, AST_OR);

  EXPECT_EQ(node7->type, AST_SUBSHELL);

  EXPECT_EQ(node8->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node8->cmd_args), "echo");
  EXPECT_STREQ(get_cmd_arg(node8->cmd_args->next), "hello");
  EXPECT_EQ(node8->cmd_args->next->next, nullptr);
  EXPECT_EQ(node8->redirects, nullptr);

  EXPECT_EQ(node9->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node9->cmd_args), "cat");
  EXPECT_EQ(node9->cmd_args->next, nullptr);
  EXPECT_EQ(node9->redirects, nullptr);

  destroy_ast(node0);
  destroy_token_list(token_list);
}

TEST(parse_list, InvalidToken) {
  // ls -l &&
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_AND_IF, "&&"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_list(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}

TEST(parse_list, InvalidToken2) {
  // ls && &&
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_AND_IF, "&&"},
                                                   {TOKEN_AND_IF, "&&"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_list(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}

TEST(parse_list, InvalidToken3) {
  // ls && |
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_AND_IF, "&&"},
                                                   {TOKEN_PIPE, "|"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_list(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}

TEST(parse_list, InvalidToken4) {
  // ( ls > )
  t_token_list *token_list = construct_token_list({{TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_R_PARENTHESIS, ")"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_list(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}

TEST(parse_lsit, InvalidToken5) {
  // ls && ( ls
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_AND_IF, "&&"},
                                                   {TOKEN_L_PARENTHESIS, "("},
                                                   {TOKEN_WORD, "ls"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_list(&token_list);

  EXPECT_EQ(node, nullptr);

  destroy_token_list(token_list);
}
