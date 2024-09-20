#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "builtins.h"
}

TEST(builtins_env, builtin_env) {
  t_env_list *env = construct_env(strdup("key"), strdup("value"));
  t_env_list *env1 = construct_env(strdup("key1"), strdup("value1"));
  t_env_list *env2 = construct_env(strdup("key2"), strdup("value2"));
  ft_lstadd_back(&env, env1);
  ft_lstadd_back(&env, env2);

  t_builtins_ctx config;
  config.env = env;

  char *args[] = {ft_strdup("env"), NULL};
  testing::internal::CaptureStdout();
  int result = builtins_env(args, &config);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_STREQ(output.c_str(), "key=value\nkey1=value1\nkey2=value2\n");
  EXPECT_EQ(result, 0);
}

TEST(builtins_env, moreArgs) {
  t_env_list *env = construct_env(strdup("key"), strdup("value"));
  t_env_list *env1 = construct_env(strdup("key1"), strdup("value1"));
  t_env_list *env2 = construct_env(strdup("key2"), strdup("value2"));
  ft_lstadd_back(&env, env1);
  ft_lstadd_back(&env, env2);

  t_builtins_ctx config;
  config.env = env;

  char *args[] = {ft_strdup("env"), ft_strdup("key3=value3"), NULL};
  testing::internal::CaptureStderr();
  int result = builtins_env(args, &config);
  std::string output = testing::internal::GetCapturedStderr();

  EXPECT_STREQ(output.c_str(), "minishell: env: too many arguments\n");
  EXPECT_EQ(result, 1);
}
