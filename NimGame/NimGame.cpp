// NimGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConsoleHandler.h"
#include <iostream>

using namespace std;
using namespace console_handler;

int main()
{
  ConsoleOutput::print(info, "Hello till");
  ConsoleOutput::print_line(menu, "-");
  ConsoleOutput::print(info, "Hello till2");
  getchar();
    return 0;
}

