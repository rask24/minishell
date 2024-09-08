#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "env.h"
}

TEST(construct_env, OneEnv) {
  t_env_list *env = construct_env(strdup("HOME"), strdup("/home/user"));

  EXPECT_STREQ(get_env_name(env), "HOME");
  EXPECT_STREQ(get_env_value(env), "/home/user");

  destroy_env_list(env);
}

TEST(construct_env, TwoEnv) {
  t_env_list *env = construct_env(strdup("HOME"), strdup("/home/user"));
  t_env_list *env2 = construct_env(strdup("PATH"), strdup("/usr/bin"));

  ft_lstadd_back(&env, env2);

  EXPECT_STREQ(get_env_name(env), "HOME");
  EXPECT_STREQ(get_env_value(env), "/home/user");

  EXPECT_STREQ(get_env_name(env->next), "PATH");
  EXPECT_STREQ(get_env_value(env->next), "/usr/bin");

  destroy_env_list(env);
}
