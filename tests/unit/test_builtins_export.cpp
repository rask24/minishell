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

  t_ctx config;
  config.env = env;

  char *args[] = {ft_strdup("export"), NULL};
  testing::internal::CaptureStdout();
  int result = builtins_export(args, &config);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_STREQ(output.c_str(),
               "declare -x key=\"value\"\n"
               "declare -x key1=\"value1\"\n"
               "declare -x key2=\"value2\"\n");
  EXPECT_EQ(result, 0);
}

TEST(builtins_export, AddArgs) {
  t_env_list *env = construct_env(strdup("key0"), strdup("value0"));
  t_env_list *env1 = construct_env(strdup("key2"), strdup("value2"));
  t_env_list *env2 = construct_env(strdup("key1"), strdup("value1"));
  ft_lstadd_back(&env, env1);
  ft_lstadd_back(&env, env2);

  t_ctx config;
  config.env = env;

  char *args[] = {ft_strdup("export"), ft_strdup("key3=value3"), NULL};
  builtins_export(args, &config);

  char *args1[] = {ft_strdup("export"), NULL};
  testing::internal::CaptureStdout();
  int result = builtins_export(args1, &config);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_STREQ(output.c_str(),
               "declare -x key0=\"value0\"\n"
               "declare -x key1=\"value1\"\n"
               "declare -x key2=\"value2\"\n"
               "declare -x key3=\"value3\"\n");
  EXPECT_EQ(result, 0);
}

TEST(builtins_export, AddMoreArgs) {
  t_env_list *env = construct_env(strdup("key0"), strdup("value0"));
  t_env_list *env1 = construct_env(strdup("key2"), strdup("value2"));
  t_env_list *env2 = construct_env(strdup("key1"), strdup("value1"));
  ft_lstadd_back(&env, env1);
  ft_lstadd_back(&env, env2);

  t_ctx config;
  config.env = env;

  char *args[] = {ft_strdup("export"), ft_strdup("key3=value3"),
                  ft_strdup("key4=value4"), NULL};
  builtins_export(args, &config);

  char *args1[] = {ft_strdup("export"), NULL};

  testing::internal::CaptureStdout();
  int result = builtins_export(args1, &config);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_STREQ(output.c_str(),
               "declare -x key0=\"value0\"\n"
               "declare -x key1=\"value1\"\n"
               "declare -x key2=\"value2\"\n"
               "declare -x key3=\"value3\"\n"
               "declare -x key4=\"value4\"\n");
  EXPECT_EQ(result, 0);
}

TEST(builtins_export, AddDupArgs) {
  t_env_list *env = construct_env(strdup("key0"), strdup("value0"));
  t_env_list *env1 = construct_env(strdup("key2"), strdup("value2"));
  t_env_list *env2 = construct_env(strdup("key1"), strdup("value1"));
  ft_lstadd_back(&env, env1);
  ft_lstadd_back(&env, env2);

  t_ctx config;
  config.env = env;

  char *args[] = {ft_strdup("export"), ft_strdup("key3=value3"),
                  ft_strdup("key3=value3_ver2"), NULL};
  builtins_export(args, &config);

  char *args1[] = {ft_strdup("export"), NULL};

  testing::internal::CaptureStdout();
  int result = builtins_export(args1, &config);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_STREQ(output.c_str(),
               "declare -x key0=\"value0\"\n"
               "declare -x key1=\"value1\"\n"
               "declare -x key2=\"value2\"\n"
               "declare -x key3=\"value3_ver2\"\n");
  EXPECT_EQ(result, 0);
}

// TEST(builtins_export, NokeyArg) {
//   t_env_list *env = construct_env(strdup("key0"), strdup("value0"));
//   t_env_list *env1 = construct_env(strdup("key2"), strdup("value2"));
//   t_env_list *env2 = construct_env(strdup("key1"), strdup("value1"));
//   ft_lstadd_back(&env, env1);
//   ft_lstadd_back(&env, env2);

//   t_ctx config;
//   config.env = env;

//   char *args[] = {ft_strdup("export"), ft_strdup("=value3"), NULL};
//   // redirect STDOUT to STDERR because GitHubActions does not support stderr
//   // capture
//   int tmp_stderr = dup(STDERR_FILENO);
//   dup2(STDOUT_FILENO, STDERR_FILENO);
//   testing::internal::CaptureStderr();
//   int result = builtins_export(args, &config);
//   std::string output = testing::internal::GetCapturedStderr();
//   dup2(tmp_stderr, STDERR_FILENO);

//   EXPECT_STREQ(output.c_str(),
//                "minishell: export: =value3: not a valid identifier\n");
//   EXPECT_EQ(result, 1);
// }

TEST(builtins_export, NoEqualArg) {
  t_env_list *env = construct_env(strdup("key0"), strdup("value0"));
  t_env_list *env1 = construct_env(strdup("key2"), strdup("value2"));
  t_env_list *env2 = construct_env(strdup("key1"), strdup("value1"));
  ft_lstadd_back(&env, env1);
  ft_lstadd_back(&env, env2);

  t_ctx config;
  config.env = env;

  char *args[] = {ft_strdup("export"), ft_strdup("key3"), NULL};
  builtins_export(args, &config);

  char *args1[] = {ft_strdup("export"), NULL};

  testing::internal::CaptureStdout();
  int result = builtins_export(args1, &config);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_STREQ(output.c_str(),
               "declare -x key0=\"value0\"\n"
               "declare -x key1=\"value1\"\n"
               "declare -x key2=\"value2\"\n"
               "declare -x key3\n");
  EXPECT_EQ(result, 0);
}

TEST(builtins_export, EnvIsNULL) {
  t_ctx config;
  config.env = NULL;

  char *args[] = {ft_strdup("export"), NULL};
  testing::internal::CaptureStdout();
  int result = builtins_export(args, &config);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_STREQ(output.c_str(), "");
  EXPECT_EQ(result, 0);
}
