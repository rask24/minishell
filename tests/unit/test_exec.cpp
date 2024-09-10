#include "gtest/gtest.h"

extern "C" {
#include "exec.h"
}

typedef void (*func)(char *command, char **envp);

__attribute__((unused)) static char *test_helper(func f, char *command,
                                                 char **envp) {
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

  f(command, envp);

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

// FIXME: This test is not working
// TEST(exec, OneWord) {
//   char *str = strdup("echo 'hello'");
//   char *answer = test_helper(spawn_process, str, NULL);
//   EXPECT_STREQ(answer, "hello\n");
// }
