#include "gtest/gtest.h"

extern "C" {
#include "exec.h"
}

TEST(exec, OneWord) {
  char *str = strdup("echo 'hello'");

  testing::internal::CaptureStdout();
  spawn_process(str, NULL);

  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(), "hello\n");
  (void)str;
}
