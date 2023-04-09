#include "mesh_component.hpp"
#include "graphics/renderer.hpp"

namespace taixu
{


void MeshComponent::loadModelData() 
{
    assert(mesh_path!="INVALID");
    //model=std::make_shared<Model_Data>(mesh_path.c_str());
    //int a=0;
    //model.loadModel(mesh_path.c_str());

}

void MeshComponent::tick() 
{
    //assert(data_target.expired());
    if(visible==true)
    {
        
        //data_target.lock()->getSwapContext()->sphere=model;
        //data_target.lock()->sphere_context->vertex_array->clear();
        //data_target.lock()->bindMesh(data_target.lock()->getSwapContext()->sphere->meshes[0],"sphere");
        //transform_component->setPosition(glm::vec3(2.0f,2.0f,2.0f));
        //transform_component->makeTransformMatrix();
        //data_target.lock()->Transform = std::move(transform_component->transform);
        
        ////camera
        // if(camera_component.has_value())
        //     data_target.lock()->_camera=(*camera_component).character_camera.get();
    }
    
    //data_target.lock()->getSwapContext()->model=model;
    //int a=0;
}

}// namespace taixu