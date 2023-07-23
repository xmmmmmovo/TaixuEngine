#ifndef TAIXUENGINE_FBXHELPER_HPP
#define TAIXUENGINE_FBXHELPER_HPP

#include "bone.hpp"
#include "model.hpp"
#include <runtime/resource/raw_data/asset_data.hpp>
namespace taixu {

class FBXData : public BaseAssetData {
public:
    Model                          *model;
    std::map<std::string, BoneInfo> m_BoneInfoMap;
    int                             m_BoneCounter{0};

    float             m_Duration;
    int               m_TicksPerSecond;
    std::vector<Bone> skeleton;

    AssimpNodeData m_RootNode;

    bool hasAnimation{false};
    void bindSkinedMesh(Model *m) { model = m; }

    Bone *FindBone(const std::string &name) {
        auto iter = std::find_if(
                skeleton.begin(), skeleton.end(),
                [&](const Bone &Bone) { return Bone.GetBoneName() == name; });
        if (iter == skeleton.end()) {
            return nullptr;
        } else {
            return &(*iter);
        }
    }

    [[nodiscard]] float GetTicksPerSecond() const { return m_TicksPerSecond; }

    [[nodiscard]] float GetDuration() const { return m_Duration; }
};

}// namespace taixu


#endif /* TAIXUENGINE_FBXHELPER_HPP */
