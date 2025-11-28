import os

pid = os.fork()
if pid < 0:
    print("Fork failed")
    exit(1)
if pid == 0:
    args = ["env"]
    environment = {"PATH": "/bin"}
    os.execvpe("env", args, environment)
