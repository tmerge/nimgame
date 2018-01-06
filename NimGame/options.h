﻿#pragma once
#include <string>
#include <vector>

namespace sites
{
  class options
  {
  public:
    static std::string name_player_a;
    static std::string name_player_b;
    static std::vector<int> field_structure;
    static void draw();
    static void change_player_names();

  };
}