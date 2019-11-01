#pragma once

#include <vector>
#include <functional>

struct CellInfo
{
   unsigned int x;
   unsigned int y;
   unsigned int value;
};

using rule_t = std::function<bool(bool, unsigned int)>;

class conway
{
public:
   conway(unsigned int num_cells, rule_t birth_rule, rule_t survival_rule);

   void set_cells(const std::vector<CellInfo>& cells);
   unsigned int get_cell(unsigned int x, unsigned int y) const;
   unsigned int num_cells() const;
   unsigned int generation_count() const;

   void update();
   void clear();
   void restart();

private:
   unsigned int m_num_cells;
   // An update is calculated from the cells in m_display_cells
   // and stored in m_updated_cells. Then once the update is 
   // we simply sway the pointers to save copying.
   std::vector<unsigned int> m_display_cells; 
   std::vector<unsigned int> m_updated_cells;
   std::vector<unsigned int> m_initial_cells;

   // Rules
   rule_t m_birth_rule;
   rule_t m_survival_rule;

   // Info
   unsigned int m_generation_count;

   bool is_alive(unsigned int x, unsigned int y) const;
   unsigned int calculate_live_neighbours(unsigned int x, unsigned int y) const;
};
