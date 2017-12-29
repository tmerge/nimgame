#include "stdafx.h"
#include "dynamic_menu.h"
#include "console_utils.h"
#include "COLOR_STRUCT.h"
#include "ascii_block_list.h"

namespace console_handler
{
  void dynamic_menu::draw()
  {
    // draw boxes
    for (int i = 0; i < items_.size(); i++)
    {
 
      // print rectangle background
      items_[i].item_rectangle.print();


      //TODO: add innerbox padding
      const int offset = items_[i].menu_item.border_size + 10;
      const int text_height = offset;
      
      // print text
      console_utils::set_console_cursor_pos({
        items_[i].item_rectangle.get_left().X + short(items_[i].menu_item.border_size * 2),
        items_[i].item_rectangle.get_right().Y - short(text_height + (text_height / 2))
      });
      ascii_block_list(items_[i].menu_item.caption, text_height,
                       COLOR_STRUCT(items_[i].menu_item.caption_foreground_color_code)).draw();

      //print icon
      const SIZE icon_size = {
        item_side_length_ - (offset * 2),
        item_side_length_ - ((offset * 2) + text_height)
      };

      console_utils::set_console_cursor_pos({
        items_[i].item_rectangle.get_left().X + short(offset),
        items_[i].item_rectangle.get_left().Y + short(offset)
      });

      ascii_block("../Icons/Settings.bmp", icon_size,
                  COLOR_STRUCT(items_[i].menu_item.icon_foreground_color_code)).draw();
    }
  }

  void dynamic_menu::select()
  {
  }

  int dynamic_menu::calculate_side_length_automatic() const
  {
    int console_height = console_utils::get_console_height() - (window_margin_ * 2);
    int console_width = console_utils::get_console_width() - (window_margin_ * 2);
    const int smalles_window_length = min(console_height, console_width);

    int max_per_row = 0;
    int side_length = smalles_window_length / menu_items_.size();

    for (int i = smalles_window_length; i > 5; i--)
    {
      const int boxes_per_row = calculate_boxes_per_row(i);
      if (boxes_per_row > 1)
        return i;
    }

    return side_length;
  }

  int dynamic_menu::calculate_boxes_per_row(const int item_side_lenght) const
  {
    int console_height = console_utils::get_console_height() - (window_margin_ * 2);
    int console_width = console_utils::get_console_width() - (window_margin_ * 2);
    const int smalles_window_length = min(console_height, console_width);

    int max_per_row = -1;
    for (int i = 1; i < menu_items_.size(); i++)
    {
      if ((((item_side_lenght + margin_between_boxes_) * i) - margin_between_boxes_) < console_width) 
        if ((((item_side_lenght + margin_between_boxes_) * ceil(double(menu_items_.size()) / double(i))) - margin_between_boxes_) < console_height)
          max_per_row = i;
    }

    return max_per_row;
  }

  void dynamic_menu::calculate_rectangles()
  {
    items_.clear();
    int current_row = 0;
    int current_row_index = 0;

    // calculate rectangles
    for (int i = 0; i < menu_items_.size(); i++)
    {
      // rectangle left & right
      const _COORD left = {
        short(window_margin_ + current_row_index * item_side_length_ + current_row_index * margin_between_boxes_),
        short(window_margin_ + current_row * item_side_length_ + current_row * margin_between_boxes_)
      };

      // rectangle shape
      const shape_rectangle shape =
        shape_rectangle(left,
                        {
                          // right
                          left.X + short(item_side_length_),
                          left.Y + short(item_side_length_)
                        },
                        menu_items_[i].item_background, ' ');
      // add to items
      items_.push_back(menu_item_rectangle(menu_items_[i], shape, current_row, current_row_index));

      // next row index & next row
      current_row_index++;

      if ((i + 1) % boxes_per_row_ == 0)
      {
        current_row++;
        current_row_index = 0;
      }
    }
  }


  dynamic_menu::dynamic_menu(const std::vector<menu_item> menu_items, const int window_margin,
                             const int margin_between_boxes)
    : menu_items_(menu_items), window_margin_(window_margin), margin_between_boxes_(margin_between_boxes)
  {
    item_side_length_ = calculate_side_length_automatic();
    boxes_per_row_ = calculate_boxes_per_row(item_side_length_);
    calculate_rectangles();
  }
}