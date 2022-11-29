/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:51:11 by rlins             #+#    #+#             */
/*   Updated: 2022/11/29 06:03:51 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_PATH 4096

# include "./libft.h"
# include <stdio.h> // Printf
# include <stdlib.h> // Malloc, Free, exit
# include <fcntl.h> // Open
# include <unistd.h> // read, execve, fork, pipe, getcwd
# include <sys/wait.h> // waitpid
# include <signal.h> // signal
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <errno.h> // errno
# include <sys/stat.h> //S_ISDIR
# include <readline/readline.h> // Readline
# include <readline/history.h> // History

# define OLD_PWD "OLDPWD"
# define PWD "PWD"

# define STDOUT	STDOUT_FILENO
# define STDIN	STDIN_FILENO
# define STDERR	STDERR_FILENO

# define OR		1
# define AND	2
# define PIPE	3

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXEC 126

// Color prompt
# define GREEN "\001\033[0;92m\002"
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[0;93m\002"

typedef struct s_command
{
	char	*cmd;
	char	**args;
	int		args_count;
}	t_command;

typedef struct s_data
{
	char		*user_input;
	char		**env;
	char		*work_dir;
	char		*old_work_dir;
	t_command	*command;
}	t_data;

typedef struct s_cmd
{
	char	*cmd;
	char	*path;
	char	**args;
	char	**redirections;
	int		*pipe_fd;
	int		exit_value;
}	t_cmd;

typedef struct s_commands
{
	pid_t	*pid;
	int		num_cmds;
	int		num_exec;
	char	**cmds;
	char	**paths;
	int		*operators;
	int		exit_value;
	t_cmd	*cmd;
}	t_commands;

typedef struct s_index_data
{
	size_t	i;
	size_t	malloc_size;
	size_t	j;
}	t_index_data;

extern int	g_status_code;

/******************************************************************************/
/*Begin - Initialization*/
/******************************************************************************/
/**
 * @brief First method in project.
 * @param argc Arguments count
 * @param argv Arguments Vector
 * @param envp Environment pointer variable
 * @return int
 */
int		init(int argc, char **argv, char **envp);

/**
 * @brief Initialize the structure of minishell
 * @param data TypeDef in MiniShell
 * @param envp Pointer to Environment variables
 * @return true - Success
 * @return false - Problem
 */
bool	init_structure(t_data *data, char **envp);

/**
 * @brief Initialize the commands structure
 * @param data Structure of MiniShell
 * @param cmds Commands structure
 */
void	init_cmds(t_data *data, t_commands *cmds);

/**
 * @brief Initialize a command structure
 * @param data Structure of MiniShell
 * @param cmds Commands structure
 */
void	init_cmd(t_data *data, t_commands *cmds);

/**
 * @brief Return the number of arguments passed in the command
 * @param args TypeDef in MiniShell
 * @return int - Count Number of arguments. The Command argument will be ignored
 * in this method. Return just arguments
 */
int		args_count(char **args);

/**
 * @brief Validate number of arguments of Mini-shell
 * @param argc Argument Counts
 * @return true - Valid
 * @return false - Failed
 */
bool	valid_args(int argc);

/**
 * @brief Verify if all sentence is just space or similar char
 * @param str String / User Input
 * @return true
 * @return false
 */
bool	just_space_string(char *str);

/******************************************************************************/
/*End - Initialization*/
/******************************************************************************/

/**
 * @brief Responsible to exit / finish the shell.
 * @param status_code
 * @param data Data to clean up
 */
void	exit_shell(t_data *data, int status_code);

/**
 * @brief Manipulate Signals in MiniShell when the prompt is waiting for a
 * command.
 * 	(Ctrl+D) The Same - Terminate
 * 	(Ctrl+C) SIGINT: New line in clean prompt
 * 	(Ctrl+\) SIGQUIT: Ignored
 */
void	signals_wait_cmd(void);

