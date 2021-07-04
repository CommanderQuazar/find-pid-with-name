//
// Created by Tobey Ragain (Commander_Quazar) on 7/4/2021
//

/*
 * UNIX MACOS LINUX VERSION
 */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1024

int strToInt(char * str)
{
    return ((str[0]-0x30)*1000)+((str[1]-0x30)*100)+((str[2]-0x30)*10)+((str[3]-0x30));
}

int getPidByName(char *task_name)
{
    DIR *dir;
    struct dirent *ptr;
    FILE *fp;
    char filepath[50];//The size is arbitrary, can hold the path of cmdline file
    char cur_task_name[50];//The size is arbitrary, can hold to recognize the command line text
    char buf[BUF_SIZE];
    dir = opendir("/proc"); //Open the path to the
    if (NULL != dir) {
        while ((ptr = readdir(dir)) != NULL) //Loop reads each file/folder in the path
        {
            //If it reads "." or ".." Skip, and skip the folder name if it is not read
            if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
                continue;

            if (DT_DIR != ptr->d_type)
                continue;

            sprintf(filepath, "/proc/%s/status", ptr->d_name);//Generates the path to the file to be read
            fp = fopen(filepath, "r");//Open the file

            if (NULL != fp) {
                if (fgets(buf, BUF_SIZE - 1, fp) == NULL)
                {
                    fclose(fp);
                    continue;
                }
                sscanf(buf, "%*s %s", cur_task_name);

                //Print the name of the path (that is, the PID of the process) if the file content meets the requirement
                if (!strcmp(task_name, cur_task_name))
                    return strToInt(ptr->d_name);

                fclose(fp);
            }
        } closedir(dir);//Shut down the path
    } return 0;
}

int main()
{
    char task_name[] = "clion.sh";

    printf("task name is %s\n", task_name);
    printf("PID: %i\n", getPidByName(task_name));
}
