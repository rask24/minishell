/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:58:39 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/18 20:27:06 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>

# include "libft.h"
# include "readline/readline.h"
# include "utils.h"

# define PROMPT "minishell$ "

void	init_signal_handlers(void);
void	reset_signal_handlers(void);
void	save_terminal_configuration(struct termios *original_termios);
void	restore_terminal_configuration(struct termios *original_termios);

#endif
