#!/usr/bin/python3
import os

x = 10

pid = os.fork()

if pid < 0:
    print("Fork failed")
    exit(1)

print("Before we change x:", x)
if pid == 0:
    x = 20
    print("Child process: x =", x)
else:
    x = 100
    print("Parent process: x =", x)
