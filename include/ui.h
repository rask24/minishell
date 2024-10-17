/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:58:39 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/16 22:03:01 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include <signal.h>
# include <termios.h>

# define PROMPT "minishell$ "

extern volatile sig_atomic_t	g_signum;

void	init_signal_handlers(void);
void	reset_signal_handlers(void);
void	set_exec_signal_handlers(void);
int		handle_sigint_hook(void);
int		handle_heredoc_sigint_hook(void);
void	save_termios(struct termios *original_termios);
void	restore_termios(struct termios *original_termios);

#endif
