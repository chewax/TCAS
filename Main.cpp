#include <iostream>
#include <ginseng/Ginseng.h>
#include <ncurses.h>
#include <vector>
#include <string>
#include <chrono>
#include "./core/utils/VirtualATC.h"
#include "./core/airspace/Drone.h"
#include "./core/ui/UICommands.h"
#include "./core/ui/UIRadar.h"
#include "./core/commands/CommandHandler.h"


int main()
{


  //NCURSES init
  initscr();
  // cbreak(); //break with ctrl + c
  // halfdelay(1);
  noecho(); //dont echo inputs
  int height, width, start_y, start_x;
  getmaxyx(stdscr, height, width);
  start_y = height - 4;
  start_x = 1;

  WINDOW* commands_window = newwin(3, width-1, start_y, start_x);
  UICommandManager ucm(start_x, start_y, commands_window);
  
  VirtualATC atc;
  WINDOW* feedback_window = newwin(3, width-1, start_y-2, start_x);
  CommandHandler cHandler(feedback_window, atc);
  
  WINDOW* radar_window = newwin(height-6, width-30, 0, 0);
  UIRadar radar(radar_window, atc);

  ucm.on_command([&cHandler](std::string cmd) -> void {
    cHandler.on_command(cmd);
  });

  auto start = std::chrono::steady_clock::now();
  while (1) {  
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();
    ucm.loop();

    if (elapsed >= 500) {
      radar.loop();
      start = std::chrono::steady_clock::now();
    }
    
  }

  //deallocates memory and ends ncurses
  endwin();

  

  // 	Ginseng repl("$DCAS>", []()
	// {
	// 	std::cout << "\nWelcome to DCAS (Drone Collission Avoidance System) Console" << "\n";
	// 	std::cout << "Type \"help\" to start" << "\n";
	// 	std::cout << "" << "\n";
	// 	std::cout << "Safe Flights" << "\n";
	// },
	// []()
	// {
	// 	std::cout << "\nBye My friend!" << "\n";
	// });
  // // DCAS repl;
  
  // // Help add_drone_h("Adds a drone", "[lat long heigh(ft) hdg climb_rate(ft/min) spd(kts)]");
  // // repl.add_command("add_drone", [](std::vector<std::string> args) -> int
  // // { 
  // //   if (args.size() < 2) return Exit::INVALID_ARGUMENTS;
  // //   std::cout << "HELLO " << args[1] << std::endl; 
  // //   return Exit::SUCCESS;
  // // }, hello_h);


  // Help show_h("Shows traffic information", "<label>");
  // repl.add_command("show", [&atc](std::vector<std::string> args) -> int
  // { 
  //   if (args.size() < 2) return Exit::INVALID_ARGUMENTS;
  //   Traffic t = atc.get_traffic(args[1]); 

  //   std::cout << "\n" << t.label << std::endl;
  //   std::cout << "=====================" << std::endl;
  //   std::cout << "lat: " << t.lat << std::endl;
  //   std::cout << "lon: " << t.lon << std::endl;
  //   std::cout << "alt: " << t.alt << std::endl;
  //   std::cout << "hdg: " << t.hdg << std::endl;
  //   std::cout << "v/s: " << t.climb_rate << std::endl;
  //   std::cout << "spd: " << t.spd << std::endl;
  //   std::cout << "=====================\n" << std::endl;
    
  //   return Exit::SUCCESS;

  // }, show_h);


  // Help add_traffic_h("Adds traffic to the virtual airspace", "<label>");
  // repl.add_command("add_traffic", [&atc, &repl](std::vector<std::string> args) -> int
  // { 
  //   if (args.size() < 8) return Exit::INVALID_ARGUMENTS;
  //   atc.add_traffic(args[1], std::stod(args[2]), std::stod(args[3]), std::stoi(args[4]), std::stoi(args[5]), std::stoi(args[6]), std::stoi(args[7]));

  //   std::string hlp = "Parsing of natural ATC commands for Traffic " + args[1];
  //   Help flt_h(hlp, "");

  //   repl.add_command(args[1], [&atc] (std::vector<std::string> args) -> int 
  //   {
  //     atc.traffic_instruction(args);
  //     return Exit::SUCCESS;
  //   }, flt_h);

  //   return Exit::SUCCESS;
  // }, add_traffic_h);

  // // Help check_conflict_h("Checks conflict between drones", "");
  // // repl.add_command("check_conflict", [](std::vector<std::string> args) -> int
  // // { 
    
  // //   return Exit::SUCCESS;
  // // }, quick_init_h);

  // repl.start();
  
  return 0;
}