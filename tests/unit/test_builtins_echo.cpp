#include <fcntl.h>

#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "../../include/builtins.h"
}

TEST(builtins_echo, WithoutN) {
  char *args[] = {strdup("echo"), strdup("Hello, world!"), NULL};
  char *env[] = {NULL};

  testing::internal::CaptureStdout();
  builtins_echo(args, env);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(),
               "Hello, world!\n");
}

TEST(builtins_echo, WithN) {
  char *args[] = {strdup("echo"), strdup("-n"), strdup("Hello, world!"), NULL};
  char *env[] = {NULL};

  testing::internal::CaptureStdout();
  builtins_echo(args, env);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(), "Hello, world!");
}

TEST(builtins_echo, WithMultipleN) {
  char *args[] = {strdup("echo"), strdup("-nnnnn"), strdup("Hello, world!"),
                  NULL};
  char *env[] = {NULL};

  testing::internal::CaptureStdout();
  builtins_echo(args, env);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(), "Hello, world!");
}

TEST(builtins_echo, WithMultipleFakeN) {
  char *args[] = {strdup("echo"), strdup("-nnnnng"), strdup("Hello, world!"),
                  NULL};
  char *env[] = {NULL};

  testing::internal::CaptureStdout();
  builtins_echo(args, env);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(),
               "-nnnnng Hello, world!\n");
}

TEST(builtins_echo, WithMultipleNWithMultipleWords) {
  char *args[] = {strdup("echo"), strdup("-n"), strdup("Hello, world!"),
                  strdup("42"), NULL};
  char *env[] = {NULL};

  testing::internal::CaptureStdout();
  builtins_echo(args, env);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(),
               "Hello, world! 42");
}

TEST(builtins_echo, WithoutNWithMultipleWords) {
  char *args[] = {strdup("echo"), strdup("Hello, world!"), strdup("42"), NULL};
  char *env[] = {NULL};

  testing::internal::CaptureStdout();
  builtins_echo(args, env);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(),
               "Hello, world! 42\n");
}
