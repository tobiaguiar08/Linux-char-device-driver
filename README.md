# How to use it 

To be able to run this application, there are a few steps to follow :

## 1. Compilation
  To compile  the application, we need to build the kernel module and the user space program. To do so, we make use of the make file and it will generate the necessary outputs. So you just need to open a terminal and write :
  ```
  make
  ```

## 2. Module installation
  Once the step 1 is finished, you need to load your new custom module into the kernel, and create a new device node as an abstraction for this driver. To do this there is a shell script which will take care of all that, so you just need to execute it with the following command :
  ```
  sudo sh install.sh
  ```
  Or, if you are in the same directory as the file :
  ```
  sudo ./install.sh
  ```
  Keep in mind that you are touching areas with privilege access (the linux kernel), that's why you need to execute it as super user.
## 3. Running the program
  Once you've installed the module, you just have the program left to run . So you just need to execute the user application program and you should be able to write and read to your new device driver! :)

## 4. Deleting the module
  Once you finished with your program, you can execute the following commands to undo what you've done :
  ```
  sudo sh clean.sh
  make clean
  ```
  Or if you are in the same directory as the files :
  ```
  sudo ./clean.sh
  make clean
  ```
### Notes
  Feel free to modify and use the code as you want. If you find something like an error or if i said something wrong, or even if my english is not clear for you, please feel also free to let me know that, so we can grow together. If you have comments or criticism i am all ears, after all i'm still a beginner in this, not trivial, field. I'm still going to keep modifing this repository and add more information and details (Like trying to explain the lines of the makefile and shellscript, and also add more comments to the sources files) to keep as undestandable as possible.
  
  Happy code!
