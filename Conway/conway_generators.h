#pragma once

#include <vector>

#include "conway.h"

// Shorthands
// SL - Still Life
// OS - Oscillators
// SS - Spaceship
// MS - Misc

std::vector<CellInfo> rectangle_MS(unsigned int top_left_x, unsigned int top_left_y, unsigned int width, unsigned int height)
{
   std::vector<CellInfo> cells;
   for (unsigned int i = 0; i < width; ++i)
   {
      for (unsigned int j = 0; j < height; ++j)
      {
         cells.push_back({ top_left_x + i, top_left_y + j, 1 });
      }
   }
   return cells;
}

std::vector<CellInfo> block_SL(unsigned int top_left_x, unsigned int top_left_y)
{
   return rectangle_MS(top_left_x, top_left_y, 2, 2);
}

std::vector<CellInfo> beehive_SL(unsigned int top_left_x, unsigned int top_left_y)
{
   std::vector<CellInfo> cells;
   auto top_block = rectangle_MS(top_left_x + 1, top_left_y, 2, 1);
   cells.insert(cells.end(), top_block.begin(), top_block.end());

   auto bottom_block = rectangle_MS(top_left_x + 1, top_left_y + 2, 2, 1);
   cells.insert(cells.end(), bottom_block.begin(), bottom_block.end());

   cells.push_back({ top_left_x, top_left_y + 1, 1 });
   cells.push_back({ top_left_x + 3, top_left_y + 1, 1 });
   return cells;
}

std::vector<CellInfo> loaf_SL(unsigned int top_left_x, unsigned int top_left_y)
{
   std::vector<CellInfo> cells;
   auto top_block = rectangle_MS(top_left_x + 1, top_left_y, 2, 1);
   cells.insert(cells.end(), top_block.begin(), top_block.end());

   auto side_block = rectangle_MS(top_left_x + 3, top_left_y + 1, 1, 2);
   cells.insert(cells.end(), side_block.begin(), side_block.end());

   cells.push_back({ top_left_x, top_left_y + 1, 1 });
   cells.push_back({ top_left_x + 1, top_left_y + 2, 1 });
   cells.push_back({ top_left_x + 2, top_left_y + 3, 1 });
   return cells;
}

std::vector<CellInfo> boat_SL(unsigned int top_left_x, unsigned int top_left_y)
{
   std::vector<CellInfo> cells;
   auto top_block = rectangle_MS(top_left_x, top_left_y, 2, 1);
   cells.insert(cells.end(), top_block.begin(), top_block.end());

   cells.push_back({ top_left_x, top_left_y + 1, 1 });
   cells.push_back({ top_left_x + 2, top_left_y + 1, 1 });
   cells.push_back({ top_left_x + 1, top_left_y + 2, 1 });
   return cells;
}

std::vector<CellInfo> tub_SL(unsigned int top_left_x, unsigned int top_left_y)
{
   std::vector<CellInfo> cells;
   cells.push_back({ top_left_x + 1, top_left_y, 1 });
   cells.push_back({ top_left_x + 1, top_left_y + 2, 1 });
   cells.push_back({ top_left_x, top_left_y + 1, 1 });
   cells.push_back({ top_left_x + 2, top_left_y + 1, 1 });
   return cells;
}

std::vector<CellInfo> blinker_OS(unsigned int top_left_x, unsigned int top_left_y, bool horizontal = false)
{
   std::vector<CellInfo> cells;
   if (horizontal)
   {
      cells.push_back({ top_left_x, top_left_y, 1 });
      cells.push_back({ top_left_x + 1, top_left_y, 1 });
      cells.push_back({ top_left_x + 2, top_left_y, 1 });
   }
   else
   {
      cells.push_back({ top_left_x, top_left_y, 1 });
      cells.push_back({ top_left_x, top_left_y + 1, 1 });
      cells.push_back({ top_left_x, top_left_y + 2, 1 });
   }
   return cells;
}

