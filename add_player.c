/*
** add_player.c for add_player in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Concurrence/PSU_2016_lemipc/bonus
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Fri Mar 24 16:04:22 2017 Valentin Nasraty
** Last update Fri Mar 24 17:15:49 2017 Valentin Nasraty
*/

#include "lemipc.h"

void		init_mouse()
{
  if (!mousemask(ALL_MOUSE_EVENTS, NULL)
      || has_mouse() != TRUE)
    {
      endwin();
      printf("Initialization mouse Ncusres failed\n");
      exit(EXIT_FAILURE);
    }
}

int		get_pos_mouse(int *x, int *y, int *key)
{
  int		i;
  MEVENT	event;

  i = getmouse(&event);
  if (i == OK)
    {
      *x = event.x;
      *y = event.y;
      *key = event.bstate;
    }
  if (*x <= 10 && *x >= 0 && *y <= 10 && *y >= 0)
    return (i);
  return (-1);
}

// FAIRE AVEC UN FORK

int		check_click()
{
  int		x;
  int		y;
  int		key;

  scrollok(stdscr, TRUE);
  getch();
  if (get_pos_mouse(&x, &y, &key) == OK)
    {
      printf("tata\n");
      if (key & BUTTON1_CLICKED)
	{
	  printf("zzzzzzzzzzzzzzzzzz\n");
	  return (1);
	}
      refresh();
    }
  return (0);
}

void		add_player()
{
  if (check_click() == 1)
    system("./lemipc ./ 1");
}
