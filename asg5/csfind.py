import argparse
import os, sys
from stat import *

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument('filename')
	# name flag
	parser.add_argument('-name')
	# grep flag
	parser.add_argument('-grep')
	args = parser.parse_args()

	filelist =  os.listdir(sys.argv[1])

	for i in filelist:
		print os.path.abspath(i)
	
	if args.name:
	if args.grep:
		print "GREP"
		print args.grep

if __name__ == '__main__': main()
