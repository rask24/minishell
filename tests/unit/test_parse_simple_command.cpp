// Copyright 2024, reasuke

#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "parser/parser_internal.h"
#include "token.h"
}

TEST(parse_simple_command, OneCommand) {
  t_token_list *token_list = nullptr;

  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_STREQ(get_cmd_arg(node->cmd_args), "ls");
  EXPECT_EQ(get_cmd_arg(node->cmd_args->next), nullptr);

  destroy_token_list(token_list);
  destroy_ast(node);
}

TEST(parse_simple_command, MultipleCommands) {
  t_token_list *token_list = nullptr;

  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("src")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

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
  t_token_list *token_list = nullptr;

  // > ls.txt
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, nullptr));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node->type, AST_COMMAND);
  EXPECT_EQ(get_cmd_arg(node->cmd_args), nullptr);
  EXPECT_EQ(get_redirect_type(node->redirects), REDIRECT_OUTPUT);
  EXPECT_STREQ(get_redirect_filepath(node->redirects), "ls.txt");

  destroy_token_list(token_list);
  destroy_ast(node);
}

TEST(parse_simple_command, MultipleRedirects) {
  t_token_list *token_list = nullptr;

  // < in1.txt > out1.txt >> out2.txt < in2.txt > out3.txt
  ft_lstadd_back(&token_list, construct_token(TOKEN_LESS, strdup("<")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("in1.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out1.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_DGREAT, strdup(">>")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out2.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_LESS, strdup("<")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("in2.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out3.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

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
  EXPECT_EQ(get_redirect_filepath(node->redirects->next->next->next->next->next),
            nullptr);

  destroy_token_list(token_list);
  destroy_ast(node);
}

TEST(parse_simple_command, CommandAndRedirect) {
  t_token_list *token_list = nullptr;

  // ls -l > out.txt
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

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
  t_token_list *token_list = nullptr;

  // ls -l > out1.txt >> out2.txt > out3.txt
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out1.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_DGREAT, strdup(">>")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out2.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out3.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

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
  t_token_list *token_list = nullptr;

  // < in1.txt > out.txt < in2.txt cat -e
  ft_lstadd_back(&token_list, construct_token(TOKEN_LESS, strdup("<")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("in1.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_LESS, strdup("<")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("in2.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("cat")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-e")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

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
  t_token_list *token_list = nullptr;

  // < in1.txt > out1.txt cat -e > out2.txt
  ft_lstadd_back(&token_list, construct_token(TOKEN_LESS, strdup("<")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("in1.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out1.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("cat")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-e")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out2.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

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
  t_token_list *token_list = nullptr;

  // ls -l >> >
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_DGREAT, strdup(">>")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node, nullptr);
}

TEST(parse_simple_command, InvalidRedirect2) {
  t_token_list *token_list = nullptr;

  // ls -l > out.txt <
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("ls")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("-l")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_GREAT, strdup(">")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_WORD, strdup("out.txt")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_LESS, strdup("<")));
  ft_lstadd_back(&token_list, construct_token(TOKEN_EOF, nullptr));

  t_ast *node = parse_simple_command(&token_list);

  EXPECT_EQ(node, nullptr);
}
