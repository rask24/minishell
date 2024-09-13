#include <string.h>
#include <unistd.h>

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

TEST(convert_env_to_array, OneEnv) {
  t_env_list *env = construct_env(strdup("HOME"), strdup("/home/user"));
  const char **env_array = convert_env_to_array(env);

  EXPECT_STREQ(env_array[0], "HOME=/home/user");
  EXPECT_EQ(env_array[1], nullptr);

  destroy_env_list(env);
}

TEST(convert_env_to_array, MultiEnv) {
  t_env_list *env = construct_env(strdup("HOME"), strdup("/home/user"));
  t_env_list *env2 = construct_env(strdup("PATH"), strdup("/usr/bin"));
  ft_lstadd_back(&env, env2);
  const char **env_array = convert_env_to_array(env);

  EXPECT_STREQ(env_array[0], "HOME=/home/user");
  EXPECT_STREQ(env_array[1], "PATH=/usr/bin");
  EXPECT_EQ(env_array[2], nullptr);

  destroy_env_list(env);
  free(env_array);
}

TEST(convert_array_to_env, OneEnv) {
  char *envp[] = {strdup("HOME=/home/user"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);

  EXPECT_STREQ(get_env_name(env_list), "HOME");
  EXPECT_STREQ(get_env_value(env_list), "/home/user");

  EXPECT_EQ(get_env_name(env_list->next), nullptr);
  EXPECT_EQ(get_env_value(env_list->next), nullptr);

  destroy_env_list(env_list);
}

TEST(convert_array_to_env, MultiEnv) {
  char *envp[] = {strdup("HOME=/home/user"), strdup("PATH=/usr/bin"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);

  EXPECT_STREQ(get_env_name(env_list), "HOME");
  EXPECT_STREQ(get_env_value(env_list), "/home/user");

  EXPECT_STREQ(get_env_name(env_list->next), "PATH");
  EXPECT_STREQ(get_env_value(env_list->next), "/usr/bin");

  EXPECT_EQ(get_env_name(env_list->next->next), nullptr);
  EXPECT_EQ(get_env_value(env_list->next->next), nullptr);

  destroy_env_list(env_list);
}
