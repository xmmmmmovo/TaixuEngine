# TaixuEngine

A simple 3D game engine.

![Cover](.github/images/cover.png)

Note: This is in OpenGL version in [main branch](https://github.com/xmmmmmovo/TaixuEngine/tree/main)

## How to build

```shell
mkdir build
cd build
cmake ..
make
```

## Features

### Supporting API

|  API   |                Progress                |
| :----: | :------------------------------------: |
| OpenGL | Deprecated(old version in main branch) |
|  DX11  |                  WIP                   |
| Vulkan |                  WIP                   |



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