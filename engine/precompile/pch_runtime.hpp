//
// Created by xmmmmmovo on 1/6/2024.
//

#ifndef ENGINE_PRECOMPILE_PCH_RUNTIME_0A0D878DBB714C9499D420BF61F1C4D8
#define ENGINE_PRECOMPILE_PCH_RUNTIME_0A0D878DBB714C9499D420BF61F1C4D8


#define NOGDICAPMASKS
#define NOVIRTUALKEYCODES
#define NOWINSTYLES
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOKEYSTATES
#define NOSYSCOMMANDS
#define NORASTEROPS
#define NOSHOWWINDOW
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOGDI
#define NOKERNEL
// #define NOUSER
// #define NONLS
#define NOMB
#define NOMEMMGR
#define NOMETAFILE
// #define NOMSG
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE

#define NOMINMAX

#include <magic_enum.hpp>

#include <simdjson/simdjson.h>

#include <Jolt/Jolt.h>

#include <refl.hpp>

#include <glm/glm.hpp>

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <argparse/argparse.hpp>

#define IMGUI_ENABLE_FREETYPE
#ifndef IMGUI_DEFINE_PLACEMENT_NEW
    #define IMGUI_DEFINE_PLACEMENT_NEW
#endif
#ifndef IMGUI_DEFINE_MATH_OPERATORS
    #define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include <imgui.h>
#include <imgui/tools/imgui_freetype.h>
#include <imgui_internal.h>


#endif// ENGINE_PRECOMPILE_PCH_RUNTIME_0A0D878DBB714C9499D420BF61F1C4D8
