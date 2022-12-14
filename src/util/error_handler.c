/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:23:22 by rlins             #+#    #+#             */
/*   Updated: 2022/12/12 14:38:51 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	response_with_quotes(char *cmd);

int	error_msg_cmd(char *cmd, char *detail, char *msg, int status_code)
{
	char	*full_msg;
	bool	is_quotes;

	if (cmd != NULL)
		is_quotes = response_with_quotes(cmd);
	full_msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		full_msg = join_strs(full_msg, cmd);
		full_msg = join_strs(full_msg, ": ");
	}
	if (detail != NULL)
	{
		if (is_quotes)
			full_msg = join_strs(full_msg, "`");
		full_msg = join_strs(full_msg, detail);
		if (is_quotes)
			full_msg = join_strs(full_msg, "'");
		full_msg = join_strs(full_msg, ": ");
	}
	full_msg = join_strs(full_msg, msg);
	ft_putendl_fd(full_msg, STDERR_FILENO);
	free_ptr(full_msg);
	return (status_code);
}

/**
 * @brief Will check if the command is like this: export temp_env =aaa-aaa.
 * ("). Return must be between quotes
 * @param cmd Command applied
 * @return true
 * @return false
 */
static bool	response_with_quotes(char *cmd)
{
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (true);
	return (false);
}
