/*
** ia_core.c for core_ia in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Concurrence/PSU_2016_lemipc
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Tue Mar 21 23:22:10 2017 Valentin Nasraty
** Last update Thu Mar 23 19:37:37 2017 Valentin Nasraty
*/

#include "lemipc.h"

t_pos	get_newpos_ia(t_util *util, t_pos pos)
{
  t_pos target_pos;

  // ATTACK COMMANDO
  if (util->commando == true && i_am_the_last_one(util) == 0)
    {
      target_pos = find_target(util, target_pos, pos);
      send_order_to_attack(util, target_pos);
      pos = move_to_target(pos, target_pos.y, target_pos.x);
    }
  // ATTACK SOLDIER
  else if (util->commando == false && i_am_the_last_one(util) == 0)
    pos = receive_order_to_attack(util, pos);
  // DEFENSE
  else if (i_am_the_last_one(util) == 1)
    pos = escape_enemies(util, pos);
  return (pos);
}
