import sys
import os

def main():
	print(f"The body of the request passed to the cgi is of length {os.environ['CONTENT_LENGTH']} and is :")
	for line in sys.stdin:
		print(line)

if __name__ == "__main__":
	exit(main())