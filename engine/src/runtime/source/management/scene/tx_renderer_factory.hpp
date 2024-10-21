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

#include "management/scene/tx_scene_renderer.hpp"
#include "taixu/common/base/core.hpp"
#include "taixu/common/designs/abstract_factory.hpp"

TX_NAMESPACE_BEGIN

class WindowFactory : public AbstractFactory<RenderAPI, TXSceneRenderer> {};

TX_NAMESPACE_END
