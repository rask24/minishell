#include <fcntl.h>

#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "builtins.h"
}

TEST(builtins_pwd, WithoutArgs) {
  char *args[] = {strdup("pwd"), NULL};
  char *env[] = {NULL};
  testing::internal::CaptureStdout();
  int res = builtins_pwd(args, env);
  EXPECT_EQ(res, 0);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(),
               ft_strjoin(getcwd(NULL, 0), "\n"));
}
