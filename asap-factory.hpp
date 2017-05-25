#ifndef _asap_h_
#define _asap_h_

#include <map>
#include <memory>

namespace asap
{
  /**
  * \class Creator
  * \brief simple abstract template creator that
  * declares the only method required by a Factory class.
  */
  template <class Interface>
  class Creator
  {
  protected:
    Creator() {};
    virtual ~Creator() {};

  public:
    virtual Interface* create() = 0;
  };

  /**
  * \class Factory
  * \brief Static members only. Is able to create Interface
  * specializations based on a KeyType.
  */
  template <class Interface, class KeyType>
  class Factory
  {
  public:
    Factory() {};
    ~Factory() {};

    static std::map<KeyType, Creator<Interface>*> creators_map;

    static void register_creator(KeyType key, Creator<Interface>* creator)
    {
      creators_map[key] = creator;
    }

    static std::unique_ptr<Interface> generate(KeyType key)
    {
      Interface* concrete = nullptr;

      auto creators_map_it = creators_map.find(key);
      if(creators_map_it != creators_map.end())
      {
        concrete = creators_map_it->second->create();
      }

      return std::unique_ptr<Interface>(concrete);
    }
  };

  /**
  * \class Resgistrator
  * \brief implements Creator<Interface> and is responsible
  * for the population of the correspondent Factory creators_map.
  */
  template <class Interface, class KeyType, class Concrete>
  class Resgistrator : public Creator<Interface>
  {
  public:
    // if we do not want this Concrete class available through the Factory
    // also this must be used for the Interface registrator
    Resgistrator() {}

    // if we want this Concrete class available through the Factory (one key)
    Resgistrator(KeyType key)
    {
      Factory<Interface, KeyType>::register_creator(key, this);
    }

    // if we want this Concrete class available through the Factory (multiple keys)
    Resgistrator(std::list<KeyType> keys)
    {
      for(auto key : keys)
      {
          Factory<Interface, KeyType>::register_creator(key, this);
      }
    }

    ~Resgistrator() {}

    Interface* create() override
    {
      return new Concrete();
    }
  };

  /**
  * \class Factorize
  * \brief to be extended by the Interface specializations.
  * makes each specialization class define their Resgistrator
  */
  template <class Interface, class KeyType>
  class Factorize
  {
  public:
    Factorize() {}
    ~Factorize() {}

    static Factory<Interface, KeyType> factory;

    template <class Concrete>
    static Resgistrator<Interface, KeyType, Concrete> registrator;
  };

} // namespace asap

#endif // _asap_h_
