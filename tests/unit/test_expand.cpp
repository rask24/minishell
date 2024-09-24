#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "env.h"
#include "expansion.h"
}

TEST(expand, NoExpand) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;
  t_list *cmd_arg = ft_lstnew(strdup("USER"));

  t_list *result = expand(cmd_arg, &ctx);
  EXPECT_STREQ((char *)(result->content), "USER");

  destroy_env_list(env_list);
}

TEST(expand, OneVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;
  t_list *cmd_arg = ft_lstnew(strdup("$USER"));

  t_list *result = expand(cmd_arg, &ctx);
  EXPECT_STREQ((char *)(result->content), "Alice");

  destroy_env_list(env_list);
}

TEST(expand, NoVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;
  t_list *cmd_arg = ft_lstnew(strdup("$USERRRR"));

  t_list *result = expand(cmd_arg, &ctx);
  EXPECT_STREQ((char *)(result->content), "");

  destroy_env_list(env_list);
}

TEST(expand, StringAfterVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;
  t_list *cmd_arg = ft_lstnew(strdup("student$USER"));

  t_list *result = expand(cmd_arg, &ctx);
  EXPECT_STREQ((char *)(result->content), "studentAlice");

  destroy_env_list(env_list);
}

TEST(expand, ManyVariables) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;
  t_list *cmd_arg = ft_lstnew(strdup("$USERis$USER$USER$"));

  t_list *result = expand(cmd_arg, &ctx);
  EXPECT_STREQ((char *)(result->content), "AliceAlice$");

  destroy_env_list(env_list);
}
