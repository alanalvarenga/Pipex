/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alachris <alachris@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 23:56:16 by alachris          #+#    #+#             */
/*   Updated: 2022/09/20 21:32:58 by alachris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> //open, close
# include <sys/wait.h> //waitpid
# include "./Libft/libft.h"

# define COMMAND_NOT_FOUND 127
# define ERR_IO_FILE 1

typedef struct s_data
{
	pid_t	pid[2];
	int		infile;
	int		outfile;
	int		pipes[2];
	int		exit_status;
	char	*path;
	char	*cmd;
	char	**path_cmd;
	char	**args_cmd;
}	t_data;

void	ft_error_file(char *str, int err_exit);
void	free_paths(t_data *data);
void	child_in(t_data data, char **argv, char **envp);
void	child_out(t_data data, char **argv, char **envp);
void	parse_args(t_data *data, char *args);

#endif