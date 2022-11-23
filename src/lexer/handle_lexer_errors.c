/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lexer_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 00:33:37 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/23 00:33:37 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	lexer_errors(t_index_data *i_data, const char *s, t_data *data)
{
	if (!s[i_data->i] && (s[i_data->i - 1] == '|' || s[i_data->i - 1] == '&'))
		{
			data->exit_value = 2;
			ft_putstr_fd("-minishell: syntax error not expecting newline\n", STDERR);
		}
	while (s[i_data->i] == '|' || s[i_data->i] == '&' || s[i_data->i] == ' ')
	{
		if ((s[i_data->i] == '|' || s[i_data->i] == '&') && data->exit_value == 0)
		{
			data->exit_value = 2;
			ft_putstr_fd("-minishell: syntax error near unexpected token `", STDERR);
			ft_putchar_fd(s[i_data->i], STDERR);
			ft_putstr_fd("'\n", STDERR);
		}
		i_data->i++;
		if (!s[i_data->i] && data->exit_value == 0)
		{
			data->exit_value = 2;
			ft_putstr_fd("-minishell: syntax error not expecting newline\n", STDERR);
		}
	}
}
