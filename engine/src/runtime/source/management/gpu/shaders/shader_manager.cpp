//
// Created by xmmmmmovo on 1/28/2024.
//

#include "shader_manager.hpp"

namespace taixu {

void TXShaderModuleManager::init() {
}

std::shared_ptr<TXShaderModule>
TXShaderModuleManager::createShaderModuleInner(const TXShaderModuleCreateInfo& info) const {
    return nullptr;
}

std::shared_ptr<TXShaderModule>
TXShaderModuleManager::createCustomShaderModule(const TXShaderModuleCreateInfo& info) const {
    // TODO: check name
    return createShaderModuleInner(info);
}

std::shared_ptr<TXShaderModule> TXShaderModuleManager::getBuiltinShaderModule(TXBuiltinShader builtin_shader) const {
    if (builtin_modules[static_cast<size_t>(builtin_shader)] == nullptr) {
        std::shared_ptr<TXShaderModule> module =
                createShaderModuleInner(builtin_shader_create_infos[static_cast<size_t>(builtin_shader)]);
        builtin_modules[static_cast<size_t>(builtin_shader)] = module;
        return module;
    }
    return builtin_modules[static_cast<size_t>(builtin_shader)]->shared_from_this();
}

}// namespace taixu
