from django.shortcuts import render
from django.http import *
import os
lsm_heading = 0
xbox_heading = 0
heading_error = 0    
print("Variables Initialized")
count = 0


def index(request):
    if request.method == 'GET':
        global count
        global f
        data = request.GET
        lsm_heading = float(data['l'])
        xbox_heading = float(data['x'])
        heading_error = float(data['e'])
        print(lsm_heading,xbox_heading,heading_error,count)
        if count < 150 :
            f = open('new.txt',"a+")
            # a = (lsm_heading,count)
            # b = (xbox_heading,count)
            # c = (heading_error,count)
            f.write(str(lsm_heading)+','+str(count)+'|')
            f.write(str(xbox_heading)+','+str(count)+'|')
            f.write(str(heading_error)+','+str(count))
            f.write("\n")
            f.close()
            count = count + 1
        else:
            # a = (lsm_heading,count)
            # b = (xbox_heading,count)
            # c = (heading_error,count)
            f = open('new.txt',"a+")
            f.write(str(lsm_heading)+','+str(count)+'|')
            f.write(str(xbox_heading)+','+str(count)+'|')
            f.write(str(heading_error)+','+str(count))
            f.write("\n")
            count = 0
            f.close()
            f = open('new.txt',"w")
            f.truncate(0)
            f.seek(0)
            f.close()
        return HttpResponse(":-)")
    else:
        return HttpResponse("Server Got Your Request :-(")  





