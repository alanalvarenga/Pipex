/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alachris <alachris@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 23:56:16 by alachris          #+#    #+#             */
/*   Updated: 2022/09/12 21:52:52 by alachris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> //open, close
# include <sys/wait.h> //waitpid

# include "./Libft/libft.h"

typedef struct s_data
{
	/* data */
	pid_t	pid[2];
	int		infile;
	int		outfile;
	int		pipe[2];
	char	*path;
	char	*cmd;
	char	**path_cmd;
	char	**args_cmd;
}	t_data;

//void	ft_init(t_data data, int argc, char **argv, char **envp);
void	child_in(t_data data,  char **argv, char **envp);
void	child_out(t_data data,  char **argv, char **envp);

#endif