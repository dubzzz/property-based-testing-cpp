#pragma once
#include <cstddef>
#include <string>

class Space
{
  const std::size_t m_dim_x, m_dim_y;
  const std::size_t m_solution_x, m_solution_y;
  std::size_t m_current_x, m_current_y;
  std::string m_hint;
  
  void update_hint()
  {
    m_hint = "";
    if (m_solution_y < m_current_y) m_hint += "U";
    else if (m_solution_y > m_current_y) m_hint += "D";
    
    if (m_solution_x < m_current_x) m_hint += "L";
    else if (m_solution_x > m_current_x) m_hint += "R";
  }

public:
  Space(
    std::size_t dim_x, std::size_t dim_y
    , std::size_t solution_x, std::size_t solution_y
    , std::size_t current_x, std::size_t current_y
  )
      : m_dim_x(dim_x)
      , m_dim_y(dim_y)
      , m_solution_x(solution_x)
      , m_solution_y(solution_y)
      , m_current_x(current_x)
      , m_current_y(current_y)
      , m_hint()
  {
    update_hint();
  }
  
  std::size_t dimension_x() const { return m_dim_x; }
  std::size_t dimension_y() const { return m_dim_y; }
  
  std::size_t previous_x() const { return m_current_x; }
  std::size_t previous_y() const { return m_current_y; }
  
  std::string const& hint() const { return m_hint; }
  
  void move(std::size_t x, std::size_t y)
  {
    m_current_x = x;
    m_current_y = y;
    update_hint();
  }
  
  bool solved() const
  {
    return m_current_x == m_solution_x
        && m_current_y == m_solution_y;
  }
};

class SpaceBuilder
{
  std::size_t m_dimension_x, m_dimension_y
      , m_solution_x, m_solution_y
      , m_current_x, m_current_y;

public:
  SpaceBuilder() = default;
  SpaceBuilder& withDimension(std::size_t x, std::size_t y) { m_dimension_x = x; m_dimension_y = y; return *this; }
  SpaceBuilder& withSolution (std::size_t x, std::size_t y) { m_solution_x  = x; m_solution_y  = y; return *this; }
  SpaceBuilder& withCurrent  (std::size_t x, std::size_t y) { m_current_x   = x; m_current_y   = y; return *this; }
  Space build() const { return Space{ m_dimension_x, m_dimension_y, m_solution_x, m_solution_y, m_current_x, m_current_y }; }
};

