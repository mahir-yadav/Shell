# Shell

### Execute

Make command: `make`

### Commands Implemented:-

### <ins>cd</ins>

cd is used to change the current working directory to a specified folder.

**Flags Implemented :-**

- <ins>-P</ins> <br>
  This flag uses physical directory structure without following symbolic links.
- <ins>-e</ins> <br>
  When this flag is used, if the -P option is supplied, and the current working directory cannot be determined successfully, exit with a non-zero status.

**Usage :-**

To use relative or absolute paths, the command is used as it is with the flags required as `cd [-P [-e]] path` . You can also go directly to the shell home using the command as `cd [-P [-e]]`. The path can also be relative to shell home using the ~ prefix.

**Error Handling :-**

1. If you give more than one argument to cd .It will throw "Too many arguments error".
2. if you give more argument after cd ~ it will show error.

### <ins>echo</ins>

Displays a line of text on the terminal.

**Flags Implemented :-**

- <ins>-n</ins> <br>
  This flag doesn’t append a new line.
- <ins>--help</ins> <br>
  This flag describes you help options.

**Error Handling :-**

1. If you don't give any argument to echo then it will print a new line character.
2. if echo --help and any other argument then it will show too many arguments.

### <ins>pwd</ins>

This command gives the present working directory of the shell.

**Flags Implemented :-**

- <ins>-L</ins> <br>
  This flag uses PWD from the environment, even if it contains symlinks.
- <ins>-P</ins> <br>
  This flag avoids all symlinks.

**Usage :-**

To use this command, simply run it as `pwd [-P] [-L]`.

**Error Handling :-**

1. If you give more than two argument to pwd .It will throw "Too many arguments error".
2. If we get cwd problem then it will show error.

### <ins>date</ins>

Using this command, the user can print the system date and time.

**Flags Implemented :-**

- <ins>-u</ins> <br>
  Prints the coordinated universal time (UTC).
- <ins>-R</ins> <br>
  Outputs date and time in RFC 5322 format.

**Usage :-**

The command can be called as `date [-u] [-R]`.

**Error Handling :-**

1. If you give more than two argument to date .It will throw "Too many arguments error".
2. If timeT gives NULL then it handles that part.

### <ins>cat</ins>

This command concatenates file and prints on the standard output.

**Flags Implemented :-**

- <ins>-E</ins> <br>
  This flag displays $ at end of each line.
- <ins>-n</ins> <br>
  This flag numbers all output lines.

**Usage :-**

The command can be called as `cat [-E] [-n] file1 file2 … ` to concatenate files in those order.

**Error Handling :-**

1. If you give only one argument to cat .It will throw "No file given to open.".
2. If it unable to open file then it will handle.

### <ins>ls</ins>

This command is used to list directory contents.

**Flags Implemented :-**

- <ins>-a</ins> <br>
  Using this flag, the command does not ignore entries starting with .
- <ins>-m</ins> <br>
  Using this flag, the command does not list implied . and ..

**Usage :-**

The command can be called as `ls [-a] [-m] path1 path2 ...` to list the contents of files or directory in that order.

**Error Handling :-**

1. If you give more than two argument to ls .It will throw "Too many arguments error".
2. If opendir() gives NULL then it will handle that part.

### <ins>rm</ins>

This command can be used to remove files or directories.

**Flags Implemented :-**

- <ins>-i</ins> <br>
  This flag prompts before every removal.
- <ins>-d</ins> <br>
  This flag explains what is being done.

**Usage :-**

The command can be called as `rm [-i] [-d] file1 file2 ...`.

**Error Handling :-**

1. If you give only one argument to rm .It will throw "No file given to remove.".
2. If you type rm -i -d it will show "Enter right command".

### <ins>mkdir</ins>

Using this command, we can make directories.

**Flags Implemented :-**

- <ins>-p</ins> <br>
  This flag creates all the directories recursively.
- <ins>-v</ins> <br>
  This flag prints a message for each created directory

**Usage :-**

The command can be called as `mkdir [-p] [-v] file1 file2 ...`.

**Error Handling :-**

1. If you give only one argument to mkdir .It will throw "Give directory name which you want to create.".
2. If there exist directory then it will throw error: "directory exist".
