#ifndef TAIXUENGINE_JOLT_UTILITIES
#define TAIXUENGINE_JOLT_UTILITIES

#include "Jolt/Jolt.h"

// Jolt includes
#include "Jolt/Core/Factory.h"
#include "Jolt/Core/JobSystemThreadPool.h"
#include "Jolt/Core/TempAllocator.h"
#include "Jolt/Physics/Body/BodyActivationListener.h"
#include "Jolt/Physics/Body/BodyCreationSettings.h"
#include "Jolt/Physics/Collision/Shape/BoxShape.h"
#include "Jolt/Physics/Collision/Shape/SphereShape.h"
#include "Jolt/Physics/PhysicsSettings.h"
#include "Jolt/Physics/PhysicsSystem.h"
#include "Jolt/RegisterTypes.h"

#include "spdlog/spdlog.h"

namespace taixu {
namespace layers {
    static constexpr uint8_t UNUSED1 =
            0;// 2 unused values so that broadphase layers values don't match with
              // object layer values (otherwise redefiend error)
    static constexpr uint8_t UNUSED2    = 1;
    static constexpr uint8_t NON_MOVING = 2;
    static constexpr uint8_t MOVING     = 3;
    static constexpr uint8_t NUM_LAYERS = 4;
};// namespace layers

/// Broadphase layers
namespace BroadPhaseLayers {
    static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
    static constexpr JPH::BroadPhaseLayer MOVING(1);
    static constexpr JPH::BroadPhaseLayer UNUSED(2);
    static constexpr uint32_t             NUM_LAYERS(3);
};// namespace BroadPhaseLayers

/// BroadPhaseLayerInterface implementation
class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface {
public:
    BPLayerInterfaceImpl();

    [[nodiscard]] std::uint32_t GetNumBroadPhaseLayers() const override {
        return BroadPhaseLayers::NUM_LAYERS;
    }

    [[nodiscard]] JPH::BroadPhaseLayer
    GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override {
        assert(inLayer < layers::NUM_LAYERS);
        return m_object_to_broad_phase[inLayer];
    }

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
    [[nodiscard]] const char *
    GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const override;
#endif// JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

private:
    JPH::BroadPhaseLayer m_object_to_broad_phase[layers::NUM_LAYERS];
};

using namespace JPH;

class MyContactListener : public JPH::ContactListener {
public:
    // See: ContactListener
    ValidateResult
    OnContactValidate(const Body &inBody1, const Body &inBody2,
                      Vec3Arg                   inBaseOffset,
                      const CollideShapeResult &inCollisionResult) override {
        //std::cout << "Contact validate callback" << std::endl;
        spdlog::debug("Contact validate callback");

        // Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
        return ValidateResult::AcceptAllContactsForThisBodyPair;
    }

    void OnContactAdded(const Body &inBody1, const Body &inBody2,
                        const ContactManifold &inManifold,
                        ContactSettings       &ioSettings) override {
        //cout << "A contact was added" << endl;
        spdlog::debug("A contact was added");
    }

    void OnContactPersisted(const Body &inBody1, const Body &inBody2,
                            const ContactManifold &inManifold,
                            ContactSettings       &ioSettings) override {
        //cout << "A contact was persisted" << endl;
        spdlog::debug("A contact was persisted");
    }

    void OnContactRemoved(const SubShapeIDPair &inSubShapePair) override {
        //cout << "A contact was removed" << endl;
        spdlog::debug("A contact was removed");
    }
};

// An example activation listener
class MyBodyActivationListener : public BodyActivationListener {
public:
    void OnBodyActivated(const BodyID &inBodyID,
                         uint64        inBodyUserData) override {
        //cout << "A body got activated" << endl;
        spdlog::debug("A body got activated");
    }

    void OnBodyDeactivated(const BodyID &inBodyID,
                           uint64        inBodyUserData) override {
        //cout << "A body went to sleep" << endl;
        spdlog::debug("A body went to sleep");
    }
};

/// Class that determines if two object layers can collide
class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter {
public:
    [[nodiscard]] bool ShouldCollide(ObjectLayer inObject1,
                                     ObjectLayer inObject2) const override {
        switch (inObject1) {
            case layers::UNUSED1:
            case layers::UNUSED2:
                return false;
            case layers::NON_MOVING:
                return inObject2 == layers::MOVING;
            case layers::MOVING:
                return inObject2 == layers::NON_MOVING ||
                       inObject2 == layers::MOVING;
            default: {
                spdlog::debug("IVALID");
                assert(false);
                return false;
            }
        }
    }
};

class ObjectVsBroadPhaseLayerFilterImpl : public ObjectVsBroadPhaseLayerFilter {
public:
    bool ShouldCollide(ObjectLayer     inLayer1,
                       BroadPhaseLayer inLayer2) const override {
        switch (inLayer1) {
            case layers::NON_MOVING:
                return inLayer2 == BroadPhaseLayers::MOVING;
            case layers::MOVING:
                return inLayer2 == BroadPhaseLayers::NON_MOVING ||
                       inLayer2 == BroadPhaseLayers::MOVING;
            default: {
                spdlog::debug("IVALID");
                assert(false);
                return false;
            }
        }
    }
};

}// namespace taixu

#endif /* TAIXUENGINE_JOLT_UTILITIES */
