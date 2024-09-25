#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "../../src/expansion/expansion_internal.h"
#include "env.h"
#include "expansion.h"
}

TEST(expand_variable, NoExpand) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;

  EXPECT_STREQ(expand_variable(strdup("USER"), &ctx), "USER");

  destroy_env_list(env_list);
}

TEST(expand_variable, OneVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;

  EXPECT_STREQ(expand_variable(strdup("$USER"), &ctx), "Alice");

  destroy_env_list(env_list);
}

TEST(expand_variable, NoVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;

  EXPECT_STREQ(expand_variable(strdup("$USERRRRR"), &ctx), "");

  destroy_env_list(env_list);
}

TEST(expand_variable, StringAfterVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;

  EXPECT_STREQ(expand_variable(strdup("student$USER"), &ctx), "studentAlice");
  destroy_env_list(env_list);
}

TEST(expand_variable, ManyVariables) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;

  EXPECT_STREQ(expand_variable(strdup("$USERis$USER$USER$"), &ctx),
               "AliceAlice$");
  destroy_env_list(env_list);
}
