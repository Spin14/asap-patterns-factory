#ifndef _salad_h_
#define _salad_h_

#include <iostream>
#include <map>

#include "asap-factory.hpp"

namespace salad
{

  // These are our colors.
  enum Color { ORANGE, RED, GREEN, BLACK };

  // Vegetable is our interface.

  // Lets make Vegetable specializations available through a
  // abstract factory which takes a Color as the key.

  // To do so we extende asap::Factorize<Vegetable, Color>
  struct Vegetable : public asap::Factorize<Vegetable, Color>
  {
    Vegetable() { std::cout << "Creating Vegetable..." << "\n";}
    virtual ~Vegetable() { std::cout << "Destroying Vegetable." << "\n\n";}
    virtual void who_am_i() = 0;
  };

  // Implementation of Tomato, nothing to do here.
  struct Tomato : public Vegetable
  {
    void who_am_i() override { std::cout << "Tomato !" << '\n'; }
  };

  // Implementation of Carrot, nothing to do here.
  struct Carrot : public Vegetable
  {
    void who_am_i() override { std::cout << "Carrot !" << '\n'; }
  };

  // Some typedefs we can benefit from.
  using VegetableMap = std::map<Color, asap::Creator<Vegetable>*>;
  using VegetableFactory = asap::Factory<Vegetable, Color>;

  template<class V>
  using VegetableResgistrator = asap::Resgistrator<Vegetable, Color, V>;

} // end namespace salad

namespace asap
{
  // Defining specializations for template members.
  // In this case is asap::Resgistrator, as all Vegetable
  // derivates will have a static member of such type.
  // Through these asap::Resgistrator specializations we
  // control how we populate the Factory's map.

  // These specializations must be done inside the asap
  // namespace ( otherwise code does not compile... ?)
  using namespace salad;

  // empty map for starters
  template<>
    VegetableMap VegetableFactory::creators_map = {{}};

  // use default constructor -> no registed in the factory map
  template<>
  VegetableResgistrator<Vegetable> Vegetable::registrator<Vegetable>;

  // map specializations -> one or more entries in the factory map
  template<>
    VegetableResgistrator<Tomato> Tomato::registrator<Tomato>({RED, GREEN});

  template<>
    VegetableResgistrator<Carrot> Carrot::registrator<Carrot>(ORANGE);

} // end namespace asap

#endif // _salad_h_
