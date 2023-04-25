#ifndef TAIXUENGINE_MESH_COMPONENT
#define TAIXUENGINE_MESH_COMPONENT

#include "management/ecs/entity_component/camera/camera_component.hpp"
#include "management/ecs/entity_component/entity_component.hpp"
#include "management/ecs/entity_component/transform/transform_component.hpp"
#include "management/graphics/renderer.hpp"
#include <cstdint>
#include <optional>
#include <string>

namespace taixu {
class MeshComponent : public EntityComponent {
    PROTOTYPE_DFT(private, std::uint32_t, GO, 0);

public:
    MeshComponent(bool renderable, std::uint32_t guid, std::string path1,
                  std::string path2)
        : visible(renderable), _GO(guid), mesh_path(path1),
          material_path(path2) {}
    bool                           visible;
    std::string                    mesh_path{"INVALID"};
    std::string                    material_path{"INVALID"};
    TransformComponent            *transform_component{};
    std::optional<CameraComponent> camera_component;
    void                           initialize();
    void                           tick() override;
};

}// namespace taixu

#endif /* TAIXUENGINE_MESH_COMPONENT */
