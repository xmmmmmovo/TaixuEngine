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
    auto mesh=std::make_shared<MeshComponent>(true,current_GO.get_id(),"assets/model/cube.obj","assets/textures/concreteTexture.png");
    mesh->data_target = data_target;
    
    //transform
    //glm::vec3 pos{1.0f,1.0f,1.0f},scale{2.0f,2.0f,2.0f},rotate{45.0f,45.0f,45.0f};
    auto trans = std::make_unique<TransformComponent>();
    trans->GO = current_GO.get_id();

    trans->setScale(glm::vec3(10.0f,0.1f,10.0f));

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
    rigid_body->initialize(RigidBodyShapeType::BOX,MotionType::STATIC);

    all_components[0].addComponent(rigid_body);

    //next mesh
    current_GO = taixu_world->current_level->GOs[1];
    
    auto sphere_mesh = std::make_shared<MeshComponent>(true,current_GO.get_id(),"assets/model/planet.obj","assets/textures/mars.png");
    sphere_mesh->data_target = data_target;

    auto sphere_trans = std::make_unique<TransformComponent>();
    sphere_trans->GO = current_GO.get_id();

    sphere_trans->setPosition(glm::vec3(0.0f,6.0f,0.0f));
    //sphere_trans->setScale(glm::vec3(1.f,0.5f,0.5f));
    
    global_transform.push_back(std::move(sphere_trans));
    TransformComponent *sphere_pointer = global_transform.back().get();
    sphere_mesh->transform_component = sphere_pointer;

    //rigid body

    auto sphere_rigid_body = std::make_shared<RigidBodyComponent>(
        current_GO.get_id(),
        sphere_pointer,
        scene_target
    );
    sphere_rigid_body->initialize(RigidBodyShapeType::SPHERE,MotionType::DYNAMIC);

    all_components[0].addComponent(sphere_rigid_body);
    sphere_mesh->initialize();
    all_components[1].addComponent(sphere_mesh);




    //next mesh
    current_GO = taixu_world->current_level->GOs[2];
    
    auto sphere_mesh1 = std::make_shared<MeshComponent>(true,current_GO.get_id(),"assets/model/sphere.obj","INVALID");
    sphere_mesh1->data_target = data_target;

    auto sphere_trans1 = std::make_unique<TransformComponent>();
    sphere_trans1->GO = current_GO.get_id();

    sphere_trans1->setPosition(glm::vec3(4.0f,6.0f,0.0f));
    //sphere_trans->setScale(glm::vec3(1.f,0.5f,0.5f));
    
    global_transform.push_back(std::move(sphere_trans1));
    TransformComponent *sphere_pointer1 = global_transform.back().get();
    sphere_mesh1->transform_component = sphere_pointer1;

    //rigid body

    auto sphere_rigid_body1 = std::make_shared<RigidBodyComponent>(
        current_GO.get_id(),
        sphere_pointer1,
        scene_target
    );
    sphere_rigid_body1->initialize(RigidBodyShapeType::SPHERE,MotionType::DYNAMIC);

    all_components[0].addComponent(sphere_rigid_body1);
    sphere_mesh1->initialize();
    all_components[1].addComponent(sphere_mesh1);


    //light
    auto light1 = std::make_unique<LightSourse>();
    light1->unique_id = GUID_Generator::generate_new_guid();
    auto light_trans = std::make_unique<TransformComponent>();
    light_trans->GO = light1->unique_id;

    light_trans->setPosition(glm::vec3(10.0f,10.0f,10.0f));
    //sphere_trans->setScale(glm::vec3(1.f,0.5f,0.5f));
    
    global_transform.push_back(std::move(light_trans));
    TransformComponent *light1_pointer = global_transform.back().get();
    light1->transform = light1_pointer;
    
    data_target.lock()->getSwapContext()->light_source.push_back(std::move(light1));
    
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


