import zipfile
import os
from pathlib import Path
import shutil
import glob

def fmu_zip(folder_name, fmu_name):
    # create a zipfile object
    
    Path(fmu_name).parent.mkdir(exist_ok=True)
    with zipfile.ZipFile(fmu_name, 'w') as f:
        # walk through the folder
        for root, dirs, files in os.walk(folder_name):
            for file in files:
                file_path = os.path.join(root, file)
                f.write(file_path, os.path.relpath(file_path, start=folder_name))

def fmu_prepare(target_path: str):
    # creating folders
    Path(f"{target_path}/binaries/win64").mkdir(parents=True, exist_ok=True)
    Path(f"{target_path}/binaries/linux64").mkdir(parents=True, exist_ok=True)
    Path(f"{target_path}/src").mkdir(parents=True, exist_ok=True)

    shutil.copy("cpp/zig-out/x86_64-windows/BouncingBall.dll", f"{target_path}/binaries/win64")
    shutil.copy("cpp/zig-out/x86_64-linux-gnu/libBouncingBall.so", f"{target_path}/binaries/linux64/BouncingBall.so")
    for file in glob.glob("cpp/src/*.cpp"):
        shutil.copy(file, f"{target_path}/src/")
    shutil.copy("cpp/src/modelDescription.xml", f"{target_path}/")

fmu_prepare('z_fmu_out/temp')
fmu_zip('z_fmu_out/temp', 'z_fmu_out/BouncingBall.fmu')


