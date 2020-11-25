#include <string>
#include <vector>
#include "vector.hpp"
#include "test_runner.hpp"

struct President {
  std::string name;
  std::string country;
  int year;

  President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year) {
  }
};

void EmplaceTest() {
  Vector<President> temp;
  temp.emplace_back("Nelson Mandela", "South Africa", 1994);
  ASSERT_EQUAL(temp[0].name, "Nelson Mandela")
  ASSERT_EQUAL(temp[0].country, "South Africa")
  ASSERT_EQUAL(temp[0].year, 1994)
}

void SimpleTest() {
  Vector<size_t> temp;
  for (size_t i = 0; i < 10; i++) {
    temp.push_back(i);
  }
  for (size_t i = 0; i < temp.size(); i++) {
    ASSERT_EQUAL(temp[i], i);
  }
  size_t comp = 0;
  for (auto element : temp) {
    ASSERT_EQUAL(element, comp)
    comp++;
  }
  ASSERT_EQUAL(comp, temp.size())
  for (auto it = temp.rbegin(); it != temp.rend(); it++) {
    comp--;
    ASSERT_EQUAL(*it, comp)
  }
  ASSERT_EQUAL(comp, comp * 0)
  for (size_t i = 0; i < 5; i++) {
    temp.pop_back();
  }
  comp = 5;
  ASSERT_EQUAL(temp.size(), comp);
  for (size_t i = 0; i < temp.size(); i++) {
    ASSERT_EQUAL(temp[i], i);
  }
  temp.clear();
  comp = 0;
  ASSERT_EQUAL(temp.size(), comp)
  ASSERT_EQUAL(temp.empty(), true)
  ASSERT_EQUAL(temp.capacity() != comp, true)
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, SimpleTest);
  RUN_TEST(tr, EmplaceTest);
  return 0;
}
