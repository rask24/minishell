#include <string.h>

#include "gtest/gtest.h"

extern "C" {
#include "utils.h"
}

void del(void *content) { free(content); }

bool is_node_hello(t_list *node) {
  return (strcmp((char *)(node->content), "hello") == 0);
}

TEST(ft_lstremove_if, RemoveFirstElement) {
  t_list *lst = ft_lstnew(ft_xstrdup("hello"));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("world")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("42")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("tokyo")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("paris")));

  ft_lstremove_if(&lst, is_node_hello, del);

  EXPECT_STREQ((char *)lst->content, "world");
  EXPECT_STREQ((char *)lst->next->content, "42");
  EXPECT_STREQ((char *)lst->next->next->content, "tokyo");
  EXPECT_STREQ((char *)lst->next->next->next->content, "paris");
  EXPECT_EQ(lst->next->next->next->next, nullptr);
}

bool is_node_world(t_list *node) {
  return (strcmp((char *)(node->content), "world") == 0);
}

TEST(ft_lstremove_if, RemoveMiddleElement) {
  t_list *lst = ft_lstnew(ft_xstrdup("hello"));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("world")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("42")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("tokyo")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("paris")));

  ft_lstremove_if(&lst, is_node_world, del);

  EXPECT_STREQ((char *)lst->content, "hello");
  EXPECT_STREQ((char *)lst->next->content, "42");
  EXPECT_STREQ((char *)lst->next->next->content, "tokyo");
  EXPECT_STREQ((char *)lst->next->next->next->content, "paris");
  EXPECT_EQ(lst->next->next->next->next, nullptr);
}

TEST(ft_lstremove_if, RemoveMiddleElements) {
  t_list *lst = ft_lstnew(ft_xstrdup("hello"));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("world")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("world")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("tokyo")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("paris")));

  ft_lstremove_if(&lst, is_node_world, del);

  EXPECT_STREQ((char *)lst->content, "hello");
  EXPECT_STREQ((char *)lst->next->content, "tokyo");
  EXPECT_STREQ((char *)lst->next->next->content, "paris");
  EXPECT_EQ(lst->next->next->next, nullptr);
}

TEST(ft_lstremove_if, RemoveAll) {
  t_list *lst = ft_lstnew(ft_xstrdup("world"));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("world")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("world")));

  ft_lstremove_if(&lst, is_node_world, del);

  EXPECT_EQ(lst, nullptr);
}
