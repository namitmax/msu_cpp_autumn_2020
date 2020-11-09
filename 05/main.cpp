#include <iostream>
#include "test_runner.hpp"
#include "serializer.hpp"

struct Data {
  uint64_t a;
  bool b;
  uint64_t c;

  template <class Serializer>
  Error serialize(Serializer& serializer) {
    return serializer(a, b, c);
  }
};

struct BadData {
  bool a;
  double c;

  template <class Serializer>
  Error serialize(Serializer& serializer) {
    return serializer(a, c);
  }
};

void BadTestSerializer() {
  BadData x {true, 1.15};
  std::stringstream stream;

  Serializer serializer(stream);
  ASSERT_EQUAL(serializer.save(x), Error::CorruptedArchive);
  Deserializer deserializer(stream);
  BadData y {false, 0.0};
  const Error err = deserializer.load(y);

  ASSERT_EQUAL(err, Error::CorruptedArchive)
}

void TestSerializer() {
  Data x { 1, true, 2 };

  std::stringstream stream;

  Serializer serializer(stream);
  serializer.save(x);

  Data y { 0, false, 0 };

  Deserializer deserializer(stream);
  const Error err = deserializer.load(y);

  ASSERT_EQUAL(err, Error::NoError)

  ASSERT_EQUAL(x.a, y.a)
  ASSERT_EQUAL(x.b, y.b)
  ASSERT_EQUAL(x.c, y.c)
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSerializer);
  RUN_TEST(tr, BadTestSerializer);
  return 0;
}
