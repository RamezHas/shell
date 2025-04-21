# 🌀 SimpleShell v1.0

> A lightweight custom shell written in C with a set of built-in commands.

![Language](https://img.shields.io/badge/C-Manual_Implementation-blue?style=flat-square)
![Version](https://img.shields.io/badge/Version-1.0-lightgrey?style=flat-square)
![Status](https://img.shields.io/badge/Status-Working-brightgreen?style=flat-square)

---

## 🧭 About

**SimpleShell v1.0** is a minimal shell interpreter written in C.  
It supports a small set of built-in commands and parses input directly from the user.  
Ideal for learning how shells process input and handle basic command execution.

---

## ⚙️ Built-in Commands

| 🔧 Command | 📝 Description                  |
|-----------|----------------------------------|
| `help`    | List all available commands      |
| `pwd`     | Show current working directory   |
| `echo`    | Print provided arguments         |
| `exit`    | Exit the shell                   |

> Unknown commands are handled with a friendly message like:  
> `Command not found: your_command`

---

## 🛠️ Build

To compile the shell, use:

```bash
gcc shell.c -o shell
```
## ▶️ Run

After building, start the shell with:

```bash
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

$ echo Hello, SimpleShell!
Hello, SimpleShell!

$ pwd
/home/ramez/simpleshell

$ ls
Command not found: ls

$ exit

```
