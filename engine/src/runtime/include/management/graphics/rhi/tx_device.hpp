//
// Created by xmmmmmovo on 1/18/2024.
//

#ifndef TX_DEVICE_HPP_A1E5FEAC9CF2412B81B9B310A1E41EF9
#define TX_DEVICE_HPP_A1E5FEAC9CF2412B81B9B310A1E41EF9

#include "common/base/macro.hpp"
#include "gameplay/gui/window.hpp"

namespace taixu {

template<typename DeviceT, typename >
class TXDevice : private Noncopyable {
    PROTOTYPE_ONLY_GETTER_CONST(protected, DeviceT, device);

public:
    virtual void init(Window* window) = 0;
};

}// namespace taixu

#endif// TX_DEVICE_HPP_A1E5FEAC9CF2412B81B9B310A1E41EF9
