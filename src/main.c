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
/*   Created : 2026/10/05 21:23:36
/*   Updated : 2026/10/05 21:23:36
/* @@HEADER-END@@ */

#include "sysmon.h"

// the global variable g_run: control the principal loop
volatile int	g_run = 1;

// handle_signit: called when we press on Ctrl+C
void	handle_sigint(int sig)
{
	(void)sig; //to avoid the warning "unused parameter"
	g_run = 0;
}
int	main(void)
{
	t_cpu	prev;
	t_cpu	curr;
	t_mem	mem;
	t_proc	procs[5];
	int	usage;
	int	proc_count;
	
	// install the handler for Ctrl+C
	signal(SIGINT, handle_sigint);

	// first CPU read(reference)
	read_cpu(&prev);
	while(g_run)
	{
		//read CPU and memorie
		read_cpu(&curr);
		read_mem(&mem);

		//calculate the usage
		usage = cpu_usage(&prev, &curr);

		//count	the processus and read the topp 5
		proc_count = count_procs();
		read_top_procs(procs, 5);

		//print
		display_header();
		display_cpu(&curr, usage);
		display_mem(&mem);
		display_procs(procs, 5);

		// update the reference
		prev = curr;

		//sleep 1 second(1 000 000 ms)
		usleep(1000000);
	}
	// output message
	ft_putstr("\nGood bye !\n");
	return (0);
}
