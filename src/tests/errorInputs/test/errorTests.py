#!/usr/bin/python
import os, sys ,re
import subprocess

for file in os.listdir("."):
    if file.endswith(".cmm"):
        p = subprocess.Popen(["./rx-cc",file], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = p.communicate()
        rc = p.returncode
        if "SemErr" in file:
            if not(err.startswith("Semantic error:")):
                print "expected Semantic error in:", file
            if not (rc==3):
                print "expected returncode 3 in:", file
        elif "SynErr" in file:
            if not(err.startswith("Syntax error:")):
                print "expected Syntax error in:", file
            if not (rc==2):
                print "expected returncode 2 in:", file
                
p = subprocess.Popen(["./rx-cc",file, file], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
out, err = p.communicate()
rc = p.returncode
if not(err.startswith("Operational error:")):
    print "expected Operational error"
if not (rc==9):
    print "expected returncode 9"