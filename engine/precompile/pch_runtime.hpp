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

#ifndef NOMINMAX
    #define NOMINMAX
#endif

#include <magic_enum.hpp>

#include <Jolt/Jolt.h>

#include <rfl.hpp>
#include <rfl/json.hpp>

#include <glm/glm.hpp>

#include <fmt/format.h>

#include <spdlog/spdlog.h>

#include <argparse/argparse.hpp>

#define IMGUI_ENABLE_FREETYPE
#define IMGUI_DEFINE_PLACEMENT_NEW
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

#include <imgui/tools/imgui_freetype.h>

#include <magic_enum.hpp>

#include <freetype/freetype.h>

// assimp
#include <assimp/Exporter.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

// taskflow
#include <taskflow/taskflow.hpp>

#include <generated/fonts/lucide_iconfont.hpp>
#include <generated/fonts/source_han_sans_cn_font.hpp>

#endif// ENGINE_PRECOMPILE_PCH_RUNTIME_0A0D878DBB714C9499D420BF61F1C4D8
