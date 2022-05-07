/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>



int local_conv_trans_HWC_q15_nonsquare(void);
int get_boundaries(int start);
int show_tab(int size_x, int size_y,int size_c,int *tab, int nnom);
void fill_buffer(int *tab, int size, int zero);

int main()
{
    local_conv_trans_HWC_q15_nonsquare();
}



int local_conv_trans_HWC_q15_nonsquare()
{
    static int count = 0;
    int input [16 *1];
    int size_channels=2; // output & kernel
    int kernel[ 9 *size_channels]; 
    int output[ 36 *size_channels];
    int bias [1   *size_channels];

    fill_buffer(input, sizeof(input) /sizeof(int),1);
    fill_buffer(kernel,sizeof(kernel)/sizeof(int),1);
    fill_buffer(output,sizeof(output)/sizeof(int),0);
    fill_buffer(bias , sizeof(bias)  /sizeof(int),0);
    
    
    int i=0,j=0,k=0,l=0,m=0,n=0;
    int kernel_size_c=size_channels,    kernel_size_x=sqrt((sizeof(kernel)/kernel_size_c)/sizeof(int)),        kernel_size_y=sqrt((sizeof(kernel)/kernel_size_c)/sizeof(int)) ;
    int input_size_c=1,                 input_size_x =sqrt((sizeof(input)/input_size_c)/sizeof(int)),          input_size_y =sqrt((sizeof(input)/input_size_c)/sizeof(int));        
    int output_size_c=size_channels,    output_size_x=sqrt((sizeof(output)/output_size_c)/sizeof(int)),        output_size_y=sqrt((sizeof(output)/output_size_c)/sizeof(int)) ;
    
    int kernel_index = 0, output_index=0, input_index=0,  starting_output_x=0, starting_output_y=0;
    int stride_x=1, stride_y=1, padding_x=0, padding_y=0;
    
    //printf("size input x %d\r\n",input_size_x);
    
    for(n=0;n<kernel_size_c;n++)                        //kernel channel
    {
        for(l=0;l<input_size_y;l++)                     //input axe y 
        {
   
            for(m=0;m<input_size_x;m++)                 //input axe x
            {
                //get_boundaries(&starting_output_y);
                
                for(i=0;i<kernel_size_y;i++)            //kernel axe y
                {
                    
                    for(j=0;j<kernel_size_x;j++)        //kernel axe x
                    {
                        for(k=0;k<input_size_c;k++)     //input channel
                        {
                            kernel_index = i*kernel_size_x+j                     + (kernel_size_x*kernel_size_y*n);                 // + (x*y*n) is changing kernel layer to the corresponding pixel
                            output_index = i*output_size_x+j+ (m*stride_x) + (l*stride_y*output_size_x) + (output_size_x*output_size_y*n);   // + (x*y*n) is changing output layer to the corresponding pixel
                            input_index  = l*input_size_x+m                      + (input_size_x*input_size_y*k);                   // + (x*y*k) is changing input layer to the corresponding pixel
                            output[output_index] += input[input_index]*kernel[kernel_index];
                            //printf("output index %d ,value %d \r\n",output_index,output[output_index] );
                            printf("output index %d \r\n",output_index);
                        }
                    }
                }
                //printf("\nChanging  input axe x \r\n");
                //if(count++ == 6) return 0;
                
            }
            //printf("\nChanging  input axe y \r\n");
            
        }
        //printf("\nChanging channel kernel \r\n");
    }
    //show_tab(output_size_x,output_size_y,output_size_c,output,1);
    for(i=0;i<size_channels;i++)
    {
        for(j=0;j<output_size_x*output_size_y;j++)
        {
            output[j+(i*output_size_x*output_size_y)] += bias[i];
            //printf("%d  ",j+(i*output_size_x*output_size_y));
        }
    }
    //show_tab(output_size_x,output_size_y,output_size_c,output);
}

int show_tab(int size_x, int size_y,int size_c,int *tab, int nnom)
{
    int i,j,c;
    int index= 0;
    if(nnom == 1)
    {
        for(i=0;i<size_y;i++)
        {
            for(j=0;j<size_x;j++)
            {
                for(c=0;c<size_c;c++)
                {
                    index = (i*size_x+j)+ (size_x*size_y*c);
                    printf("%d ",tab[index]);
                }
            }
            printf("\r\n");
        }
    }
    else
    {
        for(c=0;c<size_c;c++)
        {
            for(j=0;j<size_y;j++)
            {
                for(i=0;i<size_x;i++)
                {
                    {
                        index = (j*size_x+i)+ (c*size_x*size_y);
                        printf("%d ",tab[index]);
                    }
                }
                printf("\r\n");
            }
        }
    }
}


void fill_buffer(int *tab, int size, int zero)
{
    int i;
    for(i=0;i<size;i++)
    {
        if(zero == 0)   tab[i]=0;
        else            tab[i]=1;
    }
}

