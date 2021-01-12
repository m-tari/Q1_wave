#!/usr/bin/python
# -*-coding:utf-8 -*

# run this script to add wave directory to PATH

import os
import sys

WAVEROOT=os.environ['PWD']

INPUTTEXT = "\n# Applying WAVE environment variables\n"
INPUTTEXT+= "export PATH=$PATH:"+WAVEROOT+"/bin\n"
INPUTTEXT+= "\n"

path = os.environ['HOME']
name=path+"/.bashrc"

Input = open(name,"a")
Input.write(INPUTTEXT)
Input.close()