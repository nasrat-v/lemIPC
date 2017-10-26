/*
** semcontrol.c for  in /home/ernst_m/Documents/Tek2/lemipc/PSU_2016_lemipc
** 
** Made by ernst_m
** Login   <ernst_m@epitech.net>
** 
** Started on  Tue Mar 21 16:21:57 2017 ernst_m
** Last update Tue Mar 21 16:22:10 2017 ernst_m
*/

#include "lemipc.h"

int     lock_sem(int x, int y, t_util *util)
{
  int i;

  util->sem_id = semget(util->key, HEIGTH * WIDTH, SHM_R | SHM_W);
  util->sops.sem_num = util->tab[y][x].sem_index;
  util->sops.sem_flg = IPC_NOWAIT;
  util->sops.sem_op = -1;
  i = semop(util->sem_id, &util->sops, 1);
  return i;
}

int     unlock_sem(int x, int y, t_util *util)
{
  int i;

  util->sem_id = semget(util->key, HEIGTH * WIDTH, SHM_R | SHM_W);
  util->sops.sem_num = util->tab[y][x].sem_index;
  util->sops.sem_flg = 0;
  util->sops.sem_op = +1;
  i = semop(util->sem_id, &util->sops, 1);
  return i;
}
