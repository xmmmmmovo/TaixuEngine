#include "Jolt_utilities.hpp"

namespace taixu {
BPLayerInterfaceImpl::BPLayerInterfaceImpl() {
    // Create a mapping table from object to broad phase layer
    m_object_to_broad_phase[layers::UNUSED1]    = BroadPhaseLayers::UNUSED;
    m_object_to_broad_phase[layers::UNUSED2]    = BroadPhaseLayers::UNUSED;
    m_object_to_broad_phase[layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
    m_object_to_broad_phase[layers::MOVING]     = BroadPhaseLayers::MOVING;
}

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
const char *BPLayerInterfaceImpl::GetBroadPhaseLayerName(
        JPH::BroadPhaseLayer inLayer) const {
    switch ((JPH::BroadPhaseLayer::Type) inLayer) {
        case (JPH::BroadPhaseLayer::Type) BroadPhaseLayers::NON_MOVING:
            return "NON_MOVING";
        case (JPH::BroadPhaseLayer::Type) BroadPhaseLayers::MOVING:
            return "MOVING";
        case (JPH::BroadPhaseLayer::Type) BroadPhaseLayers::UNUSED:
            return "UNUSED";
        default:
            assert(false);
            return "INVALID";
    }
}
#endif// JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

bool ObjectvsObjectCollide(JPH::ObjectLayer inObject1,
                           JPH::ObjectLayer inObject2) {
    switch (inObject1) {
        case layers::UNUSED1:
        case layers::UNUSED2:
            return false;
        case layers::NON_MOVING:
            return inObject2 == layers::MOVING;
        case layers::MOVING:
            return inObject2 == layers::NON_MOVING ||
                   inObject2 == layers::MOVING;
        default:
            assert(false);
            return false;
    }
}

bool ObjectvsBroadPhaseCanCollide(JPH::ObjectLayer     inLayer1,
                                  JPH::BroadPhaseLayer inLayer2) {
    switch (inLayer1) {
        case layers::NON_MOVING:
            return inLayer2 == BroadPhaseLayers::MOVING;
        case layers::MOVING:
            return inLayer2 == BroadPhaseLayers::NON_MOVING ||
                   inLayer2 == BroadPhaseLayers::MOVING;
        default:
            assert(false);
            return false;
    }
}

}// namespace taixu