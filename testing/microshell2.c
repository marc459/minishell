#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define NONE 0
#define PIPE 1

typedef struct		c_cmd {
	char			**args;
	int				type;
	int				pp[2];
	struct c_cmd	*next;
	struct c_cmd	*prev;
}					t_cmd;

int		ft_strlen(char *str) {
	int		len = 0;

	while (str[len])
		len++;
	return (len);
}

void	ft_putstr(char *str) {
	write(2, str, ft_strlen(str));
}

void	exit_fatal(void) {
	ft_putstr("error: fatal\n");
	exit(EXIT_FAILURE);
}

char	*ft_strdup(char *str) {
	char	*res;
	int		i = -1;

	if (!(res = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		exit_fatal();
	while (str[++i])
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

void	clear(t_cmd *cmd) {
	t_cmd	*tmp;
	int		i;

	while (cmd) {
		i = -1;
		while (cmd->args[++i])
			free(cmd->args[i]);
		free(cmd->args);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

t_cmd	*create_cmd(t_cmd *tmp, char **av, int n_elem, int type) {
	t_cmd	*new_cmd;
	int		i = -1;

	if (!(new_cmd = malloc(sizeof(t_cmd))))
		exit_fatal();
	new_cmd->type = type;
	new_cmd->next = NULL;
	new_cmd->prev = tmp;
	if (tmp != NULL)
		tmp->next = new_cmd;
	if (!(new_cmd->args = malloc(sizeof(char *) * (n_elem + 1))))
		exit_fatal();
	while (++i < n_elem)
		new_cmd->args[i] = ft_strdup(av[i]);
	new_cmd->args[i] = NULL;
	return (new_cmd);
}

int		exec_cd(t_cmd *cmd) {
	int		res = 0, count = 0;

	while (cmd->args[count])
		count++;
	if (count != 2) {
		ft_putstr("error: cd: bad arguments\n");
		return (1);
	}
	else if ((res = chdir(cmd->args[1])) < 0) {
		ft_putstr("error: cd: cannot change directory to ");
		ft_putstr(cmd->args[1]);
		ft_putstr("\n");
	}
	return (res);
}

int		exec_non_built_in(t_cmd *cmd, char **env) {
	pid_t	pid;
	int		res = 0, status;

	if (cmd->type == PIPE)
		if (pipe(cmd->pp) < 0)
			exit_fatal();
	pid = fork();
	if (pid < 0)
		exit_fatal();
	else if (pid == 0) {
		if (cmd->type == PIPE && dup2(cmd->pp[1], 1) < 0)
			exit_fatal();
		if (cmd->prev && cmd->prev->type == PIPE && dup2(cmd->prev->pp[0], 0) < 0)
			exit_fatal();
		if ((res = execve(cmd->args[0], cmd->args, env)) < 0) {
			ft_putstr("error: cannot execute ");
			ft_putstr(cmd->args[0]);
			ft_putstr("\n");
		}
		exit(res);
	}
	else {
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			res = WEXITSTATUS(status);
		if (cmd->type == PIPE) {
			close(cmd->pp[1]);
			if (!cmd->next)
				close(cmd->pp[0]);
		}
		if (cmd->prev && cmd->prev->type == PIPE)
			close(cmd->prev->pp[0]);
	}
	return (res);
}

int		exec(t_cmd *cmd, char **env) {
	int		res = 0;

	while (cmd) {
		if (!strcmp(cmd->args[0], "cd"))
			res = exec_cd(cmd);
		else
			res = exec_non_built_in(cmd, env);
		cmd = cmd->next;
	}
	return (res);
}

int		main(int ac, char **av, char **env) {
	t_cmd	*cmd = NULL, *tmp = NULL;
	int		first = 1, last = 0, type, res = 0;

	while (++last < ac) {
		if (!strcmp(av[last], "|") || !strcmp(av[last], ";") || last + 1 == ac) {
			if (!strcmp(av[last], "|"))
				type = PIPE;
			else if (!strcmp(av[last], ";"))
				type = NONE;
			else {
				type = NONE;
				last++;
			}
			if (last - first != 0) {
				tmp = create_cmd(tmp, &av[first], last - first, type);
				if (cmd == NULL)
					cmd = tmp;
			}
			first = last + 1;
		}
	}
	res = exec(cmd, env);
	clear(cmd);
	return (res);
}
