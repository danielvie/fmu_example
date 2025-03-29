# from fmpy import read_model_description, simulate_fmu
import fmpy
from pathlib import Path

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
    fmu_path = 'cpp_fmu_out/BouncingBall.fmu'
    
    print(f'reading {fmu_path}...')
    assert Path(fmu_path).is_file() == True


    # simulate
    result = try_catch(lambda: fmpy.simulate_fmu(fmu_path, start_time=0.0, stop_time=5.0, step_size=0.01))
    
    if result.fail():
        print('this went wrong: ', result.error)
        return

    # extract results
    time = result.value['time']
    height = result.value['h']
    velocity = result.value['v']
    
    for t,h,v in zip(time, height, velocity):
        print(f'{t:5.2f}, {h:7.2f}, {v:7.2f}')

    # dumping model info
    fmpy.dump(fmu_path)

if __name__ == "__main__":
    main()