std::vector<CellInfo> toad_OS(unsigned int top_left_x, unsigned int top_left_y, bool closed = true)
{
   std::vector<CellInfo> cells;
   if (closed)
   {
      auto top_block = rectangle_MS(top_left_x + 1, top_left_y, 3, 1);
      cells.insert(cells.end(), top_block.begin(), top_block.end());

      auto bottom_block = rectangle_MS(top_left_x, top_left_y + 1, 3, 1);
      cells.insert(cells.end(), bottom_block.begin(), bottom_block.end());
   }
   else
   {
      auto left_block = rectangle_MS(top_left_x, top_left_y + 1, 1, 2);
      cells.insert(cells.end(), left_block.begin(), left_block.end());

      auto right_block = rectangle_MS(top_left_x + 3, top_left_y + 1, 1, 2);
      cells.insert(cells.end(), right_block.begin(), right_block.end());

      cells.push_back({ top_left_x + 1, top_left_y + 3, 1 });
      cells.push_back({ top_left_x + 2, top_left_y, 1 });
   }
   return cells;
}

std::vector<CellInfo> beacon_OS(unsigned int top_left_x, unsigned int top_left_y, bool filled = true)
{
   std::vector<CellInfo> cells;
   if (filled)
   {
      auto top_left_block = rectangle_MS(top_left_x, top_left_y, 2, 2);
      cells.insert(cells.end(), top_left_block.begin(), top_left_block.end());

      auto bottom_right_block = rectangle_MS(top_left_x + 2, top_left_y + 2, 2, 2);
      cells.insert(cells.end(), bottom_right_block.begin(), bottom_right_block.end());
   }
   else
   {
      auto top_left_block = rectangle_MS(top_left_x, top_left_y, 2, 1);
      cells.insert(cells.end(), top_left_block.begin(), top_left_block.end());
      cells.push_back({ top_left_x, top_left_y + 1, 1 });

      auto bottom_right_block = rectangle_MS(top_left_x + 2, top_left_y + 3, 2, 1);
      cells.insert(cells.end(), bottom_right_block.begin(), bottom_right_block.end());
      cells.push_back({ top_left_x + 3, top_left_y + 2, 1 });
   }
   return cells;
}

std::vector<CellInfo> pulsar_OS(unsigned int top_left_x, unsigned int top_left_y)
{
   std::vector<CellInfo> cells;
   // Top left quadrant
   {
      auto top_block = rectangle_MS(top_left_x + 2, top_left_y, 3, 1);
      cells.insert(cells.end(), top_block.begin(), top_block.end());

      auto left_block = rectangle_MS(top_left_x, top_left_y + 2, 1, 3);
      cells.insert(cells.end(), left_block.begin(), left_block.end());

      auto bottom_block = rectangle_MS(top_left_x + 2, top_left_y + 5, 3, 1);
      cells.insert(cells.end(), bottom_block.begin(), bottom_block.end());

      auto right_block = rectangle_MS(top_left_x + 5, top_left_y + 2, 1, 3);
      cells.insert(cells.end(), right_block.begin(), right_block.end());
   }
   // Top right quadrant
   {
      auto top_block = rectangle_MS(top_left_x + 8, top_left_y, 3, 1);
      cells.insert(cells.end(), top_block.begin(), top_block.end());

      auto left_block = rectangle_MS(top_left_x + 7, top_left_y + 2, 1, 3);
      cells.insert(cells.end(), left_block.begin(), left_block.end());

      auto bottom_block = rectangle_MS(top_left_x + 8, top_left_y + 5, 3, 1);
      cells.insert(cells.end(), bottom_block.begin(), bottom_block.end());

      auto right_block = rectangle_MS(top_left_x + 12, top_left_y + 2, 1, 3);
      cells.insert(cells.end(), right_block.begin(), right_block.end());
   }

   // Bottom left quadrant
   {
      auto top_block = rectangle_MS(top_left_x + 2, top_left_y + 7, 3, 1);
      cells.insert(cells.end(), top_block.begin(), top_block.end());

      auto left_block = rectangle_MS(top_left_x, top_left_y + 8, 1, 3);
      cells.insert(cells.end(), left_block.begin(), left_block.end());

      auto bottom_block = rectangle_MS(top_left_x + 2, top_left_y + 12, 3, 1);
      cells.insert(cells.end(), bottom_block.begin(), bottom_block.end());

      auto right_block = rectangle_MS(top_left_x + 5, top_left_y + 8, 1, 3);
      cells.insert(cells.end(), right_block.begin(), right_block.end());
   }

   // Bottom right quadrant
   {
      auto top_block = rectangle_MS(top_left_x + 8, top_left_y + 7, 3, 1);
      cells.insert(cells.end(), top_block.begin(), top_block.end());

      auto left_block = rectangle_MS(top_left_x + 7, top_left_y + 8, 1, 3);
      cells.insert(cells.end(), left_block.begin(), left_block.end());

      auto bottom_block = rectangle_MS(top_left_x + 8, top_left_y + 12, 3, 1);
      cells.insert(cells.end(), bottom_block.begin(), bottom_block.end());

      auto right_block = rectangle_MS(top_left_x + 12, top_left_y + 8, 1, 3);
      cells.insert(cells.end(), right_block.begin(), right_block.end());
   }
   return cells;
}

