# 🐚 Simple Shell (v1.0)

A lightweight custom shell written in C — built entirely **without using `fork()` or `execvp()`**.  
Supports a few essential built-in commands with clean input parsing and error handling.

---

## 🚀 Features

✅ Interactive shell loop with custom prompt  
✅ Command parsing with arguments  
✅ Built-in commands:
- `pwd` – Print current directory
- `cd <path>` – Change current directory
- `ls` – List files in the current directory (non-hidden)
- `exit` – Exit the shell  

✅ Basic error handling for unknown commands and failed operations  
✅ Clean, readable, and modular C code  

---

## 🛠️ Tech Stack

- **Language**: C
- **Headers Used**: `stdio.h`, `stdlib.h`, `string.h`, `unistd.h`, `dirent.h`

---

## 📦 Installation

1. **Clone the repository**
```bash
git clone https://github.com/RamezHas/simple_shell.git
cd simple_shell
