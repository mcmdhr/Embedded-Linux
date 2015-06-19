#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BACKLOG 10
#define SUCCESS 0
#define ERR -1
#define UP 1
#define DOWN 2
#define CHAT 3
#define IMAGE 4
#define SONG 5
#define LED 6
#define TEMP 7

typedef struct sockaddr SA;

typedef struct info {
    int tag;
    int cmd;
	char filename[32];
    char buf[1024];
	int temp;

}INFO;

int fd;
int cli_fd;
INFO info;

void *work(void *arg);
int updata(INFO info);
int downdata(INFO info, int c_fd);
int check(INFO info, int c_fd);
int creatcon(int argc, char **argv);

void *image(void *arg);
int song(INFO info);
int led(INFO info);
void *temp(void *arg);
char *getImageToPC();
char *getImageToLCD();
float getTemp();

pthread_t pidImage = 0;
pthread_t pidTemp = 0;


int main(int argc ,char ** argv){
    int res = creatcon(argc, argv);
    while(1){
        cli_fd = accept(fd, NULL, NULL);
        if(cli_fd>0){
            printf("There is a client connect!\n");
			printf("%d\n",cli_fd);
            pthread_t pid = 0;
            pthread_create(&pid,NULL,work,(void *)cli_fd);
        }
    }

    return 0;
}

void *work(void * arg){
    int c_fd=(int)arg;
    int m=0;
	int x;
    memset(&info,0,sizeof(info));
    while(1){
//		puts("RECEIVE");
        fcntl(c_fd, F_SETFL, O_NONBLOCK);
		read(c_fd,&info,sizeof(info));
		//printf("tag = %d, cmd = %d\n",info.tag, info.cmd);
        switch(info.tag){
            case UP:
                m = updata(info);
                if( m == -1  )
                    printf("file up error");
				break;
            case DOWN:
                m = downdata(info,c_fd);
                if(m == -1)
                    printf("file downdata error");
                break;
            case CHAT:
                //m = check( info ,c_fd );
                if( m == -1)
                    printf("file null");
                break;
            case IMAGE:
				printf("IMAGE cmd= %d\n", info.cmd);
				x = info.cmd & 0xf000;
				if(x >0){
					//printf("xxxxx");
					pthread_create(&pidImage,NULL, image,(void *)c_fd);
					//image(info, c_fd);
				}else{
					pthread_cancel(pidImage);
				}
                break;
            case SONG:
				song(info);
                break;
            case LED:
				printf("LED cmd = %d\n",info.cmd);
				led(info);
                break;
            case TEMP:
				printf("TEMP cmd = %d\n",info.cmd);
				x = info.cmd & 0xf000000;
				//printf("%d\n",x);
				if(x >0){
					printf("%d\n",c_fd);
					pthread_create(&pidTemp,NULL, temp,(void *)c_fd);
					//image(info, c_fd);
				}else{
					pthread_cancel(pidTemp);
				}			
				//temp(info);
                break;
            default:
                ;
        }
        memset(&info,0,sizeof(info));
    }
}

int creatcon(int argc, char **argv){
    fd=socket(AF_INET,SOCK_STREAM,0);
    if( fd == -1 ){
        perror("socket");
        return ERR;
    }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,  //xie yi zhu
        .sin_port   = htons(atoi(argv[1])),//c -> int  zhuanhuan
        .sin_addr.s_addr  = htonl(INADDR_ANY),
    };

    int ret=0;
    ret = bind(fd, (SA *)&addr,sizeof(SA));
    if(ret == -1){
        perror("bind");
        return ERR;
    }

    ret =listen (fd , BACKLOG );//jianting lianjie geshu
    if( ret == -1 ){
        perror("listen");
        return ERR;
    }

    cli_fd = 0;

}

void *image(void *arg){
	while (1){
		int c_fd = (int)arg;
		puts("xxxxx");
		strcpy(info.filename, "1.jpg");
	//	strcpy(info.filename,getImageToPC());
		printf("filename = %s\n", info.filename);
		getImageToLCD();
		FILE * fp_image = fopen(info.filename,"r");
		if(!fp_image){
			char *buf = "no such file\n";
			printf("%s\n", buf);
			return;
			//return ERR;
		}
		fread(info.buf,sizeof(info.buf),1,fp_image);
		info.buf[strlen(info.buf)] = '\0';
		//printf("filename %s\n",info.filename);
		//puts(filename);
		write(c_fd,&info,sizeof(info));
		sleep(1);
	
	}
}

int song(INFO info){

}

int led(INFO info){

}

void *temp(void * arg){
	int c_fd = (int)arg;
	while (1){
		float t=0;
		t = getTemp();
		info.temp = t;
		printf("t = %f\n",t);
		printf("%d\n", c_fd);
		//fcntl(cli_fd, F_SETFL, O_NONBLOCK);
		write(c_fd, &info, sizeof(info));
		sleep(1);	
	}

}
int updata(INFO info){
    /*FILE * fp_up = fopen(info.filename,"w");
    fwrite(info.buf,strlen(info.buf),1,fp_up);
    fseek(fp_up, 0,SEEK_SET);
    fclose(fp_up);
    return SUCCESS;*/
}

int downdata(INFO info, int c_fd){
/*    FILE * fp_down = fopen(info.filename,"r");
    if(!fp_down){
        char *buf = "no such file\n";
        info.cmd = 5;
        write(c_fd, &info, sizeof(info));
        return ERR;
    }
    fread(info.buf,sizeof(info.buf),1,fp_down);
    info.buf[strlen(info.buf)] = '\0';
    puts(info.buf);
    write(c_fd,&info,sizeof(info));
    fclose(fp_down);
    return SUCCESS;*/
}

int check(INFO info,int c_fd){
/*	FILE *fp_check=fopen(info.filename,"r");
    puts(info.filename);
    if( fp_check ){
        fclose(fp_check);
        printf("write cmd:%d\n", info.cmd);
        write(c_fd,&info,sizeof(info));
        return ERR;
    }
    else{
        info.cmd = 4;
        write(c_fd,&info,sizeof(info));
        return SUCCESS;
    }
*/
}

char *getImageToLCD(){

}
char *test = "1.jpg";
char *getImageToPC(){
	//static char test[32];
	//strcpy(test,"1.jpg");
	return test;
}

float getTemp(){
	float k= 1.1;
	return k;
}