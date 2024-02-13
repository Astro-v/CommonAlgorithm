#include <functional>
using namespace std;

struct SingletonTester
{
  template <typename T>
  bool is_singleton(function<T*()> factory)
  {
    auto elem_1 = factory();
    auto elem_2 = factory();
    return elem_1 == elem_2;
  }
};