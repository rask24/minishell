// Copyright 2024, reasuke

#ifndef UTILS_PARSER_HPP
#define UTILS_PARSER_HPP

#include <vector>
extern "C" {
#include "token.h"
}

t_token_list *construct_token_list(
    std::vector<std::pair<t_token_type, const char *>> tokens);

#endif
