/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: bdenfir <bdenfir@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/03 14:45:01 by bdenfir		   #+#	#+#			 */
/*   Updated: 2024/10/05 21:42:34 by bdenfir		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(t_pipex *data)
{
	int i;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (pipe(data->pipe_fd[i]) == -1)
			error_exit("failed to create pipe", data);
		i++;
	}
}

void wait_pid(pid_t **pids, int nb_cmd)
{
	int i;
		
	i = 0;
	while (i < nb_cmd)
	{	
		waitpid((*pids)[i], NULL, 0);
		i++;
	}
}

void	clean_data(t_pipex *data)
{
	int i;

	if (!data)
		return;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (data->pipe_fd[i][0] >= 0)
			close(data->pipe_fd[i][0]);
		if (data->pipe_fd[i][1] >= 0)
			close(data->pipe_fd[i][1]);
		i++;
	}
	if (data->infile >= 0)
		close(data->infile);
	if (data->outfile >= 0)
		close(data->outfile);
}

void	error_exit(char *str, t_pipex *data)
{
	clean_data(data);
	if (data)
	{
		if (data->pids)
			free(data->pids);
		free(data);
	}
	perror(str);
	exit(EXIT_FAILURE);
}
