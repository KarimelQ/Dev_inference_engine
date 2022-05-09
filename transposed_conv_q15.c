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


#define NNOM 1
#define KERAS 0

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
    int ch_image_in = 2;
    int ch_image_out=1; // output & kernel
    //25 *ch_image_in
    //https://medium.com/apache-mxnet/transposed-convolutions-explained-with-ms-excel-52d13030c7e8
    int input []={1,0,1,0,2,1,1,3,2,1,1,1,0,1,1,2,3,2,1,3,0,2,0,1,0,     1,0,0,1,0,2,0,1,2,0,3,1,1,3,0,0,3,0,3,2,1,0,3,2,1};
    //9 *ch_image_in*ch_image_out
    int kernel[]={0,1,0,0,0,2,0,1,0,   2,1,0,0,0,0,0,3,0}; 
    int output[49 *ch_image_out];
    int bias  [ 1 *ch_image_out];

    //fill_buffer(input, sizeof(input) /sizeof(int),1);
    //fill_buffer(input+16, ( sizeof(input) /sizeof(int))/2, 0.5);
    //fill_buffer(kernel,sizeof(kernel)/sizeof(int),1);
    fill_buffer(output,sizeof(output)/sizeof(int),0);
    fill_buffer(bias , sizeof(bias)  /sizeof(int),0);
    
    
    int i=0,j=0,k=0,l=0,m=0,n=0;
    int kernel_size_c=ch_image_in*ch_image_out,    kernel_size_x=sqrt((sizeof(kernel)/kernel_size_c)/sizeof(int)),        kernel_size_y=sqrt((sizeof(kernel)/kernel_size_c)/sizeof(int)) ;
    int input_size_c=ch_image_in,                  input_size_x =sqrt((sizeof(input)/input_size_c)/sizeof(int)),          input_size_y =sqrt((sizeof(input)/input_size_c)/sizeof(int));        
    int output_size_c=ch_image_out,                output_size_x=sqrt((sizeof(output)/output_size_c)/sizeof(int)),        output_size_y=sqrt((sizeof(output)/output_size_c)/sizeof(int)) ;
    
    int kernel_index = 0, output_index=0, input_index=0,  starting_output_x=0, starting_output_y=0;
    int stride_x=1, stride_y=1, padding_x=0, padding_y=0;
    
    printf("size input  c %d\r\n",input_size_c);


    for(n=0;n<ch_image_out;n++)                         //output channel / kernel filter
    {
        for(l=0;l<input_size_y;l++)                     //input axe y 
        {
            for(m=0;m<input_size_x;m++)                 //input axe x
            {
                for(i=0;i<kernel_size_y;i++)            //kernel axe y
                {
                    for(j=0;j<kernel_size_x;j++)        //kernel axe x
                    {
                        for(k=0;k<input_size_c;k++)     //input channel / kernel channel
                        { 
                            input_index  = l*input_size_x+m   + (input_size_x*input_size_y*k);                                                       // + (x*y*k) is changing input layer to the corresponding pixel
                            kernel_index = i*kernel_size_x+j  + (kernel_size_x*kernel_size_y*k)+  (kernel_size_x*kernel_size_y*input_size_c*n);      // + (x*y*p) is changing kernel layer to the corresponding pixel
                            output_index = i*output_size_x+j  + (m*stride_x) + (l*stride_y*output_size_x) + (output_size_x*output_size_y*n);                      // + (x*y*p) is changing output layer to the corresponding pixel
                            output[output_index] += input[input_index]*kernel[kernel_index];
                            //printf("output index %d ,value %d \r\n",output_index,output[output_index] );
                            //printf("input index %d * kernel index %d -> put in %d\r\n",input_index, kernel_index, output_index);
                        }
                    }
                }
                //printf("\nChanging  input axe x \r\n");
                //if(count++ == 6) return 0;
                
            }
            //printf("\nChanging  input axe y \r\n");
            
        }
        //printf("\nChanging  kernel filter \r\n");
    }
    //printf("%d, %d, %d \r\n",output_size_x,output_size_y,output_size_c);
    show_tab(output_size_x,output_size_y,output_size_c,output,NNOM);
    for(i=0;i<ch_image_out;i++)
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

