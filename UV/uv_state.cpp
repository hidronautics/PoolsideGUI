#include "uv_state.h"

ImuData::ImuData()
{
    roll = 0;
    pitch = 0;
    yaw = 0;
    rollSpeed = 0;
    pitchSpeed = 0;
    yawSpeed = 0;
    depth = 0;
}

ControlData::ControlData()
{
    march = 0;
    lag = 0;
    depth = 0;
    roll = 0;
    pitch = 0;
    yaw = 0;
};

UV_State::UV_State()
{
    device[UV_Device::DEVICE_LIGHT].name = "Light";
    device[UV_Device::DEVICE_LIGHT].slot = UV_Device::DEVICE_LIGHT;

    device[UV_Device::DEVICE_DEV1].name = "Dev1";
    device[UV_Device::DEVICE_DEV1].slot = UV_Device::DEVICE_DEV1;

    device[UV_Device::DEVICE_DEV2].name = "Dev2";
    device[UV_Device::DEVICE_DEV2].slot = UV_Device::DEVICE_DEV2;

    device[UV_Device::DEVICE_GRAB].name = "Grab";
    device[UV_Device::DEVICE_GRAB].slot = UV_Device::DEVICE_GRAB;

    device[UV_Device::DEVICE_GRAB_ROTATE].name = "Grab Rotation";
    device[UV_Device::DEVICE_GRAB_ROTATE].slot = UV_Device::DEVICE_GRAB_ROTATE;

    device[UV_Device::DEVICE_TILT].name = "Tilt";
    device[UV_Device::DEVICE_TILT].slot = UV_Device::DEVICE_TILT;

    resetImu = false;
}
