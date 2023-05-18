#ifndef TAIXUENGINE_FBXHELPER_HPP
#define TAIXUENGINE_FBXHELPER_HPP

#include "resource/raw_data/asset_data.hpp"
#include "model.hpp"
#include "bone.hpp"
namespace taixu
{

class FBXData: public BaseAssetData
{
public:
    Model *model;
    std::map<string, BoneInfo> m_BoneInfoMap;
	int m_BoneCounter = 0;
    std::vector<Bone> skeleton;

    void transferAnimationDatatoGPU(){

    }
    void bindSkinedMesh(Model *m){
        model = m;
    }

};

}


#endif /* TAIXUENGINE_FBXHELPER_HPP */
