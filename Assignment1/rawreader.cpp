#include "stdio.h"
#include "fstream"
#include "cstring"
#include "rawreader.h"
#include "Stack.h"
#include "RawQueue.h"
#include "cstdio"

void Symmetry(std::string Image){
    Stack<unsigned char> st;
    int width = 256, height = 256;
    FILE* input_file, *output_file;
    unsigned char input_data[256][256];
    unsigned char output_data[256][256];

    input_file = fopen(Image.c_str(),"rb");
    if (input_file == NULL)
    {
        return;
    }
    fread(input_data, sizeof(unsigned char), width * height, input_file);

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            st.push(input_data[i][j]);
            output_data[255-i][255-j] = st.Top();
            st.pop();
        }
    }
    char* filename = new char[100];
    char* image = new char[100];

    Image = Image.substr(8);
    strcpy(image,Image.c_str());
    filename = strtok(image,".R");
    const char* result = "./Result";
    const char* flip = "_flipped";
    const char* raw = ".RAW";
    char* editfile = new char[100];
    strcpy(editfile,result);
    strcat(filename,flip);
    strcat(filename,raw);
    strcat(editfile,filename);
    output_file = fopen(editfile, "wb");
    if (output_file == NULL)
    {
        return;
    }
    fwrite(output_data, sizeof(unsigned char), width * height, output_file);
    delete[]editfile;
    delete[]filename;
    fclose(input_file);
    fclose(output_file);
    return;
}

void Light(std::string control,std::string Image)
{
    RawQueue queue;
    FILE* fp_In = nullptr;
    FILE* fp_Out = nullptr;
    char* con = new char[100];
    strcpy(con,control.c_str());
    int Light;
    Light = atoi(con);
    fp_In = fopen(Image.c_str(),"rb");
    if(fp_In != NULL){
        const char* adjust = "_adjust";
        char* image = new char[100];
        char* editfile = new char[100];
        const char* result = "./Result";
        Image = Image.substr(8);
        strcpy(image,Image.c_str());
        image = strtok(image,".R");
        strcpy(editfile,result);
        strcat(image,adjust);
        strcat(image,".RAW");
        strcat(editfile,image);
        fp_Out = fopen(editfile,"wb");
        if(fp_Out != NULL){
            unsigned char ch = 0;
			while (true)
			{
				int iCnt = fread(&ch, sizeof(unsigned char), 1, fp_In);
				if (1 > iCnt){
                    break;
                }
                if(ch + Light >=255){
                    ch = 255;
                    queue.push(ch);
                }
                else{
                    ch = ch + Light;
                    queue.push(ch);
                }
			}
            while(queue.empty() != true){
                ch = queue.pop();
                fwrite(&ch, sizeof(unsigned char), 1, fp_Out);
            }
			fclose(fp_Out);
        }
        fclose(fp_In);
        delete [] editfile;
        delete [] image;
    }
    delete [] con;
}

void Reduction(std::string Image){
    FILE* fp_In = nullptr;
    FILE* fp_Out = nullptr;
    int width = 256, height = 256;
    unsigned char input_data[256][256];
    unsigned char output_data[128][128];
    char* filename = new char[100];
    char* image = new char[100];
    char* editfile = new char[100];
    const char* result = "./Result";
    std::string openImage = Image;
    if(Image == "\0"){
        return;
    }
    Image = Image.substr(8);
    strcpy(editfile,result);
    strcpy(image,Image.c_str());
    filename = strtok(image,".R");
    const char* resize = "_resized";
    const char* raw = ".RAW";
    strcat(filename,resize);
    strcat(filename,raw);
    strcat(editfile,image);

    int ave;
    fp_In = fopen(openImage.c_str(),"rb");
    if(fp_In == NULL){
        return;
    }
    fp_Out = fopen(editfile,"wb");
    if(fp_Out == NULL){
        return;
    }
    fread(input_data, sizeof(unsigned char), width * height, fp_In);


    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            if(i%2 == 0 && j%2 == 0){
                ave = input_data[i][j] +input_data[i+1][j] + input_data[i][j+1]+input_data[i+1][j+1];
                ave = ave/4;
                output_data[i/2][j/2] = (unsigned char)ave;
            }
        }
    }
    fwrite(output_data, sizeof(unsigned char), height* width, fp_Out);
    fclose(fp_Out);
    fclose(fp_In);
    delete[]editfile;
    delete[]filename;
}
