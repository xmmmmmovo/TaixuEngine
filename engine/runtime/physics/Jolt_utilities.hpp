#ifndef TAIXUENGINE_JOLT_UTILITIES
#define TAIXUENGINE_JOLT_UTILITIES

// #include "core/base/macro.hpp"
// #include "Jolt/Jolt.h"
// #include "Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h"

#include <Jolt/Jolt.h>

// Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
namespace taixu
{
    namespace Layers
    {
        static constexpr uint8_t UNUSED1 = 0; // 2 unused values so that broadphase layers values don't match with
                                              // object layer values (otherwise redefiend error)
        static constexpr uint8_t UNUSED2    = 1;
        static constexpr uint8_t NON_MOVING = 2;
	    static constexpr uint8_t MOVING = 3;
	    static constexpr uint8_t NUM_LAYERS = 4;
    }; 

    /// Broadphase layers
    namespace BroadPhaseLayers
    {
        static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
        static constexpr JPH::BroadPhaseLayer MOVING(1);
        static constexpr JPH::BroadPhaseLayer UNUSED(3);
        static constexpr uint32_t             NUM_LAYERS(2);
    }; 

    /// BroadPhaseLayerInterface implementation
    class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface
    {
    public:
        BPLayerInterfaceImpl();

        uint32_t GetNumBroadPhaseLayers() const override { return BroadPhaseLayers::NUM_LAYERS; }

        JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override
        {
            assert(inLayer < Layers::NUM_LAYERS);
            return m_object_to_broad_phase[inLayer];
        }

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
        const char* GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const override;
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

    private:
        JPH::BroadPhaseLayer m_object_to_broad_phase[Layers::NUM_LAYERS];
    };

    /// Function that determines if two object layers can collide
    bool ObjectvsObjectCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2);

    /// Function that determines if two broadphase layers can collide
    bool ObjectvsBroadPhaseCanCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2);

    



}

#endif /* TAIXUENGINE_JOLT_UTILITIES */
