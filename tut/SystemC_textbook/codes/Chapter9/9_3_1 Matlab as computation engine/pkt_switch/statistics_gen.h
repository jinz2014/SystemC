#include "systemc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"
#define MAX_SIZE 1000
class statistics_gen:public sc_module
{   public:
    sc_in<bool> ctrl;
    sc_in<int> din0;
	sc_in<int> din1;
	sc_in<int> din2;
	sc_in<int> din3;
	sc_in<int> din4;
	sc_in<int> din5;	
    int i;	
    double data[MAX_SIZE][6]; 
	int disp();	
	void catch_data(){
		if(i<MAX_SIZE) {
			data[i][0]=(double) din0.read();            
			data[i][1]=(double) din1.read();  
			data[i][2]=(double) din2.read();  
			data[i][3]=(double) din3.read();  
			data[i][4]=(double) din4.read();  
			data[i][5]=(double) din5.read();  
			++i;
		}
		else {disp();sc_stop();}
	};
	
	SC_CTOR(statistics_gen)
	{SC_METHOD(catch_data);
	sensitive<<ctrl;
	i=0;	
	}
   
};

int statistics_gen::disp(){

Engine *ep;
mxArray *T = NULL;
/*
* Start the MATLAB engine locally by executing the string
* "matlab".
*
* To start the session on a remote host, use the name of
* the host as the string rather than \0.
*
* For more complicated cases, use any string with whitespace,
* and that string will be executed literally to start MATLAB.
*/
if (!(ep = engOpen("matlab"))) {
fprintf(stderr, "\nCan't start MATLAB engine\n");
return EXIT_FAILURE;
}
/*
* we will send data to MATLAB, analyze the data, and plot the result.
*/

/*
* Create a variable for our data.
*/
T = mxCreateDoubleMatrix(6, MAX_SIZE, mxREAL);
if(T==NULL) {cout<<"Matlab create matrix failed!"<<endl;sc_stop();}
/*
*Copy data to mxArray
*/
memcpy((void *)mxGetPr(T), (void *)data, sizeof(data));

/*
* Place the variable T into the MATLAB workspace.
*/
engPutVariable(ep, "T", T);

/*
* Plot the result.
*/
engEvalString(ep, "T=T';");
engEvalString(ep, "subplot(2,1,1);");
engEvalString(ep, "bar(T(:,1:4),'group');");
engEvalString(ep, "title('The performance monitoring of helix switch');");
engEvalString(ep, "xlabel('switch cycle number.');");
engEvalString(ep, "ylabel('Pkt Num.');");
engEvalString(ep, "axis([0,1000,0,5]);");
engEvalString(ep, "subplot(2,1,2);");
engEvalString(ep, "bar(T(:,5:6),'stack');");
engEvalString(ep, "xlabel('switch cycle number');");
engEvalString(ep, "ylabel('switched/lost Num.');");
engEvalString(ep, "axis([0,1000,0,1000]);");

/*
* Use fgetc() to make sure that we pause long enough to be
* able to see the plot.
*/
printf("Hit return to continue\n\n");
fgetc(stdin);
/*
* We're done! Free memory, close MATLAB engine.
*/
mxDestroyArray(T);
engEvalString(ep, "close;");
engClose(ep);
return EXIT_SUCCESS;
	};

