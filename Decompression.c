/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include<string.h>
struct encoded_struct
{
    int index;
    char code;
}encoded[25];
int encoded_len=20;
int encoded_index = 0;
char encoded_output[30];
int encoded_output_index=0;
char *decode_str;
char* decodeIt(int,char);
char* getCode(struct encoded_struct);
void append(char* s, char c);
void decode();
void printCode(struct encoded_struct);
int hexadecimalToDecimal(char c1,char c2) 
{    
    char hexVal[3];
    hexVal[0]=c1;
    hexVal[1]=c2;
    hexVal[3]='\0';
    
    int i=0;
    int len = strlen(hexVal); 
    // Initializing base value to 1, i.e 16^0 
    int base = 1; 
    int dec_val = 0; 
      
    // Extracting characters as digits from last character 
    for (i=len-1; i>=0; i--) 
    {    
        // if character lies in '0'-'9', converting  
        // it to integral 0-9 by subtracting 48 from 
        // ASCII value. 
        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
                  
            // incrementing base by power 
            base = base * 16; 
        } 

        // if character lies in 'A'-'F' , converting  
        // it to integral 10 - 15 by subtracting 55  
        // from ASCII value 
        else if (hexVal[i]>='A' && hexVal[i]<='F') 
        { 
            dec_val += (hexVal[i] - 55)*base; 
          
            // incrementing base by power 
            base = base*16; 
        } 
    } 
    return dec_val; 
}
void string2hexString(char* input, char* output)
{
    int loop;
    int i; 
    int len=1;
    int out=0;
    char c;
    
    printf("\n");
    for(i=0;i<strlen(input);i+=2)
    {
        
        c = (char)hexadecimalToDecimal(input[i],input[i+1]);
        output[out] = c;
        out++;
    }

}

int main()
{
    char d[] = "0608151C460F0200079667760C14";
    char str_d[25];
    int len,i,k,l;
    char output_msg[30];
    len = strlen(d);
    // 
    for(i=0;i<strlen(d);i+=2)
    {
        encoded[encoded_index].index = (int)(d[i])-48;
        encoded[encoded_index].code = d[i+1];
        encoded_index++;
    }
    decode();
    //encoded_output(hex) -> output_msg(string)
    string2hexString(encoded_output,output_msg);
    
    printf("MSG:%s",output_msg);
    return 0;
}

void decode()
{
    int i;
    for(i=0;i<encoded_index;i++)
    {
        printCode(encoded[i]);
    }
}
void printCode(struct encoded_struct d)
{
    if(d.index!=0)
    {
        printCode(encoded[d.index-1]);
    }
    encoded_output[encoded_output_index++] = d.code;
    
}
