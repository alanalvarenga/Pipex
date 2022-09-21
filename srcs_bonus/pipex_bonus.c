/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alachris <alachris@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 22:38:05 by alachris          #+#    #+#             */
/*   Updated: 2022/09/21 02:32:47 by alachris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	ft_error_file(char *str, int err_exit)
{
	ft_putstr_fd(str, 2);
	exit (err_exit);
}

static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
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
	data->total_cmds = argc - 3;
	pipes_create(data, argv, envp);
	free_paths(data);
}

int	ft_init_here_doc()
{
	return 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
		ft_error_file("Too few arguments\n", 2);
	else if ((ft_strncmp(argv[1], "here_doc", 8) == 0) && (argc < 6))
		ft_error_file("Too few arguments to here_doc\n", 2);
	else if ((ft_strncmp(argv[1], "here_doc", 8) == 0) && (argc >= 6))
		ft_init_here_doc();
		//ft_init_here_doc(&data, argc, argv, envp);
	else if (argc >= 5)
		ft_init(&data, argc, argv, envp);

	return 0;
}
