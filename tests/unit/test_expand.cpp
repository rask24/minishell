#include <fcntl.h>

#include <cstring>
#include <filesystem>
#include <iostream>
#include <set>

#include "gtest/gtest.h"

extern "C" {
#include "env.h"
#include "expansion.h"
#include "expansion/expansion_internal.h"
}

TEST(expand_variable, NoExpand) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;

  char *string = strdup("USER");

  EXPECT_STREQ(expand_variable(string, &ctx), "USER");

  destroy_env_list(env_list);
}

TEST(expand_variable, OneVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;

  char *string = strdup("$USER");

  EXPECT_STREQ(expand_variable(string, &ctx), "Alice");

  destroy_env_list(env_list);
}

TEST(expand_variable, NoVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USERRRRR");

  EXPECT_STREQ(expand_variable(string, &ctx), "");

  destroy_env_list(env_list);
}

TEST(expand_variable, StringAfterVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("student$USER");

  EXPECT_STREQ(expand_variable(string, &ctx), "studentAlice");

  destroy_env_list(env_list);
}

TEST(expand_variable, ManyVariables) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USERis$USER$USER$");

  EXPECT_STREQ(expand_variable(string, &ctx), "AliceAlice$");

  destroy_env_list(env_list);
}

TEST(expand_variable, IgnoreSingleQuote) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USER'$USER'");

  EXPECT_STREQ(expand_variable(string, &ctx), "Alice'$USER'");

  destroy_env_list(env_list);
}

TEST(expand_variable, DoNotIgnoreDoubleQuote) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USER\"$USER\"");

  EXPECT_STREQ(expand_variable(string, &ctx), "Alice\"Alice\"");

  destroy_env_list(env_list);
}

TEST(expand_variable, SingleQuotePutAmongNonIdentifierChars) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USER,'$USER'");

  EXPECT_STREQ(expand_variable(string, &ctx), "Alice,'$USER'");

  destroy_env_list(env_list);
}

TEST(expand_variable, DoubleQuoteAmongNonIdentifierChars) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USER,\"$USER\"");

  EXPECT_STREQ(expand_variable(string, &ctx), "Alice,\"Alice\"");

  destroy_env_list(env_list);
}

TEST(expand_variable, ExitStatus) {
  t_ctx ctx;
  ctx.exit_status = 42;
  EXPECT_STREQ(expand_variable(strdup("$?$?"), &ctx), "4242");
}

TEST(expand_quotes, NoQuote) {
  char *string = strdup("hello");

  EXPECT_STREQ(expand_quotes(string), "hello");
}

TEST(expand_quotes, SingleQuote) {
  char *string = strdup("'$USER'");

  EXPECT_STREQ(expand_quotes(string), "$USER");
}

TEST(expand_quotes, DoubleQuote) {
  char *string = strdup("\"Alice\"");

  EXPECT_STREQ(expand_quotes(string), "Alice");
}

TEST(expand_quotes, QuotesAmongChars) {
  char *string = strdup("TheNameIs\"Alice\",And'Bob'.");

  EXPECT_STREQ(expand_quotes(string), "TheNameIsAlice,AndBob.");
}

class FileTest : public testing::Test {
 protected:
  //  private:
  char *create_files[6] = {strdup("file1"),    strdup("file2"), strdup("file3"),
                           strdup("filefile"), strdup("dir1"),  nullptr};
  char *test_dir = strdup("wildcard_test_dir");

  void SetUp() override {
    mkdir(test_dir, 0700);
    chdir(test_dir);
    for (int i = 0; create_files[i] != nullptr; i++) {
      creat(create_files[i], 0700);
    }
  }

  void TearDown() override {
    for (int i = 0; create_files[i] != nullptr; i++) {
      remove(create_files[i]);
      free(create_files[i]);
    }
    chdir("..");
    rmdir(test_dir);
    free(test_dir);
  }
};

std::set<std::string> charArrayToStringSet(char **arr) {
  std::set<std::string> result;
  while (*arr) {
    result.insert(std::string(*arr));
    ++arr;
  }
  return result;
}

bool areCharArraysEqual(char **arr1, char **arr2) {
  std::set<std::string> set1 = charArrayToStringSet(arr1);
  std::set<std::string> set2 = charArrayToStringSet(arr2);
  bool res = (set1 == set2);
  if (res == false) {
    if (set1.empty()) {
      std::cout << "set1 is empty" << std::endl;
    } else {
      for (auto &i : set1) {
        std::cout << i << std::endl;
      }
    }
  }
  return res;
}

