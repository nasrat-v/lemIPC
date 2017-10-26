/*
** main.c for  in /home/ernst_m/Documents/Tek2/lemipc
** 
** Made by ernst_m
** Login   <ernst_m@epitech.net>
** 
** Started on  Fri Mar 17 14:24:34 2017 ernst_m
** Last update Fri Mar 24 16:59:01 2017 Valentin Nasraty
*/

#include "lemipc.h"

void		init_ncurses(SCREEN *win)
{
  win = newterm(NULL, stderr, stdin);
  set_term(win);
  refresh();
  keypad(stdscr, 1);
  curs_set(0);
  start_color();
  noecho();
  set_bordure(6);
  init_mouse();
}

void		spawn(t_util *util, int teamnb)
{
  int		x;
  int		y;

  x = rand() % WIDTH;
  y = rand() % HEIGTH;
  if ((lock_sem(x, y, util)) == 0)
    {
      util->tab[y][x].nteam = teamnb;
      go_move(util, x, y, teamnb);
    }
  else
    spawn(util, teamnb);
}

void		core(int teamnb, char *path)
{
  SCREEN	*win;
  t_util	*util;
  
  util = malloc(sizeof(t_util));
  util->key = ftok(path, 0);
  util->shm_id = shmget(util->key, WIDTH * HEIGTH * sizeof(t_case), SHM_R | SHM_W);
  if ((strcmp(path, "exit")) == 0)
    {
      util->key = ftok("./", 0);
      util->shm_id = shmget(util->key, WIDTH * HEIGTH * sizeof(t_case), SHM_R | SHM_W);
      util->msg_id = msgget(util->key, SHM_R | SHM_W);
      msgctl(util->msg_id, IPC_RMID, NULL);
      delete_sems(util);
      shmctl(util->shm_id, IPC_RMID, NULL);
      return ;
    }
  if (util->shm_id == -1)
    {
      win = NULL;
      util->shm_id = shmget(util->key, WIDTH * HEIGTH * sizeof(t_case),
		      IPC_CREAT | SHM_R | SHM_W);
      util->msg_id = msgget(util->key, IPC_CREAT | SHM_R | SHM_W);
      init_ncurses(win);
      fill_struct(util);
      fill_map(util);
      create_sems(util);
      print_map(util);
    }
  else
    {
      util->my_team = teamnb;
      fill_struct(util);
      spawn(util, teamnb);
    }
}

int		check_params(int ac, char **av)
{
  if (ac < 3)
    {
      printf("Usage : ./lemipc path_to_key team_number\n\npath_to_key is a valid path that will be used by ftok\nteam_number is the team number assigned to the current player");
      return (1);
    }
  else
    {
      if ((atoi(av[2])) <= 0)
	{
	  printf("Usage : ./lemipc path_to_key team_number\n\npath_to_key is a valid path that will be used by ftok\nteam_number is the team number assigned to the current player");
	  return (1);
	}
    }
  return (0);
}

int		main(int ac, char **av)
{
  if (check_params(ac, av) == 1)
    return (1);
  srand(time(NULL));
  core(atoi(av[2]), av[1]);
  endwin();
  return (0);
}
