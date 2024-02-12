//
// Created by xmmmmmovo on 2/12/2024.
//

#pragma once

#include "management/graphics/rhi/tx_buffer.hpp"

namespace taixu {
class DX11Buffer final : public TXBuffer {
public:
  void map() override;
  void updateResource() override;
  void unmap() override;
};

}