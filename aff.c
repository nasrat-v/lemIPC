/*
** aff.c for  in /home/ernst_m/Documents/Tek2/lemipc/PSU_2016_lemipc
** 
** Made by ernst_m
** Login   <ernst_m@epitech.net>
** 
** Started on  Tue Mar 21 16:19:47 2017 ernst_m
** Last update Tue Mar 28 16:48:23 2017 Valentin Nasraty
*/

#include "lemipc.h"

void	choose_color(int nb_team)
{
  if (nb_team == 0)
    nb_team = 7;
  init_pair((nb_team % 7) + 1, nb_team % 7, nb_team % 7);
  attron(COLOR_PAIR((nb_team % 7) + 1));
}

void	print_char(int i, int n)
{
  mvprintw(i, n, "[");
  mvprintw(i, (n + 1), "]");
}

void	set_bordure(int attr)
{
  int	i;
  int	n;

  i = -1;
  init_pair((attr + 1), 0, attr);
  attron(COLOR_PAIR(attr + 1));
  while (++i <= (HEIGTH + 1))
    {
      n = -1;
      while (++n <= (WIDTH + 1))
	{
	  if ((i == 0) || (i == HEIGTH + 1))
	    print_char(i, (n + n));
	  else if ((n == 0) || (n == WIDTH + 1))
	    print_char(i, (n + n));
	}
    }
  mvprintw(50, 90, "ADD1");
  mvprintw(51, 88, "********");
  mvprintw(50, 88, "*");
  mvprintw(50, 95, "*");
  mvprintw(49, 88, "********");
  attroff(COLOR_PAIR(attr + 1));
}

void    print_map(t_util *util)
{
  int	i;
  int	n;

  init_pair(0, COLOR_BLACK, COLOR_BLACK);
  while (1)
    {
      i = 0;
      timeout(1);
      getch();
      while (i < HEIGTH)
  	{
  	  n = 0;
  	  while (n < WIDTH)
  	    {
  	      if (util->tab[i][n].nteam != 0)
  		{
  		  choose_color(util->tab[i][n].nteam);
		  print_char((i + 1), (n + n + 2));
  		  attroff(COLOR_PAIR((util->tab[i][n].nteam % 7) + 1));
  		}
  	      else
  		{
  		  attron(COLOR_PAIR(1));
		  print_char((i + 1), (n + n + 2));
  		  attroff(COLOR_PAIR(1));
  		}
  	      n++;
  	    }
  	  i++;
  	}
      if ((msgrcv(util->msg_id, &util->msg,
		  sizeof(util->msg), 2, IPC_NOWAIT)) != -1)
  	{
  	  printf("END GAAAAAME\n");
  	  end_game(util, util->msg.team);
  	}
    }
}
