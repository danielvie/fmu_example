import sys
import shutil

RED = "\033[91m"
MAGENTA = "\033[35m"
RESET = "\033[0m"

# specify the directory
assert len(sys.argv) == 2

# get folder path
folder_path = sys.argv[1]

# delete folder
try:
    shutil.rmtree(folder_path)
except Exception as e:
    print(f"{RED}ERROR:{MAGENTA} {e}{RESET}")
