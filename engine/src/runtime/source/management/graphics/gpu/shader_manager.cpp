//
// Created by xmmmmmovo on 1/28/2024.
//

#include "shader_manager.hpp"

namespace taixu {
TXShadrModuleManager::TXShadrModuleManager(
        TXShadrModuleManager::AdapterPtrT&& adapter)
    : _adapter(std::forward<AdapterPtrT>(adapter)) {
    _builtin_modules.fill(nullptr);

    _adapter->initForBuiltinShaderCreateInfo(_builtin_shader_create_infos);
}

std::shared_ptr<TXShaderModule> TXShadrModuleManager::createShaderModuleInner(
        const TXShaderModuleCreateInfo& info) {
    return _adapter->create(info);
}

std::shared_ptr<TXShaderModule>
TXShadrModuleManager::createShaderModule(const TXShaderModuleCreateInfo& info) {
    return std::shared_ptr<TXShaderModule>();
}

std::shared_ptr<TXShaderModule> TXShadrModuleManager::getBuiltinShaderModule(
        EnumTXBuiltinShader builtin_shader) {
    if (_builtin_modules[builtin_shader] == nullptr) {
        return createShaderModuleInner(
                _builtin_shader_create_infos[static_cast<size_t>(
                        builtin_shader)]);
    }
    return _builtin_modules[static_cast<size_t>(builtin_shader)];
}

}// namespace taixu