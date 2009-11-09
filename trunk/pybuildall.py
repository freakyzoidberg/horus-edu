import os
import os.path
import shutil
import getpass

print "Hey " + getpass.getuser()

if getpass.getuser() == "zoidberg":
    MV_CLIENT_PLUGINS_TO="/home/zoidberg/.Horus/Plugins/"
    MV_SERVER_PLUGINS_TO=""
    PATH_TO_TRUNK="/home/zoidberg/Epitech/EIP/trunk/"
elif getpass.getuser() == "toto":
    MV_CLIENT_PLUGINS_TO=""
    MV_SERVER_PLUGINS_TO=""
    PATH_TO_TRUNK=""
else:
    MV_CLIENT_PLUGINS_TO=""
    MV_SERVER_PLUGINS_TO=""
    PATH_TO_TRUNK="."


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    ENDC = '\033[0m'

    def disable(self):
        self.HEADER = ''
        self.OKBLUE = ''
        self.OKGREEN = ''
        self.ENDC = ''


def ParseCompileCopy(fromwhere, towhere):
    print bcolors.HEADER + "Compiling " + fromwhere + bcolors.ENDC
    os.chdir(fromwhere)
    os.system("qmake")
    os.system("make")
    os.chdir("Plugins")
    flag = 0
    
    for filename in os.listdir ("./"):
        if os.path.isdir (os.path.join (filename)) and filename != ".svn":
            print bcolors.OKBLUE + "Compiling " + filename + bcolors.ENDC
            os.chdir(filename)
            os.system("qmake")
            os.system("make")
            if towhere != "":
                for pluginfiles in os.listdir ("./"):
                    if pluginfiles.endswith(".so") or pluginfiles.endswith(".dll"):
                        print bcolors.OKGREEN + "Copying " + pluginfiles + bcolors.ENDC
                        shutil.copy (pluginfiles,towhere)
            os.chdir("..")
    os.chdir("../..")
    return

os.chdir(PATH_TO_TRUNK)
ParseCompileCopy("./Client", MV_CLIENT_PLUGINS_TO)
ParseCompileCopy("./Server", MV_SERVER_PLUGINS_TO)
