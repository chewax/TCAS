#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <functional>

//   // wattron(command_window, A_STANDOUT);
//   // mvwprintw(command_window, 1,1, "this is my window");
//   // wattroff(command_window, A_STANDOUT);

using OnCommandCb = std::function<void(std::string)>;

class UICommandManager {

  private: 
    int start_x;
    int start_y;
    int cmd_x;
    int cmd_y;

    WINDOW* command_window;

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
    UICommandManager(int t_start_x, int t_start_y, WINDOW* t_win, std::string t_delim);
};

// Class constructor
// Initialises history and iterators.
UICommandManager::UICommandManager(int t_start_x, int t_start_y, WINDOW* t_win, std::string t_delim="$>")
:start_x(t_start_x), start_y(t_start_y), command_window(t_win), delim(t_delim)
{
  nodelay(command_window, true);
  keypad(command_window, true);

  history.push_back("...");
  it = history.end();
  cmd_x = t_delim.size() + 3; //1 for the border, 1 for the leading space, 1 for the trailing space
  cmd_y = 1;
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
  mvwprintw(command_window, cmd_y, 2, delim.c_str());
  wclrtoeol(command_window);
  mvwprintw(command_window, cmd_y, cmd_x, command.c_str());
  box(command_window, 0, 0);
  wrefresh(command_window);
}

// Ends command and parses contents
// Updates screen
void UICommandManager::end_command()
{
  if (command == "" || command == "...")  return;
  
  history.push_back(command);
  it = history.end();
  cb(command); 
  // int c = wgetch(command_window);
  command = "";
}

// Updates buffered command with current character input
void UICommandManager::update_command()
{
  int c = wgetch(command_window);

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
