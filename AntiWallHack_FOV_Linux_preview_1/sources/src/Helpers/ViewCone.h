#pragma once
#include <cmath>
namespace awh {
// Conservative horizontal cone; full vertical visibility and near-field bypass.
// Unknown input always allows transmission. Radius encloses the target hull.
inline bool OutsideViewCone(float yaw, float dx, float dy, float radius,
                            float degrees, float nearDistance) {
    if (!std::isfinite(yaw) || !std::isfinite(dx) || !std::isfinite(dy) ||
        !std::isfinite(radius) || radius < 0 || !std::isfinite(degrees) ||
        degrees < 120 || degrees > 360 || !std::isfinite(nearDistance) || nearDistance < 0)
        return false;
    const double distance = std::hypot(double(dx), double(dy));
    if (distance <= double(nearDistance) + radius || degrees >= 360) return false;
    constexpr double rad = 3.14159265358979323846 / 180.0;
    const double bearing = std::atan2(double(dy), double(dx)) / rad;
    const double difference = std::abs(std::remainder(bearing - double(yaw), 360.0));
    const double extent = std::asin(double(radius) / distance) / rad;
    return difference > double(degrees) * 0.5 + extent;
}
}
