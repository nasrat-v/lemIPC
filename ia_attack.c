/*
** ia.c for ia in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Concurrence/PSU_2016_lemipc
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Tue Mar 21 19:38:22 2017 Valentin Nasraty
** Last update Tue Mar 28 16:51:31 2017 Valentin Nasraty
*/

#include "lemipc.h"

t_pos	compare_pos_target(t_pos *target_pos, t_pos pos)
{
  float	first_x_diff;
  float	first_y_diff;
  float	second_x_diff;
  float	second_y_diff;

  // THEOREME DE PYTHAGORE
  first_x_diff = (pos.x - target_pos[0].x);
  first_y_diff = (pos.y - target_pos[0].y);
  second_x_diff = (pos.x - target_pos[1].x);
  second_y_diff = (pos.y - target_pos[1].y);
  if (sqrt(pow(first_x_diff, 2) + pow(first_y_diff, 2)) <
      sqrt(pow(second_x_diff, 2) + pow(second_y_diff, 2)))
    return (target_pos[0]);
  return (target_pos[1]);
}

t_pos	find_target(t_util *util, t_pos target_pos, t_pos pos)
{
  int	i;
  int	n;
  bool	make_calcul;
  t_pos	comp_target[2];

  i = -1;
  make_calcul = false;
  comp_target[1].x = 0;
  comp_target[1].y = 0;
  while (++i < HEIGTH)
    {
      n = -1;
      while (++n < WIDTH)
	{
	  if (util->tab[i][n].nteam != util->my_team &&
	      util->tab[i][n].nteam != 0)
	    {
	      target_pos.y = i;
	      target_pos.x = n;
	      comp_target[0] = target_pos;
	      if (make_calcul == false)
		{
		  make_calcul = true;
		  comp_target[1] = comp_target[0];
		}
	      else
		comp_target[1] = compare_pos_target(comp_target, pos);
	    }
	}
    }
  return (target_pos = comp_target[1]);
}

void   	send_order_to_attack(t_util *util, t_pos target_pos)
{
  int	i;
  int  	n;
 
  i = -1;
  util->order.ord[0] = target_pos.y;
  util->order.ord[1] = target_pos.x;
  util->msg_id = msgget(util->key, SHM_R | SHM_W);
  while (++i < HEIGTH)
    {
      n = -1;
      while (++n < WIDTH)
	{
	  if (util->tab[i][n].nteam == util->my_team)
	    {
	      // Index du sémaphore + décalage de la plage d'écoute
	      util->order.mtype = (util->tab[i][n].sem_index + OFFSET_PLAGE);
	      msgsnd(util->msg_id, &util->order, sizeof(util->order), 0);
	    }
	}
    }
}

t_pos	move_to_target(t_pos pos, int t_y, int t_x)
{
  if (t_y > pos.y)
    pos.y += 1;
  else if (t_y < pos.y)
    pos.y -= 1;
  if (t_x > pos.x)
    pos.x += 1;
  else if (t_x < pos.x)
    pos.x -= 1;
  return (pos);
}

t_pos	receive_order_to_attack(t_util *util, t_pos pos)
{
  if ((msgrcv(util->msg_id, &util->order,
	      sizeof(util->order), (util->tab[pos.y][pos.x].sem_index + OFFSET_PLAGE), IPC_NOWAIT)) != -1)
    pos = move_to_target(pos, util->order.ord[0], util->order.ord[1]);
  return (pos);
}
