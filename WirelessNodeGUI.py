import tkinter as tk
from tkinter import *
from tkinter import ttk
from functools import *
import random
import math
import time

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

def make_routes(root, Lbl, button):
    button.destroy()
    Lbl["text"] = ""
    file = open("routes.txt", "r")
    text = file.read()
    l = text.split("\n")
    ls = []
    for i in range(len(l)):
        ls += [l[i].split(",")]
    print(ls)
    #Get node coordinates
    info_file = open("data.txt", "r")
    texti = info_file.read()
    #print(texti)
    data = texti.split("\n")
    #print(data)
    lsi = []
    for i in range(len(data)):
        if data[i][0]=='N' and data[i][1]==' ':
            a = data[i].split(" ")
            #print(a)
            b = a[2].split(",")
            #print(b)
            lsi += [[int(b[0]),int(b[1])]]
    print(lsi)
    print(len(ls))
    print(int(len(ls)/3))
    lbl = root.create_text(0,0, text="", fill="white")
    for j in range(len(ls)):
        Lbl['text'] += "Route ["+ls[j][0]+"->"+ls[j][len(ls[j])-1]+"]\n"
        root.itemconfig(lbl, text=str(j+1))
        for i in range(0,int(len(ls[j]))-1,3):
            print()
            src = int(ls[j][i])
            print(src)
            chnl = int(ls[j][i+1])
            print(chnl)
            dest = int(ls[j][i+2])
            print(dest)
            print(lsi[src][0])
            Lbl["text"] += " "+str(ls[j][i])+"-["+str(ls[j][i+1])+"]->"+str(ls[j][i+2])+","
            make_edge(root, lsi[src][0], lsi[src][1], lsi[dest][0], lsi[dest][1], chnl)
            i += 2
        Lbl["text"] += "\n"        

def dist_bool(Ax,Ay,Bx,By, max_dist):
    a = abs(Ax-Bx)
    b = abs(Ay-By)
    c = math.sqrt((a*a)+(b*b))
    if c > max_dist:
        #print("coord exceeds radius: ")
        #print(c)
        return False
    else:
        #print("coordinate okay: ")
        #print(c)
        return True

def make_BS(root, bsid):
    radius = 250
    color="#3ce28e"
    x = random.randrange(200,800)
    y = random.randrange(200,800)
    coord = [x,y]
    root.create_oval(x-radius, y-radius, x+radius, y+radius, outline="#3ce28e", width=2)
    root.create_rectangle(x-10, y-10, x+10, y+10, fill=color, outline="#3ce28e")
    root.create_text(x,y,text=bsid, fill="black")
    return(coord)

def init_DV(root,coord_ls,N, dv_ls, file_string):
    radius = 250
    for i in range(N):#Loop for N nodes
        #Select random BS
        BSID = random.randrange(0,len(coord_ls))
        x = coord_ls[BSID][0]
        y = coord_ls[BSID][1]
        #Generate random coordinates in BS radius
        dvx = random.randrange(x-radius, x+radius)
        dvy = random.randrange(y-radius, y+radius)
        while not dist_bool(x,y,dvx,dvy,radius) and dvx<1000 and dvy<1000:
            dvx = random.randrange(x-radius, x+radius)
            dvy = random.randrange(y-radius, y+radius)
        #Create device on canvas
        root.create_oval(dvx-10, dvy-10, dvx+10, dvy+10, outline="#e1e1e1", fill="#e1e1e1")
        root.create_text(dvx,dvy,text=i, fill="black")
        #Record device coordinates
        dv_ls.append([dvx,dvy])
        file_string+= "\nN "+str(i)+" "+str(dvx)+","+str(dvy)
    #print(file_string)
    f = open("data.txt", "a")
    f.write(file_string)
    f.close()

def init_BS(root, enter, enterB, nodels, but, file_string):
    file_string = "GD 1000\nBSN "+enter.get()+"\nBSR 250 "+"\nNN "+enterB.get()+"\nNR 100 "
    n = ord(enter.get())-48
    #print(n)
    m = 0
    if enterB.get()=="10":
        m = 10
    else:
        m = ord(enterB.get())-48
    #print(m)
    ltrLs = ['A','B','C']
    coords = []
    for i in range(n):
        coords.append(make_BS(root, ltrLs[i]))
    #Inititalize Nodes in BS's
        #print(coords)
    #print("BS list")
    #print(coords)
    for i in range(len(coords)):
        file_string+="\nB "+ltrLs[i]+" "+str(coords[i][0])+","+str(coords[i][1])
    #print("BS Count")
    #print(n)
    init_DV(root, coords, m, nodels, file_string)
    init = 1
    but.destroy()
        
