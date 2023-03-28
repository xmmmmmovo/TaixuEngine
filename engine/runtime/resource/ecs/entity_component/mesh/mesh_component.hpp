#ifndef TAIXUENGINE_MESH_COMPONENT
#define TAIXUENGINE_MESH_COMPONENT

#include <string>
#include "../entity_component.hpp"
#include "graphics/render/model.hpp"
#include "graphics/renderer.hpp"
#include "resource/ecs/entity_component/entity_component.hpp"

namespace taixu
{
class MeshComponent:public EntityComponent
{
public:
MeshComponent(bool renderable,std::string path1,std::string path2)
:visible(renderable),mesh_path(path1),material_path(path2){}
//std::string name{};
bool visible;
std::string mesh_path{"INVALID"};
std::string material_path{"INVALID"};
std::shared_ptr<Model_Data>model;
//std::weak_ptr<Render_Context>data_target;
void loadModelData();
void tick();
};
}

#endif /* TAIXUENGINE_MESH_COMPONENT */
