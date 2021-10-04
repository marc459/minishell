
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#define READ_END 0
#define WRITE_END 1

int		main(void)
{
	int i;
	int a;
	a = 42;
	printf("espiritu%p\n",&a);
	i = fork();
	if(i == 0)
	{	a = 3;
		printf("hijo    %p %d\n",&a,a);
	}
	else
	{
		a = 4;
		printf("padre   %p %d\n",a,a);
	}
	/*const char	*father = "I am your father.\n";
	const char	*son = "It's not a phase! *doorslam*\n";
	char		buff[8];
	int			filedes[2];
	int			out;
	int fdtmp;

	int fd = open("a", O_WRONLY | O_APPEND);

	if (0 == pipe(filedes))
		write(1, "Pipe\n", 5);
	
	//close(filedes[READ_END]);
	fdtmp = dup(STDOUT_FILENO);
	dup2(filedes[WRITE_END], STDOUT_FILENO);
	
	//close(filedes[WRITE_END]);
	dup2(STDOUT_FILENO,filedes[WRITE_END]);
	write(STDOUT_FILENO, "hola", 5);

	//write(STDOUT_FILENO, buff, 8);
	return (0);
	*/
}
