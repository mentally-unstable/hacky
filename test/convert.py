
filename = 'out.hack'
with open(filename, 'rb') as f:
    lines = [
            [int(line[0:4], 2),
             int(line[4:8], 2),
             int(line[8:12], 2),
             int(line[12:16], 2)]
            for line in f]

with open(f'{filename[0:4]}.diff', 'w+') as f2:
    for line in lines:
        i = 0
        for num in line:
            if i < 4:
                f2.write(f'{num:x}')
            i += 1
        f2.write('\n')
