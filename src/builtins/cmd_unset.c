/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:02:42 by rlins             #+#    #+#             */
/*   Updated: 2022/11/18 11:45:10 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/** TODO: Centralizar estas msgs de erro
 * TODO: Tem que colocar o valor digitado no retorno do erro
*/
void	cmd_unset(t_data *data)
{
	int	i;
	int	index;

	i = 1;
	while (data->command->args[i])
	{
		if (is_valid_var_name(data->command->args[i]) == false)
		{
			ft_putstr_fd("Minishell: unset: not a valid identifier\n",
				STDOUT_FILENO);
			exit(EXIT_FAILURE);
		}
		else
		{
			index = get_env_var_index(data->env, data->command->args[i]);
			if (index != -1)
				env_var_remove(data, index);
		}
		i++;
	}
}

bool	is_valid_var_name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (ft_isalnum(name[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}
