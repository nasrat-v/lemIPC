/*
** create.c for  in /home/ernst_m/Documents/Tek2/lemipc/PSU_2016_lemipc
** 
** Made by ernst_m
** Login   <ernst_m@epitech.net>
** 
** Started on  Tue Mar 21 16:20:32 2017 ernst_m
** Last update Wed Mar 22 14:31:34 2017 ernst_m
*/

#include "lemipc.h"

void    create_sems(t_util *util)
{
  int   i;
  int   n;
  int   j;

  i = 0;
  n = 0;
  j = 0;
  util->sem_id = semget(util->key, HEIGTH * WIDTH, IPC_CREAT | SHM_R | SHM_W);
  while (i < HEIGTH)
    {
      n = 0;
      while (n < WIDTH)
	{
	  semctl(util->sem_id, j, SETVAL, 1);
	  util->tab[i][n].sem_index = j;
	  n++;
	  j++;
	}
      i++;
    }
}

void    fill_map(t_util *util)
{
  int   i = 0;
  int   n = 0;

  while (i < HEIGTH)
    {
      n = 0;
      while (n < WIDTH)
	{
	  util->tab[i][n].x = n;
	  util->tab[i][n].y = i;
	  util->tab[i][n].nteam = 0;
	  n++;
	}
      i++;
    }
}

void		set_commando(t_util *util)
{
  int		i;
  int		n;

  i = 0;
  while (i < HEIGTH)
    {
      n = 0;
      while (n < WIDTH)
	{
	  if (util->tab[i][n].nteam == util->my_team)
	    {
	      util->commando = false;
	      return;
	    }
	  n += 1;
	}
      i += 1;
    }
  util->commando = true;
}

void		fill_struct(t_util *util)
{
  int		n;

  n = 0;
  util->addr = shmat(util->shm_id, NULL, SHM_R | SHM_W);
  util->tab = malloc(sizeof(t_case *) * HEIGTH);
  while (n < HEIGTH)
    {
      util->tab[n] = (t_case*)(&((char*)util->addr)[n * sizeof(t_case) * WIDTH]);
      n++;
    }  
  set_commando(util);
}

void    delete_sems(t_util *util)
{
  int   i;
  int   n;

  i = 0;
  n = 0;
  while (i < HEIGTH)
    {
      n = 0;
      while (n < WIDTH)
	{
	  util->sem_id = semget(util->key,1, SHM_R | SHM_W);
	  semctl(util->sem_id, 1, IPC_RMID, NULL);
	  n++;
	}
      i++;
    }
}
