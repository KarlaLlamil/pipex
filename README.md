pipex

📌 Description

Pipes are one of the interprocess communication in UNIX systems.

Every time you type a sequence of commands in a pipeline for the shell to
execute, the shell creates a separate process for each command and links the 
standard output of one process to the standard input of the next using a pipe.

This project recreates the behavior of shell pipelines for two commands by
creating multiple processes and redirecting file descriptors using system calls.

1. The program creates a pipe

2. Forks two child processes

3. Redirects:

 - file1 → stdin of cmd1

 - stdout of cmd1 → stdin of cmd2

 - stdout of cmd2 → file2

4. Executes commands using execve

The program reproduces the behavior of the following shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

🛠️ Features

- Executes commands using execve

- Creates child processes with fork

- Redirects input/output using pipe and dup2

- Resolves commands using the $PATH environment variable

- Handles file and command errors the same way as the shell




⚙️ Installation

```bash
git clone git@github.com:KarlaLlamil/pipex.git
cd minishell
make
```
Usage

```bash
./pipex file1 comd1 cmd2 file2
```
