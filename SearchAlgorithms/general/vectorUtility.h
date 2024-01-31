#ifndef VECTOR_UTIL_DOT_H
#define VECTOR_UTIL_DOT_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <map>

using namespace std;

namespace vecUtil {

    template <typename T>
    ostream& operator << (ostream& out, const vector<T>& v) {
        if (v.empty()) {
            out << "[]";
            return out;
        }
        out << "[";
        for (int i = 0; i < v.size() - 1; i++) {
            out << v.at(i) << ", ";
        }
        out << v.back() << "]";
        return out;
    }

    template <typename T>
    bool contains(const vector<T>& v, const T& t) {
        for (const T& e : v) {
            if (e == t) {
                return true;
            }
        }
        return false;
    }

    template <typename T>
    bool strictlyIncreasing(const vector<T>& v) {
        if (v.size() <= 1) {
            return true;
        }
        bool result = true;
        for (int i = 0; i < v.size() - 1; i++) {
            result = result && (v.at(i) < v.at(i + 1));
        }
        return result;
    }

    template <typename T>
    bool strictlyDecreasing(const vector<T>& v) {
        if (v.size() <= 1) {
            return true;
        }
        bool result = true;
        for (int i = 0; i < v.size() - 1; i++) {
            result = result && (v.at(i) > v.at(i + 1));
        }
        return result;
    }

    template <typename T>
    bool generallyIncreasing(const vector<T>& v) {
        if (v.size() <= 1) {
            return true;
        }
        bool result = true;
        for (int i = 0; i < v.size() - 1; i++) {
            result = result && (v.at(i) <= v.at(i + 1));
        }
        return result;
    }

    template <typename T>
    bool generallyDecreasing(const vector<T>& v) {
        if (v.size() <= 1) {
            return true;
        }
        bool result = true;
        for (int i = 0; i < v.size() - 1; i++) {
            result = result && (v.at(i) >= v.at(i + 1));
        }
        return result;
    }

    template <typename T>
    bool allEqual(const vector<T>& v) {
        if (v.size() <= 1) {
            return true;
        }
        bool result = true;
        for (int i = 0; i < v.size() - 1; i++) {
            result = result && (v.at(i) == v.at(i + 1));
        }
        return result;
    }

    template <typename T>
    bool atLeast1NotEqual(const vector<T>& v) {
        return !allEqual(v);
    }

    // inserts e into v at index pos, so that v.at(pos) == e after the insert
    template <typename T>
    void insertAtPos(vector<T>& v, int pos, const T& e) {
        vector<T> newVector;
        for (int i = 0; i < pos; i++) {
            newVector.push_back(v.at(i));
        }
        newVector.push_back(e);
        for (int i = pos; i < v.size(); i++) {
            newVector.push_back(v.at(i));
        }
        v = newVector;
    }

    // splices the elements of spliceInput into v at index pos, so that v.at(pos) == spliceInput.at(0) after the splice
    template <typename T>
    void spliceAtPos(vector<T>& v, int pos, const vector<T>& spliceInput) {
        vector<T> newVector;
        for (int i = 0; i < pos; i++) {
            newVector.push_back(v.at(i));
        }
        for (int i = 0; i < spliceInput.size(); i++) {
            newVector.push_back(spliceInput.at(i));
        }
        for (int i = pos; i < v.size(); i++) {
            newVector.push_back(v.at(i));
        }
        v = newVector;
    }

    // removes the first instance of e from v
    template <typename T>
    void removeFirstInstance(vector<T>& v, const T& e) {
        vector<T> newVector;
        int pos;
        for (pos = 0; pos < v.size(); pos++) {
            if (v.at(pos) == e) {
                // do not append onto newVector
                pos++;
                break;
            } else {
                newVector.push_back(v.at(pos));
            }
        }
        for (int i = pos; i < v.size(); i++) {
            newVector.push_back(v.at(i));
        }
        v = newVector;
    }

    // removes all instances of e from v
    template <typename T>
    void removeAllInstances(vector<T>& v, const T& e) {
        vector<T> newVector;
        for (const T& t : v) {
            if (t != e) {
                newVector.push_back(t);
            }
        }
        v = newVector;
    }

    template <typename T>
    int findIndex(const vector<T>& v, const T& e) {
        for (int i = 0; i < v.size(); i++) {
            if (v.at(i) == e) {
                return i;
            }
        }
        return -1;
    }

    template <typename T>
    void removeByIndex(vector<T>& v, int index) {
        vector<T> newVector;
        for (int i = 0; i < v.size(); i++) {
            if (i != index) {
                newVector.push_back(v.at(i));
            }
        }
        v = newVector;
    }

    template <typename T>
    void removeByIndexes(vector<T>& v, const vector<int>& indexes) {
        vector<T> newVector;
        for (int i = 0; i < v.size(); i++) {
            if (!contains(indexes, i)) {
                newVector.push_back(v.at(i));
            }
        }
        v = newVector;
    }

