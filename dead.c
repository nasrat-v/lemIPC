/*
** dead.c for  in /home/ernst_m/Documents/Tek2/lemipc/PSU_2016_lemipc
** 
** Made by ernst_m
** Login   <ernst_m@epitech.net>
** 
** Started on  Tue Mar 21 16:15:51 2017 ernst_m
** Last update Tue Mar 21 16:19:23 2017 ernst_m
*/

#include "lemipc.h"

void    check_other_team(t_util *util, int nbteam)
{
  int   i;
  int   n;

  i = -1;
  while (++i < HEIGTH)
    {
      n = -1;
      while (++n < WIDTH)
	{
	  if (util->tab[i][n].nteam != 0 && util->tab[i][n].nteam != nbteam)
	    return ;
	}
    }
  end_message(util, nbteam);
}

void    check_last_dead(t_util *util)
{
  int   i;
  int   n;

  i = -1;
  while (++i < HEIGTH)
    {
      n = -1;
      while (++n < WIDTH)
	{
	  if (util->tab[i][n].nteam != 0)
	    check_other_team(util, util->tab[i][n].nteam);
	}
    }
}

int     is_dead2(t_util *util, t_pos pos, int nbteam)
{
  t_pos newpos;
  int   nb;

  newpos.y = pos.y - 2;
  nb = 0;
  while (++newpos.y < pos.y + 2)
    {
      newpos.x = pos.x - 2;
      while (++newpos.x < pos.x + 2)
	{
	  if (newpos.x >= 0 && newpos.y >= 0 && newpos.x < WIDTH && newpos.y < HEIGTH
	      && (newpos.x != pos.x || newpos.y != pos.y) &&
	      util->tab[newpos.y][newpos.x].nteam == nbteam)
	    {
	      nb++;
	    }
	}
    }
  if (nb > 1)
    return 1;
  return 0;
}

int     is_dead(t_util *util, t_pos pos)
{
  t_pos newpos;

  newpos.y = pos.y - 2;
  while (++newpos.y < pos.y + 2)
    {
      newpos.x = pos.x - 2;
      while (++newpos.x < pos.x + 2)
	{
	  if (newpos.x >= 0 && newpos.y >= 0 && newpos.x < WIDTH && newpos.y < HEIGTH
	      && (newpos.x != pos.x || newpos.y != pos.y) &&
	                    util->tab[newpos.y][newpos.x].nteam != 0 &&
	      util->tab[pos.y][pos.x].nteam != util->tab[newpos.y][newpos.x].nteam)
	    {
	      if (is_dead2(util, pos, util->tab[newpos.y][newpos.x].nteam))
		return 1;
	    }
	}
    }
  return 0;
}
