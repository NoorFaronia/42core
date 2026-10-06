*This project has been created as part of the 42 curriculum by nnasered, nfaronia.*

---

# minishell

## Description

Minishell is a simplified Unix shell implemented in C as part of the 42 school curriculum. The goal of the project is to deeply understand how a shell works by building one from scratch — covering input parsing, command execution, process management, redirections, pipes, variable expansion, and signal handling.

The shell replicates the core behavior of bash in interactive mode. It reads commands from the user via a prompt, parses them into an internal representation, expands variables, sets up redirections and pipelines, then forks processes to execute commands. Built-in commands are executed directly in the shell process without forking.

The project covers the following major areas:

- Lexical analysis: tokenizing raw input into a stream of typed tokens (words, pipes, redirections)
- Parsing: building an Abstract Syntax Tree (AST) from the token stream
- Expansion: resolving environment variables, quote stripping, and word splitting
- Execution: single commands, pipelines, built-ins, external commands via `execve`
- Redirections: input (`<`), output (`>`), append (`>>`), and here-document (`<<`)
- Signal handling: correct behavior for `ctrl-C`, `ctrl-D`, and `ctrl-\` in interactive and non-interactive modes
- History: persistent command history stored in `.minishell_history`
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

---

## Architecture Overview

The codebase is organized into clearly separated layers:

```
Input (readline)
     |
  Lexer       -- tokenizes raw input into a linked list of tokens
     |
  Parser      -- builds an AST from tokens (NODE_CMD, NODE_PIPE)
     |
  Expander    -- resolves $VAR, $?, quote removal, word splitting, glob-free field splitting
     |
  Translation -- converts the AST into a flat linked list of t_cmd structs
     |
  Executor    -- dispatches to pipeline or simple command execution
     |
  Builtins / execve
```

---

## Features

- Interactive prompt (`minishell$ `) using GNU Readline
- Persistent history across sessions (up to 1000 entries, stored in `.minishell_history`)
- Full quote handling: single quotes suppress all interpretation; double quotes suppress all except `$`
- Variable expansion: `$VAR`, `$?` (last exit status), bare `$` treated literally
- Word splitting after expansion (unquoted expanded values split on spaces)
- Ambiguous redirect detection (expansion of a redirection filename to multiple words is an error)
- Pipelines of arbitrary length
- All four redirection types including here-document with optional quote-suppressed expansion
- Temporary variable assignments before commands (`VAR=value cmd`) with correct scoping
- Local variable support (`VAR=value` with no following command)
- Signal handling matching bash: `ctrl-C` reprints prompt, `ctrl-D` exits, `ctrl-\` is ignored
- Correct exit codes: `127` for command not found, `126` for permission/not-executable, `130` for SIGINT

### Built-in commands

| Command | Behavior |
|---|---|
| `echo [-n] [args...]` | Print arguments to stdout; `-n` suppresses trailing newline |
| `cd [path]` | Change directory; with no argument, changes to `$HOME` |
| `pwd` | Print current working directory |
| `export [name[=value]...]` | Add or update environment variables; with no args, print in `declare -x` format |
| `unset [name...]` | Remove variables from the environment and local variable table |
| `env` | Print all exported environment variables |
| `exit [n]` | Exit the shell with optional numeric exit code |

---

## Instructions

### Requirements

- GCC or Clang
- GNU Readline development library

### Compilation

Compile the project using:

```bash
make
```
This will generate the executable `minishell`.

The Makefile exposes the standard rules:

| Rule | Action |
|---|---|
| `make` / `make all` | Compile the `minishell` binary |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the binary |
| `make re` | `fclean` then `all` |

The project depends on `libft` (a custom C standard library in 42 school) and `get_next_line`, both compiled as part of the build.

### Running

```bash
./minishell
```

The shell starts in interactive mode, displaying the `minishell$ ` prompt.

### Usage Examples

```bash
# Basic command execution
minishell$ ls -la

# Pipeline
minishell$ cat file.txt | grep "pattern" | wc -l

# Redirections
minishell$ echo "hello" > output.txt
minishell$ cat < input.txt >> output.txt

# Here-document
minishell$ cat << EOF
> line one
> line two
> EOF

# Variable expansion
minishell$ export NAME=world
minishell$ echo "Hello $NAME"
Hello world

# Exit status
minishell$ ls nonexistent
minishell$ echo $?
2

# Temporary assignment
minishell$ GREETING=hello printenv GREETING
hello

# Quote behavior
minishell$ echo '$USER'        # single quotes: literal
$USER
minishell$ echo "$USER"        # double quotes: expanded
yourusername
```

---

## Known Limitations

- The shell does not implement `&&`, `||`, `;`, subshells `()`, wildcards/globbing, or `~` expansion.
- `readline` itself causes memory leaks that are outside the project's scope to fix. All memory allocated by the shell's own code is properly freed.

---

## Resources

### Shell and Unix fundamentals

- [The Open Group Base Specifications — Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — authoritative reference for POSIX shell grammar and semantics
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — the primary behavioral reference used throughout this project
- [Advanced Programming in the UNIX Environment, 3rd ed. — W. Richard Stevens & Stephen A. Rago](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://raw.githubusercontent.com/zwan074/technical-books/master/Advanced.Programming.in.the.UNIX.Environment.3rd.Edition.0321637739.pdf&ved=2ahUKEwi2lIzSo7SUAxVIQ6QEHbMIGWIQFnoECA0QAQ&usg=AOvVaw0AyM_ghVY2wrHQR593H4E-) — chapters on process control, signals, and I/O are directly relevant
- [GNU Readline Library documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)
- `man 3 readline`, `man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, `man 2 sigaction` — essential manual pages

### Tutorials and articles

- [Building a Shell — cs.purdue.edu](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) — academic notes on shell architecture, process groups, and job control
- [Introduction of Lexical Analysis](https://www.geeksforgeeks.org/compiler-design/introduction-of-lexical-analysis/)
- [Tokens in C](https://www.geeksforgeeks.org/c/tokens-in-c/)
- [Lexical Analyser in C](https://www.geeksforgeeks.org/c/c-lexical-analyser-lexer/)
- [Parsing - Introduction to Parsers](https://www.geeksforgeeks.org/compiler-design/introduction-of-parsing-ambiguity-and-parsers-set-1/)

### AI usage

AI assistants were used during this project for the following purposes:

- Finding study resources
- Suggesting edge cases to test
- Helping draft and structure this README
