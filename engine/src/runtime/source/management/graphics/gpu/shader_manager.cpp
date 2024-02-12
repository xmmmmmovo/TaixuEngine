//
// Created by xmmmmmovo on 1/28/2024.
//

#include "shader_manager.hpp"

namespace taixu {

void TXShaderModuleManager::init(TXShaderModuleManager::AdapterPtrT&& adapter) {
    _adapter = std::forward<AdapterPtrT>(adapter);
    _adapter->initForBuiltinShaderCreateInfo(_builtin_shader_create_infos);
}

std::shared_ptr<TXShaderModule> TXShaderModuleManager::createShaderModuleInner(
        const TXShaderModuleCreateInfo& info) const {
    return _adapter->create(info);
}

std::shared_ptr<TXShaderModule> TXShaderModuleManager::createCustomShaderModule(
        const TXShaderModuleCreateInfo& info) {
    // TODO: check name
    return createShaderModuleInner(info);
}

std::shared_ptr<TXShaderModule> TXShaderModuleManager::getBuiltinShaderModule(
        EnumTXBuiltinShader builtin_shader) const {
    if (_builtin_modules[static_cast<size_t>(builtin_shader)] == nullptr) {
        std::shared_ptr<TXShaderModule> module = createShaderModuleInner(
                _builtin_shader_create_infos[static_cast<size_t>(
                        builtin_shader)]);
        _builtin_modules[static_cast<size_t>(builtin_shader)] = module;
        return module;
    }
    return _builtin_modules[static_cast<size_t>(builtin_shader)]
            ->shared_from_this();
}

}// namespace taixu