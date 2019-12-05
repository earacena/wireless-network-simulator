import tkinter as tk
from tkinter import *
from tkinter import ttk
from functools import *
import random
import math

def get_parameters():
    return param_list

def midpoint(ax, ay, bx, by):
    c = [(ax+bx)/2,(ay+by)/2]
    return c

def make_edge(root, source_x, source_y, dest_x, dest_y, channel_no):
    color = ""
    if channel_no==0:
        color = "#0000ff"
    if channel_no==1:
        color = "yellow"
    if channel_no==2:
        color = "orange"
    if channel_no==3:
        color = "magenta"
    if channel_no==4:
        color = "cyan"
    root.create_line(source_x, source_y, dest_x, dest_y, fill=color, width=2)

def dist_bool(Ax,Ay,Bx,By, max_dist):
    a = abs(Ax-Bx)
    b = abs(Ay-By)
    c = math.sqrt((a*a)+(b*b))
    if c > max_dist:
        print("coord exceeds radius: ")
        print(c)
        return False
    else:
        print("coordinate okay: ")
        print(c)
        return True

def make_BS(root, bsid):
    radius = 250
    color="red"
    x = random.randrange(200,800)
    y = random.randrange(200,800)
    coord = [x,y]
    root.create_oval(x-radius, y-radius, x+radius, y+radius, outline="red")
    root.create_rectangle(x-10, y-10, x+10, y+10, fill=color, outline="white")
    root.create_text(x,y,text=bsid, fill="white")
    return(coord)

def init_DV(root,coord_ls,N, dv_ls):
    radius = 250
    for i in range(N):#Loop for N nodes
        #Select random BS
        BSID = random.randrange(0,len(coord_ls))
        x = coord_ls[BSID][0]
        y = coord_ls[BSID][1]
        #Generate random coordinates in BS radius
        dvx = random.randrange(x-radius, x+radius)
        dvy = random.randrange(y-radius, y+radius)
        while not dist_bool(x,y,dvx,dvy,radius):
            dvx = random.randrange(x-radius, x+radius)
            dvy = random.randrange(y-radius, y+radius)
        #Create device on canvas
        root.create_oval(dvx-10, dvy-10, dvx+10, dvy+10, outline="#2fff00", fill="#2fff00")
        root.create_text(dvx,dvy,text=i, fill="black")
        #Record device coordinates
        dv_ls.append([dvx,dvy])

def init_BS(root, enter, enterB, BSn, noden, BSls, nodels, init):
    if(init == 0):
        n = ord(enter.get())-48
        print(n)
        m = 0
        if enterB.get()=="10":
            m = 10
        else:
            m = ord(enterB.get())-48
        print(m)
        ltrLs = ['A','B','C']
        coords = []
        for i in range(n):
            coords.append(make_BS(root, ltrLs[i]))
        #Inititalize Nodes in BS's
        BSls = coords
        BSn = n
        noden = m
        init_DV(root, BSls, m, nodels)
        init = 1
        
def print_contents(root):
    print(root.get())
            
def init_path(root, srcn, destn, node_ls, chnl, lbl):
    s = srcn.get()
    d = destn.get()
    src = ord(srcn.get())-48
    dest = ord(destn.get())-48
    Ax = node_ls[src][0]
    Ay = node_ls[src][1]
    Bx = node_ls[dest][0]
    By = node_ls[dest][1]
    make_edge(root, Ax,Ay,Bx,By, chnl)
    #Midpoint function call
    md = midpoint(Ax, Ay, Bx, By)
    #md[0],md[1]
    #mx = Ax + (abs(Ax-Bx)/2)
    #my = Ay + (abs(Ay-By)/2)
    root.create_text(md[0],md[1]+10, text=s+'->'+d, fill="white")
    lbl['text']+=s+'->'+d+'\n'

                                           
master = Tk()
node_cnt = 0
BS_cnt = 0
BS_list = []
node_list = []
grid_init = 0
#Node graph interface
w = Canvas(master, width=1000, height=1000, background="black")
w.pack(side=LEFT)
#User input frame
f = Frame(master, background="grey")
f.pack(side=RIGHT, fill=Y)
#BS Label
bl = Label(f, text="BS #", background="grey")
bl.pack(side=TOP, fill=X)
#Input for BS number
e = ttk.Spinbox(f,from_=1,to=3, width=8)
e.pack(padx = 5, pady = 5, fill=X, side=TOP)
#DV Label
dl = Label(f, text="DV #", background="grey")
dl.pack(side=TOP, fill=X)
#Input for DV number
eB = ttk.Spinbox(f,from_=1,to=10, width=10)
eB.pack(padx = 5, pady = 5, fill=X, side=TOP)
b = Button(f, text="Initialize", command=partial(init_BS, w, e, eB, BS_cnt, node_cnt, BS_list, node_list, grid_init))
b.pack()
#Add Route
#Input boxes
routeF = Frame(f, background="grey")
routeF.pack(side=TOP)
srcL = Label(routeF, text="Src:", background="grey")
srcL.pack(side=LEFT)
srcE = Entry(routeF, width=4)
srcE.pack(side=LEFT, fill=X)
destL = Label(routeF, text="Dest:", background="grey")
destL.pack(side=LEFT)
destE = Entry(routeF, width=4)
destE.pack(side=LEFT, fill=X)
#Routelist Label
routeL = Frame(f, background="grey")

rL = Label(routeL, text="")
rL.pack()
#Input button
routeB = Frame(f, background="grey")
routeB.pack(side=TOP)
rB = Button(routeB, text="Add Route", command=partial(init_path, w, srcE, destE, node_list, random.randrange(0,4), rL))
rB.pack()
routeL.pack(side=TOP)
confB = Button(f, text="Confirm Route Selection")
confB.pack(side=TOP)

#Execute Route

#make_BS(w, 'A')
#make_BS(w, 'B')
#make_BS(w, 'C')

#w.create_line(0, 0, 200, 100)
#make_edge(w, 0, 0, 200, 100, 2)
#w.create_line(0, 100, 200, 0, fill="red", dash=(4, 4))

#w.create_rectangle(50, 25, 150, 75, fill="blue")

mainloop()
