# Custom Linux Shell

This project is a custom Linux shell developed in C as part of my Operating Systems coursework. It supports standard shell command execution along with several extended features.

## Description

The shell replicates basic Linux terminal functionality and adds custom commands for file encryption, decryption, merging, unmerging, and history tracking.

## Purpose

Built to deepen my understanding of process handling, system calls, file operations, and user input in C.

## Features

- Execute standard Linux commands
- `encrypt <file>`: Encrypt a file
- `decrypt <file>`: Decrypt a file
- `merge <file1> <file2> <output>`: Merge two files into one
- `unmerge <file>`: Split a file into its original parts
- `history`: View recent commands used

## Sample Run

The shell displays a prompt and allows typed commands, responding to errors and unsupported operations. Example commands:

```bash
AdvShell> encrypt notes.txt
AdvShell> merge a.txt b.txt c.txt
AdvShell> history
AdvShell> exit
```
![image](https://github.com/user-attachments/assets/3f0d6ffb-765b-4b03-82b7-ddc3e743b969)


## Compilation & Usage

To compile and run the shell:

```bash
./Sys_shell.sh
```

## License

This project is for educational purposes and personal learning.

