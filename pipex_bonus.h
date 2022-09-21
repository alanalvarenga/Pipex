/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alachris <alachris@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 21:11:59 by alachris          #+#    #+#             */
/*   Updated: 2022/09/21 02:05:03 by alachris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> //open, close
# include <sys/wait.h> //waitpid
# include "./Libft/libft.h"

# define COMMAND_NOT_FOUND 127
# define ERR_IO_FILE 1

typedef struct s_data
{
	pid_t	*pid;
	int		infile;
	int		outfile;
	int		**pipes;
	int		exit_status;
	int		here_doc;
	int		total_cmds;
	char	*path;
	char	*cmd;
	char	**path_cmd;
	char	**args_cmd;
}	t_data;

void	ft_error_file(char *str, int err_exit);
void	free_paths(t_data *data);
void	child_in(t_data data, char **argv, char **envp, int i);
void	child_mid(t_data data, char **argv, char **envp, int i);
void	child_out(t_data data, char **argv, char **envp, int i);
void	parse_args(t_data *data, char *args);
void	pipes_create(t_data *data, char **argv, char **envp);
void	close_pipes(t_data *data);

#endif