TEST_F(FileTest, OneWildcard) {
  char *expected[] = {strdup("file1"),    strdup("file2"), strdup("file3"),
                      strdup("filefile"), strdup("dir1"),  nullptr};
  char **ans = expand_wildcard(strdup("*"), nullptr);
  EXPECT_TRUE(areCharArraysEqual(ans, expected));
  ft_free_strs(ans);
  for (int i = 0; expected[i] != nullptr; i++) {
    free(expected[i]);
  }
}

TEST_F(FileTest, OneWildcardWithCommonPrefix) {
  char *expected[] = {strdup("file1"), strdup("file2"), strdup("file3"),
                      strdup("filefile"), nullptr};
  char **ans = expand_wildcard(strdup("file*"), nullptr);
  EXPECT_TRUE(areCharArraysEqual(ans, expected));
  ft_free_strs(ans);
  for (int i = 0; expected[i] != nullptr; i++) {
    free(expected[i]);
  }
}

TEST_F(FileTest, OneWildcardWithCommonSuffix) {
  char *expected[] = {strdup("file1"), strdup("dir1"), nullptr};
  char **ans = expand_wildcard(strdup("*1"), nullptr);
  EXPECT_TRUE(areCharArraysEqual(ans, expected));
  ft_free_strs(ans);
  for (int i = 0; expected[i] != nullptr; i++) {
    free(expected[i]);
  }
}

TEST_F(FileTest, FullNameWithWildcard) {
  char *expected[] = {strdup("file1"), nullptr};
  char **ans = expand_wildcard(strdup("*file1"), nullptr);
  EXPECT_TRUE(areCharArraysEqual(ans, expected));
  ft_free_strs(ans);
  for (int i = 0; expected[i] != nullptr; i++) {
    free(expected[i]);
  }
}

TEST_F(FileTest, FullNameWithWildcard2) {
  char *expected[] = {strdup("file1"), nullptr};
  char **ans = expand_wildcard(strdup("file1*"), nullptr);
  EXPECT_TRUE(areCharArraysEqual(ans, expected));
  ft_free_strs(ans);
  for (int i = 0; expected[i] != nullptr; i++) {
    free(expected[i]);
  }
}

TEST_F(FileTest, Nomatch) {
  char *expected[] = {strdup("*11"), nullptr};
  char **ans = expand_wildcard(strdup("*11"), nullptr);
  EXPECT_TRUE(areCharArraysEqual(ans, expected));
  ft_free_strs(ans);
  for (int i = 0; expected[i] != nullptr; i++) {
    free(expected[i]);
  }
}

TEST_F(FileTest, FailsInShortMatchButNotInLongMatch) {
  char *expected[] = {strdup("filefile"), nullptr};
  char **ans = expand_wildcard(strdup("*e"), nullptr);
  EXPECT_TRUE(areCharArraysEqual(ans, expected));
  ft_free_strs(ans);
  for (int i = 0; expected[i] != nullptr; i++) {
    free(expected[i]);
  }
}

TEST_F(FileTest, FullNameWithWildcardCrazy) {
  char *expected[] = {strdup("file1"), nullptr};
  char **ans = expand_wildcard(strdup("**fi**le1*********"), nullptr);
  EXPECT_TRUE(areCharArraysEqual(ans, expected));
  ft_free_strs(ans);
  for (int i = 0; expected[i] != nullptr; i++) {
    free(expected[i]);
  }
}

TEST(expand_variable_on_list, NoExpand) {
  t_list *list = nullptr;
  std::vector<std::string> input = {"Hello", "$MULTIWORD", "World"};
  for (const auto &i : input) {
    ft_lstadd_back(&list, ft_xlstnew(strdup(i.c_str())));
  }
  char *envp[] = {strdup("MULTIWORD=Multiple Words Here"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;

  t_list *result = expand_variable_on_list(list, &ctx);

  std::vector<std::string> expected = {"Hello", "Multiple", "Words", "Here",
                                       "World"};
  EXPECT_STREQ((char *)result->content, "Hello");
  EXPECT_STREQ((char *)result->next->content, "Multiple");
  EXPECT_STREQ((char *)result->next->next->content, "Words");
  EXPECT_STREQ((char *)result->next->next->next->content, "Here");
  EXPECT_STREQ((char *)result->next->next->next->next->content, "World");

  ft_lstclear(&result, free);
}
