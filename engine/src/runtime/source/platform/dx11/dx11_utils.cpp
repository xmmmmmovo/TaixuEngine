//
// Created by xmmmmmovo on 1/17/2024.
//
#include "dx11_utils.hpp"

namespace taixu {


void dx11SetDebugObjectName(ID3D11DeviceChild*      resource,
                            const std::string_view& name) {
#if (defined(_DEBUG)) && (GRAPHICS_DEBUGGER_OBJECT_NAME)
    HRESULT const ret = resource->SetPrivateData(WKPDID_D3DDebugObjectName,
                                                 name.size(), name.data());
#else
    UNREFERENCED_PARAMETER(resource);
    UNREFERENCED_PARAMETER(name);
#endif
}


void dxgiSetDebugObjectName(IDXGIObject* object, const std::string_view& name) {
#if (defined(_DEBUG)) && (GRAPHICS_DEBUGGER_OBJECT_NAME)
    HRESULT const ret = object->SetPrivateData(WKPDID_D3DDebugObjectName,
                                               name.size(), name.data());
#else
    UNREFERENCED_PARAMETER(resource);
    UNREFERENCED_PARAMETER(name);
#endif
}

}// namespace taixu