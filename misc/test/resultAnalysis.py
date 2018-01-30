from collections import Counter
import sys
import matplotlib.pyplot as plt

#filename = sys.argv[1]
#f=open(filename,"r")
f2=open("ActualFreq.txt","r")
f3=open("BloomFreq.txt","r")
#f5=open("MBFFreq_proj_0.txt","r")
f4=open("ResultFreq.txt","w")
numdiffiden=0
MBFnumdiffiden=0
hist={}
histval=[]
MBFhist={}
MBFhistval=[]
numDiff=[]
MBFnumDiff=[]
isDiff = []
MBFisDiff = []
totaliden=0
MBFtotaliden=0
numWrite=[]
MBFnumWrite=[]
act=f2.readlines()
bf=f3.readlines()
#MBFFreq=f5.readlines()
LBAfreq={}
falseIdenRate=[]
for x in act:
  LBAfreq[int(x.split(' ')[0])] = int(x.split(' ')[1])

for y in bf:
  #print y.split(' ')[1]
  BFelem = int(y.split(' ')[0])
  BFfreq = int(y.split(' ')[1])
  #BFelem = int(y.split(' ')[1])
  #BFfreq = float(y.split(' ')[2])
  Diff = 0
  #print BFelem, BFfreq
  if BFelem in LBAfreq:
    totaliden = totaliden+1
    if LBAfreq[BFelem] != int(BFfreq):
      numdiffiden = numdiffiden+1
      Diff=1
    f4.write("{} {} {} {}\n".format(int(BFelem), int(LBAfreq[BFelem]),  int(BFfreq),  int(numdiffiden)))
    isDiff.append(Diff)
    numWrite.append(totaliden)
    numDiff.append(numdiffiden)
    falseIdenRate.append(float(numdiffiden)/float(totaliden)*100)  
    if abs(LBAfreq[BFelem] - int(BFfreq)) not in hist:
      hist[abs(LBAfreq[BFelem] - int(BFfreq))] = 1
    else:
      hist[abs(LBAfreq[BFelem] - int(BFfreq))]=hist[abs(LBAfreq[BFelem] - int(BFfreq))] + 1
histval = hist.values()
totfalseIdenRate=float(numdiffiden)/float(totaliden)
print "numdiffiden"
print numdiffiden
print "totaliden"
print totaliden
print "float(totfalseIdenRate)"
print float(totfalseIdenRate)
print "float(1/totfalseIdenRate)"
print float(1/totfalseIdenRate)
print"histval"
print histval
#plt.bar(hist.keys(), histval)
#plt.show()
#plt.plot(numDiff)
#plt.show()
# for z in MBFFreq:
#   MBFelem = int(z.split(' ')[1])
#   MBFfreq = int(float(z.split(' ')[2]))
#   MBFDiff = 0
#   #print MBFelem
#   if int(MBFelem) in LBAfreq:
#     MBFtotaliden = MBFtotaliden+1
#     if LBAfreq[MBFelem] != (MBFfreq):
#       #print "%s %s" % (LBAfreq[MBFelem], MBFfreq)
#       MBFnumdiffiden = MBFnumdiffiden+1
#       MBFDiff=1
#     #f4.write("{} {} {} {}\n".format(int(BFelem), int(LBAfreq[BFelem]),  int(BFfreq),  int(numdiffiden)))
#     MBFisDiff.append(MBFDiff)
#     MBFnumWrite.append(MBFtotaliden)
#     MBFnumDiff.append(MBFnumdiffiden)
#     falseIdenRate.append(float(MBFnumdiffiden)/float(MBFtotaliden)*100)
#     if abs(LBAfreq[MBFelem] - int(MBFfreq)) not in MBFhist:
#       MBFhist[abs(LBAfreq[MBFelem] - int(MBFfreq))] = 1
#     else:
#       MBFhist[abs(LBAfreq[MBFelem] - int(MBFfreq))]=MBFhist[abs(LBAfreq[MBFelem] - int(MBFfreq))] + 1 
# MBFhistval = MBFhist.values()

# MBFtotfalseIdenRate=float(MBFnumdiffiden)/float(MBFtotaliden)
# print "MBFnumdiffiden"
# print MBFnumdiffiden
# print "MBFtotaliden"
# print MBFtotaliden
# print "float(MBFtotfalseIdenRate)"
# print float(MBFtotfalseIdenRate)
# print "float(1/MBFtotfalseIdenRate)"
# print float(1/MBFtotfalseIdenRate)
# print"MBFhistval"
# print MBFhistval
#plt.plot(falseIdenRate)
#plt.show()
#plt.plot(MBFnumDiff)
#plt.show()

#print isDiff
f2.close()
f3.close()
#f5.close()