std::vector<CellInfo> gosper_gun_MS(unsigned int top_left_x, unsigned int top_left_y)
{
   std::vector<CellInfo> cells;
   // Add the two blocks
   auto first_block = block_SL(top_left_x, top_left_y + 4);
   cells.insert(cells.end(), first_block.begin(), first_block.end());

   auto second_block = block_SL(top_left_x + 35, top_left_y + 2);
   cells.insert(cells.end(), second_block.begin(), second_block.end());

   // Add the 'tear drop' section
   auto one_by_three = rectangle_MS(top_left_x + 10, top_left_y + 4, 1, 3);
   cells.insert(cells.end(), one_by_three.begin(), one_by_three.end());

   cells.push_back({ top_left_x + 11, top_left_y + 3, 1 });
   cells.push_back({ top_left_x + 11, top_left_y + 7, 1 });

   auto one_by_two_top = rectangle_MS(top_left_x + 12, top_left_y + 2, 2, 1);
   cells.insert(cells.end(), one_by_two_top.begin(), one_by_two_top.end());

   auto one_by_two_bottom = rectangle_MS(top_left_x + 12, top_left_y + 8, 2, 1);
   cells.insert(cells.end(), one_by_two_bottom.begin(), one_by_two_bottom.end());

   cells.push_back({ top_left_x + 14, top_left_y + 5, 1 });

   cells.push_back({ top_left_x + 15, top_left_y + 3, 1 });
   cells.push_back({ top_left_x + 15, top_left_y + 7, 1 });

   auto one_by_three_r = rectangle_MS(top_left_x + 16, top_left_y + 4, 1, 3);
   cells.insert(cells.end(), one_by_three_r.begin(), one_by_three_r.end());

   cells.push_back({ top_left_x + 17, top_left_y + 5, 1 });

   // Final section
   auto two_by_three = rectangle_MS(top_left_x + 20, top_left_y + 2, 2, 3);
   cells.insert(cells.end(), two_by_three.begin(), two_by_three.end());

   cells.push_back({ top_left_x + 22, top_left_y + 1, 1 });
   cells.push_back({ top_left_x + 22, top_left_y + 5, 1 });

   auto two_by_one_top = rectangle_MS(top_left_x + 24, top_left_y, 1, 2);
   cells.insert(cells.end(), two_by_one_top.begin(), two_by_one_top.end());

   auto two_by_one_bottom = rectangle_MS(top_left_x + 24, top_left_y + 5, 1, 2);
   cells.insert(cells.end(), two_by_one_bottom.begin(), two_by_one_bottom.end());

   return cells;
}
