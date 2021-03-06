#include "mode.h"
#include "Rover.h"

void ModeManual::update()
{
    // check for radio failsafe
    if (rover.failsafe.bits & FAILSAFE_EVENT_THROTTLE) {
        g2.motors.set_throttle(0.0f);
        g2.motors.set_steering(0.0f);
    } else {
        float desired_steering, desired_throttle;
        get_pilot_desired_steering_and_throttle(desired_steering, desired_throttle);
        // copy RC scaled inputs to outputs
        g2.motors.set_throttle(desired_throttle);
        g2.motors.set_steering(desired_steering);
    }

    // mark us as in_reverse when using a negative throttle to stop AHRS getting off
    rover.set_reverse(is_negative(g2.motors.get_throttle()));
}
