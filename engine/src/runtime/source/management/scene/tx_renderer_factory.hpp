/**
 * @file tx_renderer_factory.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-09-16
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "common/designs/abstract_factory.hpp"
#include "management/scene/tx_scene_renderer.hpp"
#include "taixu/common/base/core.hpp"

TX_NAMESPACE_BEGIN

class WindowFactory : public AbstractFactory<WindowAPI, TXSceneRenderer> {};

TX_NAMESPACE_END
