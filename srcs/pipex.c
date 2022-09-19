/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alachris <alachris@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 23:49:17 by alachris          #+#    #+#             */
/*   Updated: 2022/09/16 22:06:49 by alachris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_error_file(char *str, int err_exit)
{
	ft_putstr_fd(str, 2);
	exit (err_exit);
}

void	free_paths(t_data *data)
{
	int	i;

	i = 0;
	while (data->path_cmd[i])
	{
		free(data->path_cmd[i]);
		i++;
	}
	free(data->path_cmd);
}

static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

static void	ft_init(t_data *data, int argc, char **argv, char **envp)
{
	data->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (data->outfile < 0)
		ft_error_file("Invalid outfile\n", ERR_IO_FILE);
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile < 0)
	{
		if (!access(argv[1], F_OK))
			ft_error_file("Infile not permission\n", 0);
		ft_error_file("Invalid infile\n", ERR_IO_FILE);
	}
	data->path = find_path(envp);
	data->path_cmd = ft_split(data->path, ':');
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
		ft_error_file("Invalid numbers of inputs\n", 2);
	ft_init(&data, argc, argv, envp);
	if (pipe(data.pipe) < 0)
		ft_error_file("Invalid pipe\n", 2);
	data.pid[0] = fork();
	if (data.pid[0] == 0)
		child_in(data, argv, envp);
	data.pid[1] = fork();
	if (data.pid[1] == 0)
		child_out(data, argv, envp);
	close(data.infile);
	close(data.outfile);
	close(data.pipe[0]);
	close(data.pipe[1]);
	waitpid(data.pid[0], NULL, 0);
	waitpid(data.pid[1], &data.exit_status, 0);
	free_paths(&data);
	return (WEXITSTATUS(data.exit_status));
}
