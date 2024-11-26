#include <fcntl.h>

#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "builtins.h"
}

TEST(builtins_echo, WithoutN) {
  // echo Hello, world!
  char *args[] = {strdup("echo"), strdup("Hello, world!"), NULL};
  t_ctx ctx;

  testing::internal::CaptureStdout();
  builtins_echo(args, &ctx);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(),
               "Hello, world!\n");
}

TEST(builtins_echo, WithN) {
  // echo -n Hello, world!
  char *args[] = {strdup("echo"), strdup("-n"), strdup("Hello, world!"), NULL};
  t_ctx ctx;

  testing::internal::CaptureStdout();
  builtins_echo(args, &ctx);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(), "Hello, world!");
}

TEST(builtins_echo, WithMultipleN) {
  // echo -nnnnn Hello, world!
  char *args[] = {strdup("echo"), strdup("-nnnnn"), strdup("Hello, world!"),
                  NULL};
  t_ctx ctx;

  testing::internal::CaptureStdout();
  builtins_echo(args, &ctx);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(), "Hello, world!");
}

TEST(builtins_echo, WithMultipleFakeN) {
  // echo -nnnnng Hello, world!
  char *args[] = {strdup("echo"), strdup("-nnnnng"), strdup("Hello, world!"),
                  NULL};
  t_ctx ctx;

  testing::internal::CaptureStdout();
  builtins_echo(args, &ctx);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(),
               "-nnnnng Hello, world!\n");
}

TEST(builtins_echo, WithMultipleNWithMultipleWords) {
  // echo -n Hello, world! 42
  char *args[] = {strdup("echo"), strdup("-n"), strdup("Hello, world!"),
                  strdup("42"), NULL};
  t_ctx ctx;

  testing::internal::CaptureStdout();
  builtins_echo(args, &ctx);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(),
               "Hello, world! 42");
}

TEST(builtins_echo, WithoutNWithMultipleWords) {
  // echo Hello, world! 42
  char *args[] = {strdup("echo"), strdup("Hello, world!"), strdup("42"), NULL};
  t_ctx ctx;

  testing::internal::CaptureStdout();
  builtins_echo(args, &ctx);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(),
               "Hello, world! 42\n");
}

TEST(builtins_echo, BrokenNoption) {
  // echo - n Hello
  char *args[] = {strdup("echo"), strdup("-"), strdup("n"), strdup("Hello"),
                  NULL};
  t_ctx ctx;

  testing::internal::CaptureStdout();
  builtins_echo(args, &ctx);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(), "- n Hello\n");
}

TEST(builtins_echo, MultipleOption) {
  // echo -n -n Hello
  char *args[] = {strdup("echo"), strdup("-n"), strdup("-n"), strdup("Hello"),
                  NULL};
  t_ctx ctx;

  testing::internal::CaptureStdout();
  builtins_echo(args, &ctx);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(), "Hello");
}

TEST(builtins_echo, MultipleOption2) {
  // echo -n Hello -n
  char *args[] = {strdup("echo"), strdup("-n"), strdup("Hello"), strdup("-n"),
                  NULL};
  t_ctx ctx;

  testing::internal::CaptureStdout();
  builtins_echo(args, &ctx);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(), "Hello -n");
}

TEST(builtins_echo, MultipleOption3) {
  // echo -nnnn Hello -n
  char *args[] = {strdup("echo"), strdup("-nnnn"), strdup("Hello"),
                  strdup("-n"), NULL};
  t_ctx ctx;

  testing::internal::CaptureStdout();
  builtins_echo(args, &ctx);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(), "Hello -n");
}
