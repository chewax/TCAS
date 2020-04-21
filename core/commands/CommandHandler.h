#include <vector>
#include <string>
#include <ncurses.h>
#include "utils/VirtualATC.h"
#include "ui/UIController.h"

class CommandHandler: public UIController {
  private:
    VirtualATC atc;
    void quick_setup();
    void show_traffic(const std::vector<std::string> &args);
    void add_traffic(const std::vector<std::string> &args);
    void show_all(const std::vector<std::string> &args);

    int xOut = 2;
    int yOut = 1;
    void parse_command(const std::string &str, std::vector<std::string> &args) const;

  public:
    void on_command(std::string command);
    CommandHandler(WINDOW* t_window, const VirtualATC &t_atc);
};

// Parses an input command into a vector of strings
void CommandHandler::parse_command(const std::string &str, std::vector<std::string> &args) const
{
  std::istringstream src(str);
  std::string s;
  while (std::getline(src, s, ' ')) args.push_back(s);
}

void CommandHandler::on_command(std::string command)
{

  std::vector<std::string> args;
  parse_command(command, args);
  _print("> %s", args[0].c_str());

  if (args[0] == "qs") quick_setup();
  if (args[0] == "trshow") show_traffic(args);
  if (args[0] == "trshall") show_all(args);
  if (args[0] == "tradd") add_traffic(args);

  // parse_instruction(args); //Parse an instruction for an airplane to perform an acti
}

CommandHandler::CommandHandler(WINDOW* t_window, const VirtualATC &t_atc): UIController(t_window), atc(t_atc)
{
  wrefresh(_window);
}

void CommandHandler::quick_setup()
{
    Traffic t1("LA1107", 51.463543, -0.523353, 34000, 360, 0, 250);
    Traffic t2("BA509", 51.4686977, -0.542833, 35000, 90, 0, 295);
    atc.add_traffic(t1);
    atc.add_traffic(t2);
}

void CommandHandler::show_traffic(const std::vector<std::string> &args)
{
      if (args.size() < 2) 
      {
        wattron(_window, A_STANDOUT);
        _print("INVALID ARGUMENTS");
        wattroff(_window, A_STANDOUT);
        return;
      }

      Traffic t = atc.get_traffic(args[1]); 
      _print("[%s] %d %dft %d %dkts", t.label.c_str(), t.hdg, t.alt, t.climb_rate, t.spd, t.lat, t.lon);
}


void CommandHandler::show_all(const std::vector<std::string> &args)
{
      if (args.size() < 1) 
      {
        wattron(_window, A_STANDOUT);
        _print("INVALID ARGUMENTS");
        wattroff(_window, A_STANDOUT);
        return;
      }


      std::vector<Traffic> traff = atc.get_all(); 
      _print("SHOW ALL: traff=%d", traff.size());
      wgetch(_window);

      for (const auto &it:traff)
      {
        _print("[%s] %d %dft %d %dkts", it.label.c_str(), it.hdg, it.alt, it.climb_rate, it.spd, it.lat, it.lon);
        wgetch(_window);
      }
}

void CommandHandler::add_traffic(const std::vector<std::string> &args)
{
      if (args.size() < 8) 
      {
        wattron(_window, A_STANDOUT);
        _print("INVALID ARGUMENTS: tradd LABEL LAT LON ALT HDG VS SPD");
        wattroff(_window, A_STANDOUT);
        return;
      }

      atc.add_traffic(args[1], std::stod(args[2]), std::stod(args[3]), std::stoi(args[4]), std::stoi(args[5]), std::stoi(args[6]), std::stoi(args[7]));
      Traffic t = atc.get_traffic(args[1]); 
      if (!t._void) _print("NEW TRAFFIC %s: HDG:%d ALT:%d VS:%d SPD:%d [%f,%f]", t.label.c_str(), t.hdg, t.alt, t.climb_rate, t.spd, t.lat, t.lon);
      else _print("TRAFFIC NOT FOUND");
}

