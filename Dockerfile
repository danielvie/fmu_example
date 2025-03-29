FROM python:3.13-slim

WORKDIR /app

# Install system dependencies required for uv and Python
RUN apt-get update && apt-get install -y --no-install-recommends \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Install uv via pip and verify
RUN pip install -U uv \
    && uv --version

# Set Python environment variables for better behavior
ENV PYTHONDONTWRITEBYTECODE=1 \
    PYTHONUNBUFFERED=1
    
# Copy python project
# COPY ./python_test/.python_version .
COPY python_test/.python-version .
COPY python_test/main_docker.py .
COPY python_test/pyproject.toml .

RUN uv sync
    
CMD [ "bash", "-c", "uv run main_docker.py" ]