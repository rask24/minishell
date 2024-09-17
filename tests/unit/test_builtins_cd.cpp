#include <fcntl.h>

#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "builtins.h"
}

// TEST(join_path, RelativePath) {
//   const char *ans = join_path(getenv("HOME"), "tests");
//   EXPECT_STREQ(ans, ft_strjoin(getenv("HOME"), "/tests"));
// }

// TEST(join_path, RelativePath2) {
//   const char *ans = join_path("/", "bin/");
//   EXPECT_STREQ(ans, "/bin/");
// }

TEST(builtins_cd, WithoutArgs) {
  char *args[] = {strdup("cd"), NULL};

  builtins_cd(args, NULL);
  char *expected = getcwd(NULL, 0);

  EXPECT_STREQ(expected, getenv("HOME"));
}
