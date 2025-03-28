#include <cmath>

class BouncingBall {
private:
    // State variables
    double h;  // Height (m)
    double v;  // Velocity (m/s)
    // Parameters
    double g;  // Gravity (m/s²)
    double c;  // Coefficient of restitution

public:
    BouncingBall() : h(10.0), v(0.0), g(9.81), c(0.8) {}

    // Getters
    double getHeight() const { return h; }
    double getVelocity() const { return v; }

    // Setters
    void setHeight(double height) { h = height; }
    void setVelocity(double velocity) { v = velocity; }

    // Compute derivatives
    void computeDerivatives(double* dhdt, double* dvdt) {
        *dhdt = v;
        *dvdt = -g;
    }

    // Handle bounce event
    bool checkAndHandleEvent() {
        if (h <= 0.0 && v < 0.0) {
            v = -c * v;  // Bounce: reverse and dampen velocity
            h = 0.0;     // Ensure height doesn’t go negative
            return true; // Event occurred
        }
        return false;
    }

    // Step the model forward
    void doStep(double t, double dt) {
        double dhdt, dvdt;
        computeDerivatives(&dhdt, &dvdt);

        // Simple Euler integration
        h += dhdt * dt;
        v += dvdt * dt;

        // Check for bounce
        checkAndHandleEvent();
    }
};