//
// Created by xmmmmmovo on 2023/5/4.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_OBJECT_ABSTRACT_COMPONENT_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_OBJECT_ABSTRACT_COMPONENT_HPP

#include "core/base/macro.hpp"
#include "guid_genenrator.hpp"
namespace taixu {

class AbstractComponent {
    PROTOTYPE_DFT_ONLY_GETTER(protected, GUID, guid,
                              GuidGenerator::generateNewGuid())
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_OBJECT_ABSTRACT_COMPONENT_HPP
