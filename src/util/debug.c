/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:57:56 by rlins             #+#    #+#             */
/*   Updated: 2022/12/12 11:11:14 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_cmds(t_commands *cmds);
static void	print_operators(int operator);
static void	print_io(t_io *io);

/**
 * @brief Auxiliary method to expose all values of the structure
 * @param cmds
 */
void	debug_structs(t_commands *cmds, bool show_path)
{
	int	i;

	i = 0;
	printf("----Begin Debug (state Obj)----\n");
	printf("Nro num_cmds:	%i\n", cmds->num_cmds);
	print_operators(*cmds->operators);
	printf("Nro num_exec:	%i\n", cmds->num_exec);
	if (show_path)
	{
		while (cmds->paths[i])
		{
			printf("Paths:	%s\n", cmds->paths[i]);
			i++;
		}
	}
	i = 0;
	while (cmds->cmds[i])
		printf("Cmds:	%s\n", cmds->cmds[i++]);
	print_cmds(cmds);
	print_io(cmds->io);
	printf("----End Debug (state Obj)----\n");
}

static void	print_io(t_io *io)
{
	printf("----Begin Debug (state IO)----\n");
	printf("\tfd_in:%i\n", io->fd_in);
	printf("\tfd_out:%i\n", io->fd_out);
	printf("\tstd_in_bkp:%i\n", io->std_in_bkp);
	printf("\tstd_out_bkp:%i\n", io->std_out_bkp);
	printf("\tin file name:%s\n", io->in_file);
	printf("\tout file name:%s\n", io->out_file);
	printf("----End Debug (state IO)----\n");
}

static void	print_operators(int operator)
{
	if (operator == 1)
		printf("Operators: 	OR\n");
	else if (operator == 2)
		printf("Operators: 	AND\n");
	else if (operator == 3)
		printf("Operators: 	PIPE\n");
}

/**
 * @brief Print array of commands
 * @param cmds
 */
static void	print_cmds(t_commands *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmds->num_cmds)
	{
		printf("\tcmd - path: %s\n", cmds->cmd[i].path);
		printf("\tcmd - exit_value: %i\n", cmds->exit_value);
		j = 0;
		while (cmds->cmd[i].redirections[j])
		{
			printf("  cmd [%i][%i]- red.: %s\n", i, j,
				cmds->cmd[i].redirections[j]);
			j++;
		}
		j = 0;
		while (cmds->cmd[i].args[j])
		{
			printf("  cmd - args [%i][%i]: %s\n", i, j, cmds->cmd[i].args[j]);
			j++;
		}
	i++;
	}
}
