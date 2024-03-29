```
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝

```                                                                 
Minishell is a project that simulate a real shell like bash.
Compatible with linux && Mac.

### How to use

### Clone repo

```sh
git clone https://github.com/marc459/minishell.git
```

### Linux dependencies

Install readline library:

- On Debian based platforms, like Ubuntu:

```sh
sudo apt install libreadline-dev
```

- Platforms with `yum`, like SUSE:

```sh
yum install readline-devel
```

- For other platform please search for the package name on google, thx :)

### MAC dependencies

- Install readline library:

```sh
brew install readline
```

### Compile and execute

Run `make` (make rules: `all`, `clean`, `fclean` and `re`)

```sh
cd ./minishell && make
```

Execute the `./minishell` binary generated after running `make`

```sh
./minishell
```

## Features

- Recreates most of the bash shell.
- support for config file `.minishrc` (like bash `.bashrc`).
- comments with `#` (NOTE: `#` must be at the start of the line).
- Pipes `|` works like in bash.
- Redirections `<`, `>`, `<<`, `>>` work like in bash.
- `$?` works like in bash.
- wildcards `*` and `?` works for the current directory.
- Handle signals: `Ctrl-C`, `Ctrl-D` and `Ctrl-\` like in bash.
- Enviroments variables.
- Arrow keys.
- History (command history).
- Auto-complete with tab key.
//Bonus Features to implement
- `;`, `&&` and `||` work like in bash.
- Parenthesis: `(` and `)` works with `&&`, `||` and `;` for priorities.

### Built-in commands

- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

## Components

minishell is formed by 3 components:

1. Lexical analyzer: parse the input line into tokens.

2. Parser: parse tokens into an abstract syntax tree (ast).

3. Executor: execute the commands

## DEVELOPING PARTS ##

### LEXER ###
Reads de line and identify all the parts that component the comands, tokenising them


t_general : General structure has the next parameters.

|	type	|		Name		|		Description								|
|-----------|-------------------|-----------------------------------------------|
|	size_t	|	npipes			|	Number of pipes.							|
|	----	|		----		|					----						|
|	size_t	|	nexecutables		|	Number of comands executables.				|
|	----	|		----		|					----						|
|	size_t	|	nredirections	|	Number of redirections.						|
|	----	|		----		|					----						|
|	size_t	|	nfiles			|	Number of files.							|
|	----	|		----		|					----						|
|	int		|	quote			|	Integer who is 1 if the single quote are	|
|			|					|	closed or -1 if are open.					|
|			|					|	Example :									|
|			|					|	1.- str = echo 'hi my name is EMA.'			|
|			|					|	1.- quote = 1. 								|
|			|					|	2.- str = echo 'hi my name is EMA.			|
|			|					|	2.- quote = -1. 							|
|	    	|		    		|					    						|
|	int		|	dquote			|	Integer who is 1 if the double quote are	|
|			|					|	closed or -1 if are open.					|
|			|					|	Example :									|
|			|					|	1.- str = echo "hi my name is EMA."			|
|			|					|	1.- quote = 1. 								|
|			|					|	2.- str = echo "hi my name is EMA.			|
|			|					|	2.- quote = -1. 							|
|	    	|			    	|						    					|
|	t_arg	|	*arg			|	Array of a t_arg structure that has all the	|
|			|					|	information about the string.				|



Example :

comand : < infile.txt ls -la | grep hola > outfile.txt

{
	npipes = 1;
	nexecutables = 2;
	nredirections = 2;
	nfiles = 2;
	quote = 1;
	dquote = 1;
	t_arg =

|	1	|		4			|		3		|	5	|		3		|	2	|		4			|
|-------|-------------------|---------------|-------|---------------|-------|-------------------|
|	"<"	|	"infile.txt"	|	"ls -la"	|	"|"	|	"grep hola"	|	">"	|	"outfile.txt"	|
|-------|-------------------|---------------|-------|---------------|-------|-------------------|

}

t_arg : Argument structure has the infromtion of itch comand, pipe, redirection, etc.


|	type	|		Name		|		Description								|
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
|	----	|		----		|					----						|
|	char *	|	content			|	String whith the content of the instruction	|

### PARSER ###
Builds de command table and identify them as a (command, pipe, inputfile, outputfile, $expansionvars, redirecctions, *subshell* )**/ 
parser(command);
	
### EXECUTOR ###

The executor will take the command table generated by the parser and for every 
SimpleCommand in the array it will create a new process. It will also if necessary create pipes 
to communicate the output of one process to the input of the next one. Additionally, it will 
redirect the standard input, standard output, and standard error if there are any redirections.

## :star:AUTHORS:star: ##
:boy: msantos- 
:boy: emgarcia
