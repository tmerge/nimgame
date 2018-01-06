#include "stdafx.h"
#include "play.h"
#include "console_output.h"
#include "options.h"

namespace sites
{
  console_handler::dynamic_grid play::current_session_field_;

  void play::gameplay()
  {
    do {
      std::vector<int> selected_by_current_user = current_session_field_.mark_and_select(true, options::max_allowed_per_row, "{_#BBDEFB}", "{_#E3F2FD}");
      // disable items
      for (int i = 0; i < selected_by_current_user.size(); i++)
        current_session_field_.disable_item(selected_by_current_user[i], "{_#F5F5F5}", "{_#EEEEEE}");
    } while (!current_session_field_.all_items_disabled());

    // Current player winns
  }

  void play::new_game()
  {
    //TODO: Make pretty game-color design
    console_handler::console_output::fill_background("{_#FFFFFF}");
    generate_field();
    current_session_field_.draw();
    gameplay();
  }

  void play::generate_field()
  {
    std::vector<console_handler::grid_item> field_items;

    // Get max items per row given
    int max_items_per_row = 0;
    for (int row = 0; row < options::field_structure.size(); row++)
    {
      if (max_items_per_row < options::field_structure[row])
        max_items_per_row = options::field_structure[row];
    }

    for (int row = 0; row < options::field_structure.size(); row++)
    {
      for (int field_item = 1; field_item <= max_items_per_row; field_item++)
      {
        //(currently) testing center boxes (MAKE THIS LATER @ME(CG))
        // THE TIME IS RUNNING AWAY!

        //if(max_items_per_row != options::field_structure[row])
        //{
        //  if(max_items_per_row % options::field_structure[row] == 0)
        //  {
        //    if (field_item < max_items_per_row / options::field_structure[row] || field_i)
        //    
        //  }
        //  else
        //  {
        //  }
        //}

        bool disiabled_item = false;
        if (field_item > options::field_structure[row])
          disiabled_item = true;

        console_handler::grid_item new_field_item = console_handler::grid_item([](void) {}, "", "{_#FDD835}", "../Icons/FireMatch.bmp", "{_#D84315}", ' ', "{_#37474F}", 5);
        new_field_item.disabled = disiabled_item;
        new_field_item.visible = !disiabled_item;
        field_items.push_back(new_field_item);
      }
    }
    current_session_field_ = console_handler::dynamic_grid("Go!", 30, field_items, 10, 5, max_items_per_row);
  }
}
