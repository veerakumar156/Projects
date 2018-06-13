#!/usr/bin/env python

import os
import re
import sys
 
 
def usage():
	print '\nUsage:'
	print '\t\tpython process_regex.py <root_dir> <keyword>'
	print '\t\tExamples : python process_regex.py "." ".*"'
	print '\t\t         : python process_regex.py C:\Users\Public .*'
	print 'Requires two input arguments'
	print '<root_dir> - directory in which the search should be done'
	print '<keyword> - regular expression to be used for the search'

	
def validate_inputs(root_dir, keyword):
	valid_root_path = validate_root_dir(root_dir)
	if valid_root_path == "":
		print "Enter a valid directory name"
		return 
	
	if not validate_keyword(keyword):
		print "Enter a valid regular expression"
		return
	return valid_root_path
	

def validate_root_dir(root_dir):
	try:
		if root_dir == "\\":
			return ""
		elif (root_dir == ".") or (os.path.isdir(root_dir)):
			return root_dir
		else:
			valid_root_path = os.path.join(os.getcwd(), root_dir)
			if os.path.exists(valid_root_path):
				return valid_root_path 
			else:
				return ""
	except IOError as e:
		print "I/O error({0}): {1}".format(e.errno, e.strerror)
	except: #handle other exceptions such as attribute errors
		print "Unexpected error:", sys.exc_info()[0]
		return ""

		
def validate_keyword(keyword):
	try:
		re.compile(keyword)
		return True
	except re.error:
		return False
		
		
def search_for_regular_expressions(valid_root_path, keyword):
	extensions_list = ['.txt', '.text', '.log', '.dat']
	regex_matches = dict()
	try:
		# traverse root directory, and list directories as dirs and files as files
		for root, dirs, files in os.walk(valid_root_path, topdown = False):
			count = 0 
			for file in files:
				absolute_path =  os.path.join(root, file)
				if not (os.path.splitext(absolute_path)[-1] in extensions_list): #Skip processing PDF or word documents 
					continue
				elif file == currentfile: #Skip processing this .py file 
					continue
				f = open(absolute_path, "rb")
				for line in f:
					if re.search(keyword, line):
						count =  count+1
				subdir_path = os.path.dirname(os.path.abspath(absolute_path))
				regex_matches[subdir_path] = count
	except IOError as e:
		print "I/O error({0}): {1}".format(e.errno, e.strerror)
	except: #handle other exceptions such as attribute errors
		print "Unexpected error:", sys.exc_info()[0]

	for k,v in regex_matches.items():
		print k,'\t\t',v
	return regex_matches

	if not regex_matches:
		return 
	x = []
	y = []
	
	for k,v in regex_matches.items():
		head, tail = os.path.split(os.path.split(k)[-1])
		x.append(tail)
		y.append(v)

	plt.plot(x, y, color='green', linestyle='dashed', linewidth = 3,
			 marker='o', markerfacecolor='blue', markersize=12)
	plt.xlabel('Names of sub directories')
	plt.ylabel('Regex match count')
	plt.title('Subdirectories vs Regex matches')
	plt.show()
		
		
def main(currentfile,root_dir, keyword):
	valid_root_path = validate_inputs(root_dir, keyword)
	regex_matches = search_for_regular_expressions(valid_root_path, keyword)

if __name__== "__main__":
	if len(sys.argv) != 3:
		usage()
	else:
		root_dir = sys.argv[1]
		keyword = sys.argv[2]
		currentfile = sys.argv[0]
		main(currentfile,root_dir, keyword)

