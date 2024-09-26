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

  char *string = strdup("USER");

  EXPECT_STREQ(expand_variable(string, &ctx), "USER");

  destroy_env_list(env_list);
}

TEST(expand_variable, OneVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;

  char *string = strdup("$USER");

  EXPECT_STREQ(expand_variable(string, &ctx), "Alice");

  destroy_env_list(env_list);
}

TEST(expand_variable, NoVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USERRRRR");

  EXPECT_STREQ(expand_variable(string, &ctx), "");

  destroy_env_list(env_list);
}

TEST(expand_variable, StringAfterVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("student$USER");

  EXPECT_STREQ(expand_variable(string, &ctx), "studentAlice");

  destroy_env_list(env_list);
}

TEST(expand_variable, ManyVariables) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USERis$USER$USER$");

  EXPECT_STREQ(expand_variable(string, &ctx), "AliceAlice$");

  destroy_env_list(env_list);
}

TEST(expand_variable, IgnoreSingleQuote) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USER'$USER'");

  EXPECT_STREQ(expand_variable(string, &ctx), "Alice'$USER'");

  destroy_env_list(env_list);
}

TEST(expand_variable, IgnoreDoubleQuote) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USER\"$USER\"");

  EXPECT_STREQ(expand_variable(string, &ctx), "Alice\"$USER\"");

  destroy_env_list(env_list);
}

TEST(expand_quotes, NoSingleQuote) {
  char *envp[] = {nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("hello");

  EXPECT_STREQ(expand_quotes(string, &ctx), "hello");

  destroy_env_list(env_list);
}

TEST(expand_quotes, ManySingleQuotes) {
  char *envp[] = {nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("'hello'''");

  EXPECT_STREQ(expand_quotes(string, &ctx), "hello");

  destroy_env_list(env_list);
}

TEST(expand_quotes, ManyDoubleQuotes) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_builtins_ctx ctx;
  ctx.env = env_list;

  char *result = expand_quotes(strdup("\"$USER\"\"\""), &ctx);
  EXPECT_STREQ(result, "Alice");
}
