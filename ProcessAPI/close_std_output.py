import sys

sys.stdout.close()

try:
    print("Hello, world!")
except Exception as e:
    sys.stderr.write("write failed: " + str(e) + "\n")
