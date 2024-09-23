#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "builtins.h"
}

TEST(builtins_unset, OneEnv) {
  t_env_list *env = construct_env(strdup("HOME"), strdup("/home/user"));
  t_builtins_ctx config = {
      .cwd = nullptr,
      .env = env,
      .exit_status = 0,
  };

  char *args[] = {strdup("unset"), strdup("HOME"), NULL};
  builtins_unset(args, &config);

  EXPECT_EQ(config.env, nullptr);
}

TEST(builtins_unset, TwoEnv) {
  t_env_list *env = construct_env(strdup("HOME"), strdup("/home/user"));
  t_env_list *env2 = construct_env(strdup("PATH"), strdup("/usr/bin"));
  ft_lstadd_back(&env, env2);
  t_builtins_ctx config = {
      .cwd = nullptr,
      .env = env,
      .exit_status = 0,
  };

  char *args[] = {strdup("unset"), strdup("HOME"), strdup("PATH"), NULL};
  builtins_unset(args, &config);

  EXPECT_EQ(config.env, nullptr);
}
