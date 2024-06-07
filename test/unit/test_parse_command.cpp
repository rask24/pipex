// Copyright 2024, reasuke.

#include <cstdio>
#include <cstring>
#include <string>

#include "gtest/gtest.h"

extern "C" {
#include "libft.h"
#include "parse_command.h"
}

TEST(parse_command, commandOnly) {
  const char *input = "cat";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("cat"));
  EXPECT_EQ(cmd_list[1], nullptr);
}

TEST(parse_command, commandWithOneOption) {
  const char *input = "cat -e";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("cat"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("-e"));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandWithTwoOptions) {
  const char *input = "grep -rn hello";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("-rn"));
  EXPECT_EQ(std::string(cmd_list[2]), std::string("hello"));
  EXPECT_EQ(cmd_list[3], nullptr);
}

TEST(parse_command, commandWithDelimitedByTab) {
  const char *input = "cat\t-e";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("cat"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("-e"));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandBeginWithSpace) {
  const char *input = "  cat";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("cat"));
  EXPECT_EQ(cmd_list[1], nullptr);
}

TEST(parse_command, commandEndWithSpace) {
  const char *input = "cat  ";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("cat"));
  EXPECT_EQ(cmd_list[1], nullptr);
}

TEST(parse_command, commandWithMultipleBlanks) {
  const char *input = "  \t\t cat -e \t \t -n \t";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("cat"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("-e"));
  EXPECT_EQ(std::string(cmd_list[2]), std::string("-n"));
  EXPECT_EQ(cmd_list[3], nullptr);
}

TEST(parse_command, commandWithSingleQuotation) {
  // grep 'message: hello'
  const char *input = "grep 'message: hello'";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("message: hello"));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandWithEscapedSpecialCharactors) {
  // grep a\ b
  const char *input = "grep a\\ b";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("a b"));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandWithDoubleQuotation) {
  // grep "message: hello"
  const char *input = "grep \"message: hello\"";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("message: hello"));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandWithSingleQuotationInDoubleQuotation) {
  // grep "message: 'hello'"
  const char *input = "grep \"message: 'hello'\"";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("message: 'hello'"));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandWithDoubleQuotationInSingleQuotation) {
  // grep 'message: "hello"'
  const char *input = "grep 'message: \"hello\"'";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("message: \"hello\""));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandWithEscapedDoubleQuotation) {
  // grep "message: \"hello\""
  const char *input = "grep \"message: \\\"hello\\\"\"";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("message: \"hello\""));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandWithEscapedDoubleQuotationAndBackslash) {
  // echo "\\:\ :\":\a"
  // \:\ :":\a
  const char *input = "echo \"\\\\:\\ :\\\":\\a\"";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("echo"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("\\:\\ :\":\\a"));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandWithEmptyString) {
  // echo ""''""''
  const char *input = "echo \"\"''\"\"''";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("echo"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string(""));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandWithConsectiveBackslashes) {
  // grep a\ \b
  const char *input = "grep a\\ \\b";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("a b"));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandWithConsecutiveSingleQuotations) {
  // grep 'message'': ''hello'
  const char *input = "grep 'message'': ''hello'";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("message: hello"));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandWithConsecutiveEscapes) {
  // grep 'message'": "'hello
  const char *input = "grep 'message'\": \"'hello'";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("message: hello"));
  EXPECT_EQ(cmd_list[2], nullptr);
}

TEST(parse_command, commandWithConsecutiveEscapesIncludingBashslash) {
  // grep 'message'"\\"'hello'
  const char *input = "grep 'message'\"\\\\\"'hello'";
  char **cmd_list = parse_command(input);

  EXPECT_EQ(std::string(cmd_list[0]), std::string("grep"));
  EXPECT_EQ(std::string(cmd_list[1]), std::string("message\\hello"));
  EXPECT_EQ(cmd_list[2], nullptr);
}
