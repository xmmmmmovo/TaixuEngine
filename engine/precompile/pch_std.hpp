//
// Created by xmmmmmovo on 2023/7/22.
//

#pragma once

// C
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

// C++
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <complex>
#include <condition_variable>
#include <deque>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <set>
#include <shared_mutex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201703L
    #include <any>
    #include <charconv>
    #if __has_include(<execution>)
        #include <execution>
    #endif
    #include <filesystem>
    #include <memory_resource>
    #include <optional>
    #include <variant>
#endif

#if __cplusplus >= 202002L
    #include <barrier>
    #include <bit>
    #include <compare>
    #include <concepts>
    #include <format>
    #include <latch>
    #include <numbers>
    #include <ranges>
    #include <semaphore>
    #include <source_location>
    #include <span>
    #include <stop_token>
    #if __has_include(<syncstream>)
        #include <syncstream>
    #endif
    #include <version>
#endif

#if __cplusplus >= 202302L
    #include <expected>
    #include <spanstream>
    #if __has_include(<stacktrace>)
        #include <stacktrace>
    #endif
    #include <stdatomic.h>
    #include <stdfloat>
#endif
