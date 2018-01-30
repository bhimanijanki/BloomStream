from collections import Counter
import sys
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('Agg')
plt.style.use('seaborn-white')
import numpy as np
filename = sys.argv[1]
f=open(filename,"r")
lines=f.readlines()
LBA=[]
freq=[]
time=[]
count = 1
for x in lines:
	LBA.append(long(x.split(' ')[0]))
	freq.append(long(x.split(' ')[1]))
	time.append(long(count))
	count=count+1
fig = plt.contourf(time, LBA, freq, 20, cmap='RdGy')
plt.colorbar();
plt.show(hold=False)
plt.savefig('fig.pdf')

