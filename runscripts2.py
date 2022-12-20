import subprocess

FILE = 4

def main():
    #for i in range(FILE):
    
    sts = True
    grid = ""
    word=""
    
    for i in range(FILE):
        fileName = "puzzel"+ str(i+1)+".txt"
        file = open("puzzels/"+fileName,'r')
        data = file.readlines()
        
        data = "".join(data)
        print("Test Case",i+1,":")
        print(data)
        print("Output:")
        out = subprocess.run(["puzzel1.exe","-","-"],shell=True,input=data.encode())
        print("Return Code:",out.returncode)
        print()
        
        file.close()

if __name__ == '__main__':
    main()