#pragma once

#include <vector>
#include <algorithm>
#include <initializer_list>

namespace G3D {

template<typename T>
class Array {
public:
    std::vector<T> data;

    Array() = default;
    Array(std::initializer_list<T> init) : data(init) {}

    // Assignment from std::vector — the engine does things like
    //     G3D::Array<const Primitive*> tempIgnore;
    //     tempIgnore = *ignorePrim;   // *ignorePrim is std::vector<...>
    Array& operator=(const std::vector<T>& v) {
        data = v;
        return *this;
    }

    // ── Size / capacity ─────────────────────────────────────────────────
    int size() const { return static_cast<int>(data.size()); }
    int length() const { return size(); }
    bool empty() const { return data.empty(); }

    void resize(int n) { data.resize(n); }
    void resize(int n, const T& value) { data.resize(n, value); }
    void clear() { data.clear(); }
    void fastClear() { data.clear(); }

    void reserve(int n) { data.reserve(n); }

    // ── Access ──────────────────────────────────────────────────────────
    T& operator[](int i) { return data[i]; }
    const T& operator[](int i) const { return data[i]; }

    T& last() { return data.back(); }
    const T& last() const { return data.back(); }

    T& first() { return data.front(); }
    const T& first() const { return data.front(); }

    // ── Append ──────────────────────────────────────────────────────────
    void append(const T& x) { data.push_back(x); }
    void fastAppend(const T& x) { data.push_back(x); }
    void push_back(const T& x) { data.push_back(x); }

    template<typename It>
    void append(It first, It last) { data.insert(data.end(), first, last); }

    // ── Remove ──────────────────────────────────────────────────────────
    // fastRemove swaps with the last element (unordered). Matches G3D.
    void fastRemove(const T& x) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i] == x) {
                data[i] = data.back();
                data.pop_back();
                return;
            }
        }
    }

    // remove preserves order.
    void remove(const T& x) {
        auto it = std::find(data.begin(), data.end(), x);
        if (it != data.end()) data.erase(it);
    }

    void pop_back() { data.pop_back(); }

    // ── Search ──────────────────────────────────────────────────────────
    bool contains(const T& x) const {
        return std::find(data.begin(), data.end(), x) != data.end();
    }

    // G3D's Array::find returns an ITERATOR, not an index.
    // util/indexarray.h compares it against .end().
    auto find(const T& x) {
        return std::find(data.begin(), data.end(), x);
    }
    auto find(const T& x) const {
        return std::find(data.begin(), data.end(), x);
    }

    // ── Iteration ───────────────────────────────────────────────────────
    auto begin() { return data.begin(); }
    auto end()   { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end()   const { return data.end(); }
    auto cbegin() const { return data.cbegin(); }
    auto cend()   const { return data.cend(); }

    // ── Operators ───────────────────────────────────────────────────────
    bool operator==(const Array& o) const { return data == o.data; }
    bool operator!=(const Array& o) const { return !(*this == o); }
};

} // namespace G3D