#ifndef _salad_h_
#define _salad_h_

#include <iostream>
#include <map>

#include "asap-factory.hpp"

namespace salad
{
  // Food is going to be our interface.
  struct Food;

  // Our goal is to make Food specializations available through a
  // abstract factory which will respond to std::string keys.

  // To do so we derive our interface from
  // asap::Factorize<Food (Interface), Key (Factory Key type)>
  struct Food : public asap::Factorize<Food, std::string>
  {
    Food() { std::cout << "Creating Food..." << "\n";}
    virtual ~Food() { std::cout << "Destroying Food." << "\n\n";}

    virtual void who_am_i() = 0;
  };

  // Implementation of Tomato, nothing to do here.
  struct Tomato : public Food
  {
    void who_am_i() override { std::cout << "Tomato !" << '\n'; }
  };

  // Implementation of Pepper, nothing to do here.
  struct Pepper : public Food
  {
    void who_am_i() override { std::cout << "Pepper !" << '\n'; }

    static std::list<std::string> colors() { return {"green", "yellow"}; }
  };

  // Implementation of Onion, nothing to do here.
  struct Onion : public Food
  {
    void who_am_i() override { std::cout << "Onion !" << '\n'; }
  };

  // Now we use define some typedefs we can benefit from.
  using FoodMap = std::map<std::string, asap::Creator<Food>*>;
  using FoodFactory = asap::Factory<Food, std::string>;

  template<class Concrete>
  using FoodResgistrator = asap::Resgistrator<Food, std::string, Concrete>;

} // end namespace salad

namespace asap
{
  // Defining specializations for template members.
  // In this case is asap::Resgistrator, as all Food
  // specializations will have a static member of such type.
  // Through these asap::Resgistrator specializations we
  // control how we populate the Factory's map.

  // These specializations must be done inside the
  // asap namespace ( otherwise code does not compile... ?)
  using namespace salad;

  // Notice that the following definitions should always
  // belong in the same translation unit otherwise
  // we could make the mistake of trying to write to the
  // factory map before its exists.

  // Thus, a empty map for starters
  template<>
  FoodMap FoodFactory::creators_map = {{}};

  // For the interface type we use default constructor
  // -> nothing gets registered in the factory map.
  template<>
  FoodResgistrator<Food> Food::registrator<Food>;

  // Now we must map the specializations -> one or more entries in the factory map
  template<>
  FoodResgistrator<Tomato> Tomato::registrator<Tomato>("red");


  template<>
  FoodResgistrator<Pepper> Pepper::registrator<Pepper>(Pepper::colors());

  template<>
  FoodResgistrator<Onion> Onion::registrator<Onion>("white");

} // end namespace asap

#endif // _salad_h_
