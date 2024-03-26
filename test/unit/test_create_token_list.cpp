// Copyright 2024, reasuke.

#include <cstdio>
#include <cstring>
#include <string>

#include "gtest/gtest.h"

extern "C" {
#include "split_cmd.h"
}

TEST(create_token_list, commandOnly) {
  const char *input = "cat";
  t_list *token_list = create_token_list(input);

  EXPECT_EQ(std::string(get_token(token_list)->content), std::string("cat"));
  EXPECT_EQ(token_list->next, nullptr);
}

TEST(create_token_list, commandWithOneOption) {
  const char *input = "cat -e";
  t_list *token_list = create_token_list(input);

  EXPECT_EQ(std::string(get_token(token_list)->content), std::string("cat"));
  EXPECT_EQ(std::string(get_token(token_list->next)->content),
            std::string("-e"));
  EXPECT_EQ(token_list->next->next, nullptr);
}

TEST(create_token_list, commandWithTwoOptions) {
  const char *input = "grep -rn hello";
  t_list *token_list = create_token_list(input);

  EXPECT_EQ(std::string(get_token(token_list)->content), std::string("grep"));
  EXPECT_EQ(std::string(get_token(token_list->next)->content),
            std::string("-rn"));
  EXPECT_EQ(std::string(get_token(token_list->next->next)->content),
            std::string("hello"));
  EXPECT_EQ(token_list->next->next->next, nullptr);
}

TEST(create_token_list, commandWithDelimitedByTab) {
  const char *input = "cat\t-e";
  t_list *token_list = create_token_list(input);

  EXPECT_EQ(std::string(get_token(token_list)->content), std::string("cat"));
  EXPECT_EQ(std::string(get_token(token_list->next)->content),
            std::string("-e"));
  EXPECT_EQ(token_list->next->next, nullptr);
}

TEST(create_token_list, commandWithSingleQuotation) {
  const char *input = "grep 'message: hello'";
  t_list *token_list = create_token_list(input);

  EXPECT_EQ(std::string(get_token(token_list)->content), std::string("grep"));
  EXPECT_EQ(std::string(get_token(token_list->next)->content),
            std::string("'message: hello'"));
  EXPECT_EQ(token_list->next->next, nullptr);
}

TEST(create_token_list, commandWithEscapedSpecialCharactors) {
  const char *input = "grep \\(\\)\\<\\>\\`\\!\\#\\&\\|\\;\\.\\:\\'\\$\\\\";
  t_list *token_list = create_token_list(input);

  EXPECT_EQ(std::string(get_token(token_list)->content), std::string("grep"));
  EXPECT_EQ(std::string(get_token(token_list->next)->content),
            std::string("\\(\\)\\<\\>\\`\\!\\#\\&\\|\\;\\.\\:\\'\\$\\\\"));
  EXPECT_EQ(token_list->next->next, nullptr);
}

TEST(create_token_list, commandWithDoubleQuotation) {
  const char *input = "grep \"message: hello\"";
  t_list *token_list = create_token_list(input);

  EXPECT_EQ(std::string(get_token(token_list)->content), std::string("grep"));
  EXPECT_EQ(std::string(get_token(token_list->next)->content),
            std::string("\"message: hello\""));
  EXPECT_EQ(token_list->next->next, nullptr);
}

TEST(create_token_list, commandWithEscapedDoubleQuotation) {
  const char *input = "grep \"double\\\"quotation\"";
  t_list *token_list = create_token_list(input);

  EXPECT_EQ(std::string(get_token(token_list)->content), std::string("grep"));
  EXPECT_EQ(std::string(get_token(token_list->next)->content),
            std::string("\"double\\\"quotation\""));
  EXPECT_EQ(token_list->next->next, nullptr);
}

TEST(create_token_list, commandWithEscapedBackSlash) {
  const char *input = "grep \"back\\\\slash\"";
  t_list *token_list = create_token_list(input);

  EXPECT_EQ(std::string(get_token(token_list)->content), std::string("grep"));
  EXPECT_EQ(std::string(get_token(token_list->next)->content),
            std::string("\"back\\\\slash\""));
  EXPECT_EQ(token_list->next->next, nullptr);
}
