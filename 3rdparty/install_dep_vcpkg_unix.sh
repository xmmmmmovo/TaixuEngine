#!/usr/bin/env bash

# install the vcpkg
git clone https://github.com/Microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh -disableMetrics
cd vcpkg || return
./vcpkg install