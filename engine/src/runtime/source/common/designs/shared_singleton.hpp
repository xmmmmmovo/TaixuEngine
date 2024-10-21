/**
 * @file shared_singleton.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-10-17
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#define SINGLETON_DEFINATION(class_name) static class_name& instance();

#define SINGLETON_IMPLEMENTATION(class_name)                                                                           \
    class_name& class_name::instance() {                                                                               \
        static class_name instance;                                                                                    \
        return instance;                                                                                               \
    }
