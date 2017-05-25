#include <string>
#include <iostream>
#include <list>
#include <memory>
#include "asap-factory.hpp"
#include "salad.hpp"

#define print(str) std::cout << str;

int main()
{
  print("Let's try our Salad factory:\n\n");

  std::list<std::string> colors {"green", "red", "yellow", "black", "white"};

  for(auto color : colors)
  {
    auto food = salad::Food::factory.generate(color);

    print("With color " << color << " => ");
    if(food) food->who_am_i();
    else print("No Food for this color..\n\n");
  }
}
