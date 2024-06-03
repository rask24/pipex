// Copyright 2024, reasuke.

#include <cstdio>
#include <cstring>
#include <string>

#include "gtest/gtest.h"

extern "C" {
#include "../../src/parse_command/parse_command_internal.h"
}

TEST(clean_tokens, commandOnly) {
  const char *input = "cat";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("cat"));
  EXPECT_EQ(cleaned_tokens->next, nullptr);
}

TEST(clean_tokens, commandWithOneOption) {
  const char *input = "cat -e";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("cat"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("-e"));
  EXPECT_EQ(cleaned_tokens->next->next, nullptr);
}

TEST(clean_tokens, commandWithTwoOptions) {
  const char *input = "grep -rn hello";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("-rn"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->next->content),
            std::string("hello"));
  EXPECT_EQ(cleaned_tokens->next->next->next, nullptr);
}

TEST(clean_tokens, commandWithDelimitedByTab) {
  const char *input = "cat\t-e";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("cat"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("-e"));
  EXPECT_EQ(cleaned_tokens->next->next, nullptr);
}

TEST(clean_tokens, commandBeginWithSpace) {
  const char *input = "  cat";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("cat"));
  EXPECT_EQ(cleaned_tokens->next, nullptr);
}

TEST(clean_tokens, commandEndWithSpace) {
  const char *input = "cat  ";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("cat"));
  EXPECT_EQ(cleaned_tokens->next, nullptr);
}

TEST(clean_tokens, commandWithMultipleBlanks) {
  const char *input = "  \t\t cat -e \t \t -n \t";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("cat"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("-e"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->next->content),
            std::string("-n"));
  EXPECT_EQ(cleaned_tokens->next->next->next, nullptr);
}

TEST(clean_tokens, commandWithSingleQuotation) {
  // grep 'message: hello'
  const char *input = "grep 'message: hello'";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("message: hello"));
  EXPECT_EQ(tokens->next->next, nullptr);
}

TEST(clean_tokens, commandWithEscapedSpecialCharactors) {
  // grep a\ b
  const char *input = "grep a\\ b";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("a b"));
  EXPECT_EQ(cleaned_tokens->next->next, nullptr);
}

TEST(clean_tokens, commandWithDoubleQuotation) {
  // grep "message: hello"
  const char *input = "grep \"message: hello\"";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("message: hello"));
  EXPECT_EQ(cleaned_tokens->next->next, nullptr);
}

TEST(clean_tokens, commandWithSingleQuotationInDoubleQuotation) {
  // grep "message: 'hello'"
  const char *input = "grep \"message: 'hello'\"";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("message: 'hello'"));
  EXPECT_EQ(cleaned_tokens->next->next, nullptr);
}

TEST(clean_tokens, commandWithDoubleQuotationInSingleQuotation) {
  // grep 'message: "hello"'
  const char *input = "grep 'message: \"hello\"'";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("'essage: \"hello\""));
  EXPECT_EQ(cleaned_tokens->next->next, nullptr);
}

TEST(clean_tokens, commandWithEscapedDoubleQuotation) {
  // grep "message: \"hello\""
  const char *input = "grep \"message: \\\"hello\\\"\"";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("message: \"hello\""));
  EXPECT_EQ(cleaned_tokens->next->next, nullptr);
}

TEST(clean_tokens, commandWithConsectiveBackslashes) {
  // grep a\ \b
  const char *input = "grep a\\ \\b";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("a \\b"));
  EXPECT_EQ(cleaned_tokens->next->next, nullptr);
}

TEST(clean_tokens, commandWithConsecutiveSingleQuotations) {
  // grep 'message'': ''hello'
  const char *input = "grep 'message'': ''hello'";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("message: hello"));
  EXPECT_EQ(tokens->next->next, nullptr);
}

TEST(clean_tokens, commandWithConsecutiveEscapes) {
  // grep 'message'": "'hello
  const char *input = "grep 'message'\": \"'hello'";
  t_list *tokens = tokenize_command(input);
  t_list *cleaned_tokens = clean_tokens(tokens);

  EXPECT_EQ(std::string((char *)cleaned_tokens->content), std::string("grep"));
  EXPECT_EQ(std::string((char *)cleaned_tokens->next->content),
            std::string("message: hello"));
  EXPECT_EQ(cleaned_tokens->next->next, nullptr);
}
