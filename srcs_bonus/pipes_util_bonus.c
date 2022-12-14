/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alachris <alachris@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:18:11 by alachris          #+#    #+#             */
/*   Updated: 2022/09/25 00:20:33 by alachris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	allocate_data(t_data *data)
{	
	int	i;

	i = 0;
	data->pid = ft_calloc ((data->total_cmds + 1), sizeof(*data->pid));
	data->pipes = ft_calloc(data->total_cmds, sizeof(*data->pipes));
	while (i < data->total_cmds)
	{
		data->pipes[i] = ft_calloc(2, sizeof(int));
		i++;
	}
}

void	free_pid_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_cmds)
	{
		free(data->pipes[i]);
		i++;
	}
	free(data->pid);
	free(data->pipes);
}

void	open_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_cmds)
	{
		if (pipe(data->pipes[i]) < 0)
		{
			free_paths(data);
			ft_error_file("Invalid pipe\n", 2);
		}
		i++;
	}
}

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_cmds)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

void	pipes_create(t_data *data, char **argv, char **envp)
{
	int	i;

	allocate_data(data);
	open_pipes(data);
	i = 0;
	while (i < data->total_cmds)
	{
		data->pid[i] = fork();
		if ((i == 0) && (data->pid[i] == 0))
			child_in(*data, argv, envp, i);
		else if ((i < (data->total_cmds -1)) && (data->pid[i] == 0))
			child_mid(*data, argv, envp, i);
		else if (data->pid[i] == 0)
			child_out(*data, argv, envp, i);
		i++;
	}
	i = 0;
	while ((i < data->total_cmds) && (data->pid[i]))
	{
		close_pipes(data);
		waitpid(data->pid[i], &data->exit_status, 0);
		i++;
	}
	free_pid_pipes(data);
}
