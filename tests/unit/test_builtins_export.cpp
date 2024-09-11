#include <fcntl.h>

#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "builtins.h"
}

TEST(builtins_export, NoArgs) {
  t_env_list *env = construct_env(strdup("key"), strdup("value"));
  t_env_list *env1 = construct_env(strdup("key2"), strdup("value2"));
  t_env_list *env2 = construct_env(strdup("key1"), strdup("value1"));
  ft_lstadd_back(&env, env1);
  ft_lstadd_back(&env, env2);

  t_config config;
  config.env = env;

  testing::internal::CaptureStdout();
  int result = builtins_export(NULL, &config);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_STREQ(output.c_str(),
               "declare -x key=\"value\"\ndeclare -x key1=\"value1\"\ndeclare "
               "-x key2=\"value2\"\n");
  EXPECT_EQ(result, 0);
}
