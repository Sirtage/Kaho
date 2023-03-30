import os

_Cdname = "kaho"

_Lignore = ["resource.h", "KahoExec.cpp"]

try:
    os.mkdir(_Cdname)
except:
    1

arr = os.listdir()
for i in range(len(arr)):
    if (arr[i][len(arr[i])-2:] == ".h" or arr[i][len(arr[i])-4:] == ".cpp") and arr[i] not in _Lignore:
        with open(f"{_Cdname}/{arr[i]}", 'w') as f:
            with open(arr[i], 'r') as r:
                f.write(r.read())
