#include "conway.h"

conway::conway(unsigned num_cells, rule_t birth_rule, rule_t survival_rule) : m_num_cells(num_cells), m_birth_rule(birth_rule), m_survival_rule(survival_rule)
{
   m_display_cells.resize(num_cells*num_cells);
   m_updated_cells.resize(num_cells*num_cells);
}

void conway::set_cells(const std::vector<CellInfo>& cells)
{
   for (const auto& cell : cells)
   {
      m_display_cells[cell.x + m_num_cells * cell.y] = cell.value > 0 ? 1 : 0;
   }
}

unsigned conway::get_cell(unsigned x, unsigned y) const
{
   return m_display_cells[x + m_num_cells * y];
}

unsigned conway::num_cells() const
{
   return m_num_cells;
}

void conway::update()
{
   // Use the display cells to calculate the updated cells
   // then swap the pointers
   for (unsigned int i = 0; i < m_num_cells; ++i)
   {
      for (unsigned int j = 0; j < m_num_cells; ++j)
      {
         const auto num_neighbours_alive = calculate_live_neighbours(i, j);
         const bool alive = is_alive(i, j);
         if (m_birth_rule(alive, num_neighbours_alive) || m_survival_rule(alive, num_neighbours_alive))
         {
            m_updated_cells[i + m_num_cells * j] = 1;
         }
         else
         {
            m_updated_cells[i + m_num_cells * j] = 0;
         }
      }
   }
   // Swap the vectors around - This should be swap but doesnt work for some reason...
   m_display_cells.swap(m_updated_cells);
}

bool conway::is_alive(unsigned int x, unsigned int y) const
{
   return get_cell(x, y) == 1;
}

unsigned int conway::calculate_live_neighbours(unsigned x, unsigned y) const
{
   //   x
   // * * *
   // * * * y
   // * * *

   // TODO: Bounds checking here!
   unsigned int num_alive_cells = 0;
   if (x != 0 && y != 0 && is_alive(x-1, y-1)) num_alive_cells++;
   if (x != 0 && is_alive(x-1, y)) num_alive_cells++;
   if (x != 0 && y != m_num_cells-1 && is_alive(x-1, y+1)) num_alive_cells++;
   if (y != m_num_cells - 1 && is_alive(x, y+1)) num_alive_cells++;
   if (x != m_num_cells - 1 && y != m_num_cells - 1 && is_alive(x+1, y+1)) num_alive_cells++;
   if (x != m_num_cells - 1 && is_alive(x+1, y)) num_alive_cells++;
   if (x != m_num_cells - 1 && y != 0 && is_alive(x+1, y-1)) num_alive_cells++;
   if (y != 0 && is_alive(x, y-1)) num_alive_cells++;
   return num_alive_cells;
}
