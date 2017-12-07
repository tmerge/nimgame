// NimGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "console_handler.h"
#include <iostream>
#include "console_output.h"
#include "console_utils.h"

using namespace std;
using namespace console_handler;

int main()
{
  console_handler_core::prepare_console();
  console_output::fill_background("{_#0944a3}");
  std::vector<MENU_ITEM> menu_items;
  menu_items.push_back({ "","","" });
  menu_items.push_back({ "","","" });
  menu_items.push_back({ "","","" });
  console_output::draw_menu(menu_items);



  //console_output::print_line("Hello {#ff00ff}til");
  //console_output::print_separatorline("-");
  //console_output::print_rectangle({ {5,2},{10,7} }, "{_#00FF00}");
  /*

  console_output::print_line("Dies ist ein {#00FFFF}elendiger Satz.{;} {_#666666}YAY, grauer hintergrund");
  console_output::print_line("Hello til2");*/
  getchar();
    return 0;
}

