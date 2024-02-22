//
// Created by xmmmmmovo on 1/19/2024.
//

#ifndef TX_CONTEXT_HPP_E44E4790097B4E56BFBC9C093EEB4AD1
#define TX_CONTEXT_HPP_E44E4790097B4E56BFBC9C093EEB4AD1

#include "common/base/macro.hpp"
#include "common/designs/noncopyable.hpp"

namespace taixu {

class TXContext : Noncopyable {
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, uint32_t, major_version, 0);
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, uint32_t, minor_version, 0);

    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, uint32_t, max_fps, 60);

    PROTOTYPE_DFT_VALPASS(protected, bool, enable_msaa, false);

    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, uint32_t, msaa_best_count, 0);
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, uint32_t, msaa_best_qualities,
                                      0);
};

}// namespace taixu

#endif// TX_CONTEXT_HPP_E44E4790097B4E56BFBC9C093EEB4AD1
