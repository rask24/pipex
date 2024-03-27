// Copyright 2024, reasuke.

#include <cstdio>
#include <cstring>
#include <string>

#include "gtest/gtest.h"

extern "C" {
#include "split_word.h"
}

TEST(create_word_list, commandOnly) {
  const char *input = "cat";
  t_list *word_list = create_word_list(input);

  EXPECT_EQ(std::string(get_word(word_list)->content), std::string("cat"));
  EXPECT_EQ(word_list->next, nullptr);
}

TEST(create_word_list, commandWithOneOption) {
  const char *input = "cat -e";
  t_list *word_list = create_word_list(input);

  EXPECT_EQ(std::string(get_word(word_list)->content), std::string("cat"));
  EXPECT_EQ(std::string(get_word(word_list->next)->content),
            std::string("-e"));
  EXPECT_EQ(word_list->next->next, nullptr);
}

TEST(create_word_list, commandWithTwoOptions) {
  const char *input = "grep -rn hello";
  t_list *word_list = create_word_list(input);

  EXPECT_EQ(std::string(get_word(word_list)->content), std::string("grep"));
  EXPECT_EQ(std::string(get_word(word_list->next)->content),
            std::string("-rn"));
  EXPECT_EQ(std::string(get_word(word_list->next->next)->content),
            std::string("hello"));
  EXPECT_EQ(word_list->next->next->next, nullptr);
}

TEST(create_word_list, commandWithDelimitedByTab) {
  const char *input = "cat\t-e";
  t_list *word_list = create_word_list(input);

  EXPECT_EQ(std::string(get_word(word_list)->content), std::string("cat"));
  EXPECT_EQ(std::string(get_word(word_list->next)->content),
            std::string("-e"));
  EXPECT_EQ(word_list->next->next, nullptr);
}

TEST(create_word_list, commandWithSingleQuotation) {
  const char *input = "grep 'message: hello'";
  t_list *word_list = create_word_list(input);

  EXPECT_EQ(std::string(get_word(word_list)->content), std::string("grep"));
  EXPECT_EQ(std::string(get_word(word_list->next)->content),
            std::string("'message: hello'"));
  EXPECT_EQ(word_list->next->next, nullptr);
}

TEST(create_word_list, commandWithEscapedSpecialCharactors) {
  const char *input = "grep \\(\\)\\<\\>\\`\\!\\#\\&\\|\\;\\.\\:\\'\\$\\\\";
  t_list *word_list = create_word_list(input);

  EXPECT_EQ(std::string(get_word(word_list)->content), std::string("grep"));
  EXPECT_EQ(std::string(get_word(word_list->next)->content),
            std::string("\\(\\)\\<\\>\\`\\!\\#\\&\\|\\;\\.\\:\\'\\$\\\\"));
  EXPECT_EQ(word_list->next->next, nullptr);
}

TEST(create_word_list, commandWithDoubleQuotation) {
  const char *input = "grep \"message: hello\"";
  t_list *word_list = create_word_list(input);

  EXPECT_EQ(std::string(get_word(word_list)->content), std::string("grep"));
  EXPECT_EQ(std::string(get_word(word_list->next)->content),
            std::string("\"message: hello\""));
  EXPECT_EQ(word_list->next->next, nullptr);
}

TEST(create_word_list, commandWithEscapedDoubleQuotation) {
  const char *input = "grep \"double\\\"quotation\"";
  t_list *word_list = create_word_list(input);

  EXPECT_EQ(std::string(get_word(word_list)->content), std::string("grep"));
  EXPECT_EQ(std::string(get_word(word_list->next)->content),
            std::string("\"double\\\"quotation\""));
  EXPECT_EQ(word_list->next->next, nullptr);
}

TEST(create_word_list, commandWithEscapedBackSlash) {
  const char *input = "grep \"back\\\\slash\"";
  t_list *word_list = create_word_list(input);

  EXPECT_EQ(std::string(get_word(word_list)->content), std::string("grep"));
  EXPECT_EQ(std::string(get_word(word_list->next)->content),
            std::string("\"back\\\\slash\""));
  EXPECT_EQ(word_list->next->next, nullptr);
}
