#include <cmath>
#include "BouncingBall.h"

class BouncingBall {
private:
    // State structure
    State m_state;

    // Parameters
    double m_g;  // Gravity (m/s²)
    double m_c;  // Coefficient of restitution

    // RK4 integration method
    void rk4(State& s, double dt) {
        // Current state
        State s0 = s;

        // RK4 coefficients
        double k1x1, k1x2;
        double k2x1, k2x2;
        double k3x1, k3x2;
        double k4x1, k4x2;

        // Stage 1
        m_state = s0;
        compute_derivatives(&k1x1, &k1x2);

        // Stage 2
        m_state.h = s0.h + 0.5 * dt * k1x1;
        m_state.v = s0.v + 0.5 * dt * k1x2;
        compute_derivatives(&k2x1, &k2x2);

        // Stage 3
        m_state.h = s0.h + 0.5 * dt * k2x1;
        m_state.v = s0.v + 0.5 * dt * k2x2;
        compute_derivatives(&k3x1, &k3x2);

        // Stage 4
        m_state.h = s0.h + dt * k3x1;
        m_state.v = s0.v + dt * k3x2;
        compute_derivatives(&k4x1, &k4x2);

        // Update state using weighted average
        s.h = s0.h + (dt/6.0) * (k1x1 + 2.0*k2x1 + 2.0*k3x1 + k4x1);
        s.v = s0.v + (dt/6.0) * (k1x2 + 2.0*k2x2 + 2.0*k3x2 + k4x2);
    }

public:
    BouncingBall() : m_g(9.81), m_c(0.8) {
        m_state.h = 10.0;  // Initial height
        m_state.v = 0.0;   // Initial velocity
    }

    // Getters
    double get_height() const { return m_state.h; }
    double get_velocity() const { return m_state.v; }

    // Setters
    void set_height(double height) { m_state.h = height; }
    void set_velocity(double velocity) { m_state.v = velocity; }

    // Compute derivatives
    void compute_derivatives(double* dx1dt, double* dx2dt) {
        *dx1dt = m_state.v;  // dx1/dt = velocity
        *dx2dt = -m_g;       // dx2/dt = acceleration
    }

    // Handle bounce event
    bool check_and_handle_event() {
        if (m_state.h <= 0.0 && m_state.v < 0.0) {
            m_state.v = -m_c * m_state.v;  // Bounce: reverse and dampen velocity
            m_state.h = 0.0;            // Ensure height doesn’t go negative
            return true;               // Event occurred
        }
        return false;
    }

    // Step the model forward
    void do_step(double t, double dt) {
        // Advance the simulation state using RK4 numerical integration
        rk4(m_state, dt);

        // Check and handle bounce condition after integration
        // This ensures the bounce is processed at the new state
        check_and_handle_event();
    }
};