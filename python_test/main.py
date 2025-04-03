# from fmpy import read_model_description, simulate_fmu
from pathlib import Path
import fmpy
import matplotlib.pyplot as plt

class Result:
    def __init__(self, value, error):
        self.value = value
        self.error = error

    def ok(self):
        return self.error is None

    def fail(self):
        return self.error is not None

def try_catch(fun: callable):
    try:
        result = fun()
        return Result(result, None)
    except Exception as e:
        return Result(None, e)

def main():

    # loading fmu
    fmu_path = '../z_fmu_out/BouncingBall.fmu'
    
    print(f'reading {fmu_path}...')
    assert Path(fmu_path).is_file() == True

    # dumping model info
    # fmpy.dump(fmu_path)

    # simulate
    result = fmpy.simulate_fmu(fmu_path, start_time=0.0, stop_time=10.0, step_size=0.01)
    # model_description = fmpy.read_model_description(fmu_path)
    # fmu = fmpy.instantiate_fmu(model_description=model_description)
    
    # extract results
    time = result['time']
    height = result['h']
    velocity = result['v']

    # plot
    plt.figure()
    plt.subplot(2, 1, 1)
    plt.plot(time, height, label='Height (m)')
    plt.grid(True)
    plt.legend()
    plt.subplot(2, 1, 2)
    plt.plot(time, velocity, label='Velocity (m/s)')
    plt.grid(True)
    plt.legend()
    plt.xlabel('Time (s)')
    plt.show()

if __name__ == "__main__":
    main()
