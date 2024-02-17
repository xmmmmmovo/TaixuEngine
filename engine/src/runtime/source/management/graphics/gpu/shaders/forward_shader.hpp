//
// Created by xmmmmmovo on 1/28/2024.
//
#pragma once

#ifdef USE_DX11
    #ifdef _DEBUG
        #include "forward_frag_dx11_d.hpp"
        #include "forward_vert_dx11_d.hpp"
    #else
        #include "forward_frag_dx11.hpp"
        #include "forward_vert_dx11.hpp"
    #endif
#endif

#ifdef USE_VULKAN
    #include "triangle_frag_vk.h"
    #include "triangle_vert_vk.h"
#endif
