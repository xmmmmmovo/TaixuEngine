#ifndef TAIXUENGINE_MESH_COMPONENT
#define TAIXUENGINE_MESH_COMPONENT

#include <string>
#include "../entity_component.hpp"
namespace taixu
{
class MeshComponent:public EntityComponent
{
public:
MeshComponent(bool renderable,std::string path1,std::string path2)
:visible(renderable),mesh_path(path1),material_path(path2){}
//std::string name{};
bool visible;
std::string mesh_path;
std::string material_path;
};
}

#endif /* TAIXUENGINE_MESH_COMPONENT */
