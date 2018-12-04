import matplotlib.pyplot as plt
import matplotlib.animation as animation
import math
from matplotlib import style
style.use('classic')

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
# ax2 = fig.add_subplot(1,1,1)
fig.suptitle('Manual Bot Heading')
plt.ylabel("Time")
plt.xlabel("Angle")
plt.autoscale(enable=False,axis='both')
l_d = []
x_d = []
e_d = []
xs = []
ys = []
def animate(i):
    global l_d,x_d,e_d
    graph_data = open('new.txt','r').read()
    lines = graph_data.split('\n')
    i = 0
    for line in lines:
        if len(line) > 1:
            data = line.split('|')
            x,y = data[0].split(',')
            x = float(x)
            y = int(y)
            l_d.append(x)
            ax1.plot(x,y)
            x,y = data[1].split(',')
            x = float(x)
            y = int(y)
            x_d.append(x)
            ax1.plot(x,y)
            x,y = data[2].split(',')
            x = float(x)
            y = int(y)
            e_d.append(x)
            ax1.plot(x,y)
            ys.append(y)
    ax1.clear()
    ax1.plot(l_d)
    ax1.plot(x_d)
    ax1.plot(e_d)
    plt.legend(['LSM', 'XBOX', 'Error'], loc='upper left')
    l_d = []
    x_d = []
    e_d = []

# print(xs,ys)
ani = animation.FuncAnimation(fig, animate, interval = 1,repeat = False)
plt.show()
