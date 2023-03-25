//
// Created by xmmmmmovo on 2023/2/26.
//

#ifndef TAIXUENGINE_BUFFER_LAYOUT_HPP
#define TAIXUENGINE_BUFFER_LAYOUT_HPP

#include <glm/glm.hpp>
#include <string>
#include <utility>
#include <vector>

namespace taixu {

enum class AttributeType { POSITION = 3, COLOR = 3, NORMAL = 3, TEXCOORD = 2 };

struct BufferElement {
    std::string_view name;
    AttributeType    type;
};

class BufferLayout {
private:
    std::vector<BufferElement> elements{};

public:
    BufferLayout(std::initializer_list<BufferElement> const &element)
        : elements(element) {}

    std::vector<BufferElement> getElements() { return this->elements; }

    std::vector<BufferElement>::iterator begin() { return elements.begin(); }
    std::vector<BufferElement>::iterator end() { return elements.end(); }
    [[nodiscard]] std::vector<BufferElement>::const_iterator cbegin() const {
        return elements.cbegin();
    }
    [[nodiscard]] std::vector<BufferElement>::const_iterator cend() const {
        return elements.cend();
    }

    size_t size() { return elements.size(); }
};

}// namespace taixu

#endif//TAIXUENGINE_BUFFER_LAYOUT_HPP
