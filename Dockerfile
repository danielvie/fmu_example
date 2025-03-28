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
    
CMD [ "bash", "-c", "uv run main.py" ]