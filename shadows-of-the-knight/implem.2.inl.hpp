#include <utility>

void locate_in_space(Space& space, std::size_t rounds)
{
  std::size_t x_min = 0;
  std::size_t x_max = space.dimension_x();
  std::size_t y_min = 0;
  std::size_t y_max = space.dimension_y();
  
  for (std::size_t n {} ; n != rounds && ! space.solved() ; ++n)
  {
    if (x_min >= x_max || y_min >= y_max) { return; }
    
    std::size_t x0 = space.previous_x();
    std::size_t y0 = space.previous_y();
    auto const& hint = space.hint();
    
    if (hint[0] == 'U')
    {
      y_max = y0;
      y0 = (y_max + y_min) /2;
    }
    else if (hint[0] == 'D')
    {
      y_min = y0 +1;
      y0 = (y_max + y_min) /2;
    }
    
    if (hint.back() == 'L')
    {
      x_max = x0;
      x0 = (x_max + x_min) /2;
    }
    else if (hint.back() == 'R')
    {
      x_min = x0 +1;
      x0 = (x_max + x_min) /2;
    }
    
    space.move(x0, y0);
  }
}

