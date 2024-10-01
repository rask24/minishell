/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_lazy_match.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:20:45 by yliu              #+#    #+#             */
/*   Updated: 2024/10/01 21:51:23 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

static void	exec_dp(bool **dp, const char *str, const char *pattern)
{
	int	i;
	int	j;
	int	pattern_len;
	int	str_len;

	str_len = strlen(str);
	pattern_len = strlen(pattern);
	i = 0;
	while (i < pattern_len)
	{
		j = 0;
		while (j < str_len)
		{
			if (pattern[i] == '*')
				dp[i + 1][j + 1] = (dp[i][j + 1] || dp[i + 1][j]);
			else if (pattern[i] == '?' || pattern[i] == str[j])
				dp[i + 1][j + 1] = dp[i][j];
			j++;
		}
		i++;
	}
}

static void	exec_first_row(bool **dp, const char *pattern, int pattern_len)
{
	int	i;

	i = 0;
	while (i < pattern_len && pattern[i] == '*')
	{
		dp[i + 1][0] = true;
		i++;
	}
}

static void	construct_dp(bool ***dp, int pattern_len, int str_len)
{
	int	i;

	*dp = (bool **)ft_xmalloc(sizeof(bool *) * (pattern_len + 1));
	i = 0;
	while (i <= pattern_len)
	{
		(*dp)[i] = (bool *)ft_xmalloc(sizeof(bool) * (str_len + 1));
		i++;
	}
}

static void	destruct_dp(bool **dp, int pattern_len)
{
	int	i;

	i = 0;
	while (i <= pattern_len)
	{
		free(dp[i]);
		i++;
	}
	free(dp);
}

bool	wildcard_lazy_match(const char *str, const char *pattern)
{
	int		pattern_len;
	int		str_len;
	bool	**dp;
	bool	result;

	pattern_len = strlen(pattern);
	str_len = strlen(str);
	construct_dp(&dp, pattern_len, str_len);
	dp[0][0] = true;
	exec_first_row(dp, pattern, pattern_len);
	exec_dp(dp, str, pattern);
	result = dp[pattern_len][str_len];
	destruct_dp(dp, pattern_len);
	return (result);
}
