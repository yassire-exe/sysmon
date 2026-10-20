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
/*   Created : 2026/10/05 20:52:53
/*   Updated : 2026/10/05 20:52:56
/* @@HEADER-END@@ */

#include "sysmon.h"
#include <dirent.h>

int count_procs(void)
{
    DIR             *dir;
    struct dirent   *entry;
    int             count;

    count = 0;
    dir = opendir("/proc");
    if (!dir)
        return (0);
    entry = readdir(dir);
    while (entry)
    {
        if (entry->d_name[0] >= '0' && entry->d_name[0] <= '9')
            count++;
        entry = readdir(dir);
    }
    closedir(dir);
    return (count);
}

void read_top_procs(t_proc *procs, int max)
{
    DIR             *dir;
    struct dirent   *entry;
    int             count;
    int             fd;
    char            path[256];
    char            buf[512];
    int             n;
    int             i;

    count = 0;
    dir = opendir("/proc");
    if (!dir)
        return ;
    entry = readdir(dir);
    while (entry && count < max)
    {
        if (entry->d_name[0] >= '0' && entry->d_name[0] <= '9')
        {
            i = 0;
            char *prefix = "/proc/";
            int j = 0;
            while (prefix[j]) { path[i] = prefix[j]; i++; j++; }
            j = 0;
            while (entry->d_name[j]) { path[i] = entry->d_name[j]; i++; j++; }
            char *suffix = "/stat";
            j = 0;
            while (suffix[j]) { path[i] = suffix[j]; i++; j++; }
            path[i] = '\0';

            fd = open(path, O_RDONLY);
            if (fd != -1)
            {
                n = read(fd, buf, 511);
                if (n > 0)
                {
                    buf[n] = '\0';
                    procs[count].pid = ft_atoi(buf);
                    int k = 0;
                    while (buf[k] && buf[k] != '(') k++;
                    k++;
                    int m = 0;
                    while (buf[k] && buf[k] != ')' && m < 63)
                        procs[count].name[m++] = buf[k++];
                    procs[count].name[m] = '\0';
                    procs[count].cpu_time = n;
                }
                close(fd);
            }
            count++;
        }
        entry = readdir(dir);
    }
    closedir(dir);

    // Selection sort, descending
    int a = 0;
    while (a < count)
    {
        int b = a + 1;
        while (b < count)
        {
            if (procs[b].cpu_time > procs[a].cpu_time)
            {
                t_proc tmp = procs[a];
                procs[a] = procs[b];
                procs[b] = tmp;
            }
            b++;
        }
        a++;
    }
}
