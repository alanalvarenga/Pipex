/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alachris <alachris@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:01:09 by alachris          #+#    #+#             */
/*   Updated: 2022/09/21 02:00:11 by alachris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static void	put_spaces(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '\'')
		{
			i++;
			while ((args[i] != '\'') && (args[i] != '\0'))
			{
				if (args[i] == 1)
					args[i] = ' ';
				i++;
			}
		}
		i++;
	}
}

static void	change_spaces(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '\'')
		{
			i++;
			while ((args[i] != '\'') && (args[i] != '\0'))
			{
				if (args[i] == ' ')
					args[i] = 1;
				i++;
			}
		}
		i++;
	}
}

static char	*remove_quotes(char *args)
{
	int		i;
	int		str_len;
	char	*new_str;

	i = 0;
	str_len = 0;
	while (args[i])
	{
		if (args[i] != '\'')
			str_len++;
		i++;
	}
	new_str = ft_calloc(str_len + 1, sizeof(char));
	i = 0;
	while (*args)
	{
		if (*args != '\'')
		{
			new_str[i] = *args;
			i++;
		}
		args++;
	}
	return (new_str);
}

void	parse_args(t_data *data, char *args)
{
	int	x;
	int	y;

	y = 0;
	change_spaces(args);
	data->args_cmd = ft_split(args, ' ');
	while (data->args_cmd[y])
	{
		put_spaces(data->args_cmd[y]);
		x = 0;
		while (data->args_cmd[y][x])
		{
			if (data->args_cmd[y][x] == '\'')
			{
				data->args_cmd[y] = remove_quotes(data->args_cmd[y]);
				break ;
			}
			x++;
		}
		y++;
	}
}
