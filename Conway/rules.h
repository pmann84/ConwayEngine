#pragma once

// Classic Conway Game of Life Rules - B3/S23
inline bool conway_birth_rule(bool alive, unsigned int num_neighbours_alive)
{
   return !alive && num_neighbours_alive == 3;
}

inline bool conway_survival_rule(bool alive, unsigned int num_neighbours_alive)
{
   return alive && (num_neighbours_alive == 2 || num_neighbours_alive == 3);
}

// Highlife Game of Life Rules - B36/S23
inline bool highlife_birth_rule(bool alive, unsigned int num_neighbours_alive)
{
   return !alive && (num_neighbours_alive == 3 || num_neighbours_alive == 6);
}

inline bool highlife_survival_rule(bool alive, unsigned int num_neighbours_alive)
{
   return alive && (num_neighbours_alive == 2 || num_neighbours_alive == 3);
}