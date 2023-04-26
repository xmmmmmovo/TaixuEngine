#ifndef TAIXUENGINE_RIGID_BODY_JSON
#define TAIXUENGINE_RIGID_BODY_JSON

#include "resource/ecs/entity_component/rigid_body/rigid_body_component.hpp"
#include "transform_json.hpp"
namespace taixu
{
class JsonRigidBody
{
public:
    RigidBodyShapeType shapeType;
    MotionType motionType;
    Vec3 rigid_body_scale;

    void to_json(nlohmann::json& j, JsonRigidBody r) {
        j = nlohmann::json{{"shapeType", r.shapeType}, {"motionType", r.motionType}};
        r.rigid_body_scale.to_json(j["rigid_body_scale"], r.rigid_body_scale);
    }   

    void from_json(const nlohmann::json& j, JsonRigidBody &r) {
        j.at("shapeType").get_to(r.shapeType);
        j.at("motionType").get_to(r.motionType);
        r.rigid_body_scale.from_json(j["rigid_body_scale"], r.rigid_body_scale);
    }
};


}



#endif /* TAIXUENGINE_RIGID_BODY_JSON */
