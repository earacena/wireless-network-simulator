import tkinter as tk
from tkinter import *
from tkinter import ttk
from functools import *
import random
import math
import time
import matplotlib
import Metrics
from PIL import Image, ImageTk
import subprocess

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
        ls += [l[i][0:len(l[i])-1].split(",")]
    print(ls)
    ls = ls[:-1]
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
    generate_random_graphs()
    subprocess.run(["a_out.exe"])
    

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

def randomize_node(pair, bs_crd_list):
    radius=250
    rand_bs = random.randrange(1, len(bs_crd_list))
    x = bs_crd_list[rand_bs][0]
    y = bs_crd_list[rand_bs][1]
    dvx = random.randrange(x-radius, x+radius)
    dvy = random.randrange(y-radius, y+radius)
    while not dist_bool(x,y,dvx,dvy,radius) and dvx<1000 and dvy<1000:
            dvx = random.randrange(x-radius, x+radius)
            dvy = random.randrange(y-radius, y+radius)
    pair = [dvx, dvy]
    return pair

def generate_random_graphs():
    f = open("data.txt","r")
    s = f.read()
    print("modifying file...")
    lsf = s.split('\n')
    print(s)
    nls = []
    bls = []
    rls = []
    for i in range(len(lsf)):
        if(lsf[i][0]=='N' and lsf[i][1]==' ' ):
            ln = lsf[i].split(" ")[2].split(",")
            nls.append([int(ln[0]),int(ln[1])])
        if(lsf[i][0]=='B' and lsf[i][1]==' ' ):
            ln = lsf[i].split(" ")[2].split(",")
            bls.append([int(ln[0]),int(ln[1])])        
        if(lsf[i][0]=='R' and lsf[i][1]==' ' ):
            ln = lsf[i].split(" ")[1].split(",")
            rls.append([int(ln[0]),int(ln[1])])
    snode = int(rls[0][0])
    enode = int(rls[0][1])
    for h in range(2):
        lsf_temp = lsf
        nls_temp = []
        for i in range(len(nls)):
            if i!=snode and i!=enode:
                nls_temp.append(randomize_node(nls[i], bls))
            else:
                nls_temp.append(nls[i])
        j = 0
        for i in range(len(lsf_temp)):
            if(lsf_temp[i][0]=='N' and lsf_temp[i][1]==' ' ):
                lsf_temp[i] = 'N '+str(j)+" "+str(nls_temp[j][0])+','+str(nls_temp[j][1])
                j += 1
        s_temp = '\n'.join(lsf_temp)
        filename = "data"+str(h+1)+".txt"
        file = open(filename, "w")
        file.write(s_temp)
        file.close()
        print(s_temp)
    if len(nls) < 10:
        for h in range(3):
            print("version "+str(h+1))
            lsf_temp = lsf[:]
            nls_temp = []
            for i in range(len(nls)+1):
                if i!=snode and i!=enode:
                    nls_temp.append(randomize_node([0,0], bls))
                else:
                    nls_temp.append(nls[i])
            print("Len: "+str(len(nls_temp)))
            j = 0
            for i in range(len(lsf_temp)+1):
                if(i < len(lsf_temp)-1 and lsf_temp[i][0]=='N' and lsf_temp[i][1]=='N' ):
                    lsf_temp[i] = 'NN '+str(len(nls_temp))
                if(i < len(lsf_temp)-1 and lsf_temp[i][0]=='N' and lsf_temp[i][1]==' ' ):
                    lsf_temp[i] = 'N '+str(j)+" "+str(nls_temp[j][0])+','+str(nls_temp[j][1])
                    j += 1
                if i==len(lsf_temp):
                    lsf_temp.append('N '+str(j)+" "+str(nls_temp[j][0])+','+str(nls_temp[j][1]))
            print(lsf)
            print(lsf_temp)
            s_temp = '\n'.join(lsf_temp)
            filename = "data"+str(h+1)+"B.txt"
            file = open(filename, "w")
            file.write(s_temp)
            file.close()
            print(s_temp)
##    if len(nls) == 10:
##        for h in range(3):
##            print("version "+str(h+1))
##            lsf_temp = lsf[:]
##            nls_temp = []
##            for i in range(len(nls)):
##                if i!=snode and i!=enode:
##                    nls_temp.append(randomize_node([0,0], bls))
##                else:
##                    nls_temp.append(nls[i])
##            print("Len: "+str(len(nls_temp)))
##            j = 0
##            toggle = 0
##            for i in range(len(lsf_temp)):
##                if(i < len(lsf_temp)-1 and lsf_temp[i][0]=='N' and lsf_temp[i][1]=='N' ):
##                    lsf_temp[i] = 'NN '+str(len(nls_temp)-1)
##                if(i < len(lsf_temp)-1 and lsf_temp[i][0]=='N' and lsf_temp[i][1]==' ' ):
##                    lsf_temp[i] = 'N '+str(j)+" "+str(nls_temp[j][0])+','+str(nls_temp[j][1])
##                    j += 1
##            rn = random.randrange(0,9)
##            while (rn==snode or rn==enode):
##                rn = random.randrange(0,10)
##            for i in range(len(lsf_temp)):
##                if(i < len(lsf_temp)-1 and lsf_temp[i][0]=='N' and lsf_temp[i][1]==' ' and int(lsf_temp[i][2])==rn):
##                     del lsf_temp[i]
##                
##            print(lsf)
##            print(lsf_temp)
##            s_temp = '\n'.join(lsf_temp)
##            filename = "data"+str(h+1)+"B.txt"
##            file = open(filename, "w")
##            file.write(s_temp)
##            file.close()
##            print(s_temp)
    Metrics.main()
##    imgA = Image.open("/Users/acret/AppData/Local/Programs/Python/Python37/graph-hops-nodes.png")
##    photoA = ImageTk.PhotoImage(imgA)
##    imgB = Image.open("/Users/acret/AppData/Local/Programs/Python/Python37/graph-switches-channels.png")
##    photoB = ImageTk.PhotoImage(imgB)
##    photoA = PhotoImage("graph-hops-nodes.png")
##    photoB = PhotoImage("graph-switches-channels.png")

    
    
    

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
