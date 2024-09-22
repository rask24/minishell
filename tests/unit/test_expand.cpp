#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "env.h"
#include "expansions.h"
}

TEST(expand, noexpand) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);

  char *command = strdup("USER");

  char *result = expand(command, env_list);
  EXPECT_STREQ(result, "USER");

  destroy_env_list(env_list);
}

TEST(expand, OneVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);

  char *command = strdup("$USER");

  char *result = expand(command, env_list);
  EXPECT_STREQ(result, "Alice");

  destroy_env_list(env_list);
}

TEST(expand, novariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);

  char *command = strdup("$USERRRR");

  char *result = expand(command, env_list);
  EXPECT_STREQ(result, "");

  destroy_env_list(env_list);
}

TEST(expand, StringAfterVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);

  char *command = strdup("student$USER");

  char *result = expand(command, env_list);
  EXPECT_STREQ(result, "studentAlice");

  destroy_env_list(env_list);
}

TEST(expand, DoubleVariables) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);

  char *command = strdup("$USERis$USER$USER");

  char *result = expand(command, env_list);
  EXPECT_STREQ(result, "AliceAlice");

  destroy_env_list(env_list);
}
