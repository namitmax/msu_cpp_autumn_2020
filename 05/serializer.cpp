#include "serializer.hpp"

Error Serializer::makeString(uint64_t digit) {
  out_ << digit;
  return Error::NoError;
}

Error Serializer::makeString(bool f) {
  if (f) {
    out_ << "true";
  } else {
    out_ << "false";
  }
  return Error::NoError;
}

Error Deserializer::fromStream(uint64_t& value) {
  std::string text;
  in_ >> text;
  uint64_t tempValue;
  try {
    tempValue = std::stoull(text);
  }
  catch (std::logic_error& ex) {
    return Error::CorruptedArchive;
  }
  value = tempValue;
  return Error::NoError;
}

Error Deserializer::fromStream(bool& f) {
  std::string input;
  in_ >> input;
  if (input == "true") {
    f = true;
  } else if (input == "false") {
    f = false;
  } else {
    return Error::CorruptedArchive;
  }
  return Error::NoError;
}
