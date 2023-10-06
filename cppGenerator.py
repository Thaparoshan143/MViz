import os

def getCppFileContent(fileName):
    include = "#include\"" + f'{fileName}' + ".h\"\n"
    openWrapper = "\nnamespace Sandbox\n{\n"
    defaultConst = f'\t{fileName}::{fileName}()\n' + "\t{\n\n\t}\n\n"
    paraConst = f'\t{fileName}::{fileName}(...)\n' + "\t{\n\n\t}"
    closeWrapper = "\n}"
    fileContent = include + openWrapper + defaultConst + paraConst + closeWrapper
    return fileContent

def getHFileContent(fileName):
    include = f'#pragma once\n\n'
    openWrapper = "namespace Sandbox\n{\n"
    openClass = f'\tclass {fileName}\n'
    classContent = "\t{\n\t\tpublic:\n\t\t" + f'{fileName}();\n\t\t{fileName}(...);\n\n\t\tprivate:\n\n'
    closeClass = "\t};\n"
    closeWrapper = "\n}"
    fileContent = include + openWrapper + openClass + classContent + closeClass + closeWrapper
    return fileContent


fileName = input()
fileNameList = fileName.split()

currDir = os.getcwd()
# Edit with the directory to start populating the file with
generatingDir = "/Sandbox/Base/"
workingDir=currDir+generatingDir
print("Working at directory: " + workingDir)

try:
    for fileName in fileNameList:
        with open(workingDir + fileName + ".cpp","w") as ncppf:
            ncppf.write(getCppFileContent(fileName))
        with open(workingDir + fileName+ ".h", "w") as nhf:
            nhf.write(getHFileContent(fileName))
        
        print("Cpp file : " + fileName + ".cpp and Header File : " + fileName + ".h generated successfully")
except:
    print("Error in dir or code! try again after debugging")