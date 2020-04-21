#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <functional>
#include "../utils/VirtualATC.h"


class UIRadar {

  private:
  WINDOW* _window;
  VirtualATC atc;
  
  public:
  UIRadar(WINDOW* t_window, const VirtualATC &atc);
  void loop();
};

UIRadar::UIRadar(WINDOW* t_window, const VirtualATC &t_atc): _window(t_window), atc(t_atc)
{
  wrefresh(_window);
}

void UIRadar::loop()
{
  wclear(_window);
  std::vector<Traffic> traff = atc.get_all();
  wprintw(_window, "%d", traff.size());
  wrefresh(_window);
}
