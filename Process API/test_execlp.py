import os

pid = os.fork()
if pid < 0:
    print("Fork failed")
    exit(1)
if pid == 0:
    args = ["ls", "-l", "."]
    os.execlp("ls", *args)
