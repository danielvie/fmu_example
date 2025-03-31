import zipfile
import os
from pathlib import Path

def fmu_zip(folder_name, fmu_name):
    # create a zipfile object
    
    Path(fmu_name).parent.mkdir(exist_ok=True)
    with zipfile.ZipFile(fmu_name, 'w') as f:
        # walk through the folder
        for root, dirs, files in os.walk(folder_name):
            for file in files:
                file_path = os.path.join(root, file)
                f.write(file_path, os.path.relpath(file_path, start=folder_name))

# Example usage
fmu_zip('cpp/z_fmu_out', 'cpp_fmu_out/BouncingBall.fmu')