t_general : General structure has the next parameters.


|	Type	|		Name		|		Description								|
|-----------|-------------------|-----------------------------------------------|
|	size_t	|	npipes			|	Number of pipes.							|
|	size_t	|	ncomands		|	Number of comands executables.				|
|	size_t	|	nredirections	|	Number of redirections.						|
|	size_t	|	nfiles			|	Number of files.							|
|	t_arg	|	*arg			|	Array of a t_arg structure that has all the	|
|			|					|	information about the string.				|
|-----------|-------------------|-----------------------------------------------|

Example :

comand : < infile.txt ls -la | grep hola > outfile.txt

{
	npipes = 1;
	ncomands = 2;
	nredirections = 2;
	nfiles = 2;
	t_arg =	
	|-------|-------------------|---------------|-------|---------------|-------|-------------------|
	|	1	|		4			|		3		|	5	|		3		|	2	|		4			|
	|	"<"	|	"infile.txt"	|	"ls -la"	|	"|"	|	"grep hola"	|	">"	|	"outfile.txt"	|
	|-------|-------------------|---------------|-------|---------------|-------|-------------------|			
}

t_arg : Argument structure has the infromtion of itch comand, pipe, redirection, etc.


|	Type	|		Name		|		Description								|
|-----------|-------------------|-----------------------------------------------|
|	size_t	|	type			|	Kind of argument you have : 				|
|			|					|	1 .- Input redirection (<)					|
|			|					|	2 .- Output redirection (>)					|
|			|					|	3 .- Excecutable (echo, ls, grep, etc)		|
|			|					|	4 .- Files to read or write.				|
|			|					|	5 .- Pipe. (|)								|
|			|					|	6 .- End comand. (;)						|
|			|					|	7 .- Apend redirection. (>>)				|
|			|					|	8 .- Heredoc redirection. (<<)				|
|			|					|												|
|	char *	|	content			|	String whith the content of the instruction	|
|-----------|-------------------|-----------------------------------------------|

