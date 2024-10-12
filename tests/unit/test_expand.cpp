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

TEST(expand_variable_for_heredoc, NoExpand) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;

  char *string = strdup("USER");

  EXPECT_STREQ(expand_variable_for_heredoc(string, &ctx), "USER");

  destroy_env_list(env_list);
}

TEST(expand_variable_for_heredoc, OneVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;

  char *string = strdup("$USER");

  EXPECT_STREQ(expand_variable_for_heredoc(string, &ctx), "Alice");

  destroy_env_list(env_list);
}

TEST(expand_variable_for_heredoc, NoVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USERRRRR");
  char *ans = expand_variable_for_heredoc(string, &ctx);

  EXPECT_STREQ(ans, "");

  destroy_env_list(env_list);
  free(string);
  free(ans);
}

TEST(expand_variable_for_heredoc, StringAfterVariable) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("student$USER");
  char *ans = expand_variable_for_heredoc(string, &ctx);

  EXPECT_STREQ(ans, "studentAlice");

  destroy_env_list(env_list);
  free(string);
  free(ans);
}

TEST(expand_variable_for_heredoc, ManyVariables) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USERis$USER$USER$");
  char *ans = expand_variable_for_heredoc(string, &ctx);

  EXPECT_STREQ(ans, "AliceAlice$");

  destroy_env_list(env_list);
  free(string);
  free(ans);
}

TEST(expand_variable_for_heredoc, IgnoreSingleQuote) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USER'$USER'");
  char *ans = expand_variable_for_heredoc(string, &ctx);

  EXPECT_STREQ(ans, "Alice'Alice'");

  destroy_env_list(env_list);
  free(string);
  free(ans);
}

TEST(expand_variable_for_heredoc, DoNotIgnoreDoubleQuote) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USER\"$USER\"");
  char *ans = expand_variable_for_heredoc(string, &ctx);

  EXPECT_STREQ(ans, "Alice\"Alice\"");

  destroy_env_list(env_list);
  free(string);
  free(ans);
}

TEST(expand_variable_for_heredoc, SingleQuotePutAmongNonIdentifierChars) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USER,'$USER'");
  char *ans = expand_variable_for_heredoc(string, &ctx);

  EXPECT_STREQ(ans, "Alice,'Alice'");

  destroy_env_list(env_list);
  free(string);
  free(ans);
}

