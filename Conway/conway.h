#pragma once

#include <vector>

struct CellInfo
{
   unsigned int x;
   unsigned int y;
   unsigned int value;
};

class conway
{
public:
   conway(unsigned int num_cells);

   void set_cells(const std::vector<CellInfo>& cells);
   unsigned int get_cell(unsigned int x, unsigned int y) const;
   unsigned int num_cells() const;

   void update();

private:
   unsigned int m_num_cells;
   // An update is calculated from the cells in m_display_cells
   // and stored in m_updated_cells. Then once the update is 
   // we simply sway the pointers to save copying.
   std::vector<unsigned int> m_display_cells; 
   std::vector<unsigned int> m_updated_cells;

   bool is_alive(unsigned int x, unsigned int y) const;
   unsigned int calculate_live_neighbours(unsigned int x, unsigned int y) const;
};
