// TODO: Parallelise?
// TODO: Ability to specify configurations in a text file and read them in - integer grid size, then triples of indices (x, y, value)
// TODO: Ability to use precanned conway generators at certain positions
// TODO: Control colour of dead and alive cells
// TODO: Output info on screen, num dead cells, alive cells etc
// TODO: Output controls on screen
// TODO: Event to control speed of simulation - Make this work properly
// TODO: Display status of simulation - running or paused
// TODO: Display speed of simulation
#include <sstream>

#include <SFML/Graphics.hpp>

#include "conway.h"
#include "conway_generators.h"
#include "update_timer.h"

void draw(sf::RenderWindow& window, const conway& conway, float square_size)
{
   sf::RectangleShape shape(sf::Vector2f(square_size, square_size));
   // x -> left to right -> j (inner) subscript
   // y -> top to bottom -> i (outer) subscript
   float x = 0.0f, y = 0.0f;
   for (unsigned int i = 0; i < conway.num_cells(); ++i)
   {
      for (unsigned int j = 0; j < conway.num_cells(); ++j)
      {
         shape.setPosition(x, y);
         auto shape_colour = conway.get_cell(j, i) == 0 ? sf::Color::Black : sf::Color::White;
         shape.setFillColor(shape_colour);
         window.draw(shape);
         x += square_size;
      }
      y += square_size;
      x = 0.0f;
   }
}

sf::Text create_game_information_text(const sf::Font& font, bool running)
{
   std::stringstream ss;
   ss << "Status: ";
   ss << (running ? "running" : "paused");
   
   sf::Text text;
   text.setFont(font);
   text.setString(ss.str());
   text.setFillColor(sf::Color::White);
   text.setPosition(10.0f, 5.0f);
   text.setCharacterSize(16);
   return text;
}

int main()
{
   unsigned int screen_width = 800;
   float square_size = 10.0f;
   // Calculate the number of squares we need to populate the screen
   unsigned int num_squares_per_dimension = static_cast<float>(screen_width) / square_size;

   sf::RenderWindow window(sf::VideoMode(screen_width, screen_width), "Conway's Game of Life");
   sf::RectangleShape shape(sf::Vector2f(square_size, square_size));

   // Setup conway object
   conway con(num_squares_per_dimension);

   std::vector<CellInfo> block = block_SL(10, 10);
   con.set_cells(block);

   std::vector<CellInfo> beehive = beehive_SL(20, 10);
   con.set_cells(beehive);

   std::vector<CellInfo> loaf = loaf_SL(30, 10);
   con.set_cells(loaf);

   std::vector<CellInfo> boat = boat_SL(40, 10);
   con.set_cells(boat);

   std::vector<CellInfo> tub = tub_SL(50, 10);
   con.set_cells(tub);

   std::vector<CellInfo> blinker = blinker_OS(10, 20);
   con.set_cells(blinker);

   std::vector<CellInfo> toad = toad_OS(20, 20);
   con.set_cells(toad);

   std::vector<CellInfo> beacon = beacon_OS(30, 20);
   con.set_cells(beacon);

   std::vector<CellInfo> pulsar = pulsar_OS(40, 20);
   con.set_cells(pulsar);

   //std::vector<CellInfo> gosper_gun = gosper_gun_MS(10, 10);
   //con.set_cells(gosper_gun);

   // Timer stuff
   unsigned int update_interval_ms = 100;
   update_timer timer(update_interval_ms);

   // Game control stuff
   bool paused = true;
   unsigned int update_interval_increment_ms = 5;

   // Overlay stuff
   sf::Font overlay_font;
   if (!overlay_font.loadFromFile(R"(C:\Users\peterm\projects\Conway\res\UbuntuMono-R.ttf)"))
   {
      throw std::runtime_error("Failed to load font!");
   }
   sf::Text game_text = create_game_information_text(overlay_font, !paused);

   // Main simulation/render loop
   while (window.isOpen())
   {
      sf::Event event;
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
         {
            window.close();
         }
         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
         {
            paused = !paused;
            game_text = create_game_information_text(overlay_font, !paused);
         }
         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
         {
            timer.update_interval_ms(timer.update_interval_ms() + update_interval_increment_ms);
         }
         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
         {
            timer.update_interval_ms(timer.update_interval_ms() - update_interval_increment_ms);
         }
      }

      // Only want to advance the conway simulation at regular intervals
      while (!paused && timer.can_update())
      {
         // Advance the conway simulation
         con.update();
         // Restart the timer
         timer.restart();
      }
      // Clear the screen
      window.clear();
      // Draw life
      draw(window, con, square_size);
      // Draw Overlay
      window.draw(game_text);
      window.display();
   }
}