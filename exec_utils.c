/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alachris <alachris@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 00:28:44 by alachris          #+#    #+#             */
/*   Updated: 2022/09/11 02:57:53 by alachris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, 0) == 0)
			return (command);
		paths++;
	}
	return (NULL);
}

void	child_in(t_data data,  char **argv, char **envp)
{
	dup2(data.pipe[1], STDOUT_FILENO);
	dup2(data.infile, 0);
	close(data.pipe[0]);
	close(data.pipe[1]);
	close(data.infile);
	data.args_cmd = ft_split(argv[2], ' ');
	data.cmd = get_cmd(data.path_cmd, data.args_cmd[0]);
	execve(data.cmd, data.args_cmd, envp);
}

void	child_out(t_data data,  char **argv, char **envp)
{
	dup2(data.pipe[0], STDIN_FILENO);
	dup2(data.outfile, 1);
	close(data.pipe[0]);
	close(data.pipe[1]);
	close(data.outfile);
	data.args_cmd = ft_split(argv[3], ' ');
	data.cmd = get_cmd(data.path_cmd, data.args_cmd[0]);
	execve(data.cmd, data.args_cmd, envp);
}