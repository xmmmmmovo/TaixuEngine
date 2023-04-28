#ifndef TAIXUENGINE_ENTITY_COMPONENT
#define TAIXUENGINE_ENTITY_COMPONENT

#include <cstdint>
#include <typeinfo>
#include <unordered_map>

#include "core/base/macro.hpp"

namespace taixu {

class AbstractEntityComponent {
    PROTOTYPE_DFT_ONLY_GETTER(protected, std::uint32_t, GO, 0);

public:
    virtual void tick()                = 0;
    virtual ~AbstractEntityComponent() = default;
};

}// namespace taixu
#endif /* TAIXUENGINE_ENTITY_COMPONENT */
