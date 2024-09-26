/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_parse_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 02:28:39 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/26 17:03:23 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "ast.h"
#include "parser_internal.h"
#include "readline.h"
#include "token.h"
#include "utils.h"

static int	open_heredoc_tmpfile(void)
{
	int	fd;

	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC,
			S_IRUSR | S_IWUSR);
	if (fd == -1)
		print_error_exit("open", strerror(errno), EXIT_FAILURE);
	return (fd);
}

static void	write_heredoc_tmpfile(int fd, t_list *input_list)
{
	t_list	*node;

	node = input_list;
	while (node != NULL)
	{
		ft_putendl_fd(node->content, fd);
		node = node->next;
	}
	ft_lstclear(&input_list, free);
}

static int	handle_heredoc(const char *delimiter)
{
	char	*line;
	int		fd;
	t_list	*input_list;

	input_list = NULL;
	while (true)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_lstadd_back(&input_list, ft_xlstnew(line));
	}
	fd = open_heredoc_tmpfile();
	write_heredoc_tmpfile(fd, input_list);
	close(fd);
	fd = open("heredoc", O_RDONLY | O_CLOEXEC, S_IRUSR | S_IWUSR);
	unlink("heredoc");
	return (fd);
}

bool	is_redirect_token(t_token_type type)
{
	return (type == TOKEN_LESS
		|| type == TOKEN_GREAT
		|| type == TOKEN_DLESS
		|| type == TOKEN_DGREAT);
}

bool	try_parse_redirect(t_ast *node, t_token_list **cur_token)
{
	t_redirect_info	redirect_info;
	t_token_type	token_type;

	token_type = get_token_type(*cur_token);
	redirect_info.type = (t_redirect_type)token_type;
	if (!expect_token(cur_token, token_type))
		return (false);
	redirect_info.filepath = get_token_value(*cur_token);
	if (!expect_token(cur_token, TOKEN_WORD))
		return (false);
	if (redirect_info.type == REDIRECT_HEREDOC)
		redirect_info.heredoc_fd = handle_heredoc(redirect_info.filepath);
	push_redirect_info(node, &redirect_info);
	return (true);
}
