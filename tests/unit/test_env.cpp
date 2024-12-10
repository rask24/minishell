#include <string.h>
#include <unistd.h>

#include "gtest/gtest.h"

extern "C" {
#include "env.h"
}

TEST(construct_env, OneEnv) {
  t_env_list *env = construct_env(strdup("HOME"), strdup("/home/user"));

  EXPECT_STREQ(get_env_key(env), "HOME");
  EXPECT_STREQ(get_env_value(env), "/home/user");

  destroy_env_list(env);
}

TEST(construct_env, TwoEnv) {
  t_env_list *env = construct_env(strdup("HOME"), strdup("/home/user"));
  t_env_list *env2 = construct_env(strdup("PATH"), strdup("/usr/bin"));

  ft_lstadd_back(&env, env2);

  EXPECT_STREQ(get_env_key(env), "HOME");
  EXPECT_STREQ(get_env_value(env), "/home/user");

  EXPECT_STREQ(get_env_key(env->next), "PATH");
  EXPECT_STREQ(get_env_value(env->next), "/usr/bin");

  destroy_env_list(env);
}

TEST(convert_env_to_array, OneEnv) {
  t_env_list *env = construct_env(strdup("HOME"), strdup("/home/user"));
  char **env_array = convert_env_to_array(env);

  EXPECT_STREQ(env_array[0], "HOME=/home/user");
  EXPECT_EQ(env_array[1], nullptr);

  destroy_env_list(env);
}

TEST(convert_env_to_array, MultiEnv) {
  t_env_list *env = construct_env(strdup("HOME"), strdup("/home/user"));
  t_env_list *env2 = construct_env(strdup("PATH"), strdup("/usr/bin"));
  ft_lstadd_back(&env, env2);
  char **env_array = convert_env_to_array(env);

  EXPECT_STREQ(env_array[0], "HOME=/home/user");
  EXPECT_STREQ(env_array[1], "PATH=/usr/bin");
  EXPECT_EQ(env_array[2], nullptr);

  destroy_env_list(env);
  free(env_array);
}

TEST(convert_array_to_env, OneEnv) {
  char *envp[] = {strdup("HOME=/home/user"), nullptr};
  // char *def_path =
  //     strdup("/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.");
  t_env_list *env_list = convert_array_to_env(envp);

  EXPECT_STREQ(get_env_key(env_list), "HOME");
  EXPECT_STREQ(get_env_value(env_list), "/home/user");

  EXPECT_EQ(get_env_key(env_list->next), nullptr);
  EXPECT_EQ(get_env_value(env_list->next), nullptr);

  destroy_env_list(env_list);
}

TEST(convert_array_to_env, MultiEnv) {
  char *envp[] = {strdup("HOME=/home/user"), strdup("PATH=/usr/bin"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);

  EXPECT_STREQ(get_env_key(env_list), "HOME");
  EXPECT_STREQ(get_env_value(env_list), "/home/user");

  EXPECT_STREQ(get_env_key(env_list->next), "PATH");
  EXPECT_STREQ(get_env_value(env_list->next), "/usr/bin");

  EXPECT_EQ(get_env_key(env_list->next->next), nullptr);
  EXPECT_EQ(get_env_value(env_list->next->next), nullptr);

  destroy_env_list(env_list);
}

TEST(lookup_value, OneEnv) {
  t_env_list *env = construct_env(strdup("HOME"), strdup("/home/user"));

  EXPECT_STREQ(lookup_value("HOME", env), "/home/user");
  EXPECT_EQ(lookup_value("PATH", env), nullptr);

  destroy_env_list(env);
}

TEST(init_env, OneEnv) {
  char *envp[] = {strdup("HOME=/home/user"), nullptr};
  char *def_path =
      strdup("/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.");
  char *cwd = strdup("/home/user");
  t_env_list *env_list = init_env(envp, cwd);

  EXPECT_STREQ(get_env_key(env_list), "HOME");
  EXPECT_STREQ(get_env_value(env_list), "/home/user");

  EXPECT_STREQ(get_env_key(env_list->next), "PATH");
  EXPECT_STREQ(get_env_value(env_list->next), def_path);

  EXPECT_STREQ(get_env_key(env_list->next->next), "PWD");
  EXPECT_STREQ(get_env_value(env_list->next->next), "/home/user");

  EXPECT_STREQ(get_env_key(env_list->next->next->next), "SHLVL");
  EXPECT_STREQ(get_env_value(env_list->next->next->next), "1");

  EXPECT_EQ(get_env_key(env_list->next->next->next->next), nullptr);
  EXPECT_EQ(get_env_value(env_list->next->next->next->next), nullptr);

  destroy_env_list(env_list);
}
