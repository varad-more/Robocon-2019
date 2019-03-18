import math

x = []
y = []
r = 20
count = 0
for ang in range(180,0,-1):
	x.append(int(r*math.cos(ang*math.pi/180)))
	y.append(int(40 - r*math.sin(ang*math.pi/180)))
	
for a in range(len(x)):
#	print('{',x[a],',',y[a],'},',end="")
	continue
for b in range(20,-21,-1):
	if b == 0 :
		continue
	print('{',b,',',45,'},',end="")
	count = count + 1

print(count)
