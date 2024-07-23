# TaixuEngine

A simple 3D game engine.

![Cover](.github/images/cover.png)

Note: This is in OpenGL version in [main branch](https://github.com/xmmmmmovo/TaixuEngine/tree/main)

## How to build

**Prerequisites:**

- C++20 compliant compiler
- [python](https://www.python.org/)
- [cmake](https://cmake.org/)
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home)

**Build:**

```shell
mkdir build
cd build
cmake ..
make
```

## Features

### Supporting API

|  API  |                Progress                |
| :----: | :------------------------------------: |
| OpenGL | Deprecated(old version in main branch) |
| Vulkan |                  WIP                  |

Note: New RHI design, others api will be implemented by `Mesa` project.

## Architecture

```mermaid
flowchart TD
    editor --> runtime/include;
    runtime/include --> engine;
    engine --> common;
    engine --> management;
    management --> gameplay;
    management --> resource;
    management --> platform;
    gameplay --> common;
    management --> common;
    platform --> common;
    resource --> common;
```
