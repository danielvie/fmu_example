# from fmpy import read_model_description, simulate_fmu
import fmpy
from pathlib import Path
import matplotlib.pyplot as plt

def main():

    # loading fmu
    fmu_path = './BouncingBall.fmu'
    
    print(f'reading {fmu_path}...')
    assert Path(fmu_path).is_file() == True

    # dumping model info
    fmpy.dump(fmu_path)

    # simulate
    result = fmpy.simulate_fmu(fmu_path, start_time=0.0, stop_time=10.0, step_size=0.01)
    
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
