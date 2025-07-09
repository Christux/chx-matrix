import subprocess
import pytest

@pytest.fixture(scope="session", autouse=True)
def build_extension():
    print("⏳ Compilation du module C...")
    subprocess.run(["python3", "setup.py", "build_ext", "--inplace"], check=True)
    print("✅ Compilation terminée.")
