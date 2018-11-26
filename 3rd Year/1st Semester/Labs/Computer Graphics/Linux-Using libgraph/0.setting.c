/*
*
*   command line syntax (case insensitive)
*
*   -ctln = sets origin to narrow top left
*   -ctb  = sets origin to top center
*           notice the 'b'ottom is ignored
*           as it contradicts the 't'op
*   -cn   = sets origin to center of the screen
*   -c    = no change to origin
*
*   -w25  = sets raster pixel width to 25p
*   -w    = no change to width
*
*   -d0.5 = sets rasterisation delay to 1/2s
*   -d    = no change to delay
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "0.raster.c"

int main(int argc, char **argv)
{
	int x, y, n, i, j, flag;
	FILE *setting;
	x=y=n=i=j=flag=0;
	if(argc>1) //arguments to parse
	{
		setting=fopen("settings.kpd", "rx"); //open settings file
    	if(!setting) //file not opened, use defaults
    	{
    		raster.centerX=320; //origin at center of screen
    		raster.centerY=240;
    		raster.width=10; //width 10p
    		raster.dely=0.25; //delay 1/4s
    		setting=fopen("settings.kpd","w"); //force create settings file...
    		if(!setting)
    		{
    		    printf("\nFATAL ERROR : could not create file \"settings.kpd\"\n");
    		    return 1;
    		}
    		else
    		    fwrite(&raster, sizeof(raster), 1, setting); //...and store defaults
    	}
    	else
    	{
    		fread(&raster, sizeof(raster), 1, setting); //read settings
    		fclose(setting);
    	}
    }
    else return 0; //no arguments, do nothing
	while((i++)<argc-1) //parse the arguments
	{
		if(argv[i][0]=='-') //commands start with a '-'
			switch(argv[i][1])
			{
				case 'c': case 'C': //center command
					for(j=2; argv[i][j]; ++j)
						switch(argv[i][j])
						{
							case 't': case 'T': //top
								if(!y)
									y=1;
							    break;
							case 'b': case 'B': //bottom
								if(!y)
									y=-1;
							    break;
							case 'l': case 'L': //left
								if(!x)
									x=-1;
							    break;
							case 'r': case 'R': //right
								if(!x)
									x=1;
							    break;
							case 'n': case 'N': // narrow/neutral
								if(!n)
									n=1;
							    break;
						}
					if(x || y || n) //if a change has been made
					{
						flag=1; //set flag
						raster.centerX=320 + x*(160 + 140*n); //recalculate
						raster.centerY=240 - y*(120 + 100*n);
					}						
				    break;
				case 'w': case 'W': //width command
					raster.width=atoi(argv[i]+2);
					flag=1; //set flag
				    break;
				case 'd': case 'D': //delay command
					raster.dely=atof(argv[i]+2);
					flag=1; //set flag
				    break;
				default:
					printf("\nLOG [ERROR] : Command [ %s ] not found", argv[i]);
			}
	}
	if(flag)
	{
		setting=fopen("settings.kpd", "w");
		if(!setting)
		{
			printf("FATAL ERROR : aborted");
			return 1;
		}
		fwrite(&raster, sizeof(raster), 1, setting); //write changes to file
		fclose(setting);
	}
	return 0;
}
