/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alachris <alachris@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 00:28:44 by alachris          #+#    #+#             */
/*   Updated: 2022/09/16 22:06:56 by alachris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		paths++;
		free(command);
	}
	return (NULL);
}

static void	free_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->args_cmd[i])
	{
		free(data->args_cmd[i]);
		i++;
	}
	free(data->args_cmd);
	free(data->cmd);
}

void	child_in(t_data data, char **argv, char **envp)
{
	dup2(data.pipe[1], STDOUT_FILENO);
	dup2(data.infile, 0);
	close(data.pipe[0]);
	close(data.pipe[1]);
	close(data.infile);
	parse_args(&data, argv[2]);
	data.cmd = get_cmd(data.path_cmd, data.args_cmd[0]);
	if (!data.cmd)
	{
		free_cmd(&data);
		free_paths(&data);
		ft_error_file("Invalid command 1\n", COMMAND_NOT_FOUND);
	}
	execve(data.cmd, data.args_cmd, envp);
}

void	child_out(t_data data, char **argv, char **envp)
{
	dup2(data.pipe[0], STDIN_FILENO);
	dup2(data.outfile, 1);
	close(data.pipe[0]);
	close(data.pipe[1]);
	close(data.outfile);
	parse_args(&data, argv[3]);
	data.cmd = get_cmd(data.path_cmd, data.args_cmd[0]);
	if (!data.cmd)
	{
		free_cmd(&data);
		free_paths(&data);
		ft_error_file("Invalid command 2\n", COMMAND_NOT_FOUND);
	}
	execve(data.cmd, data.args_cmd, envp);
}
