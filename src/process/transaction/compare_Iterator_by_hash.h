#ifndef STDCHAIN_PROCESS_TRANSACTION_COMPARE_ITERATOR_BY_HASH_H
#define STDCHAIN_PROCESS_TRANSACTION_COMPARE_ITERATOR_BY_HASH_H

#include <type_traits>

// SFINAE for T where T is either a pointer type or a std::reference_wrapper<T>
struct CompareIteratorByHash {

    template<typename T>
    bool operator()(const std::reference_wrapper<T> &a, const std::reference_wrapper<T> &b) const;

    template<typename T>
    bool operator()(const T &a, const T &b) const;

};

template<typename T>
bool CompareIteratorByHash::operator()(const std::reference_wrapper<T> &a, const std::reference_wrapper<T> &b) const {
    return a.get().getTx().getHash() < b.get().getTx().getHash();
}

template<typename T>
bool CompareIteratorByHash::operator()(const T &a, const T &b) const {
    return a->getTx().getHash() < b->getTx().getHash();
}

#endif //STDCHAIN_PROCESS_TRANSACTION_COMPARE_ITERATOR_BY_HASH_H
