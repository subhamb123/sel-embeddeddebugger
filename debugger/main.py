import os

option = 0

while option != 4:
    print("-----------------\n")
    print("Embedded Debugger\n")
    print("-----------------\n")
    print("1. Run debugger\n")
    print("2. Run debugger from a snapshot\n")
    print("3. Delete a snapshot\n")
    option = int(input("4. Exit\n\n"))

    if option == 1:
        f = open("option.txt", "w")
        f.write(str(option))
        f.close()
        exec(open("debugger.py").read())
        exec(open("extractSymbolTable.py").read())
        f2 = open("version.txt", "r+")
        f2.write(int(f2.read()) + 1)
        f2.close()
        exec(open("StackDecode.py").read())
    elif option == 2:
        f = open("option.txt", "w")
        f.write(str(option))
        f.close()
        exec(open("extractSymbolTable.py").read())
        exec(open("StackDecode.py").read())
    elif option == 3:
        with open("archive.txt", "r") as f:
            lines = f.readlines()
            i = 0
            for line in lines:
                i += 1
                print(str(i) + ". " + line + "\n")
        with open("archive.txt", "w") as f:
            choice = input("\nYour choice: ")
            i = 0
            for line in lines:
                i += 1
                if i != int(choice):
                    f.write(line)
                else:
                    os.remove("./Versions/" + line)