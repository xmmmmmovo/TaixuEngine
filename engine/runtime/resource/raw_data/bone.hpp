#ifndef TAIXUENGINE_BONE_HPP
#define TAIXUENGINE_BONE_HPP

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
namespace taixu
{
#define MAX_BONE_INFLUENCE 4
struct KeyPosition
{
    glm::vec3 position;
    float timeStamp;
};

struct KeyRotation
{
    glm::quat orientation;
    float timeStamp;
};

struct KeyScale
{
    glm::vec3 scale;
    float timeStamp;
};

struct BoneInfo
{
    /*id is index in finalBoneMatrices*/
    int id;

    /*offset matrix transforms vertex from model space to bone space*/
    glm::mat4 offset;
};

struct VertexRelateBoneInfo
{
    int related_bones[MAX_BONE_INFLUENCE];
    float related_bones_weights[MAX_BONE_INFLUENCE];
};

class Bone
{
public:
    std::vector<KeyPosition> m_Positions;
    std::vector<KeyRotation> m_Rotations;
    std::vector<KeyScale> m_Scales;
    int m_NumPositions;
    int m_NumRotations;
    int m_NumScalings;

    glm::mat4 m_LocalTransform;
    std::string m_Name;
    int m_ID;
};

}
#endif /* TAIXUENGINE_BONE_HPP */
