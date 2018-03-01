#include "Camera.h"


Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM) {
    m_Position = position;
    m_WorldUp = up;
    m_Yaw = yaw;
    m_Pitch = pitch;
    updateVectors();
}


Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM){
    m_Position = glm::vec3(posX, posY, posZ);
    m_WorldUp = glm::vec3(upX, upY, upZ);
    m_Yaw = yaw;
    m_Pitch = pitch;
    updateVectors();
}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::processKeyboardInput(CameraMovement dir, float deltaTime){
    float velocity = m_MovementSpeed * deltaTime;
    switch(dir){
        case CameraMovement::FORWARD:  m_Position += m_Front * velocity;
                                       break;
        case CameraMovement::BACKWARD: m_Position -= m_Front * velocity;
                                       break;
        case CameraMovement::LEFT:     m_Position -= m_Right * velocity;
                                       break;
        case CameraMovement::RIGHT:    m_Position += m_Right * velocity;
                                       break;
    }
}

void Camera::processMouseInput(float xOffset, float yOffset, bool constrainPitch){
    xOffset *= m_MouseSensitivity;
    yOffset *= m_MouseSensitivity;

    m_Yaw   += xOffset;
    m_Pitch += yOffset;

    if(constrainPitch){
        if(m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if(m_Pitch < -89.0f)
            m_Pitch = -89.0f;
    }

    updateVectors();
}

void Camera::processMouseScroll(float yOffset){
    if(m_Zoom >= 1.0f && m_Zoom <= 45.0f)
        m_Zoom -= yOffset;
    if(m_Zoom <= 1.0f)
        m_Zoom = 1.0f;
    if(m_Zoom >= 45.0f)
        m_Zoom = 45.0f;
}

float Camera::getZoom() const{
    return m_Zoom;
}

void Camera::updateVectors(){
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw) * glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

const float Camera::YAW = 90.0f;
const float Camera::PITCH = 0.0f;
const float Camera::SPEED = 20.5f;
const float Camera::SENSITIVITY = 0.1f;
const float Camera::ZOOM = 45.0f;
