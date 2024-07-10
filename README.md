# Shell
### Execute
Make command: ```make``` 

### Commands Implemented:-

### <ins>cd</ins>

cd is used to change the current working directory to a specified folder.

**Flags Implemented :-**

- <ins>-P</ins> <br>
  This flag uses physical directory structure without following symbolic links.
- <ins>-e</ins>  <br>
  When this flag is used, if the -P option is supplied, and the current working directory cannot be determined successfully, exit with a non-zero status.

**Usage :-**

To use relative or absolute paths, the command is used as it is with the flags required as ```cd [-P [-e]] path``` . You can also go directly to the shell home using the command as ```cd [-P [-e]]```. The path can also be relative to shell home using the ~ prefix.

### <ins>echo</ins>

Displays a line of text on the terminal.

**Flags Implemented :-**

- <ins>-n</ins>  <br>
  This flag doesn’t append a new line.
- <ins>-e</ins>  <br>
  This flag enables interpretation of backslash escapes. 

**Usage :-**

The command can be called as ```echo [-e] [-n] text ```.

### <ins>history</ins>

Maintains a history of all the commands used across all the sessions of the shell.

**Flags Implemented :-**

- <ins>-c</ins>  <br>
  This flag clears the history list by deleting all of the entries.
- <ins>-d</ins>  <br>
  This flag deletes the history entry at position *OFFSET*. Negative offsets count back from the end of the history list. 

**Usage :-**

To view the entire history, use command ```history```. To view the last OFFSET commands, use ```history OFFSET```. To delete the command at OFFSET, use ```history -d OFFSET```. To clear the entire history, use ```history -c```.

### <ins>pwd</ins>

This command gives the present working directory of the shell.

**Flags Implemented :-**

- <ins>-L</ins>  <br>
  This flag uses PWD from the environment, even if it contains symlinks.
- <ins>-P</ins>  <br>
  This flag avoids all symlinks.

**Usage :-**

To use this command, simply run it as ```pwd [-P] [-L]```.

### <ins>exit</ins>

This command exits the user from the shell.

**Usage :-**

Use as ```exit```.

### <ins>date</ins>

Using this command, the user can print the system date and time.

**Flags Implemented :-**

- <ins>-u</ins>  <br>
  Prints the coordinated universal time (UTC).
- <ins>-R</ins>  <br>
  Outputs date and time in RFC 5322 format.

**Usage :-**

The command can be called as ```date [-u] [-R]```.

### <ins>cat</ins>

This command concatenates file and prints on the standard output.

**Flags Implemented :-**

- <ins>-E</ins>  <br>
  This flag displays $ at end of each line.
- <ins>-n</ins>  <br>
  This flag numbers all output lines.

**Usage :-**

The command can be called as ```cat [-E] [-n] file1 file2 … ``` to concatenate files in those order.

### <ins>ls</ins>

This command is used to list directory contents.

**Flags Implemented :-**

- <ins>-a</ins>  <br>
  Using this flag, the command does not ignore entries starting with .
- <ins>-A</ins>  <br>
  Using this flag, the command does not list implied . and ..

**Usage :-**

The command can be called as ```ls [-a] [-A] path1 path2 ...``` to list the contents of files or directory in that order.

### <ins>rm</ins>

This command can be used to remove files or directories.

**Flags Implemented :-**

- <ins>-i</ins>  <br>
  This flag prompts before every removal.
- <ins>-v</ins>  <br>
  This flag explains what is being done.

**Usage :-**

The command can be called as ```rm [-i] [-v] file1 file2 ...```.

### <ins>mkdir</ins>

Using this command, we can make directories.

**Flags Implemented :-**

- <ins>-p</ins>  <br>
  This flag creates all the directories recursively.
- <ins>-v</ins>  <br>
  This flag prints a message for each created directory

**Usage :-**

The command can be called as ```mkdir [-p] [-v] file1 file2 ...```.
