/*
** end_game.c for  in /home/ernst_m/Documents/Tek2/lemipc/PSU_2016_lemipc
** 
** Made by ernst_m
** Login   <ernst_m@epitech.net>
** 
** Started on  Tue Mar 21 16:18:20 2017 ernst_m
** Last update Tue Mar 28 16:48:06 2017 Valentin Nasraty
*/

#include "lemipc.h"

void    end_game(t_util *util, int nbteam)
{
  int i;
  int n;

  i = -1;
  printf("The Game is Over, Team %d Won!!\n", nbteam);
  util->msg.mtype = 1;
  util->msg.team = -1;
  util->msg_id = msgget(util->key, SHM_R | SHM_W);
  while (++i < HEIGTH)
    {
      n = -1;
      while (++n < WIDTH)
	{
	  if (util->tab[i][n].nteam != 0)
	    msgsnd(util->msg_id, &util->msg, sizeof(util->msg), 0);
	}
    }
  endwin();
  exit(0);
}

void    end_message(t_util *util, int nbteam)
{
  util->msg.mtype = 2;
  util->msg.team = nbteam;
  util->msg_id = msgget(util->key, SHM_R | SHM_W);
  msgsnd(util->msg_id, &util->msg, sizeof(util->msg), 0);
}

void    clean_all(t_util *util, t_pos pos)
{
  int   i;
  int   n;
  int   j;

  i = -1;
  j = 0;
  util->tab[pos.y][pos.x].nteam = 0;
  unlock_sem(pos.x, pos.y, util);
  while (++i < HEIGTH)
    {
      n = -1;
      while (++n < WIDTH)
	{
	  if (util->tab[i][n].nteam != 0)
	    j++;
	}
    }
  if (j == 0)
    {
      util->shm_id = shmget(util->key, WIDTH * HEIGTH * sizeof(t_case), SHM_R | SHM_W);
      delete_sems(util);
      shmctl(util->shm_id, IPC_RMID, NULL);
      msgctl(util->msg_id, IPC_RMID, NULL);
    }
}
