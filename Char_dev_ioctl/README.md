# Linux character device driver with basic IOCtl commands

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
  Once you've installed the module, you just have the program left to run . So you just need to execute the user application program and you should be able to write and read IOCtls commands to your new device driver! :)

## 4. Deleting the module
  Once you finished with your program, you can execute the following commands to undo what you've done :
  ```
  sudo sh clean.sh
  ```
  Or  :
  ```
  sudo ./clean.sh
  ```

  
  Happy code!
