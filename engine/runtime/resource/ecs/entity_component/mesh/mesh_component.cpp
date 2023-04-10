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
        transform_component->makeTransformMatrix();
        RenderableModelInfo sphere;
        
        sphere.file_path = mesh_path.c_str();
        sphere.GO = GO;
        sphere.transform_matrix = transform_component->transform;
        sphere.opt = oprationType::ADD;
        data_target.lock()->getSwapContext()->dirty_models.push_back(sphere);

        
        //transform_component->setPosition(glm::vec3(2.0f,2.0f,2.0f));
        
        //data_target.lock()->Transform = std::move(transform_component->transform);
        
        ////camera
        // if(camera_component.has_value())
        //     data_target.lock()->_camera=(*camera_component).character_camera.get();
    }
    
    //data_target.lock()->getSwapContext()->model=model;
    //int a=0;
}

}// namespace taixu