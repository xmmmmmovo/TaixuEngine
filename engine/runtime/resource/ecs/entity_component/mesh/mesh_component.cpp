#include "mesh_component.hpp"
#include "graphics/renderer.hpp"

namespace taixu
{


void MeshComponent::initialize() 
{
    assert(mesh_path!="INVALID");
    if(visible==true)
    {
        transform_component->makeTransformMatrix();
        RenderableModelInfo mInfo;
        
        mInfo.file_path = mesh_path.c_str();
        if(texture_path!="INVALID")
            mInfo.texture_path = texture_path.c_str();
        mInfo.GO = GO;
        mInfo.transform_matrix = transform_component->transform;
        mInfo.opt = oprationType::ADD;
        data_target.lock()->getSwapContext()->dirty_models.push_back(mInfo);
    }
}

void MeshComponent::tick() 
{
    //assert(data_target.expired());
    if(visible==true)
    {
        transform_component->makeTransformMatrix();
        RenderableModelInfo sphere;
        
        //sphere.file_path = mesh_path.c_str();
        sphere.GO = GO;
        sphere.transform_matrix = transform_component->transform;
        sphere.opt = oprationType::TRANSFORM;
        data_target.lock()->getSwapContext()->dirty_models.push_back(sphere);
        
        ////camera
        // if(camera_component.has_value())
        //     data_target.lock()->_camera=(*camera_component).character_camera.get();
    }
    
    //data_target.lock()->getSwapContext()->model=model;
    //int a=0;
}

}// namespace taixu