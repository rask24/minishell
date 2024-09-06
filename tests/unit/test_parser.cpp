// Copyright 2024, reasuke

#include "gtest/gtest.h"

extern "C" {
#include "parser.h"
#include "parser/parser_internal.h"
}

// TODO: delete
TEST(parser, ExampleTest) {
  t_ast *ast = parser(nullptr);
  EXPECT_EQ(ast, nullptr);
}
