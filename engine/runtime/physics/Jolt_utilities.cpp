#include "physics/Jolt_utilities.hpp"

namespace taixu
{
BPLayerInterfaceImpl::BPLayerInterfaceImpl()
    {
        // Create a mapping table from object to broad phase layer
        m_object_to_broad_phase[Layers::UNUSED1]    = BroadPhaseLayers::UNUSED;
        m_object_to_broad_phase[Layers::UNUSED2]    = BroadPhaseLayers::UNUSED;
        m_object_to_broad_phase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
        m_object_to_broad_phase[Layers::MOVING]     = BroadPhaseLayers::MOVING;

    }

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
    const char* BPLayerInterfaceImpl::GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const
    {
        switch ((JPH::BroadPhaseLayer::Type)inLayer)
        {
            case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:
                return "NON_MOVING";
            case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:
                return "MOVING";
            case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::UNUSED:
                return "UNUSED";
            default:
                assert(false);
                return "INVALID";
        }
    }
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

    bool ObjectvsObjectCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2)
    {
        switch (inObject1)
        {
            case Layers::UNUSED1:
            case Layers::UNUSED2:
                return false;
            case Layers::NON_MOVING:
                return inObject2 == Layers::MOVING;
            case Layers::MOVING:
                return inObject2 == Layers::NON_MOVING || inObject2 == Layers::MOVING;
            default:
                assert(false);
                return false;
        }
    }

    bool ObjectvsBroadPhaseCanCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2)
    {
        switch (inLayer1)
        {
            case Layers::NON_MOVING:
                return inLayer2 == BroadPhaseLayers::MOVING;
            case Layers::MOVING:
                return inLayer2 == BroadPhaseLayers::NON_MOVING || inLayer2 == BroadPhaseLayers::MOVING;
            default:
                assert(false);
                return false;
        }
    }

}