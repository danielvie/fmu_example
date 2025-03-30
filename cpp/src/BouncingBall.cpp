#include <cmath>
#include "BouncingBall.h"

class BouncingBall {
private:
    // State structure
    State state;

    // Parameters
    double g;  // Gravity (m/s²)
    double c;  // Coefficient of restitution

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
        state = s0;
        computeDerivatives(&k1x1, &k1x2);

        // Stage 2
        state.h = s0.h + 0.5 * dt * k1x1;
        state.v = s0.v + 0.5 * dt * k1x2;
        computeDerivatives(&k2x1, &k2x2);

        // Stage 3
        state.h = s0.h + 0.5 * dt * k2x1;
        state.v = s0.v + 0.5 * dt * k2x2;
        computeDerivatives(&k3x1, &k3x2);

        // Stage 4
        state.h = s0.h + dt * k3x1;
        state.v = s0.v + dt * k3x2;
        computeDerivatives(&k4x1, &k4x2);

        // Update state using weighted average
        s.h = s0.h + (dt/6.0) * (k1x1 + 2.0*k2x1 + 2.0*k3x1 + k4x1);
        s.v = s0.v + (dt/6.0) * (k1x2 + 2.0*k2x2 + 2.0*k3x2 + k4x2);
    }

public:
    BouncingBall() : g(9.81), c(0.8) {
        state.h = 10.0;  // Initial height
        state.v = 0.0;   // Initial velocity
    }

    // Getters
    double getHeight() const { return state.h; }
    double getVelocity() const { return state.v; }

    // Setters
    void setHeight(double height) { state.h = height; }
    void setVelocity(double velocity) { state.v = velocity; }

    // Compute derivatives
    void computeDerivatives(double* dx1dt, double* dx2dt) {
        *dx1dt = state.v;  // dx1/dt = velocity
        *dx2dt = -g;       // dx2/dt = acceleration
    }

    // Handle bounce event
    bool checkAndHandleEvent() {
        if (state.h <= 0.0 && state.v < 0.0) {
            state.v = -c * state.v;  // Bounce: reverse and dampen velocity
            state.h = 0.0;            // Ensure height doesn’t go negative
            return true;               // Event occurred
        }
        return false;
    }

    // Step the model forward
    void doStep(double t, double dt) {
        // Advance the simulation state using RK4 numerical integration
        rk4(state, dt);

        // Check and handle bounce condition after integration
        // This ensures the bounce is processed at the new state
        checkAndHandleEvent();
    }
};