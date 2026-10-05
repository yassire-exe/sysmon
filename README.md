# sysmon

A small system monitor I wrote in C, no printf, no external libraries.
The idea was to do everything by hand: read /proc, parse, print with write.

## What it does

Every second it shows:
- CPU usage (calculated between two samples, not just a raw number)
- Memory: total, free, available, in MB
- Number of processes
- Top 5 processes

Quit with Ctrl+C, cleanly (the handler just sets a flag to 0, the loop ends by itself).

## Constraints I set for myself

I had two hard rules:
1. No printf. Everything goes through write. So I had to write my own ft_putstr, ft_putnbr, etc.
2. No for, no do-while. Only while.

It's annoying at first, but it forces you to really understand what you're writing.

## What's inside

Syscalls: open, read, write, close, opendir, readdir.
Files: /proc/stat for CPU, /proc/meminfo for RAM, and /proc/<pid>/stat for each process.

Parsing is homemade (ft_atoi / ft_atol), and for printing numbers I use a small recursive function.

## Compiling

	make
	./sysmon
No dependencies, no external lib. Just gcc and a Linux kernel with /proc mounted (so basically any distro).
