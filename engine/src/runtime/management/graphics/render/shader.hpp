#ifndef ENGINE_RUNTIME_GRAPHICS_SHADER
#define ENGINE_RUNTIME_GRAPHICS_SHADER

#include <common/base/noncopyable.hpp>

#include <runtime/management/graphics/render/render_types.hpp>

namespace taixu {

/**
 * @brief shader type
 * @see
 * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml
 */
enum ShaderTypeEnum {
    VERTEX,
    FRAGMENT,
    COMPUTE,
    TESS_CONTROL,
    TESS_EVALUATION,
    GEOMETRY
};

class IShader : private noncopyable {
protected:
    IShader() = default;

public:
    // compile time value
    [[nodiscard]] constexpr unsigned inline get_id() const noexcept {
        return _id;
    }

protected:
    unsigned int _id{0};
};

class IShaderProgram : private noncopyable {
protected:
    IShaderProgram() = default;

public:
    virtual void use() const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             bool             value) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             int              value) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             float            value) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             const glm::vec2& value) const noexcept = 0;

    virtual void set_uniform(std::string_view name, float x,
                             float y) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             const glm::vec3& value) const noexcept = 0;

    virtual void set_uniform(std::string_view name, float x, float y,
                             float z) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             const glm::vec4& value) const noexcept = 0;

    virtual void set_uniform(std::string_view name, float x, float y, float z,
                             float w) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             const glm::mat2& mat) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             const glm::mat3& mat) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             const glm::mat4& mat) const noexcept = 0;

    virtual void bind_uniform_block(const std::string_view& name,
                                    std::uint32_t idx) const noexcept = 0;

    virtual void setMat4Array(const std::string& name,
                              const glm::mat4&   mat) const noexcept = 0;

protected:
    unsigned int _id{0};
};
}// namespace taixu

#endif /* ENGINE_RUNTIME_GRAPHICS_SHADER */
