#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

/* Use 'k' as magic number */
#define MY_MAGIC_NUMBER 'k'
#define MY_IOCTL_READ_BLOCKING _IOW('k', 1, unsigned long *)
#define DEVICE "/dev/my_device"
#define open_mode O_RDWR
#define SIZE_BUFF 512

char write_buf[SIZE_BUFF];
char read_buf[SIZE_BUFF];


int main(void){
	int fd, err;
        int32_t activation;
        char option;
	char *response;
        printf("*********************************\n");
        printf("**************TONIAS*************\n");
        fd = open(DEVICE, open_mode);
        if(fd < 0) {
                printf("Cannot open device file %s\n", DEVICE);
                return 0;
        }
        while(1) {
again:
		 printf("\n");
                 fflush(stdout);
                 printf("****Do you wish to enable read blocking operation?******\n");
		 printf("******************Please type yes or no*****************\n");
                 scanf("%[^\t\n]s", response);

		 if(!strcmp(response, "yes")) activation = 1;
		 else if(!strcmp(response, "no")) activation = 0;
		 else {
			/*FIXME: For some reason when he enters here it gets in a infinite loop and i can not
			 * get to update response's value*/ 
		 	printf("Please enter a valid option.\n");
			printf("Your option : %s", response);
			goto again;
		 }
                 switch(activation){
                        case 0:
                                err = ioctl((int)fd, MY_IOCTL_READ_BLOCKING, &activation);
                                break;
                        case 1:
                                err = ioctl((int)fd, MY_IOCTL_READ_BLOCKING, &activation);
				break;
                        default:
                                printf("Invalid option.\n");
                                exit(-1);                       
                 }

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
                                exit(1);
                                break;
                        default:
                                printf("Enter Valid option = %c\n",option);
                                goto repeat;
                                break;
                }
        }
        close(fd);




	return 0;
}
