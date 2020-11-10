#ifndef SERIALIZER_HPP_
#define SERIALIZER_HPP_

#include <iostream>
#include <string>
#include <utility>

enum class Error {
  NoError,
  CorruptedArchive
};

class Serializer {
  static constexpr char space = ' ';

  private:
    std::ostream &out_;

    template <class T>
    Error process(T&& value) { return makeString(value); }

    template <class T, class... Args>
    Error process(T&& value, Args&&... args) {
      Error err = makeString(value);
      if (err != Error::NoError) {
        return err;
      }
      out_ << space;
      return process(std::forward<Args>(args)...);
    }

    template <class T>
    Error makeString(T /* value */) {
      return Error::CorruptedArchive;
    }

    Error makeString(uint64_t digit);

    Error makeString(bool f);

  public:
    explicit Serializer(std::ostream& out): out_(out) {}

    template <class T>
    Error save(T& object) { return object.serialize(*this); }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args) { return process(args...); }
};

class Deserializer {
  std::istream& in_;

  private:
    template<class T>
    Error process(T&& value) { return fromStream(value); }

    template<class T, class... Args>
    Error process(T&& value, Args&&... args) {
      Error err = fromStream(value);
      if (err != Error::NoError) {
        return err;
      }
      return process(std::forward<Args>(args)...);
    }

    template <class T>
    Error fromStream(T /* value */) {
      return Error::CorruptedArchive;
    }

    Error fromStream(uint64_t& value);

    Error fromStream(bool& f);

  public:
    explicit Deserializer(std::istream& in): in_(in) {
    }

    template <class T>
    Error load(T& object) { return object.serialize(*this); }

    template <class... ArgsT>
    Error operator() (ArgsT&&... args) { return process(args...); }
};


#endif  // SERIALIZER_HPP_
