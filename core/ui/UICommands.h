#ifndef __UICommands_H
#define __UICommands_H

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <string>
#include <functional>
#include "ui/UIController.h"

using OnCommandCb = std::function<void(std::string)>;

class UICommandManager: public UIController {

  private: 
    std::vector<std::string> history;
    std::vector<std::string>::iterator it;
    std::string delim;
    std::string command;
    OnCommandCb cb;

    void init();
    void update_window() const;
    void end_command();
    void update_command();
  
  public:
    void loop();
    void on_command(OnCommandCb cb);
    UICommandManager(WINDOW* t_window, std::string t_delim);
};

// Class constructor
// Initialises history and iterators.
UICommandManager::UICommandManager(WINDOW* t_window, std::string t_delim="$>")
:UIController(t_window), delim(t_delim)
{
  nodelay(_window, true);
  keypad(_window, true);

  history.push_back("...");
  it = history.end();
  xOut = t_delim.size() + 3; //1 for the border, 1 for the leading space, 1 for the trailing space
  yOut = 1;
  command = "";

  update_window();
}

void UICommandManager::on_command(OnCommandCb cb)
{
  this->cb = cb;
}

// Updates window with buffered information
void UICommandManager::update_window() const
{
  mvwprintw(_window, yOut, 2, delim.c_str());
  wclrtoeol(_window);
  mvwprintw(_window, yOut, xOut, command.c_str());
  box(_window, 0, 0);
  wrefresh(_window);
}

// Ends command and parses contents
// Updates screen
void UICommandManager::end_command()
{
  if (command == "" || command == "...")  return;
  
  history.push_back(command);
  it = history.end();
  cb(command); 
  // int c = wgetch(_window);
  command = "";
}

// Updates buffered command with current character input
void UICommandManager::update_command()
{
  int c = wgetch(_window);

  switch (c)
  {
    case KEY_UP:
    // Handle key up press
    // Retrieves previous from history
    {
      if (it > history.begin()) it--;;
      command = (*it);
      break;
    }
    
    case KEY_DOWN:
    // Handles key down press
    // Retrieves following command from history
    {
      if (it < history.end()) it++;        
      if (it == history.end()) command = "";
      else  command = (*it);
      break;
    }

    case 127:
    // Handles backspace press
    // Removes last charater from buffered command
    {
      command.pop_back();
      break;
    }
    
    
    case 10:
    // Handles return key press
    // Parses buffered command end resets screen
    {
      end_command();
      break;
    }

    default:
    // Handles non special characters
    // Appends character to buffered command
    {
      if (c != -1) command += c; //Input in current loop (-1 == ERR)
      break;
    }
  }
}

void UICommandManager::loop()
{
  update_window();
  update_command();
}

#endif