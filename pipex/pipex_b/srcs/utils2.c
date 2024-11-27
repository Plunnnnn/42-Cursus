/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils2.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: bdenfir <bdenfir@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/04 16:40:33 by bdenfir		   #+#	#+#			 */
/*   Updated: 2024/10/05 15:52:14 by bdenfir		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

char	*find_executable(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths || !*paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_args(paths);
			return (path);
		}
		free(path);
	}
	free_args(paths);
	return (0);
}

void    pipe_redirection(int nb_cmd, t_pipex *data)
{
    int    i;

    if (nb_cmd == 0)
    {
        dup2(data->infile, STDIN_FILENO);
        dup2(data->pipe_fd[0][1], STDOUT_FILENO);
    }
    else if (nb_cmd == data->pipe_count)
    {
        dup2(data->pipe_fd[nb_cmd - 1][0], STDIN_FILENO);
        dup2(data->outfile, STDOUT_FILENO);
    }
    else
    {
        dup2(data->pipe_fd[nb_cmd - 1][0], STDIN_FILENO);
        dup2(data->pipe_fd[nb_cmd][1], STDOUT_FILENO);
    }
    i = 0;
    while (i < data->nb_cmd)
    {
        close(data->pipe_fd[i][0]);
        close(data->pipe_fd[i][1]);
        i++;
    }
    close(data->infile);
    close(data->outfile);
}
