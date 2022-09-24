/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alachris <alachris@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 00:28:44 by alachris          #+#    #+#             */
/*   Updated: 2022/09/24 23:44:49 by alachris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

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

void	child_in(t_data data, char **argv, char **envp, int i)
{
	if ((dup2(data.pipes[i][1], STDOUT_FILENO)) < 0)
		ft_error_file("ERRO dup2\n", 2);
	if ((dup2(data.infile, 0)) < 0)
		ft_error_file("ERRO dup2\n", 2);
	close_pipes(&data);
	close(data.infile);
	parse_args(&data, argv[2 + data.have_here_doc]);
	data.cmd = get_cmd(data.path_cmd, data.args_cmd[0]);
	if (!data.cmd)
	{
		free_cmd(&data);
		free_paths(&data);
		ft_error_file("Invalid command first\n", COMMAND_NOT_FOUND);
	}
	if ((execve(data.cmd, data.args_cmd, envp)) < 0)
		ft_error_file("execve first error\n", -1);
}

void	child_mid(t_data data, char **argv, char **envp, int i)
{
	if ((dup2(data.pipes[i][1], STDOUT_FILENO)) < 0)
		ft_error_file("ERRO dup2\n", 2);
	if ((dup2(data.pipes[i - 1][0], 0)) < 0)
		ft_error_file("ERRO dup2\n", 2);
	close_pipes(&data);
	parse_args(&data, argv[2 + i + data.have_here_doc]);
	data.cmd = get_cmd(data.path_cmd, data.args_cmd[0]);
	if (!data.cmd)
	{
		free_cmd(&data);
		free_paths(&data);
		ft_error_file("Invalid command mid\n", COMMAND_NOT_FOUND);
	}
	if ((execve(data.cmd, data.args_cmd, envp)) < 0)
		ft_error_file("execve mid error\n", -1);
}

void	child_out(t_data data, char **argv, char **envp, int i)
{
	if ((dup2(data.pipes[i - 1][0], STDIN_FILENO)) < 0)
		ft_error_file("ERRO dup2\n", 2);
	if ((dup2(data.outfile, 1)) < 0)
		ft_error_file("ERRO dup2\n", 2);
	close_pipes(&data);
	close(data.outfile);
	parse_args(&data, argv[2 + i + data.have_here_doc]);
	data.cmd = get_cmd(data.path_cmd, data.args_cmd[0]);
	if (!data.cmd)
	{
		free_cmd(&data);
		free_paths(&data);
		ft_error_file("Invalid command last\n", COMMAND_NOT_FOUND);
	}
	if ((execve(data.cmd, data.args_cmd, envp)) < 0)
		ft_error_file("execve last error\n", -1);
}