/**
 * @brief Manipulate Signals in MiniShell when the prompt is executing some
 * command.
 * 	(Ctrl+D) The Same - Terminate
 * 	(Ctrl+C) SIGINT: New line
 * 	(Ctrl+\) SIGQUIT: New line
 *
 */
void	signals_run_cmd(void);

/**
 * @brief Get the prompt text of mini-shell
 * @param data Structure of MiniShell
 * @return char* Text of prompt
 */
char	*get_prompt(t_data *data);

/******************************************************************************/
/*Begin - Builtins*/
/******************************************************************************/
/**
 * @brief Verify if the command is a Builtin command. This is necessary to know
 * what is came from terminal
 * @param argv
 * @return true
 * @return false
 */
bool	is_builtin(char *argv);

/**
 * @brief Call correct function from Builtin command
 * @param data Structure of MiniShell
 * @return code of execution. Success or error
 */
int		call_builtin(t_data *data);

/**
 * @brief Builtins Echo - Represent the Echo command in shell (-n flag enabled)
 * @param data Structure of MiniShell
 */

int		cmd_echo(t_data *data);

/**
 * @brief Builtins Exit - Responsible to close the program.
 * @param data Structure of MiniShell
 * @return int - exit code
 */
int		cmd_exit(t_data *data);

/**
 * @brief Builtins - PWD Command - Print working directory
 * @return Integer - Result of command
 */
int		cmd_pwd(void);

/**
 * @brief Builtins - Env - Environment Variables
 * @param data Structure of MiniShell
 * @param exp_no_arg Export With no args - Show env with a pre-fix
 * @return integer - success or error
 */
int		cmd_env(t_data *data, bool exp_no_arg);

/**
 * @brief Builtins - Command Change Directory.
 * @param data Structure of MiniShell
 */
int		cmd_cd(t_data *data);

/**
 * @brief Builtins - Unset Variables
 * @param data Structure of MiniShell
 */
int		cmd_unset(t_data *data);

/**
 * @brief Verify if the name of variable is a valid name
 * @param name
 * @return true
 * @return false
 */
bool	is_valid_var_name(char *name);

/******************************************************************************/
/*End - Builtins*/
/******************************************************************************/

/******************************************************************************/
/*Begin - Utils*/
/******************************************************************************/

/**
 * @brief Deallocate memory from a pointer. Update the variable to NULL
 * (good pattern)
 * @param ptr Pointer to be free.
 */
void	free_ptr(void *ptr);

/**
 * @brief
 *
 * @param data
 * @param exit_shell
 */
void	free_data(t_data *data, bool exit_shell);

/**
 * @brief Temporary variable - Split the command with spaces
 * @param command
 * @return char**
 */
char	**split_args(char *command);

/**
 * @brief deallocate memory to pointer to pointer.
 * @param arr_str Pointer to pointer variable to be freed
 */
void	free_array_str(char **arr_str);

/**
 * @brief Free all the terms of cmds
 * @param cmds Commands structure
 */
void	free_cmds(t_commands *cmds);

/**
 * @brief Handler error messages when commands will be applied.
 *
 * @param cmd Command applied
 * @param detail Details. Not required
 * @param msg Msg of error
 * @param status_code Will be the return, get in method called
 * @return int Code of error returned
 */
int		error_msg_cmd(char *cmd, char *detail, char *msg, int status_code);

/******************************************************************************/
/*End - Utils*/
/******************************************************************************/

/******************************************************************************/
/*Begin - Execute*/
/******************************************************************************/

/** TODO:Lins. Add epois
 * @brief
 *
 * @param data
 * @return int
 */
int		exec_handler(t_data *data);
/******************************************************************************/
/*End - Execute*/
/******************************************************************************/

/******************************************************************************/
/*Begin - Env*/
/******************************************************************************/
/**
 * @brief Will try to find the variable in environment variable
 * @param env All the environment variables
 * @param var Variable to search
 * @return Value of the variable
 */
