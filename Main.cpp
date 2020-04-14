#include <iostream>
#include <ginseng/Ginseng.h>
#include "./core/utils/VirtualATC.h"
#include "./core/airspace/Drone.h"

int main()
{

  VirtualATC atc;

  	Ginseng repl("$DCAS>", []()
	{
		std::cout << "\nWelcome to DCAS (Drone Collission Avoidance System) Console" << "\n";
		std::cout << "Type \"help\" to start" << "\n";
		std::cout << "" << "\n";
		std::cout << "Safe Flights" << "\n";
	},
	[]()
	{
		std::cout << "\nBye My friend!" << "\n";
	});
  // DCAS repl;
  
  // Help add_drone_h("Adds a drone", "[lat long heigh(ft) hdg climb_rate(ft/min) spd(kts)]");
  // repl.add_command("add_drone", [](std::vector<std::string> args) -> int
  // { 
  //   if (args.size() < 2) return Exit::INVALID_ARGUMENTS;
  //   std::cout << "HELLO " << args[1] << std::endl; 
  //   return Exit::SUCCESS;
  // }, hello_h);

  Help quick_init_h("Quickly initializes the system with premade settings", "");
  repl.add_command("qs", [&atc, &repl](std::vector<std::string> args) -> int
  { 
    Traffic t1("LA1107", 51.463543, -0.523353, 5000, 360, 0, 5);
    Traffic t2("BA509", 51.4686977, -0.542833, 5000, 90, 0, 5);
    atc.add_traffic(t1);
    atc.add_traffic(t2);

    //Add dynamic REPL commands to interpret the ATC instructions in a
    //natural way
    Help la1107_h("Parsing of natural ATC commands for Traffic LA1107", "");
    repl.add_command("LA1107", [&atc] (std::vector<std::string> args) -> int 
    {
      atc.traffic_instruction(args);
      return Exit::SUCCESS;
    }, la1107_h);

    Help ba509_h("Parsing of natural ATC commands for Traffic BA509", "");
    repl.add_command("BA509", [&atc] (std::vector<std::string> args) -> int 
    {
      atc.traffic_instruction(args);
      return Exit::SUCCESS;
    }, ba509_h);

    return Exit::SUCCESS;
  }, quick_init_h);

  Help show_h("Shows traffic information", "<label>");
  repl.add_command("show", [&atc](std::vector<std::string> args) -> int
  { 
    if (args.size() < 2) return Exit::INVALID_ARGUMENTS;
    Traffic t = atc.get_traffic(args[1]); 

    std::cout << "\n" << t.label << std::endl;
    std::cout << "=====================" << std::endl;
    std::cout << "lat: " << t.lat << std::endl;
    std::cout << "lon: " << t.lon << std::endl;
    std::cout << "alt: " << t.alt << std::endl;
    std::cout << "hdg: " << t.hdg << std::endl;
    std::cout << "v/s: " << t.climb_rate << std::endl;
    std::cout << "spd: " << t.spd << std::endl;
    std::cout << "=====================\n" << std::endl;
    
    return Exit::SUCCESS;

  }, show_h);


  Help add_traffic_h("Adds traffic to the virtual airspace", "<label>");
  repl.add_command("add_traffic", [&atc, &repl](std::vector<std::string> args) -> int
  { 
    if (args.size() < 8) return Exit::INVALID_ARGUMENTS;
    atc.add_traffic(args[1], std::stod(args[2]), std::stod(args[3]), std::stoi(args[4]), std::stoi(args[5]), std::stoi(args[6]), std::stoi(args[7]));

    std::string hlp = "Parsing of natural ATC commands for Traffic " + args[1];
    Help flt_h(hlp, "");

    repl.add_command(args[1], [&atc] (std::vector<std::string> args) -> int 
    {
      atc.traffic_instruction(args);
      return Exit::SUCCESS;
    }, flt_h);

    return Exit::SUCCESS;
  }, add_traffic_h);

  // Help check_conflict_h("Checks conflict between drones", "");
  // repl.add_command("check_conflict", [](std::vector<std::string> args) -> int
  // { 
    
  //   return Exit::SUCCESS;
  // }, quick_init_h);

  repl.start();
  
  return 0;
}