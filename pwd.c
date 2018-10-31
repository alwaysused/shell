#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <dirent.h>

#define MAX_SIZE 2000

int get_fd(char* filename){

    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        printf("error");
    return fd;

}

void cp(int in_fd, char* output_filename){

    struct timespec start, finish;

    char buffer[MAX_SIZE];
    int read_cnt = 0;
    int out_fd = open(output_filename, O_CREAT|O_RDWR);
    gettimeofday(&start, NULL);

    while(read_cnt = read(in_fd, &buffer, MAX_SIZE)){

            write(out_fd, &buffer, read_cnt);

    }
    gettimeofday(&finish, NULL);
    printf( "%f useconds\n", (double)(finish.tv_nsec - start.tv_nsec) );


}

char* inod_to_name(ino_t target_nod){
    DIR *dir_p;
    struct dirent* dirent_p;
    dir_p = opendir(".");
    while ((dirent_p = readdir(dir_p)) != NULL){
        if (dirent_p->d_ino == target_nod){
            return dirent_p->d_name;
        }
    }
}
ino_t  get_inode(char* filename){
    struct stat info;
    stat(filename, &info);
    return info.st_ino;
}

void get_path(ino_t inod){
    ino_t parent_nod = get_inode("..");
    if (parent_nod != inod){
        chdir("..");
        char* cur_name = inod_to_name(inod);
        get_path(parent_nod);
        printf("/%s", cur_name);
    }
    else
        return;
}





int main(int argc, char** argv) {
    get_path(get_inode("."));











    printf("Hello, World!\n");
    return 0;
}
