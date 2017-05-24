#include <string>
#include <iostream>
#include <list>
#include <memory>
#include "asap-factory.hpp"
#include "salad.hpp"

#define print(str) std::cout << str;
using Factory = asap::Factory<salad::Vegetable, salad::Color>;

std::map<salad::Color, std::string>  salad_colors
{
  {salad::Color::RED,     "red"},
  {salad::Color::ORANGE,  "orange"},
  {salad::Color::GREEN,   "green"},
  {salad::Color::BLACK,   "black"}
};

int main()
{
  print("\nLet's try our Salad factory:\n\n");

  for( auto color : salad_colors)
  {
    auto vegetable = Factory::generate(color.first);

    print("With color " << color.second << " => ");
    if(vegetable) vegetable->who_am_i();
    else print("No vegetable for this color..\n\n");
  }
}
