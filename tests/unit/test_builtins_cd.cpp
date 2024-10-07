#include <fcntl.h>

#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "builtins.h"
}

TEST(builtins_cd, WithoutArgs) {
  char *args[] = {strdup("cd"), NULL};
  t_env_list *env = construct_env(strdup("HOME"), strdup(getenv("HOME")));

  t_ctx ctx;
  ctx.env = env;
  ctx.cwd = getcwd(NULL, 0);

  builtins_cd(args, &ctx);
  char *expected = getcwd(NULL, 0);

  EXPECT_STREQ(expected, getenv("HOME"));
}
