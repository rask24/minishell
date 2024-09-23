// Copyright 2024, reasuke

#include "gtest/gtest.h"
#include "utils_parser.hpp"

extern "C" {
#include "parser/parser_internal.h"
#include "token.h"
}

TEST(parse_simple_command, OneCommand) {
  // ls
  t_token_list *token_list =
      construct_token_list({{TOKEN_WORD, "ls"}, {TOKEN_EOF, nullptr}});

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "ls");
  EXPECT_EQ(get_cmd_arg(node->cmd_args->next), nullptr);

  destroy_token_list(token_list);
  destroy_ast(node);
}

TEST(parse_simple_command, MultipleCommands) {
  // ls -l src
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_WORD, "src"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_simple_command(&token_list);

  // ls -l src
  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->cmd_args->next), "-l");
  EXPECT_STREQ(get_cmd_arg(node->cmd_args->next->next), "src");
  EXPECT_EQ(get_cmd_arg(node->cmd_args->next->next->next), nullptr);

  destroy_token_list(token_list);
  destroy_ast(node);
}

TEST(parse_simple_command, OneRedirect) {
  // > ls.txt
  t_token_list *token_list = construct_token_list(
      {{TOKEN_GREAT, ">"}, {TOKEN_WORD, "ls.txt"}, {TOKEN_EOF, nullptr}});

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_EQ(get_cmd_arg(node->cmd_args), nullptr);
  EXPECT_EQ(get_redirect_type(node->redirects), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects), "ls.txt");

  destroy_token_list(token_list);
  destroy_ast(node);
}

TEST(parse_simple_command, MultipleRedirects) {
  // < in1.txt > out1.txt >> out2.txt < in2.txt > out3.txt
  t_token_list *token_list = construct_token_list({{TOKEN_LESS, "<"},
                                                   {TOKEN_WORD, "in1.txt"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out1.txt"},
                                                   {TOKEN_DGREAT, ">>"},
                                                   {TOKEN_WORD, "out2.txt"},
                                                   {TOKEN_LESS, "<"},
                                                   {TOKEN_WORD, "in2.txt"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out3.txt"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_EQ(get_cmd_arg(node->cmd_args), nullptr);
  EXPECT_EQ(get_redirect_type(node->redirects), REDIRECT_INPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects), "in1.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects->next), "out1.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next->next), REDIRECT_APPEND);
  EXPECT_STREQ(get_redirect_filepath(node->redirects->next->next), "out2.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next->next->next),
            REDIRECT_INPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects->next->next->next),
               "in2.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next->next->next->next),
            REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects->next->next->next->next),
               "out3.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next->next->next->next->next),
            REDIRECT_UNKNOWN);
  EXPECT_EQ(
      get_redirect_filepath(node->redirects->next->next->next->next->next),
      nullptr);

  destroy_token_list(token_list);
  destroy_ast(node);
}

TEST(parse_simple_command, CommandAndRedirect) {
  // ls -l > out.txt
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out.txt"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->cmd_args->next), "-l");
  EXPECT_EQ(get_cmd_arg(node->cmd_args->next->next), nullptr);
  EXPECT_EQ(get_redirect_type(node->redirects), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects), "out.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next), REDIRECT_UNKNOWN);
  EXPECT_EQ(get_redirect_filepath(node->redirects->next), nullptr);

  destroy_token_list(token_list);
  destroy_ast(node);
}

TEST(parse_simple_command, RedirectsAfterCommand) {
  // ls -l > out1.txt >> out2.txt > out3.txt
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out1.txt"},
                                                   {TOKEN_DGREAT, ">>"},
                                                   {TOKEN_WORD, "out2.txt"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out3.txt"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "ls");
  EXPECT_STREQ(get_cmd_arg(node->cmd_args->next), "-l");
  EXPECT_EQ(get_cmd_arg(node->cmd_args->next->next), nullptr);
  EXPECT_EQ(get_redirect_type(node->redirects), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects), "out1.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next), REDIRECT_APPEND);
  EXPECT_STREQ(get_redirect_filepath(node->redirects->next), "out2.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next->next), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects->next->next), "out3.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next->next->next),
            REDIRECT_UNKNOWN);
  EXPECT_EQ(get_redirect_filepath(node->redirects->next->next->next), nullptr);

  destroy_token_list(token_list);
  destroy_ast(node);
}

TEST(parse_simple_command, RedirectsBeforeCommand) {
  // < in1.txt > out.txt < in2.txt cat -e
  t_token_list *token_list = construct_token_list({{TOKEN_LESS, "<"},
                                                   {TOKEN_WORD, "in1.txt"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out.txt"},
                                                   {TOKEN_LESS, "<"},
                                                   {TOKEN_WORD, "in2.txt"},
                                                   {TOKEN_WORD, "cat"},
                                                   {TOKEN_WORD, "-e"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "cat");
  EXPECT_STREQ(get_cmd_arg(node->cmd_args->next), "-e");
  EXPECT_EQ(get_cmd_arg(node->cmd_args->next->next), nullptr);
  EXPECT_EQ(get_redirect_type(node->redirects), REDIRECT_INPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects), "in1.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects->next), "out.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next->next), REDIRECT_INPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects->next->next), "in2.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next->next->next),
            REDIRECT_UNKNOWN);
  EXPECT_EQ(get_redirect_filepath(node->redirects->next->next->next), nullptr);

  destroy_token_list(token_list);
  destroy_ast(node);
}

TEST(parse_simple_command, RedirectsBeforeAndAfterCommand) {
  // < in1.txt > out1.txt cat -e > out2.txt
  t_token_list *token_list = construct_token_list({{TOKEN_LESS, "<"},
                                                   {TOKEN_WORD, "in1.txt"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out1.txt"},
                                                   {TOKEN_WORD, "cat"},
                                                   {TOKEN_WORD, "-e"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out2.txt"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "cat");
  EXPECT_STREQ(get_cmd_arg(node->cmd_args->next), "-e");
  EXPECT_EQ(get_cmd_arg(node->cmd_args->next->next), nullptr);
  EXPECT_EQ(get_redirect_type(node->redirects), REDIRECT_INPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects), "in1.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects->next), "out1.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next->next), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects->next->next), "out2.txt");
  EXPECT_EQ(get_redirect_type(node->redirects->next->next->next),
            REDIRECT_UNKNOWN);
  EXPECT_EQ(get_redirect_filepath(node->redirects->next->next->next), nullptr);

  destroy_token_list(token_list);
  destroy_ast(node);
}

TEST(parse_simple_command, InvalidRedirect) {
  // ls -l >> >
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_DGREAT, ">>"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node, nullptr);
}

TEST(parse_simple_command, InvalidRedirect2) {
  // ls -l > out.txt <
  t_token_list *token_list = construct_token_list({{TOKEN_WORD, "ls"},
                                                   {TOKEN_WORD, "-l"},
                                                   {TOKEN_GREAT, ">"},
                                                   {TOKEN_WORD, "out.txt"},
                                                   {TOKEN_LESS, "<"},
                                                   {TOKEN_EOF, nullptr}});

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node, nullptr);
}
