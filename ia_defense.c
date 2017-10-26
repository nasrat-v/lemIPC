/*
** ia_defense.c for ia_defense in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Concurrence/PSU_2016_lemipc
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Tue Mar 21 23:05:03 2017 Valentin Nasraty
** Last update Thu Mar 23 19:38:42 2017 Valentin Nasraty
*/

#include "lemipc.h"

int	i_am_the_last_one(t_util *util)
{
  int	i;
  int	n;
  int	nb;

  i = -1;
  nb = 0;
  while (++i < HEIGTH)
    {
      n = -1;
      while (++n < WIDTH)
	{
	  if (util->tab[i][n].nteam == util->my_team)
	    nb += 1;
	  if (nb > 1)
	    return (0);
	}
    }
  return (1);
}

t_pos	escape_enemies(t_util *util, t_pos pos)
{
  t_pos target_pos;

  target_pos = find_target(util, target_pos, pos);
  if (target_pos.y > pos.y && pos.y > 0)
    pos.y -= 1;
  else if (target_pos.y < pos.y && pos.y < (HEIGTH - 1))
    pos.y += 1;
  if (target_pos.x > pos.x && pos.x > 0)
    pos.x -= 1;
  else if (target_pos.x < pos.x && pos.x < (WIDTH - 1))
    pos.x += 1;
  else
    pos = get_newpos_random(pos);
  return (pos);
}
