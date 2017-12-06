from collections import Counter
import sys
import matplotlib.pyplot as plt

#filename = sys.argv[1]
#f=open(filename,"r")
f2=open("ActualFreq.txt","r")
f3=open("BloomFreq.txt","r")
f4=open("ResultFreq.txt","w")
numdiffiden=0
numDiff=[]
isDiff = []
totaliden=0
numWrite=[]
act=f2.readlines()
bf=f3.readlines()
LBAfreq={}
falseIdenRate=[]
for x in act:
  LBAfreq[x.split(' ')[0]] = x.split(' ')[1]

for y in bf:
  totaliden = totaliden+1
  BFelem = y.split(' ')[0]
  BFfreq = y.split(' ')[1]
  Diff = 0
  if LBAfreq[BFelem] != BFfreq:
    numdiffiden = numdiffiden+1
    Diff=1
  f4.write("{} {} {} {}\n".format(int(BFelem), int(LBAfreq[BFelem]),  int(BFfreq),  int(numdiffiden)))
  isDiff.append(Diff)
  numWrite.append(totaliden)
  numDiff.append(numdiffiden)
  falseIdenRate.append(float(numdiffiden)/float(totaliden)*100)  

totfalseIdenRate=float(numdiffiden)/float(totaliden)
print numdiffiden
print totaliden
print float(totfalseIdenRate*100)
print float(1/totfalseIdenRate)
#plt.plot(falseIdenRate)
#plt.show()
plt.plot(numDiff)
plt.show()
#print isDiff
f2.close()
f3.close()