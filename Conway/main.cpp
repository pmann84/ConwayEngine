// TODO: Parallelise?
// TODO: Ability to specify configurations in a text file and read them in - integer grid size, then triples of indices (x, y, value)
// TODO: Ability to use precanned conway generators at certain positions
// TODO: Control colour of dead and alive cells
// TODO: Output info on screen, num dead cells, alive cells etc
// TODO: Revisit sim speed controls
// TODO: Improve the format of setting starting cells, so they can be easily rotated
// TODO: Add generation count

#include <sstream>

#include <SFML/Graphics.hpp>

#include "conway.h"
#include "conway_generators.h"
#include "update_timer.h"
#include "rules.h"

void draw(sf::RenderWindow& window, const conway& conway, float square_size, sf::Color cell_colour)
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
         const auto cell_value = conway.get_cell(j, i);
         if (cell_value == 1)
         {
            shape.setFillColor(cell_colour);
            window.draw(shape);
         }
         x += square_size;
      }
      y += square_size;
      x = 0.0f;
   }
}

float calculate_updates_per_second(unsigned int update_interval_ms)
{
   return 1.0f / (static_cast<float>(update_interval_ms) / static_cast<float>(1000));
}

struct game_info
{
   bool running;
   float updates_per_second;
   unsigned int generation_count;
};

sf::Text createText(const std::string& str, const sf::Font& font, unsigned int size, sf::Vector2f position, sf::Color colour)
{
   sf::Text text;
   text.setFont(font);
   text.setString(str);
   text.setFillColor(colour);
   text.setPosition(position.x, position.y);
   text.setCharacterSize(size);
   return text;
}

sf::Text create_game_information_text(sf::Vector2f position, const sf::Font& font, game_info info)
{
   std::stringstream ss;
   ss << "Status: " << (info.running ? "running" : "paused") << std::endl;
   ss << "Updates/s: " << info.updates_per_second << std::endl;
   ss << "Generation: " << info.generation_count << std::endl;
   return createText(ss.str(), font, 16, position, sf::Color::White);
}

sf::Text create_game_settings_text(sf::Vector2f position, const sf::Font& font)
{
   std::stringstream ss;
   ss << "[Space] Pause/Resume" << std::endl;
   ss << " [Left] Decrease Speed" << std::endl;
   ss << "[Right] Increase Speed" << std::endl;
   ss << "    [R] Restart" << std::endl;
   return createText(ss.str(), font, 16, position, sf::Color::White);
}

void setup_test_bed(conway& con)
{
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

   std::vector<CellInfo> penta = pentadecathlon_OS(10, 40);
   con.set_cells(penta);

   std::vector<CellInfo> honeyfarm = honey_farm_SL(30, 40);
   con.set_cells(honeyfarm);

   std::vector<CellInfo> galaxy = koks_galaxy_OS(60, 40);
   con.set_cells(galaxy);
}

struct colour_scheme
{
   sf::Color background = sf::Color::Black;
   sf::Color cell = sf::Color::White;
};

int main()
{
   unsigned int screen_width = 800;
   float square_size = 5.0f;
   // Calculate the number of squares we need to populate the screen
   unsigned int num_squares_per_dimension = static_cast<float>(screen_width) / square_size;

   // Create colour scheme
   colour_scheme cs;

   // Create the window
   sf::RenderWindow window(sf::VideoMode(screen_width, screen_width), "Conway's Game of Life");
   // Clear to background colour
   window.clear(cs.background);

   // Set up cell shape
   sf::RectangleShape shape(sf::Vector2f(square_size, square_size));

   // Setup conway object
   conway con(num_squares_per_dimension, conway_birth_rule, conway_survival_rule);
   //conway con(num_squares_per_dimension, highlife_birth_rule, highlife_survival_rule);

   // Test scene
   //setup_test_bed(con);

   auto init_mt = acorn_MT(70, 70);
   con.set_cells(init_mt);

   auto init_mt2 = rpentomino_MT(90, 90);
   con.set_cells(init_mt2);

   //std::vector<CellInfo> gosper_gun = gosper_gun_MS(100, 100);
   //con.set_cells(gosper_gun);

   //std::vector<CellInfo> gosper_gun2 = gosper_gun_MS(10, 10);
   //con.set_cells(gosper_gun2);

   // Timer stuff
   unsigned int update_interval_ms = 50;
   update_timer timer(update_interval_ms);

   // Game control stuff
   unsigned int update_interval_increment_ms = 5;

   // Overlay stuff
   sf::Font overlay_font;
   if (!overlay_font.loadFromFile(R"(C:\Users\peterm\projects\Conway\res\UbuntuMono-R.ttf)"))
   {
      throw std::runtime_error("Failed to load font!");
   }
   game_info info
   {
      false,
      calculate_updates_per_second(timer.update_interval_ms()),
      con.generation_count()
   };
   sf::Vector2f game_info_txt_pos = { 10.0f, 5.0f };
   sf::Text game_text = create_game_information_text(game_info_txt_pos, overlay_font, info);
   sf::Text settings_text = create_game_settings_text({ static_cast<float>(screen_width - 190), 5.0f }, overlay_font);

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
            info.running = !info.running;
            info.updates_per_second = calculate_updates_per_second(timer.update_interval_ms());
            game_text = create_game_information_text(game_info_txt_pos, overlay_font, info);
         }
         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
         {
            timer.update_interval_ms(timer.update_interval_ms() + update_interval_increment_ms);
            info.updates_per_second = calculate_updates_per_second(timer.update_interval_ms());
            game_text = create_game_information_text(game_info_txt_pos, overlay_font, info);
         }
         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
         {
            timer.update_interval_ms(timer.update_interval_ms() - update_interval_increment_ms);
            info.updates_per_second = calculate_updates_per_second(timer.update_interval_ms());
            game_text = create_game_information_text(game_info_txt_pos, overlay_font, info);
         }
         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
         {
            con.restart();
            info.generation_count = con.generation_count();
            game_text = create_game_information_text(game_info_txt_pos, overlay_font, info);
         }
      }

      // Only want to advance the conway simulation at regular intervals
      while (info.running && timer.can_update())
      {
         // Advance the conway simulation
         con.update();
         // Restart the timer
         timer.restart();
         // Update the game info
         info.generation_count = con.generation_count();
         game_text = create_game_information_text(game_info_txt_pos, overlay_font, info);
      }
      // Clear the screen
      window.clear();
      // Draw life
      draw(window, con, square_size, cs.cell);
      // Draw Overlay
      window.draw(game_text);
      window.draw(settings_text);
      window.display();
   }
}
