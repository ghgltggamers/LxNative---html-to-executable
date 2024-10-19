# LxNative
This is a program used to turn an LxProject into an Native executable of currrent Operating System.

Make sure that you already has
Gtk3 and WebKit3 for gtk installed with base-devel and boost installed for running and compling the app


create a project with a file named project.lxnative and paste the template in file
```lxnative
NAME=your app name

# port will contain the port where your app is going to be listened
PORT=2993

# EXEC_INCLUDE must contain a zip file which will hold your all the html files.
EXEC_INCLUDE=your zip file.zip

# package your app in form of com.yourcompainy.appname
EXEC_PCKG=com.yoourcompainy.app

# That's it your are ready to build a project
```


after this give your project path to lxnative for compiling it simply give the path to the directory containing project.lxnative not the file. eg

correct usage
```bash
lxnative /path/to/your/project/
```

wrong usage
```bash
lxnative /path/to/your/project/project.lxnative
```

## That's it now you are ready for main compilation !
But before you get into the steps for compiling you would need to make it sure that you already has the following packages already installed :-

GTK3
WEBKIT GTK
boost
base-devel
GNU/GCC G++ or LLVM Clang++

if yes then make sure that you already have transpiled your project then open your project directory and there you must see a package ddirectory if not then follow previous steep first and then after you have the directory follow this.

open the package and you would see a lxbuild.sh file permit it forr execution and fire it via terminal and once you have fired it up then wait for a while your app will be transpiled!.
