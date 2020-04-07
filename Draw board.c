volatile int pixel_buffer_start; // global variable
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>	
int main(void)
{
	volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;
	clear_screen();
	draw();
}
	
draw()
{
	/*for(int i =0;i<319;i++)
	{
		for(int j=0; j<239;j++)
		{
			draw_box(99,219);
		}
	}*/
	draw_box(149,169,39,59,0x76F6);
	
	draw_box(129,149,69,89,0xF800);
	draw_box(169,189,69,89,0xF800);
	
	draw_box(109,129,99,119,0x0F1F);
	draw_box(149,169,99,119,0x0F1F);
	draw_box(189,209,99,119,0x0F1F);
	
	draw_box(89,109,129,149,0xF81F);
	draw_box(129,149,129,149,0xF81F);
	draw_box(169,189,129,149,0xF81F);
	draw_box(209,229,129,149,0xF81F);
	
	draw_box(69,89,159,179,0x07E0);
	draw_box(109,129,159,179,0x07E0);
	draw_box(149,169,159,179,0x07E0);
	draw_box(189,209,159,179,0x07E0);
	draw_box(229,249,159,179,0x07E0);
	
	draw_box(49,69,189,209,0x888F);
	draw_box(89,109,189,209,0x888F);
	draw_box(129,149,189,209,0x888F);
	draw_box(169,189,189,209,0x888F);
	draw_box(209,229,189,209,0x888F);
	draw_box(249,269,189,209,0x888F);
	/*for(int i = 109; i<209; i+=20)
	{	
		//if(col)
		//{
			draw_box(i,i+20,99,129,0x001F);
			//col = false;
		//}
		else
		{
			draw_box(i,i+20,99,129,0x001F);
			col = true;
		}
	}*/
}

draw_box(int Xstart, int Xend, int Ystart, int Yend, int color)
{
	//clear_screen();
	for(int i= Xstart;i< Xend;i++)
	{
		for(int j= Ystart; j< Yend;j++)
		{
			plot_pixel(i,j,color);
		}
	}
}
	
clear_screen()
{
	for(int x=0; x<=319;x++)
	{
		for(int y=0;y<=239;y++)
		plot_pixel(x,y,0x0000);
	}
}
	
void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}


	
	
			
			
			
			
			
			
	
	