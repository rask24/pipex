// Copyright 2024, reasuke.

#include <cstdio>
#include <cstring>
#include <string>

#include "gtest/gtest.h"

extern "C" {
#include "split_word.h"
}

TEST(split_word, commandOnly) {
  const char *input = "cat";
  char **cmds = split_word(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("cat"));
  EXPECT_EQ(cmds[1], nullptr);
}

TEST(split_word, commandWithOneOption) {
  const char *input = "cat -e";
  char **cmds = split_word(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("cat"));
  EXPECT_EQ(std::string(cmds[1]), std::string("-e"));
  EXPECT_EQ(cmds[2], nullptr);
}

TEST(split_word, commandWithTwoOptions) {
  const char *input = "grep -rn hello";
  char **cmds = split_word(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmds[1]), std::string("-rn"));
  EXPECT_EQ(std::string(cmds[2]), std::string("hello"));
  EXPECT_EQ(cmds[3], nullptr);
}

TEST(split_word, commandWithDelimitedByTab) {
  const char *input = "cat\t-e";
  char **cmds = split_word(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("cat"));
  EXPECT_EQ(std::string(cmds[1]), std::string("-e"));
  EXPECT_EQ(cmds[2], nullptr);
}

TEST(split_word, commandWithSingleQuotation) {
  const char *input = "grep 'message: hello'";
  char **cmds = split_word(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmds[1]), std::string("message: hello"));
  EXPECT_EQ(cmds[2], nullptr);
}

TEST(split_word, commandWithEscapedSpecialCharactors) {
  const char *input = "grep \\(\\)\\<\\>\\`\\!\\#\\&\\|\\;\\.\\:\\'\\$\\\\";
  char **cmds = split_word(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmds[1]), std::string("()<>`!#&|;.:'$\\"));
  EXPECT_EQ(cmds[2], nullptr);
}

TEST(split_word, commandWithDoubleQuotation) {
  const char *input = "grep \"message: hello\"";
  char **cmds = split_word(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmds[1]), std::string("message: hello"));
  EXPECT_EQ(cmds[2], nullptr);
}

TEST(split_word, commandWithEscapedDoubleQuotation) {
  const char *input = "grep \"double\\\"quotation\"";
  char **cmds = split_word(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmds[1]), std::string("double\"quotation"));
  EXPECT_EQ(cmds[2], nullptr);
}

TEST(create_word_list, commandWithManyEscapedDoubleQuotation) {
  const char *input = "grep \"dou\\\"ble\\\"quota\\\"tion\"";
  char **cmds = split_word(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmds[1]), std::string("dou\"ble\"quota\"tion"));
  EXPECT_EQ(cmds[2], nullptr);
}

TEST(split_word, commandWithEscapedBackSlash) {
  const char *input = "grep \"back\\\\slash\"";
  char **cmds = split_word(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmds[1]), std::string("back\\slash"));
  EXPECT_EQ(cmds[2], nullptr);
}

TEST(split_word, commandWithManyEscapedBackSlash) {
  const char *input = "grep \"ba\\\\ck\\\\sla\\\\sh\"";
  char **cmds = split_word(input);

  EXPECT_EQ(std::string(cmds[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmds[1]), std::string("ba\\ck\\sla\\sh"));
  EXPECT_EQ(cmds[2], nullptr);
}
