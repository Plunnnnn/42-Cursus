/* ************************************************************************** */
/*									  */
/*							:::	 ::::::::   */
/*   pipex.c											:+:   :+:	:+:   */
/*						  +:+ +:+	   +:+	*/
/*   By: bdenfir <bdenfir@student.42.fr>			+#+  +:+	   +#+	*/
/*						+#+#+#+#+#+   +#+	 */
/*   Created: 2024/10/04 16:10:26 by bdenfir		   #+#  #+#		  */
/*   Updated: 2024/11/27 22:14:31 by bdenfir		  ###   ########.fr	*/
/*									  */
/* ************************************************************************** */

#include "pipex.h"

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

t_pipex *init_data(char *file1, char *file2, pid_t *pids, int nb_cmd, int here_doc)
{
	t_pipex *data;
	int  i;

	data = malloc(sizeof(t_pipex));
	if (!data)
		error_exit("memory allocation failed", NULL);
		
	data->nb_cmd = nb_cmd;
	data->infile = -1;
	data->outfile = -1;
	i = 0;
	while (i < nb_cmd)
	{
		data->pipe_fd[i][0] = -1;
		data->pipe_fd[i][1] = -1;
		i++;
	}
	data->pids = pids;
	data->pipe_count = nb_cmd - 1;
	if (!here_doc)
	{
		data->infile = open(file1, O_RDONLY);
		data->outfile = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
		data->outfile = open(file2, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((!here_doc && data->infile < 0) || data->outfile < 0)
		error_exit("Error opening files", data);
	return (data);
}

pid_t	fork_child(t_pipex *data, char **argv, char **envp, int nb_cmd)
{
	pid_t	pid;
	char	*cmd;
	char	**args;

	args = ft_split(argv[(nb_cmd + 2) + (argv[1][0] == 'h') ], ' ');
	if (args)
		cmd = find_executable(args[0], envp);
	else
		cmd = NULL;
	pid = fork();
	if (pid < 0)
		error_exit("Error creating fork/child process", data);
	if (pid == 0)
	{
		pipe_redirection(nb_cmd, data);
		if (execve(cmd, args, envp) == -1)
		{
			free_args(args);
			free(cmd);
			error_exit("exec", data);
		}
	}
	free_args(args);
	free(cmd);
	return (pid);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex *data;
	pid_t   *pids;
	int  i;
	int  here_doc;

	here_doc = (argc > 1 && ft_strncmp(argv[1], "here_doc", 8) == 0);
	if ((!here_doc && argc < 5) || (here_doc && argc < 6))
		error_exit("Invalid argument\nUsage: ./pipex file1 cmd1 cmd2 file2\n	   ./pipex here_doc LIMITER cmd1 cmd2 file2", NULL);
	pids = malloc(sizeof(pid_t) * (argc - (3 + here_doc)));
	if (!pids)
		error_exit("Memory allocation for pids array failed", NULL);
	if (!envp || !*envp)
		error_exit("Environment variable is NULL", NULL);
		
	data = init_data(argv[1], argv[argc - 1], pids, argc - (3 + here_doc), here_doc);
	if (here_doc)
		handle_here_doc(argv[2], data);
	create_pipe(data);
		
	i = -1;
	while (++i < argc - (3 + here_doc))
	{
		pids[i] = fork_child(data, argv, envp, i);
	}
		
	clean_data(data);
	wait_pid(&pids, argc - (3 + here_doc));
	free(pids);
	free(data);
	return (0);
}