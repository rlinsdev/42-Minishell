/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_partial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:33:45 by rlins             #+#    #+#             */
/*   Updated: 2022/11/30 16:39:05 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	input_is_dir(char *cmd)
{
	struct stat	stat_buf;

	stat(cmd, &stat_buf);
	return (S_ISDIR(stat_buf.st_mode));
}

int	validate_cmd_not_found(t_data *data, t_commands *cmds, char *cmd)
{
	if (ft_strchr(cmd, '/') == NULL
		&& get_env_var_index(data->env, "PATH") != -1)
		return (error_msg_cmd(cmd, NULL, "command not found", CMD_NOT_FOUND));
	if (access(cmd, F_OK) != 0)
		return (error_msg_cmd(cmd, NULL, strerror(errno), CMD_NOT_FOUND));
	else if (input_is_dir(cmd))
		return (error_msg_cmd(cmd, NULL, "is a directory", CMD_NOT_EXEC));
	else if (access(cmd, X_OK) != 0)
		return (error_msg_cmd(cmd, NULL, strerror(errno), CMD_NOT_EXEC));
}
