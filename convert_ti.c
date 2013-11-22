
#include<stdio.h>

#define WIDTH 1920
#define HIGHT 1102

int main(int argc, char **argv)
{
	int i;
	long unsigned int  cur_pos, file_size;
	FILE *fp;
	int width, hight;
	char *file_name;
	unsigned char up[WIDTH*HIGHT/2], vp[WIDTH*HIGHT/2], tmp[WIDTH*HIGHT];

	if (argc < 2) {
    	printf ("usage: %s <media file>\n", *argv);
    	return 1;
  	}

	file_name = *(argv+1);

	fp=fopen(file_name,"rw+");
	if (NULL == fp)
	{
		printf("Unable to open file!");
		return 1;
	}

	width = WIDTH;
	hight = HIGHT;
	
	fseek(fp,0,SEEK_END);
	file_size = ftell(fp);
	printf("file size: %ld\n",file_size);
	
	fseek(fp,0,SEEK_SET);
	cur_pos = 0;
	while (cur_pos < file_size)
	{		
		fseek(fp,width*hight,SEEK_CUR); //skip Y plane
		cur_pos = ftell(fp); 			//save the position

		fread(tmp,1,width*hight,fp);	//read UV plane
	
		for ( i=0; i<width*hight/2; i++)
		{
			up[i] = *(tmp+i*2);
			vp[i] = *(tmp+i*2+1);
		}

		fseek(fp,cur_pos,SEEK_SET);		//go back to the begining of UV plane

//		cur_pos = ftell(fp);
//		printf("cur_postions: %ld\n",cur_pos);

		fwrite(up,1,width*hight/2,fp);
		fwrite(vp,1,width*hight/2,fp);

		cur_pos = ftell(fp);
	}
	fclose(fp);
	return 0;
}
