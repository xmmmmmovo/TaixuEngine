//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_APPLICATION_HPP
#define TAIXUENGINE_APPLICATION_HPP

namespace taixu::editor {

/**
 * @brief Application for the whole editor
 *        Singleton pattern
 */
class Application {
private:
    Application()  = default;
    ~Application() = default;

public:
    Application(const Application &)            = delete;
    Application &operator=(const Application &) = delete;

    static Application &getInstance() {
        static Application instance;
        return instance;
    }

    void initialize();
    void run();
};

}// namespace taixu::editor

#endif//TAIXUENGINE_APPLICATION_HPP
