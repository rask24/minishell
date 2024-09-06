#include <fcntl.h>

#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "../../include/builtins.h"
}

typedef int (*builtins_func)(char **argc, char **argv);

static char *test_helper(builtins_func f, char **args, char **argv) {
  int pipefd[2];
  pipe(pipefd);
  if (errno) {
    return (NULL);
  }
  int write_fd = pipefd[1];
  int read_fd = pipefd[0];

  int in_fd = dup(STDOUT_FILENO);
  if (errno) {
    return (NULL);
  }
  dup2(write_fd, STDOUT_FILENO);
  if (errno) {
    return (NULL);
  }

  f(args, argv);

  char *buf = (char *)malloc(100);
  if (errno) {
    return (NULL);
  }
  read(read_fd, buf, 100);
  if (errno) {
    return (NULL);
  }

  dup2(in_fd, STDOUT_FILENO);
  if (errno) {
    return (NULL);
  }

  close(read_fd);
  close(write_fd);
  return (buf);
}

TEST(builtins_pwd, WithoutArgs) {
  char *args[] = {NULL};
  char *env[] = {NULL};

  char *result = test_helper(builtins_pwd, args, env);
  if (!result) {
    dprintf(STDERR_FILENO, "syscall error\n");
    EXPECT_FALSE(true);
    return;
  }
  char *expected = ft_strjoin(getcwd(NULL, 0), "\n");

  EXPECT_STREQ(result, expected);
  free(result);
}
