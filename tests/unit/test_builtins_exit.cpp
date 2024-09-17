
#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "builtins.h"
}

typedef struct s_result {
  char *buf;
  int res;
} t_result;

TEST(builtins_exit, NoArg) {
  char *args[] = {strdup("exit"), NULL};

  t_config config;
  config.exit_status = 0;

  EXPECT_EXIT(builtins_exit(args, &config), ::testing::ExitedWithCode(0),
              "exit\n");
}

TEST(builtins_exit, OneArgNormal) {
  char *args[] = {strdup("exit"), strdup("0"), NULL};

  EXPECT_EXIT(builtins_exit(args, NULL), ::testing::ExitedWithCode(0),
              "exit\n");
}

TEST(builtins_exit, OneArgError) {
  char *args[] = {strdup("exit"), strdup("42"), NULL};

  EXPECT_EXIT(builtins_exit(args, NULL), ::testing::ExitedWithCode(42),
              "exit\n");
}

TEST(builtins_exit, OneArgErrorPlus) {
  char *args[] = {strdup("exit"), strdup("+42"), NULL};

  EXPECT_EXIT(builtins_exit(args, NULL), ::testing::ExitedWithCode(42),
              "exit\n");
}

TEST(builtins_exit, OneArgError1) {
  char *args[] = {strdup("exit"), strdup("-1"), NULL};

  EXPECT_EXIT(builtins_exit(args, NULL), ::testing::ExitedWithCode(255),
              "exit\n");
}

TEST(builtins_exit, OneArgError2) {
  char *args[] = {strdup("exit"), strdup("2147483649"), NULL};

  EXPECT_EXIT(builtins_exit(args, NULL), ::testing::ExitedWithCode(1),
              "exit\n");
}

TEST(builtins_exit, OneArgError3) {
  char *args[] = {strdup("exit"), strdup("9223372036854775807"), NULL};

  EXPECT_EXIT(builtins_exit(args, NULL), ::testing::ExitedWithCode(255),
              "exit\n");
}

// TEST(builtins_exit, OneArgError4) {
//   char *args[] = {strdup("exit"), strdup("9223372036854775808"), NULL};

//   EXPECT_EXIT(
//       builtins_exit(args, NULL), ::testing::ExitedWithCode(2),
//       "minishell: exit: 9223372036854775808: numeric argument required\n");
// }

// TEST(builtins_exit, OneArgError5) {
//   char *args[] = {strdup("exit"), strdup("42fourtytwo"), NULL};

//   EXPECT_EXIT(builtins_exit(args, NULL), ::testing::ExitedWithCode(2),
//               "minishell: exit: 42fourtytwo: numeric argument required\n");
// }

TEST(builtins_exit, OneArgError6) {
  char *args[] = {strdup("exit"), strdup("000042"), NULL};

  EXPECT_EXIT(builtins_exit(args, NULL), ::testing::ExitedWithCode(42),
              "exit\n");
}

// TEST(builtins_exit, OneArgErrorPlusOnly) {
//   char *args[] = {strdup("exit"), strdup("+"), NULL};

//   EXPECT_EXIT(builtins_exit(args, NULL), ::testing::ExitedWithCode(2),
//               "minishell: exit: \\+: numeric argument required\n");
// }

// TEST(builtins_exit, MultiArgs) {
//   char *args[] = {strdup("exit"), strdup("0"), strdup("1"), NULL};

//   t_result result;
//   void *res = test_helper(builtins_exit, args, NULL, &result);
//   if (res == NULL) {
//     exit(1);
//   }

//   EXPECT_STREQ(result.buf, "exit\nminishell: exit: too many arguments\n");
//   EXPECT_EQ(result.res, EXIT_FAILURE);
// }

TEST(builtins_exit, WithHyphen) {
  char *args[] = {strdup("exit"), strdup("--"), strdup("1"), NULL};

  EXPECT_EXIT(builtins_exit(args, NULL), ::testing::ExitedWithCode(1),
              "exit\n");
}
