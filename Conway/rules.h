#pragma once

// Classic Conway Game of Life Rules
bool conway_birth_rule(bool alive, unsigned int num_neighbours_alive)
{
   return !alive && num_neighbours_alive == 3;
}

bool conway_survival_rule(bool alive, unsigned int num_neighbours_alive)
{
   return alive && (num_neighbours_alive == 2 || num_neighbours_alive == 3);
}