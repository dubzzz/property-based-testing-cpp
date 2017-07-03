#include <cstddef>
#include <iostream>
#include <string>

class Space
{
  const std::size_t m_dim_x, m_dim_y;
  std::size_t m_current_x, m_current_y;
  std::string m_hint;
  
public:
  Space(
    std::size_t dim_x, std::size_t dim_y,
    std::size_t current_x, std::size_t current_y)
      : m_dim_x(dim_x)
      , m_dim_y(dim_y)
      , m_current_x(current_x)
      , m_current_y(current_y)
      , m_hint()
  {
    std::cin >> m_hint;
    std::cin.ignore();
  }
  
  std::size_t dimension_x() const { return m_dim_x; }
  std::size_t dimension_y() const { return m_dim_y; }
  
  std::size_t previous_x() const { return m_current_x; }
  std::size_t previous_y() const { return m_current_y; }
  
  std::string const& hint() const { return m_hint; }
  
  void move(std::size_t x, std::size_t y)
  {
    std::cout << x << " " << y << std::endl;
    m_current_x = x;
    m_current_y = y;
    std::cin >> m_hint;
    std::cin.ignore();
  }
  
  bool solved() const
  {
    return m_hint.empty();
  }
};

/* COPY PASTE the code of "implem.inl.hpp"
   HERE                                    */

int main()
{
    std::size_t W, H;
    std::cin >> W >> H;
    std::cin.ignore();
    
    std::size_t N;
    std::cin >> N;
    std::cin.ignore();
    
    std::size_t X0, Y0;
    std::cin >> X0 >> Y0;
    std::cin.ignore();
    
    Space sp {W, H, X0, Y0};
    locate_in_space(sp, N);
}    
    
