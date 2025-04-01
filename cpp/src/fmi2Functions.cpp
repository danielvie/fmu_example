#include "fmi2Functions.h"
#include "BouncingBall.cpp"
#include <cstring>
#include <memory>

// FMI instance data
typedef struct {
    std::shared_ptr<BouncingBall> model;
    fmi2CallbackFunctions* functions;
    fmi2Boolean loggingOn;
} ModelInstance;

#define VR_HEIGHT 0  // Value reference for height
#define VR_VELOCITY 1  // Value reference for velocity

// Mandatory FMI 2.0 functions
fmi2Component fmi2Instantiate(fmi2String instanceName, fmi2Type fmuType,
                              fmi2String fmuGUID, fmi2String fmuResourceLocation,
                              const fmi2CallbackFunctions* functions,
                              fmi2Boolean visible, fmi2Boolean loggingOn) {
    std::shared_ptr<ModelInstance> comp = std::make_shared<ModelInstance>();
    comp->model = std::make_shared<BouncingBall>();
    comp->functions = const_cast<fmi2CallbackFunctions*>(functions);
    comp->loggingOn = loggingOn;
    return (fmi2Component)comp.get();
}

void fmi2FreeInstance(fmi2Component c) {
    ModelInstance* comp = static_cast<ModelInstance*>(c);
    if (comp) {
        comp->model.reset();
    }
}

fmi2Status fmi2SetDebugLogging(fmi2Component c, fmi2Boolean loggingOn,
                               size_t nCategories, const fmi2String categories[]) {
    ModelInstance* comp = static_cast<ModelInstance*>(c);
    if (!comp) {
        return fmi2Error;
    }
    comp->loggingOn = loggingOn;
    return fmi2OK;
}

fmi2Status fmi2SetupExperiment(fmi2Component c, fmi2Boolean toleranceDefined,
                               fmi2Real tolerance, fmi2Real startTime,
                               fmi2Boolean stopTimeDefined, fmi2Real stopTime) {
    return fmi2OK;
}

fmi2Status fmi2EnterInitializationMode(fmi2Component c) {
    return fmi2OK;
}

fmi2Status fmi2ExitInitializationMode(fmi2Component c) {
    return fmi2OK;
}

fmi2Status fmi2DoStep(fmi2Component c, fmi2Real currentCommunicationPoint,
                      fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint) {
    ModelInstance* comp = static_cast<ModelInstance*>(c);
    if (!comp) {
        return fmi2Error;
    }
    comp->model->do_step(currentCommunicationPoint, communicationStepSize);
    return fmi2OK;
}

fmi2Status fmi2Terminate(fmi2Component c) {
    return fmi2OK;
}

fmi2Status fmi2Reset(fmi2Component c) {
    ModelInstance* comp = static_cast<ModelInstance*>(c);
    if (!comp) {
        return fmi2Error;
    }
    comp->model.reset();
    comp->model = std::make_shared<BouncingBall>();
    return fmi2OK;
}

fmi2Status fmi2GetReal(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Real value[])
{
    ModelInstance* comp = static_cast<ModelInstance*>(c);
    if (!comp) {
        return fmi2Error;
    }

    for (size_t i = 0; i < nvr; i++) {
        if (vr[i] == VR_HEIGHT) {
            value[i] = comp->model->get_height();
        }
        else if (vr[i] == VR_VELOCITY) {
            value[i] = comp->model->get_velocity();
        }
        else {
            return fmi2Error;
        }
    }
    return fmi2OK;
}

fmi2Status fmi2SetReal(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Real value[]) {
    ModelInstance* comp = static_cast<ModelInstance*>(c);
    if (!comp) {
        return fmi2Error;
    }

    for (size_t i = 0; i < nvr; i++) {
        if (vr[i] == VR_HEIGHT) {
            comp->model->set_height(value[i]);
        }
        else if (vr[i] == VR_VELOCITY) {
            comp->model->set_velocity(value[i]);
        }
        else return fmi2Error;
    }
    return fmi2OK;
}

fmi2Status fmi2GetInteger(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Integer value[]) {
    return fmi2Error;
}

fmi2Status fmi2GetBoolean(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Boolean value[]) {
    return fmi2Error;
}

fmi2Status fmi2GetString(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2String value[]) {
    return fmi2Error;
}

fmi2Status fmi2SetInteger(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Integer value[]) {
    return fmi2Error;
}

fmi2Status fmi2SetBoolean(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Boolean value[]) {
    return fmi2Error;
}

fmi2Status fmi2SetString(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2String value[]) {
    return fmi2Error;
}

fmi2String fmi2GetTypesPlatform(void) {
    return "default";
}

fmi2String fmi2GetVersion(void) {
    return "2.0";
}

// Optional Co-Simulation functions (stubs)
fmi2Status fmi2GetFMUstate(fmi2Component c, fmi2FMUstate* FMUstate) {
    return fmi2Error;
}

fmi2Status fmi2SetFMUstate(fmi2Component c, fmi2FMUstate FMUstate) {
    return fmi2Error;
}

fmi2Status fmi2FreeFMUstate(fmi2Component c, fmi2FMUstate* FMUstate) {
    return fmi2Error;
}

fmi2Status fmi2SerializedFMUstateSize(fmi2Component c, fmi2FMUstate FMUstate, size_t* size) {
    return fmi2Error;
}

fmi2Status fmi2SerializeFMUstate(fmi2Component c, fmi2FMUstate FMUstate, fmi2Byte serializedState[], size_t size) {
    return fmi2Error;
}

fmi2Status fmi2DeSerializeFMUstate(fmi2Component c, const fmi2Byte serializedState[], size_t size, fmi2FMUstate* FMUstate) {
    return fmi2Error;
}

fmi2Status fmi2GetDirectionalDerivative(fmi2Component c, const fmi2ValueReference vUnknown_ref[], size_t nUnknown,
                                        const fmi2ValueReference vKnown_ref[], size_t nKnown,
                                        const fmi2Real dvKnown[], fmi2Real dvUnknown[]) {
    return fmi2Error;
}

fmi2Status fmi2SetRealInputDerivatives(fmi2Component c, const fmi2ValueReference vr[], size_t nvr,
                                       const fmi2Integer order[], const fmi2Real value[]) {
    return fmi2Error;
}

fmi2Status fmi2GetRealOutputDerivatives(fmi2Component c, const fmi2ValueReference vr[], size_t nvr,
                                        const fmi2Integer order[], fmi2Real value[]) {
    return fmi2Error;
}

fmi2Status fmi2CancelStep(fmi2Component c) {
    return fmi2Error;
}

fmi2Status fmi2GetStatus(fmi2Component c, const fmi2StatusKind s, fmi2Status* value) {
    return fmi2Error;
}

fmi2Status fmi2GetRealStatus(fmi2Component c, const fmi2StatusKind s, fmi2Real* value) {
    return fmi2Error;
}

fmi2Status fmi2GetIntegerStatus(fmi2Component c, const fmi2StatusKind s, fmi2Integer* value) {
    return fmi2Error;
}

fmi2Status fmi2GetBooleanStatus(fmi2Component c, const fmi2StatusKind s, fmi2Boolean* value) {
    return fmi2Error;
}

fmi2Status fmi2GetStringStatus(fmi2Component c, const fmi2StatusKind s, fmi2String* value) {
    return fmi2Error;
}