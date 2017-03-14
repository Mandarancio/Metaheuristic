def import_dat(path: str):
    f = open(path)
    lines = f.read().split('\n')
    f.close()
    n=int(lines[0])
    D=[]
    for i in range(2,14):
        nums=lines[i].split(' ')
        row=[]
        for nm in nums:
            if len(nm)>0:
                row.append(int(nm))
        D.append(row)
    W=[]
    for i in range(15,27):
        nums=lines[i].split(' ')
        row=[]
        for nm in nums:
            if len(nm)>0:
                row.append(int(nm))
        W.append(row)
    return n,D,W
