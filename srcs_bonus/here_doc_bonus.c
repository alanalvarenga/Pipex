/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alachris <alachris@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:35:54 by alachris          #+#    #+#             */
/*   Updated: 2022/09/23 22:58:34 by alachris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	fill_here_doc(t_data *data, char *limiter)
{
	char	*line;
	int		fd_line;

	fd_line = dup(0);
	while (1)
	{
		ft_putstr_fd("here_doc>", 1);
		line = get_next_line(fd_line);
		if ((ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			&& (ft_strlen(line) - 1) == ft_strlen(limiter))
		{
			free(line);
			close(fd_line);
			close(data->here_doc[0][1]);
			line = get_next_line(fd_line);
			break ;
		}
		write(data->here_doc[0][1], line, ft_strlen(line));
		free(line);
	}
	free(line);
}

void	get_infile_here_doc(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->here_doc = ft_calloc(sizeof(int **), 2);
	data->here_doc[0] = ft_calloc(sizeof(int), 2);
	if (pipe(data->here_doc[0]) < 0)
	{
		free_paths(data);
		ft_error_file("Invalid pipe\n", 2);
	}
	fill_here_doc(data, argv[2]);
	data->infile = data->here_doc[0][0];
	if (data->here_doc)
	{
		while (data->here_doc[i])
		{
			free(data->here_doc[i]);
			i++;
		}
		free(data->here_doc);
	}
}

void	ft_init_here_doc(t_data *data, int argc, char **argv, char **envp)
{
	data->have_here_doc = 1;
	data->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (data->outfile < 0)
		ft_error_file("Invalid outfile\n", ERR_IO_FILE);
	data->path = find_path(envp);
	data->path_cmd = ft_split(data->path, ':');
	data->total_cmds = argc - 4;
	get_infile_here_doc(data, argv);
	if (data->infile < 0)
		ft_error_file("Invalid infile\n", ERR_IO_FILE);
	pipes_create(data, argv, envp);
	free_paths(data);
}
