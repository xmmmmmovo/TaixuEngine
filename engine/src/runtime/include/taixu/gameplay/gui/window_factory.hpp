/**
 * @file window_factory.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-09-16
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "taixu/common/base/core.hpp"
#include "taixu/common/designs/abstract_factory.hpp"
#include "taixu/gameplay/gui/window.hpp"

TX_NAMESPACE_BEGIN

class WindowFactory : public AbstractFactory<WindowAPI, Window, WindowInfo> {};

TX_NAMESPACE_END