def print_contents(root):
    print(root.get())
            
def init_path(root, srcn, destn, node_ls, chnl, lbl):
    s = srcn.get()
    d = destn.get()
    lbl['text']+=s+'->'+d+'\n'

def conf_rts(rt_lst_wgt, butt, file_string, pkbutton, destbutton):
    main = file_string
    #Parse loop of route text widget
    wdgt = rt_lst_wgt['text']
    print(wdgt)
    rt_ls = wdgt.split("\n")
    print(rt_ls)
    for i in range(1,len(rt_ls)-1):
        rt = rt_ls[i].split("->")
        print(rt)
        if len(rt) != 0:
            main+=("\nR "+rt[0]+","+rt[1])
    #R NodeID,NodeID (route request)
    #Open, write file
    f = open("data.txt","a")
    f.write(main)
    print(main)
    print("wrote to file")
    f.close()
    #Destroy route add button
    butt.destroy()
    pkbutton.pack(side=TOP, pady=4)
    destbutton.destroy()

#def create_rt(route_list)

#Command to Initiate Route Execution

file = open("data.txt", 'w')
file.write("")
file.close()

master = Tk()
master.title("Wireless Network Interface")
master["background"]="#3ce28e"
node_cnt = 0
BS_cnt = 0
BS_list = []
node_list = []
file = ""  
grid_init = 0
#Node graph interface
w = Canvas(master, width=1000, height=1000, background="#2f2f2f")
w.pack(side=LEFT)
##
s = math.sqrt(1000)
for i in range(int(s)):
    for j in range(int(s)):
        r = w.create_rectangle(i*s, j*s, (i*s)+s, (j*s)+s, fill="#2f2f2f", outline="#2f2f2f",activefill="red")
##
#User input frame
f = Frame(master, background="#232522")
f.pack(side=RIGHT, fill=Y)
#BS Label
bl = Label(f, text="BS #", background="#3ce28e", fg="black")
bl.pack(side=TOP, fill=X)
#Input for BS number
e = ttk.Spinbox(f,from_=1,to=3, width=8)
e.pack(fill=X, side=TOP)
#DV Label
dl = Label(f, text="DV #", background="#3ce28e", fg="black")
dl.pack(side=TOP, fill=X)
#Input for DV number
eB = ttk.Spinbox(f,from_=1,to=10, width=10)
eB.pack(fill=X, side=TOP)
b = Button(f, text="Initialize")
b['command'] = partial(init_BS, w, e, eB, node_list, b, file)
b.pack(pady=2)
#Add Route
#Input boxes
routeF = Frame(f, background="#3ce28e")
routeF.pack(side=TOP, pady=2, fill=X)
srcL = Label(routeF, text="Source Node:", background="#3ce28e", fg="black")
srcL.pack(side=LEFT, fill=X, pady=2)
srcE = Entry(routeF, width=4, relief="solid")
srcE.pack(side=LEFT,padx=2)
destL = Label(routeF, text="End Node:", background="#3ce28e", fg="black")
destL.pack(side=LEFT, fill=X)
destE = Entry(routeF, width=4, relief="solid")
destE.pack(side=LEFT, padx=2)
#Routelist Label
routeL = Frame(f, background="#3ce28e")

rL = Label(routeL, text="Routes:\n", background="white", width=20)
rL.pack(pady=4,padx=4)
#Input button
routeB = Frame(f, background="#4c4c4c")
routeB.pack(side=TOP)
rB = Button(routeB, text="Add Route", command=partial(init_path, w, srcE, destE, node_list, random.randrange(0,4), rL))
rB.pack(pady=2)
routeL.pack(side=TOP, fill=X)
confB = Button(f, text="Confirm Route Selection")
confB.pack(side=TOP, pady=4)
confX = Button(f, text="Execute Routes")
confB['command']=partial(conf_rts, rL, rB, file,confX, confB)
confX['command']=partial(make_routes, w, rL, confX)

mainloop()