TEST(expand_variable_for_heredoc, DoubleQuoteAmongNonIdentifierChars) {
  char *envp[] = {strdup("USER=Alice"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;
  char *string = strdup("$USER,\"$USER\"");
  char *ans = expand_variable_for_heredoc(string, &ctx);

  EXPECT_STREQ(ans, "Alice,\"Alice\"");

  destroy_env_list(env_list);
  free(string);
  free(ans);
}

TEST(expand_variable_for_heredoc, ExitStatus) {
  t_ctx ctx;
  ctx.exit_status = 42;
  char *ans = expand_variable_for_heredoc(strdup("$?$?"), &ctx);
  EXPECT_STREQ(ans, "4242");

  free(ans);
}

TEST(expand_quotes, NoQuote) {
  char *string = strdup("hello");
  t_list *sample = ft_lstnew(string);
  t_list *ans = expand_quotes_on_list(sample);

  EXPECT_STREQ((char *)ans->content, "hello");

  ft_lstclear(&ans, free);
}

TEST(expand_quotes, SingleQuote) {
  t_list *sample = ft_lstnew(strdup("'$USER'"));
  t_list *ans = expand_quotes_on_list(sample);

  EXPECT_STREQ((char *)ans->content, "$USER");

  ft_lstclear(&ans, free);
}

TEST(expand_quotes, DoubleQuote) {
  t_list *sample = ft_lstnew(strdup("\"Alice\""));
  t_list *ans = expand_quotes_on_list(sample);

  EXPECT_STREQ((char *)ans->content, "Alice");

  ft_lstclear(&ans, free);
}

TEST(expand_quotes, QuotesAmongChars) {
  t_list *sample = ft_lstnew(strdup("TheNameIs\"Alice\",And'Bob'."));
  t_list *ans = expand_quotes_on_list(sample);

  EXPECT_STREQ((char *)ans->content, "TheNameIsAlice,AndBob.");

  ft_lstclear(&ans, free);
}

class FileTest : public testing::Test {
 protected:
  const std::vector<std::string> create_files = {"file1", "file2", "file3",
                                                 "filefile", "dir1"};
  const std::string test_dir = "wildcard_test_dir";

  void SetUp() override {
    ASSERT_EQ(mkdir(test_dir.c_str(), 0700), 0)
        << "Failed to create test directory: " << strerror(errno);
    ASSERT_EQ(chdir(test_dir.c_str()), 0)
        << "Failed to change to test directory: " << strerror(errno);
    for (const auto &file : create_files) {
      ASSERT_NE(creat(file.c_str(), 0700), -1)
          << "Failed to create file " << file << ": " << strerror(errno);
    }
  }

  void TearDown() override {
    for (const auto &file : create_files) {
      remove(file.c_str());
    }
    ASSERT_EQ(chdir(".."), 0)
        << "Failed to change to parent directory: " << strerror(errno);
    ASSERT_EQ(rmdir(test_dir.c_str()), 0)
        << "Failed to remove test directory: " << strerror(errno);
  }
};

std::set<std::string> t_list_to_string_set(const t_list *list) {
  std::set<std::string> result;
  while (list) {
    result.insert(std::string((char *)list->content));
    list = list->next;
  }
  return result;
}

bool AreListsEqual(t_list *list1, t_list *list2) {
  std::set<std::string> set1 = t_list_to_string_set(list1);
  std::set<std::string> set2 = t_list_to_string_set(list2);
  bool res = (set1 == set2);
  if (res == false) {
    if (set1.empty()) {
      std::cerr << "set1 is empty" << std::endl;
    } else {
      for (auto &i : set1) {
        std::cout << i << std::endl;
      }
    }
  }
  return res;
}

t_list *ret_expected(char **expected) {
  t_list *result;

  result = NULL;
  while (*expected) {
    ft_lstadd_back(&result, ft_xlstnew(ft_xstrdup(*expected)));
    expected++;
  }
  return (result);
}

// TEST_F(FileTest, OneWildcard) {
//   char *expected[] = {strdup("file1"),    strdup("file2"), strdup("file3"),
//                       strdup("filefile"), strdup("dir1"),  nullptr};
//   t_list *expected_list = ret_expected(expected);
//   t_list *ans = expand_wildcard_on_list(ft_xlstnew(strdup("*")));
//   EXPECT_TRUE(AreListsEqual(ans, expected_list));
//   ft_lstclear(&ans, free);
//   ft_lstclear(&expected_list, free);
// }

// TEST_F(FileTest, OneWildcardWithCommonPrefix) {
//   char *expected[] = {strdup("file1"), strdup("file2"), strdup("file3"),
//                       strdup("filefile"), nullptr};
//   t_list *expected_list = ret_expected(expected);
//   t_list *ans = expand_wildcard_on_list(ft_xlstnew(strdup("file*")));
//   EXPECT_TRUE(AreListsEqual(ans, expected_list));
//   ft_lstclear(&ans, free);
//   ft_lstclear(&expected_list, free);
// }

// TEST_F(FileTest, OneWildcardWithCommonSuffix) {
//   char *expected[] = {strdup("file1"), strdup("dir1"), nullptr};
//   t_list *expected_list = ret_expected(expected);
//   t_list *ans = expand_wildcard_on_list(ft_xlstnew(strdup("*1")));
//   EXPECT_TRUE(AreListsEqual(ans, expected_list));
//   ft_lstclear(&ans, free);
//   ft_lstclear(&expected_list, free);
// }

TEST_F(FileTest, FullNameWithWildcard) {
  char *expected[] = {strdup("file1"), nullptr};
  t_list *expected_list = ret_expected(expected);
  t_list *ans = expand_wildcard_on_list(ft_xlstnew(strdup("*file1")));
  EXPECT_TRUE(AreListsEqual(ans, expected_list));
  ft_lstclear(&ans, free);
  ft_lstclear(&expected_list, free);
}

// TEST_F(FileTest, FullNameWithWildcard2) {
//   char *expected[] = {strdup("file1"), nullptr};
//   t_list *expected_list = ret_expected(expected);
//   t_list *ans = expand_wildcard_on_list(ft_xlstnew(strdup("file1*")));
//   EXPECT_TRUE(AreListsEqual(ans, expected_list));
//   ft_lstclear(&ans, free);
//   ft_lstclear(&expected_list, free);
// }

TEST_F(FileTest, Nomatch) {
  char *expected[] = {strdup("*11"), nullptr};
  t_list *expected_list = ret_expected(expected);
  t_list *ans = expand_wildcard_on_list(ft_xlstnew(strdup("*11")));
  EXPECT_TRUE(AreListsEqual(ans, expected_list));
  ft_lstclear(&ans, free);
  ft_lstclear(&expected_list, free);
}

// TEST_F(FileTest, FailsInShortMatchButNotInLongMatch) {
//   char *expected[] = {strdup("filefile"), nullptr};
//   t_list *expected_list = ret_expected(expected);
//   t_list *ans = expand_wildcard_on_list(ft_xlstnew(strdup("*e")));
//   EXPECT_TRUE(AreListsEqual(ans, expected_list));
//   ft_lstclear(&ans, free);
//   ft_lstclear(&expected_list, free);
// }

TEST_F(FileTest, FullNameWithWildcardCrazy) {
  char *expected[] = {strdup("file1"), nullptr};
  t_list *expected_list = ret_expected(expected);
  t_list *ans =
      expand_wildcard_on_list(ft_xlstnew(strdup("**fi**le1*********")));
  EXPECT_TRUE(AreListsEqual(ans, expected_list));
  ft_lstclear(&ans, free);
  ft_lstclear(&expected_list, free);
}

TEST_F(FileTest, NoFiles) {
  const std::string test_dir = "wildcard_test_dir";
  const std::vector<std::string> create_files1 = {"file1", "file2", "file3",
                                                  "filefile", "dir1"};
  for (const auto &file : create_files1) {
    std::remove(file.c_str());
  }

  char *expected[] = {strdup("*"), nullptr};
  t_list *expected_list = ret_expected(expected);
  t_list *ans = expand_wildcard_on_list(ft_xlstnew(strdup("*")));
  EXPECT_TRUE(AreListsEqual(ans, expected_list));
  ft_lstclear(&ans, free);
  ft_lstclear(&expected_list, free);
}

TEST(expand_variable_on_list, SpaceIsNotIFSPutInsideQuotes) {
  t_list *list = nullptr;
  std::vector<std::string> input = {"'hello world'"};
  for (const auto &i : input) {
    ft_lstadd_back(&list, ft_xlstnew(strdup(i.c_str())));
  }

  t_list *result = expand_variable_on_list(list, NULL);

  EXPECT_STREQ((char *)result->content, "'hello world'");

  ft_lstclear(&result, free);
  ft_lstclear(&list, free);
}

TEST(expand_variable_on_list, VariableWithIFS) {
  char *envp[] = {strdup("GREET=hello world"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;

  t_list *ans = expand_variable_on_list(ft_xlstnew(ft_xstrdup("$GREET")), &ctx);
  EXPECT_STREQ((char *)ans->content, "hello");
  EXPECT_STREQ((char *)ans->next->content, "world");

  destroy_env_list(env_list);
  ft_lstclear(&ans, free);
}

TEST(expand_variable_on_list, VariableWithIFSAhead) {
  char *envp[] = {strdup("GREET=  hello world"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;

  t_list *ans =
      expand_variable_on_list(ft_xlstnew(ft_xstrdup("42$GREET")), &ctx);
  EXPECT_STREQ((char *)ans->content, "42");
  EXPECT_STREQ((char *)ans->next->content, "hello");
  EXPECT_STREQ((char *)ans->next->next->content, "world");

  destroy_env_list(env_list);
  ft_lstclear(&ans, free);
}

TEST(expand_variable_on_list, VariableWithIFSAfter) {
  char *envp[] = {strdup("GREET=hello world   "), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;

  t_list *ans =
      expand_variable_on_list(ft_xlstnew(ft_xstrdup("$GREET,42")), &ctx);
  EXPECT_STREQ((char *)ans->content, "hello");
  EXPECT_STREQ((char *)ans->next->content, "world");
  EXPECT_STREQ((char *)ans->next->next->content, ",42");

  destroy_env_list(env_list);
  ft_lstclear(&ans, free);
}

TEST(expand_variable_on_list, VariableWithIFSAndVariable) {
  char *envp[] = {strdup("GREET=hello world   "), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;

  t_list *ans =
      expand_variable_on_list(ft_xlstnew(ft_xstrdup("$GREET$GREET")), &ctx);
  EXPECT_STREQ((char *)ans->content, "hello");
  EXPECT_STREQ((char *)ans->next->content, "world");
  EXPECT_STREQ((char *)ans->next->next->content, "hello");
  EXPECT_STREQ((char *)ans->next->next->next->content, "world");

  destroy_env_list(env_list);
  ft_lstclear(&ans, free);
}

TEST(expand_variable_on_list, VariableWithIFSSurroundedBySingleQuotes) {
  char *envp[] = {strdup("GREET=hello world   "), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;

  t_list *ans = expand_variable_on_list(
      ft_xlstnew(ft_xstrdup("'paris'$GREET'tokyo'")), &ctx);
  EXPECT_STREQ((char *)ans->content, "'paris'hello");
  EXPECT_STREQ((char *)ans->next->content, "world");
  EXPECT_STREQ((char *)ans->next->next->content, "'tokyo'");

  destroy_env_list(env_list);
  ft_lstclear(&ans, free);
}

TEST(expand_variable_on_list, ApplyOnList) {
  t_list *list = nullptr;
  std::vector<std::string> input = {"Hello", "$MULTIWORD", "World"};
  for (const auto &i : input) {
    ft_lstadd_back(&list, ft_xlstnew(strdup(i.c_str())));
  }
  char *envp[] = {strdup("MULTIWORD=\tMultiple Words Here\t"), nullptr};
  t_env_list *env_list = convert_array_to_env(envp);
  t_ctx ctx;
  ctx.env = env_list;

  t_list *result = expand_variable_on_list(list, &ctx);

  EXPECT_STREQ((char *)result->content, "Hello");
  EXPECT_STREQ((char *)result->next->content, "Multiple");
  EXPECT_STREQ((char *)result->next->next->content, "Words");
  EXPECT_STREQ((char *)result->next->next->next->content, "Here");
  EXPECT_STREQ((char *)result->next->next->next->next->content, "World");

  ft_lstclear(&result, free);
  ft_lstclear(&list, free);
}
