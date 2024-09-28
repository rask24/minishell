#include <string.h>

#include "gtest/gtest.h"

extern "C" {
#include "utils.h"
}

void del(void *content) { free(content); }

bool is_node_hello(t_list *node, void *param) {
  return (strcmp((char *)(node->content), (char *)param) == 0);
}

TEST(ft_lstremove_if, RemoveFirstElement) {
  t_list *lst = ft_lstnew(ft_xstrdup("hello"));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("world")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("42")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("tokyo")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("paris")));

  char *param = strdup("hello");
  ft_lstremove_if(&lst, is_node_hello, (void *)param, del);

  EXPECT_STREQ((char *)lst->content, "world");
  EXPECT_STREQ((char *)lst->next->content, "42");
  EXPECT_STREQ((char *)lst->next->next->content, "tokyo");
  EXPECT_STREQ((char *)lst->next->next->next->content, "paris");
  EXPECT_EQ(lst->next->next->next->next, nullptr);
}

bool is_node_world(t_list *node, void *param) {
  return (strcmp((char *)(node->content), (char *)param) == 0);
}

TEST(ft_lstremove_if, RemoveMiddleElement) {
  t_list *lst = ft_lstnew(ft_xstrdup("hello"));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("world")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("42")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("tokyo")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("paris")));

  char *param = strdup("world");
  ft_lstremove_if(&lst, is_node_world, (void *)param, del);

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

  char *param = strdup("world");
  ft_lstremove_if(&lst, is_node_world, (void *)param, del);

  EXPECT_STREQ((char *)lst->content, "hello");
  EXPECT_STREQ((char *)lst->next->content, "tokyo");
  EXPECT_STREQ((char *)lst->next->next->content, "paris");
  EXPECT_EQ(lst->next->next->next, nullptr);
}

TEST(ft_lstremove_if, RemoveAll) {
  t_list *lst = ft_lstnew(ft_xstrdup("world"));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("world")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("world")));

  char *param = strdup("world");
  ft_lstremove_if(&lst, is_node_world, (void *)param, del);

  EXPECT_EQ(lst, nullptr);
}

static void capitalize(void *content, void *param) {
  if (strlen(static_cast<char *>(content)) == *static_cast<size_t *>(param)) {
    free(content);
    content = strdup("CAPITALIZED");
  }
}

TEST(ft_lstiterp, NoFunction) {
  t_list *lst = ft_lstnew(ft_xstrdup("hello"));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("world")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("42")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("tokyo")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("paris")));

  size_t len = 2;
  void *param = &len;
  ft_lstiterp(lst, capitalize, param);

  EXPECT_STREQ((char *)lst->content, "hello");
  EXPECT_STREQ((char *)lst->next->content, "world");
  EXPECT_STREQ((char *)lst->next->next->content, "CAPITALIZED");
  EXPECT_STREQ((char *)lst->next->next->next->content, "tokyo");
  EXPECT_STREQ((char *)lst->next->next->next->next->content, "paris");
  EXPECT_EQ(lst->next->next->next->next->next, nullptr);
}

TEST(ft_lstsort, SimpleSort) {
  t_list *lst = ft_lstnew(ft_xstrdup("world"));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("hello")));

  ft_lstsort(&lst, [](t_list *a, t_list *b) {
    return (strcmp((char *)(a->content), (char *)(b->content)) > 0);
  });

  EXPECT_STREQ((char *)lst->content, "hello");
  EXPECT_STREQ((char *)lst->next->content, "world");
  EXPECT_EQ(lst->next->next, nullptr);
}

TEST(ft_lstsort, Sort) {
  t_list *lst = ft_lstnew(ft_xstrdup("world"));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("hello")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("42")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("tokyo")));
  ft_lstadd_back(&lst, ft_lstnew(ft_xstrdup("paris")));

  ft_lstsort(&lst, [](t_list *a, t_list *b) {
    return (strcmp((char *)(a->content), (char *)(b->content)) > 0);
  });

  EXPECT_STREQ((char *)lst->content, "42");
  EXPECT_STREQ((char *)lst->next->content, "hello");
  EXPECT_STREQ((char *)lst->next->next->content, "paris");
  EXPECT_STREQ((char *)lst->next->next->next->content, "tokyo");
  EXPECT_STREQ((char *)lst->next->next->next->next->content, "world");
  EXPECT_EQ(lst->next->next->next->next->next, nullptr);
}
