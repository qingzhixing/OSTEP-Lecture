import os

pid = os.fork()
if pid < 0:
    print("Fork failed")
    exit(1)

if pid == 0:
    try:
        print(f"Child process {os.getpid()} waitpid() returns:", os.waitpid(pid, 0))
    except OSError as e:
        print(f"Child process {os.getpid()} waitpid() failed:", e)
else:
    try:
        print(f"Parent process {os.getpid()} waitpid() returns:", os.waitpid(pid, 0))
    except OSError as e:
        print(f"Parent process {os.getpid()} waitpid() failed:", e)
