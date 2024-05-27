// Copyright 2024, reasuke.

#include <cstdio>
#include <cstring>

#include "gtest/gtest.h"

extern "C" {
#include "exec.h"
}

TEST(resolve_command_path, envNotFound) {
  char *envp[] = {NULL};
  const char *expected = NULL;

  EXPECT_EQ(resolve_command_path("cat", envp), expected);
}

TEST(resolve_command_path, envPathNotFound) {
  char *envp[] = {const_cast<char *>("PWD=/home/rask24/clnag"), NULL};
  const char *expected = NULL;

  EXPECT_EQ(resolve_command_path("cat", envp), expected);
}

TEST(resolve_command_path, envOnlyPathFound) {
  char *envp[] = {
      const_cast<char *>(
          "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"),
      NULL};
  const char *expected = "/bin/cat";

  EXPECT_EQ(strcmp(resolve_command_path("cat", envp), expected), 0);
}

TEST(resolve_command_path, envPathFound) {
  char *envp[] = {
      const_cast<char *>("LANG=en_US.UTF-8"),
      const_cast<char *>("USER=reasuke"),
      const_cast<char *>("LOGNAME=reasuke"),
      const_cast<char *>("HOME=/home/reasuke"),
      const_cast<char *>(
          "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"),
      NULL};
  const char *expected = "/bin/cat";

  EXPECT_EQ(strcmp(resolve_command_path("cat", envp), expected), 0);
}