char	*get_env_var_value(char **env, char *var);

/**
 * @brief Will try to find the variable in environment variable
 * @param env All the environment variables
 * @param var Variable to search
 * @return Index inside the environment variables (-1) if there is no variable
 * with this name
 */
int		get_env_var_index(char **env, char *var);

/**
 * @brief Count the number of environment variable
 * @param envp Pointer to Environment variables
 * @return int - Number or variables
 */
int		env_var_count(char **envp);

/**
 * @brief Update or insert a new environment variable. Value may be null if
 * the variable was not found.
 * If Index is positive, the variable exist! Otherwise, will be a new variable.
 * @param data Structure of MiniShell
 * @param key key of variable
 * @param value value of variable
 * @return true - Success
 * @return false - Failed
 */
bool	set_env_var(t_data *data, char *key, char *value);

/**
 * @brief Will remove a variable environment based on this index
 * @param data Structure of MiniShell
 * @param index Index to remove
 */
void	env_var_remove(t_data *data, int index);

/**
 * @brief Builtins Export - Just one argument, just export all variables.
 * Sortable and with 'declare -x'
 */
int		cmd_export(t_data *data);

/**
 * @brief Realloc memory to Environment variable
 * @param data Data structure
 * @param size Size / number of variables
 * @return char** -> New char
 */
char	**env_var_realloc(t_data *data, int size);

/******************************************************************************/
/*End - Env*/
/******************************************************************************/

/******************************************************************************/
/*Begin - Lexer*/
/******************************************************************************/

/**
 * @brief Tokenize the string based on parenthesis and operators
 * @param s User input
 * @param cmds Structure of commands
 * @return char** -> Tokenizer string
 */
char	**lexer(char const *s, t_commands *cmds);

/**
 * @brief Copy the user input into the tokenize string
 * @param s User input
 * @param str Tokenized string
 * @param countc Number of divisions of user input
 */
void	putchar_lexer(char const *s, char **str, size_t countc);

/**
 * @brief Handle the errors that could be present in the user input
 * @param i_data Index variable
 * @param s User input
 * @param cmds Structure of commands
 */
void	lexer_errors(t_index_data *i_data, const char *s, t_commands *cmds);

/**
 * @brief Handle the parenthesis present in the user input
 * @param s User input
 * @param cmds Structure of commands
 */
void	lexer_parenthesis(const char *s, t_commands *cmds);

/**
 * @brief Handle errors that may be present in user input
 * @param i_data Index variable
 * @param s User input
 * @param cmds Structure of commands
 */
void	quotes_error(t_index_data *i_data, const char *s, t_commands *cmds);
void	lexer_redirections(const char *s, t_commands *cmds);

/******************************************************************************/
/*End - Lexer*/
/******************************************************************************/

/******************************************************************************/
/*Begin - Parser*/
/******************************************************************************/

/**
 * @brief Tokenize command based on their arguments
 * @param s Command
 * @return char** -> Command split in arguments
 */
char	**parser(char *s);

/**
 * @brief Copy the command into the tokenize string
 * @param s Command of user input
 * @param str Split command
 * @param countc Number of arguments
 */
void	putchar_parser(char *s, char **str, size_t countc);

/**
 * @brief Swap the '$' in input for environment variable value
 * @param i_data index variable
 * @param s Command of user input
 * @param data Data structure
 */
char	*handle_env(t_index_data *i_data, char *s, t_data *data);
void	find_dollar_sign(t_data *data, t_commands *cmds, int num_cmd);
char	**handle_redirection(char *s);
void	putchar_redirection(char *s, char **str, size_t countc);
char	*rm_redirection(char *s);
void	copy_cmd(char *s, char *new_str, size_t countc);

/******************************************************************************/
/*End - Parser*/
/******************************************************************************/

#endif
