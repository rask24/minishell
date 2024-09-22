/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:59:34 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 16:18:13 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions_internal.h"

static bool	is_start_of_input(t_expansion *expansions)
{
	return (expansions->left == expansions->right);
}

static void	construct_expansions(char *input, t_expansion *expansions)
{
	expansions->left = input;
	expansions->right = input;
}

static void	add_back(char **res, char *new_item)
{
	char	*new_res;

	new_res = ft_xstrjoin(*res, new_item);
	free(*res);
	free(new_item);
	*res = new_res;
}

static char	*process_eof(t_expansion *expansions)
{
	char	*section;

	if (is_start_of_input(expansions))
		return (ft_xstrdup(""));
	section = ft_xstrdup(expansions->left);
	expansions->left = expansions->right;
	return (section);
}

static char	*expand_variable(t_expansion *expansions, t_env_list *env)
{
	char	*key;
	char	*value;
	char	*expanded;

	expansions->right++;
	expansions->left++;
	while (*expansions->right && *expansions->right != '$')
		expansions->right++;
	key = ft_xstrndup(expansions->left, expansions->right - expansions->left);
	value = lookup_value(key, env);
	if (!value)
		expanded = ft_xstrdup("");
	else
		expanded = ft_xstrdup(value);
	expansions->left = expansions->right;
	free(key);
	return (expanded);
}

static char	*process_variable(t_expansion *expansion, t_env_list *env)
{
	char	*section;

	if (is_start_of_input(expansion))
		return (expand_variable(expansion, env));
	else
	{
		section = ft_xstrndup(expansion->left, expansion->right
				- expansion->left);
		expansion->left = expansion->right;
		return (section);
	}
}

static char	*get_next_section(t_expansion *expansions, t_env_list *env);
static char	*process_noexpansion(t_expansion *expansions, t_env_list *env)
{
	expansions->right++;
	return (get_next_section(expansions, env));
}

static char *process_single_quote(t_expansion *expansions)
{
	char	*section;

	expansions->right++;
	expansions->left++;
	while (*expansions->right && *expansions->right != '\'')
		expansions->right++;
	section = ft_xstrndup(expansions->left, expansions->right - expansions->left);
	expansions->right++;
	expansions->left = expansions->right;
	return (section);
}

static char	*get_next_section(t_expansion *expansions, t_env_list *env)
{
	if (!*expansions->right)
		return (process_eof(expansions));
	else if (*expansions->right == '$')
		return (process_variable(expansions, env));
	else if (*expansions->right == '\'')
		return (process_single_quote(expansions));
	else
		return (process_noexpansion(expansions, env));
}

char	*expand(char *input, t_env_list *env)
{
	char		*new_input;
	t_expansion	expansions;
	char		*section;

	new_input = NULL;
	construct_expansions(input, &expansions);
	while (true)
	{
		section = get_next_section(&expansions, env);
		add_back(&new_input, section);
		if (!*expansions.left)
			break ;
	}
	return (new_input);
}
