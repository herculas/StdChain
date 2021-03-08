#ifndef STDCHAIN_TYPE_STREAM_WRAPPER_H
#define STDCHAIN_TYPE_STREAM_WRAPPER_H

#include <type_traits>

template<typename Formatter, typename T>
class Wrapper {

    static_assert(std::is_lvalue_reference<T>::value, "Wrapper needs an lvalue reference type T.");

protected:
    T object;

public:
    explicit Wrapper(T object);

    template<typename Stream>
    void serialize(Stream &stream) const;
    template<typename Stream>
    void deserialize(Stream &stream);

};

template<typename Formatter, typename T>
Wrapper<Formatter, T>::Wrapper(T object): object(object) {}

template<typename Formatter, typename T>
template<typename Stream>
void Wrapper<Formatter, T>::serialize(Stream &stream) const {
    Formatter().serialize(stream, this->object);
}

template<typename Formatter, typename T>
template<typename Stream>
void Wrapper<Formatter, T>::deserialize(Stream &stream) {
    Formatter().deserialize(stream, this->object);
}

template<typename Formatter, typename T>
static inline Wrapper<Formatter, T &> usingWrapper(T &&t) {
    return Wrapper<Formatter, T &>(t);
}

#endif //STDCHAIN_TYPE_STREAM_WRAPPER_H
