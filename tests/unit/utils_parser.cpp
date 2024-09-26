// Copyright 2024, reasuke

#include <cstring>
#include <vector>

extern "C" {
#include "token.h"
}

t_token_list *construct_token_list(
    std::vector<std::pair<t_token_type, const char *>> tokens) {
  t_token_list *token_list = nullptr;

  for (const auto &token : tokens) {
    char *str = token.second ? strdup(token.second) : nullptr;

    ft_lstadd_back(&token_list, construct_token(token.first, str));
  }

  return token_list;
}
