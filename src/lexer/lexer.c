/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:57:26 by mtomomit          #+#    #+#             */
/*   Updated: 2022/11/17 14:57:26 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_quotes(t_index_data *i_data, const char *s, t_data *data)
{
	if (s[i_data->i++] == '\'')
	{
		while (s[i_data->i] && s[i_data->i++] != '\'')
			i_data->malloc_size++;
	}
	else
	{
		while (s[i_data->i] && s[i_data->i++] != '\"')
				i_data->malloc_size++;
	}
	if (!s[i_data->i])
		data->exit_value = 2;
}

static void	get_size(t_index_data *i_data, const char *s, t_data *data)
{
	i_data->malloc_size = 0;
	while (s[i_data->i] && s[i_data->i] != '&' && s[i_data->i++] != '|')
	{
		if (s[i_data->i] == '\'' || s[i_data->i] == '\"')
			handle_quotes(i_data, s, data);
		if (s[i_data->i])
			i_data->malloc_size++;
	}
	if (s[i_data->i] == '&' && s[i_data->i + 1] == '&')
		i_data->i = i_data->i + 2;
	if (s[i_data->i - 1] == '|' && s[i_data->i] == '|')
		i_data->i++;
	lexer_errors(i_data, s, data);
}

static size_t	ft_countstr(char const *s, t_data *data)
{
	t_index_data	i_data;
	size_t			counter;

	i_data.i = 0;
	counter = 0;
	while (s[i_data.i])
	{
		get_size(&i_data, s, data);
		if (i_data.malloc_size != 0)
			counter++;
	}
	return (counter);
}

static void	splitstr(char **str, char const *s, size_t countc, t_data *data)
{
	t_index_data	i_data;

	i_data.i = 0;
	i_data.j = 0;
	while (i_data.j < countc)
	{
		get_size(&i_data, s, data);
		str[i_data.j] = (char *)malloc((i_data.malloc_size + 1) * sizeof(char));
		str[i_data.j][i_data.malloc_size] = '\0';
		if (str[i_data.j++] == NULL)
		{
			str = NULL;
			break ;
		}
	}
}

char	**lexer(char const *s, t_data *data)
{
	char	**str;
	size_t	countstr;

	if (!s)
		return (NULL);
	countstr = ft_countstr(s, data);
	if (data->exit_value != 0)
		return (NULL);
	str = (char **)malloc((countstr + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	splitstr(str, s, countstr, data);
	if (str == NULL)
		return (NULL);
	putchar_lexer(s, str, countstr);
	return (str);
}
