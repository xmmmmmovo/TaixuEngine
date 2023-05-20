#ifndef TAIXUENGINE_SKELETON_COMPONENT_HPP
#define TAIXUENGINE_SKELETON_COMPONENT_HPP

#include "resource/raw_data/fbx_data.hpp"
#include "glm/glm.hpp"

namespace taixu
{
class SkeletonComponent
{
public:
FBXData *fbx;
std::vector<glm::mat4> m_FinalBoneMatrices;
float m_CurrentTime;
float m_DeltaTime;

void UpdateAnimation(float dt) {
    m_DeltaTime = dt;
    if (fbx) {
        m_CurrentTime += fbx->GetTicksPerSecond() * dt;
        m_CurrentTime = fmod(m_CurrentTime, fbx->GetDuration());
        CalculateBoneTransform(&fbx->m_RootNode,
                               glm::mat4(1.0f));
    }
}

void PlayAnimation(FBXData *pAnimation) {
    fbx = pAnimation;
    m_CurrentTime      = 0.0f;
}

void CalculateBoneTransform(const AssimpNodeData* node,
                            glm::mat4             parentTransform) {
    std::string nodeName      = node->name;
    glm::mat4   nodeTransform = node->transformation;

    Bone *Bone = fbx->FindBone(nodeName);

    if (Bone!=nullptr) {
        Bone->Update(m_CurrentTime);
        nodeTransform = Bone->GetLocalTransform();
    }

    glm::mat4 globalTransformation = parentTransform * nodeTransform;

    if (fbx->m_BoneInfoMap.find(nodeName) != fbx->m_BoneInfoMap.end()) {
        int       index            = fbx->m_BoneInfoMap[nodeName].id;
        glm::mat4 offset           = fbx->m_BoneInfoMap[nodeName].offset;
        m_FinalBoneMatrices[index] = globalTransformation * offset;
    }

    for (int i = 0; i < node->childrenCount; i++)
        CalculateBoneTransform(&node->children[i], globalTransformation);
}
};

}

#endif /* TAIXUENGINE_SKELETON_COMPONENT_HPP */
