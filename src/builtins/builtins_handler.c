/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:19:00 by rlins             #+#    #+#             */
/*   Updated: 2022/11/15 10:28:33 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	else
	{
		ft_putstr_fd("TODO: Must Implement!!!!\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

void	call_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		echo_cmd();
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		cmd_exit();
	else
	{
		ft_putstr_fd("TODO: Must Implement!!!!\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}
