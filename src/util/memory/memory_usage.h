#ifndef STDCHAIN_UTIL_MEMORY_USAGE_H
#define STDCHAIN_UTIL_MEMORY_USAGE_H

#include <map>
#include <memory>
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace util::memory {
    static inline size_t mallocUsage(size_t alloc) {
        if (alloc == 0)
            return 0;
        return ((alloc + 31) >> 4) << 4;
    }

    static inline size_t dynamicUsage(const int8_t &v) { return 0; }
    static inline size_t dynamicUsage(const uint8_t &v) { return 0; }
    static inline size_t dynamicUsage(const int16_t &v) { return 0; }
    static inline size_t dynamicUsage(const uint16_t &v) { return 0; }
    static inline size_t dynamicUsage(const int32_t &v) { return 0; }
    static inline size_t dynamicUsage(const uint32_t &v) { return 0; }
    static inline size_t dynamicUsage(const int64_t &v) { return 0; }
    static inline size_t dynamicUsage(const uint64_t &v) { return 0; }
    static inline size_t dynamicUsage(const float &v) { return 0; }
    static inline size_t dynamicUsage(const double &v) { return 0; }

    template<typename X> static inline size_t dynamicUsage(X *const &v) { return 0; }
    template<typename X> static inline size_t dynamicUsage(const X *const &v) { return 0; }

    template<typename X>
    struct STLTreeNode {
    private:
        int color;
        void *parent;
        void *left;
        void *right;
        X x;
    };

    struct STLSharedCounter {
        void *classType;
        size_t useCount;
        size_t weakCount;
    };

    template<typename X>
    struct UnorderedNode : private X {
    private:
        void *ptr;
    };

    template<typename X>
    static inline size_t dynamicUsage(const std::vector<X> &vec) {
        return mallocUsage(vec.capacity() * sizeof(X));
    }

    template<typename X, typename Y>
    static inline size_t dynamicUsage(const std::set<X, Y> &set) {
        return mallocUsage(sizeof(STLTreeNode<X>)) * set.size();
    }

    template<typename X, typename Y>
    static inline size_t incrementalDynamicUsage(const std::set<X, Y> &set) {
        return mallocUsage(sizeof(STLTreeNode<X>));
    }

    template<typename X, typename Y, typename Z>
    static inline size_t dynamicUsage(const std::map<X, Y, Z> &map) {
        return mallocUsage(sizeof(STLTreeNode<std::pair<const X, Y>>)) * map.size();
    }

    template<typename X, typename Y, typename Z>
    static inline size_t incrementalDynamicUsage(const std::map<X, Y, Z> &map) {
        return mallocUsage(sizeof(STLTreeNode<std::pair<const X, Y>>));
    }

    template<typename X>
    static inline size_t dynamicUsage(const std::unique_ptr<X> &ptr) {
        return ptr ? mallocUsage(sizeof(X)) : 0;
    }

    template<typename X>
    static inline size_t dynamicUsage(const std::shared_ptr<X> &ptr) {
        return ptr ? mallocUsage(sizeof(X)) + mallocUsage(sizeof(STLSharedCounter)) : 0;
    }

    template<typename X, typename Y>
    static inline size_t dynamicUsage(const std::unordered_set<X, Y> &set) {
        return mallocUsage(sizeof(UnorderedNode<X>)) * set.size() + mallocUsage(sizeof(void *) * set.bucket_count());
    }

    template<typename X, typename Y, typename Z>
    static inline size_t dynamicUsage(const std::unordered_map<X, Y, Z> &map) {
        return mallocUsage(sizeof(UnorderedNode<std::pair<const X, Y>>)) * map.size() +
               mallocUsage(sizeof(void *) * map.bucket_count());
    }
} // namespace util::memory

#endif //STDCHAIN_UTIL_MEMORY_USAGE_H