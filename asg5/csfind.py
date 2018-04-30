import argparse
import os, sys
from stat import *

def main():
	parser = argparse.ArgumentParser()
	# name flag
	parser.add_argument('-name')
	# grep flag
	parser.add_argument('-grep')
	args = parser.parse_args()

	if args.name:
		print "NAME"
		print args.name
	if args.grep:
		print "GREP"
		print args.grep

if __name__ == '__main__': main()
