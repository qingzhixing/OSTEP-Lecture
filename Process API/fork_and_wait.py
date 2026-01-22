import os

pid = os.fork()
if pid < 0:
    print("Fork failed")
    exit(1)

if pid == 0:
    try:
        print("Child process wait() returns:", os.wait())
    except OSError as e:
        print("Child process wait() failed:", e)
else:
    try:
        print("Parent process wait() returns:", os.wait())
    except OSError as e:
        print("Parent process wait() failed:", e)
