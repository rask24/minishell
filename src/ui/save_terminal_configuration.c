/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_terminal_configuration.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:34:50 by reasuke           #+#    #+#             */
/*   Updated: 2024/08/27 00:52:09 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void	save_terminal_configuration(struct termios *original_termios)
{
	if (tcgetattr(STDIN_FILENO, original_termios) == -1)
		perror("tcgetattr");
}
