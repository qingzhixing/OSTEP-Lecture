#!/usr/bin/python3
import os
import time

pid = os.fork()
if pid < 0:
    print("Fork failed")
    exit(1)

if pid == 0:
    print("Child process")
else:
    time.sleep(0.01)
    print("Parent process")
