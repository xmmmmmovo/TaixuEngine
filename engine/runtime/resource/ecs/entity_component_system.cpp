#include "entity_component_system.hpp"


namespace taixu {
void ECS::initialize() 
{
    taixu_world=std::make_shared<WorldManager>();
    taixu_world->initialize();
    
    //Due to the mesh component need to transfer data to renderer
    //So its order of tick is at the end
    
    EntityComponentMap mesh_component_map;
    EntityComponentMap rigid_body_component_map;        

                                                        //tick order
    
    all_components.push_back(rigid_body_component_map);     //0
    all_components.push_back(mesh_component_map);           //1

    //temporary read obj.json

    auto &current_GO = taixu_world->current_level->GOs[0];
    //add
    auto mesh=std::make_shared<MeshComponent>(true,current_GO.get_id(),"assets/model/sphere.obj","material");
    mesh->data_target = data_target;
    
    //transform
    //glm::vec3 pos{1.0f,1.0f,1.0f},scale{2.0f,2.0f,2.0f},rotate{45.0f,45.0f,45.0f};
    auto trans = std::make_unique<TransformComponent>();
    trans->GO = current_GO.get_id();

    global_transform.push_back(std::move(trans));
    TransformComponent *_pointer = global_transform.back().get();
    mesh->transform_component =  _pointer;

    CameraComponent camera;
    camera.initialize();
    camera.setCameraPosition(glm::vec3{0.0f,0.0f,8.0f});
    mesh->camera_component=std::move(camera);
    mesh->initialize();
    all_components[1].addComponent(mesh);

    //rigid body

    auto rigid_body = std::make_shared<RigidBodyComponent>(
        current_GO.get_id(),
        _pointer,
        scene_target
    );
    
    all_components[0].addComponent(rigid_body);

    //next mesh
    current_GO = taixu_world->current_level->GOs[1];
    
    auto sphere_mesh = std::make_shared<MeshComponent>(true,current_GO.get_id(),"assets/model/cube.obj","material");
    sphere_mesh->data_target = data_target;

    auto sphere_trans = std::make_unique<TransformComponent>();
    sphere_trans->GO = current_GO.get_id();

    global_transform.push_back(std::move(sphere_trans));
    TransformComponent *sphere_pointer = global_transform.back().get();
    sphere_mesh->transform_component = sphere_pointer;
    //all_components[1].addComponent(sphere_mesh);
    
}

void ECS::dataRedirection(
        std::shared_ptr<RenderContext> render_context) 
{
    data_target = render_context;
    //int a=0;
}

void ECS::sceneRedirection(std::shared_ptr<PhysicsScene> physics_scene)
{
    scene_target = physics_scene;
}

void ECS::reloadWorld(const std::filesystem::path & world_path)
{

}

void ECS::tick(float delta_time) 
{
for(auto map:all_components)
{
    for(auto &cpnt:map.map)
    {
        cpnt->tick();
    }
}

}
}


