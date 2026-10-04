/* @@HEADER-START@@
/*    ___    ___ ________  ________   ________  ___  ________  _______      
/*   |\  \  /  /|\   __  \|\   ____\ |\   ____\|\  \|\   __  \|\  ___ \     
/*   \ \  \/  / | \  \|\  \ \  \___|_\ \  \___|\ \  \ \  \|\  \ \   __/|    
/*    \ \    / / \ \   __  \ \_____  \\ \_____  \ \  \ \   _  _\ \  \_|/__  
/*     \/  /  /   \ \  \ \  \|____|\  \\|____|\  \ \  \ \  \\  \\ \  \_|\ \ 
/*   __/  / /      \ \__\ \__\____\_\  \ ____\_\  \ \__\ \__\\ _\\ \_______\
/*  |\___/ /        \|__|\|__|\_________\\_________\|__|\|__|\|__|\|_______|
/*  \|___|/                  \|_________\|_________|
/*
/*   Auteur  : Yassire Daniel Allaoui
/*   Login   : yassire.exe
/*   Email   : ydanielallaoui@gmail.com
/*
/*   Created : 2026/09/29 21:07:27
/*   Updated : 2026/09/29 21:07:27
/* @@HEADER-END@@ */

#include "sysmon.h"

// read_mem: read /proc/meminfo et pull up t_mem
void	read_mem(t_mem *mem)
{
	int	fd;
	char	buf[4096];
	int	n;
	int	i;

	fd = open("/proc/meminfo", O_RDONLY);
	if (fd == -1)
		return ;
	n = read(fd, buf, 4095);
	if (n <= 0)
	{
		close(fd);
		return ;
	}
	buf[n] = '\0';
	close(fd);
	i = 0;
	while(buf[i]
	{
		//search "MemTotol:"
		if (buf[i] == 'M' && buf[i + 1] == 'e' && buf[i + 2] == 'm'
			&& buf[i + 3] == 'T' && buf[i + 4] == 'o')
		{
			i += 9; // skip "MemTotal:"
			while (buf[i] == ' ' || buf[i] == '\t') i++;
			mem->total = ft_atoi(&buf[i]);
		}
		//search "MemFree:"
		else if (buf[i] == 'M' && buf[i + 1] == 'e' && buf[i + 2] == 'm'
			&& buf[i + 3] == 'F' && buf[i + 4] == 'r')
		{
			i += 8;
			while (buf[i] == ' ' || buf[i] == '\t') i++;
			mem->free = ft_atoi(&buf[i]);
		}
		//search "MemAvailable:"
		else if (buf[i] == 'M' && buf[i + 1] == 'e' && buf[i + 2] == 'm'
			&& buf[i + 3] == 'A' && buf[i + 4] == 'v')
		{
			i += 13;
			while (buf[i] == ' ' || buf[i] == '\t') i++;
				mem->available = ft_atoi(&buf[i]);
		}
		//search "Buffers:"
			else if (buf[i] == 'B' && buf[i + 1] == 'u' && buf[i + 2] == 'f')
			{
				i += 8;
				while (buf[i] == ' ' || buf[i] == '\t') i++;
				mem->buffers = ft_atoi(&buf[i]);
			}
			//search "Cached:"
			else if (buf[i] == 'C' && buf[i + 1] == 'a' && buf[i + 2] == 'c'
				&& buf[i + 3] == 'h' && buf[i + 4] == 'e')
			{
				i += 7;
				while (buf[i] == ' ' || buf[i] == '\t') i++;
				mem->cached = ft_atoi(&buf[i]);
			}
			i++;
	}
}
