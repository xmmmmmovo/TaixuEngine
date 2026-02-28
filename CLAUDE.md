# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

TaixuEngine is a modern C++23 3D game engine currently being refactored from OpenGL to Vulkan. It features both editor and runtime components with a modular architecture designed for cross-platform game development.

## Build Commands

### Prerequisites

- C++23 compliant compiler
- Python 3.10+
- CMake 3.20+
- Vulkan SDK

### Standard Build

```bash
mkdir build
cd build
cmake ..
make  # or ninja on Windows
```

### Build Options

Key CMake options to configure the build:

- `USE_VULKAN=ON` - Enable Vulkan support (current focus)
- `USE_VCPKG=ON` - Use vcpkg for dependency management
- `USE_PCH=ON` - Enable precompiled headers (default)
- `WARNINGS=ON` - Enable compiler warnings (default)
- `USE_NOEXCEPT=ON` - Use noexcept design philosophy (default)

### Testing

```bash
# Run all unit tests
cd build
ctest

# Run specific test categories
./tests/unit_tests/[test_name]
./tests/benchmarks/[benchmark_name]
```

## Architecture Overview

### Directory Structure

- `engine/src/editor/` - Editor application code and UI components
- `engine/src/runtime/` - Core engine runtime code
- `engine/shaders/` - GLSL/HLSL shader source files
- `3rdparty/` - Third-party dependencies and CMake find modules
- `cmake/` - CMake utilities and custom modules
- `tests/` - Unit tests and benchmarks

### Core Components

- **Engine**: Main engine class with lifecycle management (`engine/src/runtime/include/taixu/engine/engine.hpp`)
- **ResourceManager**: Asset and resource loading system
- **ProjectManager**: Game project management (`management/project/`)
- **ECS System**: Entity Component System in `management/ecs/`
- **Rendering**: Vulkan-based renderer (current refactor focus)
- **Platform**: OS abstraction layer in `platform/os/` and `platform/windows/`

### Engine States

The engine operates in different modes:

- `EDITORMODE` - Editor mode for project development
- `PREVIEWMODE` - Play mode for testing
- `IDLEMODE` - Idle state until project opened
- `GAMEMODE` - Packed game runtime

## Key Design Patterns

### No Exception Philosophy

The engine follows a "No Exception Design" with constructor exception safety. All engine code should avoid exceptions and use proper error handling patterns.

### Modular Architecture

Clear separation between layers:

- Editor → Runtime → Common → Management → Gameplay → Platform

### Resource Management

- JSON-based resource definitions in `resource/json_data/`
- Centralized resource managers in `resource/manager/`
- Shader compilation pipeline that generates C++ headers from GLSL

## Development Workflow

### Shader Development

Shaders are compiled automatically using the custom CMake pipeline:

1. Place `.glsl` files in `engine/shaders/`
2. CMake compiles them to SPIR-V using glslang
3. Generates C++ headers with embedded shader data
4. Include generated headers in runtime code

### Adding New Components

1. Editor components go in `engine/src/editor/ui/components/`
2. Runtime components go in `engine/src/runtime/include/taixu/`
3. Follow the existing namespace pattern: `TX_NAMESPACE_BEGIN`/`TX_NAMESPACE_END`
4. Use the engine's macro system for consistent code generation

### Platform-Specific Code

- Windows-specific code goes in `platform/windows/`
- Use platform abstraction layer in `platform/os/`
- Follow existing patterns for cross-platform compatibility

## Testing Strategy

### Unit Tests

Located in `tests/unit_tests/` covering:

- Common utilities and containers
- Resource management
- Management systems (ECS, projects)
- Logging functionality

### Benchmarks

Performance tests in `tests/benchmarks/` for:

- Function transfer overhead
- Container performance
- Critical path optimizations

## Code Quality Standards

### Formatting

- Uses `.clang-format` for consistent code formatting
- `.clang-tidy` for static analysis
- `.cmake-format.yaml` for CMake file formatting

### Dependencies

Managed through CPM (CMake Package Manager) with custom `Find*.cmake` modules for third-party libraries like Vulkan, GLFW, and other graphics dependencies.

## Current Development Focus

This branch (`refactor-vulkan`) is actively migrating from OpenGL to Vulkan. Key areas of development:

- Vulkan renderer implementation
- Resource management system overhaul
- ECS system integration
- Shader compilation pipeline optimization
