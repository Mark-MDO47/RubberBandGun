#
# Author: Mark Olson 2020-09-04
#
# This trivial code strips out blank lines, leaving a blank line only before
#    a line that begins with "--"
#

import argparse

def stripblanklns(infile):
  fptr = open(infile, "rt")
  ln = fptr.readline()
  while ln:
    ln = ln.strip()
    if 0 != len(ln):
      if (2 <= len(ln)) and ("--" == ln[:2]):
         print(" ")
      print("%s" % ln)
    ln = fptr.readline()

if __name__ == "__main__":
    my_parser = argparse.ArgumentParser(prog='stripblanklns',
        formatter_class=argparse.RawTextHelpFormatter,
        description="stdout receives input file with blank lines removed.\n  Lines that start with -- will be preceeded by blank line",
        epilog="""Example:
python stripblanklns.py file.txt > noblanks.txt
""",
        usage='%(prog)s infile')
    my_parser.add_argument('infile',type=str,help='path to infile.txt')
    args = my_parser.parse_args()

    stripblanklns(args.infile)
