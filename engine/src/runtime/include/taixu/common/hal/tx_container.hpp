/**
 * @file tx_container.hpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-07-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "tx_allocator.hpp"

namespace taixu {

template<typename T>
using tx_vector = ::std::vector<T, txAllocatorT<T>>;

template<typename T>
using tx_deque = ::std::deque<T, txAllocatorT<T>>;

template<typename T>
using tx_list = ::std::list<T, txAllocatorT<T>>;

template<typename K, typename V, typename Pr = ::std::less<K>>
using tx_map = ::std::map<K, V, Pr, txAllocatorT<std::pair<const K, V>>>;

template<typename K, typename V, typename Pr = ::std::less<K>>
using tx_multimap = ::std::multimap<K, V, Pr, txAllocatorT<std::pair<const K, V>>>;

template<typename K, typename V, typename Hasher = ::std::hash<K>, typename KeyEq = std::equal_to<K>>
using tx_unordered_map = ::std::unordered_map<K, V, Hasher, KeyEq, txAllocatorT<std::pair<const K, V>>>;

template<typename K, typename V, typename Hasher = ::std::hash<K>, typename KeyEq = ::std::equal_to<K>>
using tx_unordered_multimap = ::std::unordered_multimap<K, V, Hasher, KeyEq, txAllocatorT<::std::pair<const K, V>>>;

template<typename T, typename Pr = ::std::less<T>>
using tx_set = ::std::set<T, Pr, txAllocatorT<T>>;

template<typename T, typename Pr = ::std::less<T>>
using tx_multiset = ::std::multiset<T, Pr, txAllocatorT<T>>;

template<typename T, typename Hasher = ::std::hash<T>, typename KeyEq = ::std::equal_to<T>>
using tx_unordered_set = ::std::unordered_set<T, Hasher, KeyEq, txAllocatorT<T>>;

}// namespace taixu
