#
# mdoUniq.py - my uniq for looking between
#

import sys
import io

argFname = 1
argStart = 2
argEnd   = 3

prevLine = ""

if len(sys.argv) != 4:
   print('USAGE: fname "start string" "end string"')
   exit(0)

fobj = open(sys.argv[argFname], 'rt')
# print("DEBUG - open %s" % sys.argv[argFname])
theLine = fobj.readline()
# print("DEBUG - first line |%s|" % theLine)
while "" != theLine: # null string means EOF
   theLine = theLine.strip()
   # print("DEBUG - line.strip() |%s|" % theLine)
   nStart = theLine.find(sys.argv[argStart])
   nEnd = theLine.find(sys.argv[argEnd])
   if (-1 == nStart):
      nStart = 0
   if (-1 == nEnd):
      nEnd = len(theLine)
   if prevLine != theLine[nStart:nEnd]:
      print("%s" % theLine)
   # else:
   # print("strt:%d end:%d entire|%s| prev|%s| this|%s|" % (nStart, nEnd, theLine, prevLine, theLine[nStart:nEnd]))
   prevLine = theLine[nStart:nEnd]
   # read the next line
   theLine = fobj.readline()
fobj.close()
