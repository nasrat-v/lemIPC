
/*
** move.c for  in /home/ernst_m/Documents/Tek2/lemipc/PSU_2016_lemipc
** 
** Made by ernst_m
** Login   <ernst_m@epitech.net>
** 
** Started on  Tue Mar 21 16:14:01 2017 ernst_m
** Last update Tue Mar 28 16:47:24 2017 Valentin Nasraty
*/

#include "lemipc.h"

t_pos   get_newpos_random(t_pos pos)
{
  int   a;
  t_pos oldpos;

  oldpos.x = pos.x;
  oldpos.y = pos.y;
  a = rand() % 2;
  if (a == 1)
    {
      a = rand() % 2;
      if (a == 1)
	pos.x = pos.x + 1;
      a = rand() % 2;
      if (a == 1)
	pos.y = pos.y + 1;
    }
  else
    {
      a = rand() % 2;
      if (a == 1)
	pos.x = pos.x - 1;
      a = rand() % 2;
      if (a == 1)
	pos.y = pos.y - 1;
    }
  if ((pos.y < 0 || pos.x < 0 || pos.x >= WIDTH || pos.y >= HEIGTH))
    return oldpos;
  return pos;
}

int	there_is_enemy(t_util *util)
{
  int	i;
  int	n;

  i = -1;
  while (++i < HEIGTH)
    {
      n = -1;
      while (++n < WIDTH)
	{
	  if (util->tab[i][n].nteam != util->my_team &&
	      util->tab[i][n].nteam != 0)
	    return (1);
	}
    }
  return (0);
}

t_pos   move_pos(t_util *util, t_pos pos, int teamnb)
{
  t_pos newpos;

  if (there_is_enemy(util) == 0)
    newpos = get_newpos_random(pos);
  else
    newpos = get_newpos_ia(util, pos);
  if ((lock_sem(newpos.x, newpos.y, util)) == 0)
    {
      util->tab[pos.y][pos.x].nteam = 0;
      util->tab[newpos.y][newpos.x].nteam = teamnb;
      unlock_sem(pos.x, pos.y, util);
      pos.x = newpos.x;
      pos.y = newpos.y;
    }
  return pos;
}

void    go_move(t_util *util, int x, int y, int teamnb)
{
  t_pos pos;

  pos.x = x;
  pos.y = y;
  util->msg_id = msgget(util->key, SHM_R | SHM_W);
  while (1)
    {
      if ((msgrcv(util->msg_id, &util->msg,
		  sizeof(util->msg), 1, IPC_NOWAIT)) != -1)
	{
	  clean_all(util, pos);
	  printf("end received\n");
	  exit(0);
	}
      if (is_dead(util, pos) == 1)
	{
	  printf("DEAAAAAAAAD\n");
	  util->tab[pos.y][pos.x].nteam = 0;
	  unlock_sem(pos.x, pos.y, util);
	  if (util->commando == true)
	    {
	      util->order.mtype = (util->my_team * 10000);
	      msgsnd(util->msg_id, &util->order, sizeof(util->order), 0);
	    }
	  check_last_dead(util);
	  exit(0);
	}
      if ((msgrcv(util->msg_id, &util->order,
		  sizeof(util->order), (util->my_team * 10000), IPC_NOWAIT)) != -1)
        util->commando = true;
      pos = move_pos(util, pos, teamnb);
      add_player();
      usleep(400000);
    }
}
