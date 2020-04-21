#ifndef __UIController_H
#define __UIController_H

#include <ncurses.h>
#include <string>

class UIController 
{
  protected:
  WINDOW* _window;
  int xOut = 2;
  int yOut = 1;
  template<typename... Args>
  void _print(const std::string &msg, Args... args);

  public:
  UIController(WINDOW* _window, int t_xOut, int t_yOut);
};

UIController::UIController(WINDOW* t_window, int t_xOut=2, int t_yOut=1)
  :_window(t_window), xOut(t_xOut), yOut(t_yOut)
{
}

// Safely prints into command feedback window row.
template<typename... Args>
void UIController::_print(const std::string &msg, Args... args)
{
  wmove(_window, yOut, xOut);
  wclrtoeol(_window);
  mvwprintw(_window, yOut, xOut, msg.c_str(), args...);
  wrefresh(_window);
}

#endif