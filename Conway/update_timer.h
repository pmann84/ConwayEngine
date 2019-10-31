#pragma once
#include <algorithm>
#include <ostream>
#include <iostream>

#include <SFML/System/Clock.hpp>

class update_timer
{
public:
   update_timer(unsigned int update_interval_ms) : m_update_interval_ms(update_interval_ms)
   {
   }

   void update_interval_ms(unsigned int update_interval_ms)
   { 
      unsigned int high = 200000;
      unsigned int low = 20;
      m_update_interval_ms = (update_interval_ms < low) ? low : (high < update_interval_ms) ? high : update_interval_ms;
   }

   unsigned int update_interval_ms() const
   {
      return m_update_interval_ms;
   }

   bool can_update() const
   {
      return m_timer.getElapsedTime().asMilliseconds() >= m_update_interval_ms;
   }

   void restart()
   {
      std::cout << "Elapsed Time " << m_timer.getElapsedTime().asMilliseconds() << std::endl;
      m_timer.restart();
   }

private:
   unsigned int m_update_interval_ms;
   sf::Clock m_timer;
};
