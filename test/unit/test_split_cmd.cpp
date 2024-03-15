// Copyright 2024, reasuke.

#include <cstdio>
#include <cstring>
#include <string>

#include "gtest/gtest.h"

extern "C" {
#include "split_cmd.h"
}

TEST(split_cmd, commandOnly) {
  const char *input = "cat";
  char **cmds = split_cmd(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("cat"));
  EXPECT_EQ(cmds[1], nullptr);
}

TEST(split_cmd, commandWithOneOption) {
  const char *input = "cat -e";
  char **cmds = split_cmd(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("cat"));
  EXPECT_EQ(std::string(cmds[1]), std::string("-e"));
  EXPECT_EQ(cmds[2], nullptr);
}

TEST(split_cmd, commandWithTwoOptions) {
  const char *input = "grep -rn hello";
  char **cmds = split_cmd(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmds[1]), std::string("-rn"));
  EXPECT_EQ(std::string(cmds[2]), std::string("hello"));
  EXPECT_EQ(cmds[3], nullptr);
}

TEST(split_cmd, commandWithDelimitedByTab) {
  const char *input = "cat\t-e";
  char **cmds = split_cmd(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("cat"));
  EXPECT_EQ(std::string(cmds[1]), std::string("-e"));
  EXPECT_EQ(cmds[2], nullptr);
}

TEST(split_cmd, commandWithSingleQuotation) {
  const char *input = "grep 'message: hello'";
  char **cmds = split_cmd(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmds[1]), std::string("message: hello"));
  EXPECT_EQ(cmds[2], nullptr);
}

TEST(split_cmd, commandWithDoubleQuotation) {
  const char *input = "grep \"message: hello\"";
  char **cmds = split_cmd(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmds[1]), std::string("message: hello"));
  EXPECT_EQ(cmds[2], nullptr);
}

TEST(split_cmd, commandWithEscapedDoubleQuotation) {
  const char *input = "grep \"message\\\"hello\"";
  char **cmds = split_cmd(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmds[1]), std::string("message\"hello"));
  EXPECT_EQ(cmds[2], nullptr);
}