    // given a vector of vectors, return a single vector that combines all the individual smaller vectors together
    template <typename T>
    vector<T> concatenate(const vector<vector<T>> vectors) {
        vector<T> nv;
        for (const vector<T>& v : vectors) {
            for (int i = 0; i < v.size(); i++) {
                nv.push_back(v.at(i));
            }
        }
        return nv;
    }

    // given a vector v, return the portion of v that is v[startIndex..endIndex]
    template <typename T>
    vector<T> subvector(const vector<T>& v, int startIndex, int endIndex) {
        vector<T> nv;
        for (int i = startIndex; i <= endIndex; i++) {
            nv.push_back(v.at(i));
        }
        return nv;
    }

    template <typename T>
    vector<T> reverse(const vector<T>& v) {
        vector<T> reversed = v;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }

    template <typename T>
    vector<T> sort(const vector<T>& v) {
        vector<T> sorted = v;
        std::sort(sorted.begin(), sorted.end());
        return sorted;
    }

    template <typename T>
    void insertNoDuplicate(vector<T>& v, const T& e) {
        if (!contains(v, e)) {
            v.push_back(e);
        }
    }

    template <typename T>
    vector<T> removeDuplicate(const vector<T>& v) {
        vector<T> noDup;
        for (const T& element : v) {
            insertNoDuplicate(noDup, element);
        }
        return noDup;
    }

    // returns the number of distinct elements in v
    template <typename T>
    int sizeDistinct(const vector<T>& v) {
        return removeDuplicate(v).size();
    }

    // reorders the given vector by inserting its elements into the result in the order given by the indexes
    // ex. reorderByInsertionOrder({a, b, c, d, e}, {2, 4, 3, 0, 1}) -> {c, e, d, a, b}
    // interp. "push back old[2] = c, then push back old[4] = e, then push back old[3] = d, etc."
    // interp. "old[2] -> result[0], old[4] -> result[1], old[3] -> result[2], etc."
    template <typename T>
    const vector<T> reorderByInsertionOrder(const vector<T>& old, const vector<int>& order) {
        vector<T> result;
        for (int index : order) {
            result.push_back(old.at(index));
        }
        return result;
    }

    // reorders the given vector by inserting its elements into the index of result specified by the given order
    // ex. reorderByNewPosition({a, b, c, d, e}, {2, 4, 3, 0, 1}) -> {d, e, a, c, b}
    // interp. "a is now result[2], b is now result[4], c is now result[3], etc."
    // interp. "old[0] -> result[2], old[1] -> result[4], old[2] -> result[3], etc."
    template <typename T>
    const vector<T> reorderByNewPosition(const vector<T>& old, const vector<int>& order) {
        vector<T> result;
        map<int, int> indexMap;
        for (int i = 0; i < order.size(); i++) {
            indexMap.insert({order.at(i), i});
        }
        for (int i = 0; i < old.size(); i++) {
            result.push_back(old.at(indexMap.at(i)));
        }
        return result;
    }

    // gets the ordering indexes that reorder the old vector into the ordering vector by order of insertions
    // ex. getOrderIndexesByInsertionOrder({a, b, c, d, e}, {c, e, d, a, b}) -> {2, 4, 3, 0, 1}
    // interp. "2 is the index of c in old, 4 is the index of e in old, 3 is the index of d in old, etc."
    // interp. "index of order[0] in old is 2, index of order[1] in old is 4, index of order[2] in old is 3, etc."
    // this is the inverse function of reorderByInsertionOrder
    template <typename T>
    const vector<int> getOrderIndexesByInsertionOrder(const vector<T>& old, const vector<T>& order) {
        vector<int> result;
        map<T, int> indexMap;
        for (int i = 0; i < old.size(); i++) {
            indexMap.insert({old.at(i), i});
        }
        for (const T& element : order) {
            result.push_back(indexMap.at(element));
        }
        return result;
    }

    // gets the ordering indexes that reorder the old vector into the ordering vector by new positions
    // ex. getOrderIndexesByNewPosition({a, b, c, d, e}, {d, e, a, c, b}) -> {2, 4, 3, 0, 1})
    // interp. "2 is the index of a in order, 4 is the index of b in order, 3 is the index of c in order, etc."
    // interp. "index of old[0] in order is 2, index of old[1] in order is 4, index of old[2] in order is 3, etc."
    // this is the inverse function of reorderByNewPosition
    template <typename T>
    const vector<int> getOrderIndexesByNewPosition(const vector<T>& old, const vector<T>& order) {
        vector<int> result;
        map<T, int> indexMap;
        for (int i = 0; i < order.size(); i++) {
            indexMap.insert({order.at(i), i});
        }
        for (const T& element : old) {
            result.push_back(indexMap.at(element));
        }
        return result;
    }

}

#endif