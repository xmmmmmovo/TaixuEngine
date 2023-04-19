#include "mesh_component.hpp"
#include "graphics/renderer.hpp"

namespace taixu {


void MeshComponent::initialize() {
    assert(mesh_path != "INVALID");
    if (visible == true) {
        transform_component->makeTransformMatrix();
        RenderableModelInfo sphere;

        sphere.file_path        = mesh_path.c_str();
        sphere.GO               = GO;
        sphere.transform_matrix = transform_component->transform;
        sphere.opt              = oprationType::ADD;
        data_target->getSwapContext()->dirty_models.push_back(sphere);
    }
}

void MeshComponent::tick() {
    //assert(data_target.expired());
    if (visible == true) {
        transform_component->makeTransformMatrix();
        RenderableModelInfo sphere;

        //sphere.file_path = mesh_path.c_str();
        sphere.GO               = GO;
        sphere.transform_matrix = transform_component->transform;
        sphere.opt              = oprationType::TRANSFORM;
        data_target->getSwapContext()->dirty_models.push_back(sphere);

        ////camera
        // if(camera_component.has_value())
        //     data_target.lock()->_camera=(*camera_component).character_camera.get();
    }
}

}// namespace taixu