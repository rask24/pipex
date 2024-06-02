// Copyright 2024, reasuke.

#include <cstdio>
#include <cstring>
#include <string>

#include "gtest/gtest.h"

extern "C" {
#include "../../src/parse_command/parse_command_internal.h"
}

TEST(tokenize_command, commandOnly) {
  const char *input = "cat";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("cat"));
  EXPECT_EQ(tokens->next, nullptr);
}

TEST(tokenize_command, commandWithOneOption) {
  const char *input = "cat -e";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("cat"));
  EXPECT_EQ(std::string((char *)tokens->next->content), std::string("-e"));
  EXPECT_EQ(tokens->next->next, nullptr);
}

TEST(tokenize_command, commandWithTwoOptions) {
  const char *input = "grep -rn hello";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)tokens->next->content), std::string("-rn"));
  EXPECT_EQ(std::string((char *)tokens->next->next->content),
            std::string("hello"));
  EXPECT_EQ(tokens->next->next->next, nullptr);
}

TEST(tokenize_command, commandWithDelimitedByTab) {
  const char *input = "cat\t-e";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("cat"));
  EXPECT_EQ(std::string((char *)tokens->next->content), std::string("-e"));
  EXPECT_EQ(tokens->next->next, nullptr);
}

TEST(tokenize_commnad, commandBeginWithSpace) {
  const char *input = "  cat";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("cat"));
  EXPECT_EQ(tokens->next, nullptr);
}

TEST(tokenize_command, commandEndWithSpace) {
  const char *input = "cat  ";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("cat"));
  EXPECT_EQ(tokens->next, nullptr);
}

TEST(tokenize_command, commandWithMultipleBlanks) {
  const char *input = "  \t\t cat -e \t \t -n \t";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("cat"));
  EXPECT_EQ(std::string((char *)tokens->next->content), std::string("-e"));
  EXPECT_EQ(std::string((char *)tokens->next->next->content),
            std::string("-n"));
  EXPECT_EQ(tokens->next->next->next, nullptr);
}

TEST(tokenize_command, commandWithSingleQuotation) {
  // grep 'message: hello'
  const char *input = "grep 'message: hello'";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)tokens->next->content),
            std::string("'message: hello'"));
  EXPECT_EQ(tokens->next->next, nullptr);
}

TEST(tokenize_command, commandWithEscapedSpecialCharactors) {
  // grep a\ b
  const char *input = "grep a\\ b";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)tokens->next->content), std::string("a\\ b"));
  EXPECT_EQ(tokens->next->next, nullptr);
}

TEST(tokenize_command, commandWithDoubleQuotation) {
  // grep "message: hello"
  const char *input = "grep \"message: hello\"";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)tokens->next->content),
            std::string("\"message: hello\""));
  EXPECT_EQ(tokens->next->next, nullptr);
}

TEST(tokenize_command, commandWithSingleQuotationInDoubleQuotation) {
  // grep "message: 'hello'"
  const char *input = "grep \"message: 'hello'\"";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)tokens->next->content),
            std::string("\"message: 'hello'\""));
  EXPECT_EQ(tokens->next->next, nullptr);
}

TEST(tokenize_command, commandWithDoubleQuotationInSingleQuotation) {
  // grep 'message: "hello"'
  const char *input = "grep 'message: \"hello\"'";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)tokens->next->content),
            std::string("'message: \"hello\"'"));
  EXPECT_EQ(tokens->next->next, nullptr);
}

TEST(tokenize_command, commandWithEscapedDoubleQuotation) {
  // grep "message: \"hello\""
  const char *input = "grep \"message: \\\"hello\\\"\"";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)tokens->next->content),
            std::string("\"message: \\\"hello\\\"\""));
  EXPECT_EQ(tokens->next->next, nullptr);
}

TEST(tokenize_command, commandWithConsectiveBackslashes) {
  // grep a\ \b
  const char *input = "grep a\\ \\b";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)tokens->next->content), std::string("a\\ \\b"));
  EXPECT_EQ(tokens->next->next, nullptr);
}

TEST(tokenize_command, commandWithConsecutiveSingleQuotations) {
  // grep 'message'': ''hello'
  const char *input = "grep 'message'': ''hello'";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)tokens->next->content),
            std::string("'message'': ''hello'"));
  EXPECT_EQ(tokens->next->next, nullptr);
}

TEST(tokenize_command, commandWithConsecutiveEscapes) {
  // grep 'message'": "'hello
  const char *input = "grep 'message'\": \"'hello'";
  t_list *tokens = tokenize_command(input);

  EXPECT_EQ(std::string((char *)tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)tokens->next->content),
            std::string("'message'\": \"'hello'"));
  EXPECT_EQ(tokens->next->next, nullptr);
}
