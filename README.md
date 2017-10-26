# lemIPC
Two dimensionnal fight game using shared memory

# Rules
The goal is to fight players (spread over several teams) on a two dimensions game board.
The last team remaining on the board is the winner.
To kill a player, a minimum of two players from the same team (and different from the first) need to be in contact with the player to kill. It means on a square next to the one where the player you want to kill stands on. (including diagonally).
A square cannot host more than one player simultaneously.

# Compile
> *make*

# How to use it
Launch the board:

> *./lemipc PATH_KEY TEAM_NB*
The path will be use to share memory between all the processus.
The team number will be not used by the board.

Launch a player:
> *./lemipc PATH_KEY TEAM_NB*
The path will be use to know where is the board's shared memory.
The team number will used to create a team.

# Objectif
The goals of this project is to learn how shared memory works.

