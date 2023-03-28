#include "mesh_component.hpp"
#include "graphics/renderer.hpp"

namespace taixu
{


void MeshComponent::loadModelData() 
{
    assert(mesh_path!="INVALID");
    model=std::make_shared<Model_Data>(mesh_path.c_str());
}

void MeshComponent::tick() 
{
    // assert(data_target.expired());
    // data_target.lock()->getSwapContext()->model=model;
}

}// namespace taixu