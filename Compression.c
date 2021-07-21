#include <stdio.h>
#include <string.h>
#include<stdlib.h>

struct encoded_struct
{
    int index;
    char code;
}encoded[20];
int encoded_index=0;
char stored[20][23];
int stored_len=0;
int stored_index;
int checkInStored(char*);
void printEncoding();
void storeIt(int,char,char*);
void printStored();
char* substr(const char *src, int m, int n)
{
	int len = n - m;	
	char *dest = (char*)malloc(sizeof(char) * (len + 1));
	for (int i = m; i < n && (*src != '\0'); i++)
	{
		*dest = *(src + i);
		dest++;
	}	
	*dest = '\0';
	return dest - len;
}

void string2hexString(char* input, char* output)
{
    int loop;
    int i; 
    i=0;
    loop=0;
    
    while(input[loop] != '\0')
    {
        sprintf((char*)(output+i),"%02X", input[loop]);
        loop+=1;
        i+=2;
    }    
    output[i++] = '\0';
}

int main()
{
    char inputt[40] = "hello world";//aabaacabcabcb
    printf("Input String: %s\n\n",inputt);
    int len1 = strlen(inputt);
    char data[(len1*2)+1];
    
   
    string2hexString(inputt, data);
    printf("In Hex: %s\n\n",data);
    int s_index=0;
    int last_stored=0;
    int e_index=s_index+1;
    char *str;
    int i,j,k,len_data,stop=0;
   
    len_data = strlen(data);
    while(stop==0)
    {
        last_stored=0;   
        for(j=0;j<20 ;j++)
        {
            str = substr(data,s_index,e_index);
            // printf("SUB:%s\n",str);
            k = checkInStored(str);
            if(k!=-1)
            {
                last_stored = k;
            }
            else
            {
                j = strlen(str);
                if(j==1)
                {
                    storeIt(last_stored,str[j-1],str);
                }
                else
                    storeIt(last_stored,str[j-1],str);
                s_index=e_index;
                e_index++;
                break;
            }
            e_index++;
            if(e_index>len_data)
            {
                stop=1;
                break;
            }
        }
        
    }
    
    printEncoding();

    return 0;
}
void printEncoding()
{
    int i;
    printf(" Output  Index  String\n");
    for(i=0;i<encoded_index-1;i++)
    {
        printf(" (%d,%c)     %d      %s \n",encoded[i].index,encoded[i].code,(i+1),stored[i]);
    }
  
    printf("\nFinal output:\n");
    for(i=0;i<encoded_index-1;i++)
    {
        printf("%d%c",encoded[i].index,encoded[i].code);
    }
}
void printStored()
{
    int i;
    for(i=0;i<stored_index-1;i++)
    {
        printf("Stored : %s \n",stored[i]);
    }
}
void storeIt(int index,char s,char *st)
{
    
    strcpy(stored[stored_index],st);
  
    stored_index++;
    stored_len++;
    
    encoded[encoded_index].index=index;
    encoded[encoded_index].code = s;
    encoded_index++;
    
}
int checkInStored(char *s)
{
    int i,index=-1;
    int l=0;
    l  = strlen(s);
    if(l!=1)
        s = substr(s,0,l);
  
    for(i=0;i<stored_len;i++)
    {
       
        if(!strcmp(stored[i],s))
        {
            return (i+1);
        }
        
    }
    return -1;
}
