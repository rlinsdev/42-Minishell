/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:25:21 by rlins             #+#    #+#             */
/*   Updated: 2022/12/22 10:38:46 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	new_line(int signal);
static void	reset_prompt(int signo);

void	signals_wait_cmd(void)
{
	signal(SIGINT, reset_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_run_cmd(void)
{
	signal(SIGINT, new_line);
	signal(SIGQUIT, new_line);
}

/**
 * @brief Print a new line when the shell is processing the requisition
 * @param signo Return Code
 */
static void	new_line(int signo)
{
	g_status_code = 128 + signo;
	rl_on_new_line();
}

/**
 * @brief Reset Prompt
 * @param signo Return Code
 */
static void	reset_prompt(int signo)
{
	g_status_code = 128 + signo;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
