# from fmpy import read_model_description, simulate_fmu
import fmpy
from pathlib import Path

def main():

    # loading fmu
    fmu_path = 'cpp_fmu_out/BouncingBall.fmu'
    
    print(f'reading {fmu_path}...')
    assert Path(fmu_path).is_file() == True


    # simulate
    result = fmpy.simulate_fmu(fmu_path, start_time=0.0, stop_time=5.0, step_size=0.01)
    
    # extract results
    time = result['time']
    height = result['h']
    velocity = result['v']
    
    for t,h,v in zip(time, height, velocity):
        print(f'{t:5.2f}, {h:7.2f}, {v:7.2f}')

    # dumping model info
    fmpy.dump(fmu_path)

if __name__ == "__main__":
    main()
