# 42sh

42sh is a Unix shell written in C, inspired by TCSH. It includes features such as job control, history management, scripting, aliases, and more.

## Features

- **Job control**: `&, fg, bg`
- **History expansion**: `!`
- **Aliases**: Example: `alias ls "ls --color"`
- **Globbing**: `*, ?, []`
- **Inhibitors**: `' '`
- **Backticks**: `` `command` ``
- **Parentheses**: `(command)`
- **Variables**: Local and environment variables
- **Special variables**: `term, precmd, cwdcmd, cwd, ignoreeof`
- **Scripting**: Basic scripting capabilities

## Compilation

To compile 42sh, use the provided Makefile:

```sh
make
```

You can clean up object files and binaries with:

```sh
make clean
make fclean
```

## Usage

Run the shell with:

```sh
./42sh
```

For additional informations, type:

```sh
./42sh -h
```

## License

This project is developed as part of the EPITECH School curriculum.
