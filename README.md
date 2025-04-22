# 🌀 SimpleShell v1.5

> An enhanced custom shell with variable support and I/O redirection.

![Language](https://img.shields.io/badge/C-Manual_Implementation-blue?style=flat-square)
![Version](https://img.shields.io/badge/Version-1.5-lightgrey?style=flat-square)  <!-- Version updated -->
![Status](https://img.shields.io/badge/Status-Enhanced-brightgreen?style=flat-square)  <!-- Status updated -->

---

## 🧭 About

**SimpleShell v1.5** is an enhanced version of our minimal shell interpreter.  
Now featuring:  
✅ Variable management (`set`/`get` commands)  
✅ I/O redirection (`>` and `<` operators)  
✅ Variable expansion in `echo` commands  
Maintains all previous functionality while adding powerful new features.

---

## ⚙️ Built-in Commands (Updated)

| 🔧 Command | 📝 Description                          |
|-----------|------------------------------------------|
| `help`    | List all available commands              |
| `pwd`     | Show current working directory           |
| `echo`    | Print arguments (supports `$var` expansion) |  <!-- Echo description updated -->
| `exit`    | Exit the shell                           |
| `set`     | Set variable (`name=value` syntax)       |  <!-- New command -->
| `get`     | Get variable value                       |  <!-- New command -->

---

## 🆕 New Features

### 🔄 Variable Expansion
Use `$var_name` in `echo` commands to display variable values:
```bash
$ set name=Alice
$ echo Hello $name!
Hello Alice!
```
## 📤📥 I/O Redirection
Redirect output with > and input with <:
```bash
$ echo "File content" > output.txt  # Write to file
$ cat < input.txt                  # Read from file
```
## 🛠️ Build & ▶️ Run
```bash
gcc shell.c -o shell
./shell
```
## 💡 Example Usage
```bash
$ help
Available commands:
  exit    	Exit the shell
  pwd     	Print current directory
  echo    	Print arguments
  help    	Show this help message
  set     	Set variable (name=value)
  get     	Get variable value

$ set message="Hello World"
$ get message
message=Hello World

$ echo $message > greeting.txt
$ cat < greeting.txt
Hello World

$ echo "Current directory:" && pwd
Current directory: 
/home/user/simpleshell

$ invalid_cmd
Command not found: invalid_cmd

$ exit
```
