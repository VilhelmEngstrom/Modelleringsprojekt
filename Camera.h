#pragma once
#include <iostream>

#if defined _WIN32 || defined _WIN64
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#endif
#include "dependencies/include/glew.h"

#include "dependencies/include/glm/glm.hpp"
#include "dependencies/include/glm/gtc/matrix_transform.hpp"

#ifndef CAMERAMOVEMENT_H
#define CAMERAMOVEMENT_H

enum class CameraMovement{
    FORWARD, BACKWARD, LEFT, RIGHT
};

#endif

#ifndef CAMERA_H
#define CAMERA_H

class Camera{
    public:
        Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        glm::mat4 getViewMatrix() const;

        void processKeyboardInput(CameraMovement dir, float deltaTime);

        void processMouseInput(float xOffset, float yOffset, bool constrainPitch = true);

        void processMouseScroll(float yOffset);

        float getZoom() const;


    static const float YAW, PITCH, SPEED, SENSITIVITY, ZOOM;
    private:
        glm::vec3 m_Position;
        glm::vec3 m_Front;
        glm::vec3 m_Up;
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp;

        float m_Yaw;
        float m_Pitch;
        float m_MovementSpeed;
        float m_MouseSensitivity;
        float m_Zoom;

        void updateVectors();

};

#endif
