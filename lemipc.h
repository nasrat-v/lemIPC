/*
** lemipc.h for  in /home/ernst_m/Documents/Tek2/lemipc/PSU_2016_lemipc
** 
** Made by ernst_m
** Login   <ernst_m@epitech.net>
** 
** Started on  Tue Mar 21 16:29:09 2017 ernst_m
** Last update Thu Oct 26 19:05:04 2017 Valentin Nasraty
*/


#ifndef LEMIPC_H__
# define LEMIPC_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include <curses.h>
#include <math.h>

// PLAGE D'ECOUTE MSG
# define OFFSET_PLAGE	3

// ASCII
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_RESET   "\x1b[0m"

// SIZE MAP
# define HEIGTH 50
# define WIDTH  50

struct  s_case
{
  int   x;
  int   y;
  int   nteam;
  int	key;
  int	sem_index;
};

typedef struct s_case t_case;

typedef struct s_msg {
  long	mtype;
  int	team;
}	       t_msg;

typedef struct s_order {
  long	mtype;
  char	ord[2];
}	       t_order;

typedef struct s_util {
  bool	commando;
  int	my_team;
  int	shm_id;
  int	sem_id;
  int	msg_id;
  t_msg	msg;
  t_order order;
  int	key;
  void	*addr;
  t_case **tab;
  struct sembuf sops;
}	       t_util;

typedef struct s_pos {
  int x;
  int y;
}	       t_pos;

/* In ./semcontrol.c */
int                     lock_sem(int x, int y, t_util *util);
int                     unlock_sem(int x, int y, t_util *util);
/* In ./main.c */
void                    spawn(t_util *util, int teamnb);
void                    core(int teamnb, char *path);
int                     main(int ac, char **av);
/* In ./aff.c */
void			choose_color(int nb_team);
void			print_char(int i, int n);
void			set_bordure(int attr);
void                    print_map(t_util *util);
/* In ./dead.c */
void                    check_other_team(t_util *util, int nbteam);
void                    check_last_dead(t_util *util);
int                     is_dead2(t_util *util, t_pos pos, int nbteam);
int                     is_dead(t_util *util, t_pos pos);
/* In ./end_game.c */
void                    end_game(t_util *util, int nbteam);
void                    end_message(t_util *util, int nbteam);
void                    clean_all(t_util *util, t_pos pos);
/* In ./create.c */
void                    create_sems(t_util *util);
void                    fill_map(t_util *util);
void			set_commando(t_util *util);
void                    fill_struct(t_util *util);
void                    delete_sems(t_util *util);
/* In ./move.c */
t_pos                   get_newpos_random(t_pos pos);
t_pos                   move_pos(t_util *util, t_pos pos, int teamnb);
void                    go_move(t_util *util, int x, int y, int teamnb);
/* In ./ia_core.c */
t_pos			get_newpos_ia(t_util *util, t_pos pos);
/* In ./ia_attack.c */
t_pos			compare_pos_target(t_pos *target_pos, t_pos pos);
t_pos			find_target(t_util *util, t_pos target_pos, t_pos pos);
void			send_order_to_attack(t_util *util, t_pos target_pos);
t_pos			move_to_target(t_pos pos, int t_y, int t_x);
t_pos			receive_order_to_attack(t_util *util, t_pos pos);
t_pos			get_newpos_ia(t_util *util, t_pos pos);
/* In ./ia_defense.c */
int			i_am_the_last_one(t_util *util);
t_pos			escape_enemies(t_util *util, t_pos pos);

void			add_player();
void			init_mouse();
#endif
