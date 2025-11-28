#!/usr/bin/python3
import os

fileName = "test.txt"
file = open(fileName, "w")

pid = os.fork()
if pid < 0:
    print("Fork failed")
    exit(1)

if pid == 0:
    # 检查是否能访问open返回的描述符
    if file.write("Child process\n") == -1:
        print("Child process: write failed")
else:
    # 检查是否能访问open返回的描述符
    if file.write("Parent process\n") == -1:
        print("Parent process: write failed")

# 预期结果:
# Parent process
# Child process
#
# or
#
# Child process
# Parent process
