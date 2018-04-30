import argparse
import os, sys
from stat import *

parser = argparse.ArgumentParser()
# name flag
parser.add_argument('-name')
# grep flag
parser.add_argument('-grep')
args = parser.parse_args()

if args.name:
	print "NAME"
elif args.grep:
	print "GREP"
