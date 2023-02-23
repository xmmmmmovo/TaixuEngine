#ifndef ENGINE_RUNTIME_GRAPHICS_SHADER
#define ENGINE_RUNTIME_GRAPHICS_SHADER


namespace taixu {

enum ShaderTypeEnum { VERTEX, FRAGMENT };

class IShader {
protected:
    IShader() = default;

public:
    // do not copy
    IShader(const IShader &)            = delete;
    IShader &operator=(const IShader &) = delete;

    IShader(IShader &&other) noexcept            = default;
    IShader &operator=(IShader &&other) noexcept = default;

    virtual ~IShader() = default;

    // compile time value
    [[nodiscard]] constexpr unsigned inline get_id() const noexcept {
        return _id;
    }

protected:
    unsigned int _id{0};
};

class IShaderProgram {
protected:
    IShaderProgram() = default;

public:
    virtual ~IShaderProgram() = default;

    virtual void use() const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             bool             value) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             int              value) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             float            value) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             const glm::vec2       &value) const noexcept = 0;

    virtual void set_uniform(std::string_view name, float x,
                             float y) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             const glm::vec3       &value) const noexcept = 0;

    virtual void set_uniform(std::string_view name, float x, float y,
                             float z) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             const glm::vec4       &value) const noexcept = 0;

    virtual void set_uniform(std::string_view name, float x, float y,
                             float z, float w) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             const glm::mat2       &mat) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             const glm::mat3       &mat) const noexcept = 0;

    virtual void set_uniform(std::string_view name,
                             const glm::mat4       &mat) const noexcept = 0;

protected:
    unsigned int _id{0};
};
}// namespace taixu

#endif /* ENGINE_RUNTIME_GRAPHICS_SHADER */
