# FMU Example

This repository is a lab for testing and learning how FMUs (Functional Mock-up Units) work, including how to build them and how to use them!

**What are FMUs and FMI?**  
- **FMU (Functional Mock-up Unit):** A file (usually a `.fmu` archive) that contains a simulation model or component, including its implementation and metadata, designed to be portable across different tools.  
- **FMI (Functional Mock-up Interface):** A standard that defines how FMUs are structured and interfaced, enabling co-simulation and model exchange between various simulation environments.  
- **Learn More:** Visit the official FMI website for detailed specifications and resources: [fmi-standard.org](https://fmi-standard.org/).

## 🛠️ Dependencies for this project

This project requires the following dependencies:
- Taskfile  
- Python 3.10+  
- uv  
- Zig 0.14.0

Instructions for installing each are provided below.

### ➡️ **Taskfile**  
  A task runner to simplify build and run commands.  
  **Installation**:  
  - Download and install from the official site: [go-task.github.io](https://taskfile.dev/installation/).  

### ➡️ **Python 3.10+**  
  Required for running the Python-based FMU example.  
  **Installation**:  
  - Download from [python.org](https://www.python.org/downloads/)
  - Verify: `python --version` (or `python3 --version` on Linux/Mac).

### ➡️ **uv**  
  A fast Python package manager and dependency resolver.  
  **Installation**:  
  - Install via pip: 
  ```powershell
  pip install uv  
  ```

  - Or follow the official guide: [astral.sh/uv](https://docs.astral.sh/uv/getting-started/installation/).  
  - Verify:
  ```powershell
  uv --version
  ```

### ➡️ **Zig 0.14.0**  
  A programming language and toolchain used for building the C++ components.  
  **Installation**:  
  - Download the 0.14.0 release from [ziglang.org](https://ziglang.org/download/).  
  - Verify: (should output `0.14.0`).
  ```powershell
  zig version
  ```

## ⌨️ Main Commands

Below are the primary commands for interacting with this project, powered by Taskfile.

- **`task build`**  
  Builds the FMU (Functional Mock-up Unit) from the C++ source code using Zig.  
  - Prerequisites: Zig 0.14.0 must be installed and available in your PATH.  
  - Output: Generates the FMU binary in the project directory.

- **`task main`**  
  Builds the FMU (as above) and runs it using the provided Python example.  
  - Prerequisites: Python 3.10+, uv, and the FMU built via `task build`.  
  - Behavior: Executes the Python script to simulate or test the FMU.

## 🚀 Getting Started

1. Install all dependencies listed above.
2. Clone this repository: 
```powershell
git clone https://github.com/danielvie/fmu_example.git
```
3. Navigate to the project directory: 
```powershell
cd fmu_example
```
4. Run to build the FMU.
```powershell
task build
```
5. Run to build and test the FMU using Python.
```powershell
task main
```

<!-- ## Contributing

[Optional: Add instructions for contributing, e.g., "Feel free to submit issues or pull requests on GitHub."]

## License

[Specify your license, e.g., "This project is licensed under the MIT License - see the LICENSE file for details."] -->