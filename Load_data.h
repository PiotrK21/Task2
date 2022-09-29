#ifndef LOAD_DATA_H_INCLUDED
#define LOAD_DATA_H_INCLUDED

/*
    The function to load data from JSON file
*/

char* fun_load_data()
{
    char file_path[50];

    printf("\nPlease input path to data file, or the name if file is in folder with program, in JSON format: ");
    scanf("%s",&file_path);

    FILE *f = NULL;
    long length_file;
    char *data = NULL;

    f=fopen(file_path,"r");

    if(f==NULL)
    {
        printf("Data loading failed\n");
        system("pause");
        exit(1);
    }
    else
        printf("Data loading successful\n");

    fseek(f,0,SEEK_END);
    length_file=ftell(f);
    fseek(f,0,SEEK_SET);

    data=(char*)malloc(length_file+1);
    fread(data,1,length_file,f);
    data[length_file]='\0';

    fclose(f);

    return data;
}

#endif // LOAD_DATA_H_INCLUDED
