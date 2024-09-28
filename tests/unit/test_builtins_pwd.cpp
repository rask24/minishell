#include <fcntl.h>

#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "builtins.h"
}

TEST(builtins_pwd, WithoutArgs) {
  char *args[] = {strdup("pwd"), NULL};
  t_ctx ctx;
  testing::internal::CaptureStdout();
  int res = builtins_pwd(args, &ctx);
  EXPECT_EQ(res, 0);
  EXPECT_STREQ(testing::internal::GetCapturedStdout().c_str(),
               ft_strjoin(getcwd(NULL, 0), "\n"));
}
