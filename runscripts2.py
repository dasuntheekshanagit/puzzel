import subprocess

FILE = 3

def main():
    #for i in range(FILE):
    
    sts = True
    grid = ""
    word=""
    
    for i in range(FILE):
        fileName = "puzzel"+ str(i+1)+".txt"
        file = open(fileName,'r')
        data = file.readlines()
        
        data = "".join(data)
        #print(data)
        out = subprocess.run(["puzzel1.exe","-","-"],shell=True,input=data.encode())
        print()
        file.close()

if __name__ == '__main__':
    main()