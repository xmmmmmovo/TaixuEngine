#ifndef TAIXUENGINE_MESH_COMPONENT
#define TAIXUENGINE_MESH_COMPONENT

#include "../entity_component.hpp"
#include "graphics/render/model.hpp"
#include "graphics/render_context.hpp"
#include "graphics/renderer.hpp"
#include "resource/ecs/entity_component/camera/camera_component.hpp"
#include "resource/ecs/entity_component/entity_component.hpp"
#include "resource/ecs/entity_component/transform/transform_component.hpp"
#include <optional>
#include <string>

namespace taixu {
class MeshComponent : public EntityComponent {
public:
    MeshComponent(bool renderable, std::uint32_t guid, std::string path1,
                  std::string path2)
        : visible(renderable), GO(guid), mesh_path(path1),
          material_path(path2) {}
    //std::string name{};
    bool                           visible;
    std::uint32_t                  GO;
    std::string                    mesh_path{"INVALID"};
    std::string                    material_path{"INVALID"};
    IGraphicsContext              *data_target;
    std::uint32_t                  getGO() override { return GO; };
    TransformComponent            *transform_component;
    std::optional<CameraComponent> camera_component;
    void                           initialize();
    void                           tick() override;
};
}// namespace taixu

#endif /* TAIXUENGINE_MESH_COMPONENT */
