import math

dirpath = './dummy_output/'

for n in range(50, 501, 50):
    filename = 'n'+str(n)+'.txt'
    limit = math.ceil(n/4)
    with open(dirpath+filename, 'w+') as f:
        f.write('0\n')
        for i in range(3):
            for j in range(limit):
                if j != 0:
                    f.write(' ')
                f.write(str(j+i*limit+1))
            f.write('\n')
        for i in range(3*limit+1, n):
            f.write(str(i)+' ')
        f.write(str(n)+'\n')
