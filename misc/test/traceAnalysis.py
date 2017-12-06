from collections import Counter
import sys
filename = sys.argv[1]
traceType = sys.argv[2]
chunk_size = 4
f=open(filename,"r")
f2=open("ActualFreq.txt","w")
f3=open("chunkwiseFile.txt","w")
lines=f.readlines()
LBA=[]
for x in lines:
	if traceType == "0":
		elem = long(x.split(' ')[2])
		size = long(x.split(' ')[3])
	elif traceType == "MSR":
		elem = long(x.split(',')[4])/512
		size = long(x.split(',')[5])/512
	elif traceType == "FIU":
		elem = long(x.split(' ')[3])
		size = long(x.split(' ')[4])
	elif traceType == "UMASS":
		elem = long(x.split(',')[1])
		size = long(x.split(',')[2])/512

	LBA.append(elem/chunk_size)
	if (size/chunk_size) > 1:
		#print int(size/chunk_size)
		for i in xrange((size/chunk_size)-1):
			LBA.append((elem/chunk_size)+1+i)

# for x in lines:
# 	if x.split(',')[3] == "Write":
# 	LBA.append(x.split(',')[4]/512)
f.close()
for item in LBA:
	f3.write("%s\n" % item)
cLBA=Counter(LBA)
#print LBA

for k,v in  cLBA.iteritems():
	f2.write("{0} {1}\n".format(k, v))
f2.close()