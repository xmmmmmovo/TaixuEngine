#ifndef TAIXUENGINE_PERSPECTIVE_CAMERA_HPP
#define TAIXUENGINE_PERSPECTIVE_CAMERA_HPP

#include <vector>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <common/base/macro.hpp>

namespace taixu {

enum class CameraMovement : std::uint8_t { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

// Default camera values
static constexpr float YAW          = -90.0f;
static constexpr float PITCH        = 0.0f;
static constexpr float NORMAL_SPEED = 10.0f;
static constexpr float FASTS_PEED   = 20.0f;
static constexpr float SENSITIVITY  = 0.1f;
static constexpr float ZOOM         = 45.0f;

class EulerCamera {
    PROTOTYPE_DFT(private, float, aspect_ratio, 16.0f / 9.0f);

public:
    // camera Attributes
    glm::vec3 Position{};
    glm::vec3 Front{};
    glm::vec3 Up{};
    glm::vec3 Right{};
    glm::vec3 WorldUp{};
    // euler Angles
    float     Yaw;
    float     Pitch;
    // camera options
    float     MovementSpeed;
    float     MouseSensitivity;
    float     Zoom;

    // constructor with vectors
    explicit EulerCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.5f),
                         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
                         float pitch = PITCH)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(NORMAL_SPEED),
          MouseSensitivity(SENSITIVITY), Zoom(ZOOM), Position(position), WorldUp(up), Yaw(yaw),
          Pitch(pitch) {
        updateCameraVectorsPerspective();
    }

    // constructor with scalar values
    EulerCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw,
                float pitch)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(NORMAL_SPEED),
          MouseSensitivity(SENSITIVITY), Zoom(ZOOM), Position(glm::vec3(posX, posY, posZ)),
          WorldUp(glm::vec3(upX, upY, upZ)), Yaw(yaw), Pitch(pitch) {
        updateCameraVectorsPerspective();
    }

    // processes input received from any keyboard-like input system. Accepts
    // input parameter in the form of camera defined ENUM (to abstract it from
    // windowing systems)
    void processKeyboard(CameraMovement direction, float deltaTime) {
        float const velocity = MovementSpeed * deltaTime;
        if (direction == CameraMovement::FORWARD) { Position += Front * velocity; }
        if (direction == CameraMovement::BACKWARD) { Position -= Front * velocity; }
        if (direction == CameraMovement::LEFT) { Position -= Right * velocity; }
        if (direction == CameraMovement::RIGHT) { Position += Right * velocity; }
        if (direction == CameraMovement::UP) { Position += Up * velocity; }
        if (direction == CameraMovement::DOWN) { Position -= Up * velocity; }
    }

    void accelerate() { MovementSpeed = FASTS_PEED; }
    void decelerate() {
        if (MovementSpeed == FASTS_PEED) { MovementSpeed = NORMAL_SPEED; }
    }

    // processes input received from a mouse input system. Expects the offset
    // value in both the x and y direction.
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get
        // flipped
        if (constrainPitch) {
            if (Pitch > 89.0f) { Pitch = 89.0f; }
            if (Pitch < -89.0f) { Pitch = -89.0f; }
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectorsPerspective();
    }

    // processes input received from a mouse scroll-wheel event. Only requires
    // input on the vertical wheel-axis
    void processMouseScroll(float yoffset) {
        Zoom -= yoffset;
        if (Zoom < 1.0f) { Zoom = 1.0f; }
        if (Zoom > 45.0f) { Zoom = 45.0f; }
    }

    [[nodiscard]] glm::mat4 const& getViewMatrix() const { return _view_matrix; }

    [[nodiscard]] glm::mat4 const& getProjectionMatrix() { return _projection_matrix; }

    void updateCameraVectorsOrtho(float width, float height) {
        _projection_matrix = glm::ortho(-width * 0.5f, width * 0.5f, -height * 0.5f, height * 0.5f,
                                        Z_NEAR, Z_FAR);
        updateViewMat();
    }

    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectorsPerspective() {
        // calculate the new Front vector
        _projection_matrix = glm::perspective(glm::radians(_fov), _aspect_ratio, Z_NEAR, Z_FAR);
        updateViewMat();
    }

private:
    void updateViewMat() {
        glm::vec3 front;
        front.x      = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y      = sin(glm::radians(Pitch));
        front.z      = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front        = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right        = glm::normalize(glm::cross(Front,
                                                 WorldUp));// normalize the vectors, because their length
                                                    // gets closer to 0 the more you look up or down
                                                    // which results in slower movement.
        Up           = glm::normalize(glm::cross(Right, Front));
        _view_matrix = glm::lookAt(Position, Position + Front, Up);
    }

private:
    float static constexpr Z_NEAR = 0.01f;
    float static constexpr Z_FAR  = 500.0f;
    float     _fov                = 90.0f;
    // calculates the front vector from the Camera's (updated) Euler Angles
    glm::mat4 _projection_matrix{};
    glm::mat4 _view_matrix{};
};

}// namespace taixu

#endif// TAIXUENGINE_PERSPECTIVE_CAMERA_HPP
