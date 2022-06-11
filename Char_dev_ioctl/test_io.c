#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

/*Use 'k' as magic number*/
#define MY_MAGIC_NUMBER 'k'
#define MY_IOC_W _IOW(MY_MAGIC_NUMBER, 0 , unsigned char *)
#define MY_IOC_R _IOR(MY_MAGIC_NUMBER, 1, unsigned char *)

#define DEVICE "/dev/my_ioc_device"
#define open_mode O_RDWR
#define SIZE_BUFF 512

char write_buf[SIZE_BUFF];
char read_buf[SIZE_BUFF];


int main(void){
	int fd, err;
	unsigned char response[50];
        char option;
        int activation;
        printf("***************************************************\n");
        printf("********************TOBIAS*************************\n");
        fd = open(DEVICE, open_mode);
        if(fd < 0) {
                printf("Cannot open device file %s\n", DEVICE);
                exit(-1);
        }
        printf("****Please enter the option you want to do : ******\n");
        printf("****IOCTL Operations or common R/W operations******\n");
       printf("****************(Type IOCTL or common)**************\n");
	scanf("%s",response);
	if(!strcmp(response, "IOCTL")) {
		goto again;	
	}		
	else if(!strcmp(response,"common")) {
		goto repeat;
	}		
	else { 	       	
		printf("Bad input.\n");
		exit(-1);
	}

	//printf("response : %s\n", response);
	
	
        while(1) {
                again:
                 printf("****Please enter the IOCTL Option******\n");
                 printf("        1.IOCTL Write               \n");
                 printf("        2.IOCTL Read                 \n");
                 printf("        3. Exit                 \n");
                 printf("*********************************\n");
                 scanf(" %d", &activation);
                 switch(activation){
                        case 1:
                                printf("Enter the string to write into driver :");
                                scanf("  %[^\t\n]s", write_buf);
                                printf("Data Writing ...");
                                err = ioctl(fd, MY_IOC_W, write_buf);
				if (err < 0) {
					printf("IOCTL Write failed.\n");
					exit(-1);
				}
                                printf("Done!\n");
                                break;
                        case 2:
                        	fflush(stdout);
                                printf("Data Reading ...");
                                err = ioctl(fd, MY_IOC_R, read_buf);
				if (err < 0) {
					printf("IOCTL READ failed.\n");
					exit(-1);
				}
                                printf("Done!\n\n");
                                printf("Data = %s\n\n", read_buf);
                                break;
			case 3:
                                close(fd);
                                printf("Exiting..\n");
				return 0;
			default:
                                printf("Enter Valid option. Your option : %d\n",activation);
                                goto again;
                        break;                        
                 }
		goto again;
        	repeat:
                printf("****Please Enter the Option******\n");
                printf("        1. Write               \n");
                printf("        2. Read                 \n");
                printf("        3. Exit                 \n");
                printf("*********************************\n");
                scanf(" %c", &option);
                printf("Your Option = %c\n", option);
                
                switch(option) {
                        case '1':
                                printf("Enter the string to write into driver :");
                                scanf("  %[^\t\n]s", write_buf);
                                printf("Data Writing ...");
                                write(fd, write_buf, strlen(write_buf)+1);
                                printf("Done!\n");
                                break;
                        case '2':
                        		fflush(stdout);
                                printf("Data Reading ...");
                                read(fd, read_buf, SIZE_BUFF);
                                printf("Done!\n\n");
                                printf("Data = %s\n\n", read_buf);
                                break;
                        case '3':
                                close(fd);
                                printf("Exiting..\n");
				return 0;
                        default:
                                printf("Enter Valid option. Your option : %c\n",option);
                                goto repeat;
                                break;
                }
		goto repeat;
        }
	
        close(fd);




	return 0;
}
