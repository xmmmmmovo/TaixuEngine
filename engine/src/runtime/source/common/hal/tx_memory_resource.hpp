//
// Created by xmmmmmovo on 23/09/2023.
//

#pragma once

namespace taixu {


template<typename T>
class TXMemoryResource {
public:
             TXMemoryResource() = default;
    virtual ~TXMemoryResource() = default;

    virtual void* allocate(size_t size) = 0;
    virtual void  deallocate(void* ptr) = 0;
};


}// namespace taixu
