/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2002 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.3 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  source.cpp - This is the implementation file for the synchronous process
               "source".

  Original Author: Rashmi Goswami, Synopsys, Inc.

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/


#include "systemc.h"
#include "source.h"
#include <stdio.h>
#include <stdlib.h>
#include "mat.h"
#include "math.h" 
#include "D:\Sc_lib\sc1\msvc60\examples\fft_fxpt\globals.h"

#define  DL 16
void source::entry()
{     int tmp_val=0;
/*
  FILE *fp_real, *fp_imag;



    fp_real = fopen("in_real", "r");
    fp_imag = fopen("in_imag", "r");
*/
  fx_db temp;   
  data_valid.write(false);  
  const char *filename="test.mat"; 
   if(getMat(filename)) cout<<"File open error!"<<endl;   
  while(true)
  {  
     wait_until(data_req.delayed() == true);
	 //cout<<"wait_until executed"<<endl;
     if(tmp_val<16) {
		 cout<<"out_real is "<<data[tmp_val]<<endl;		
		temp=((data[tmp_val])*pow(2,SFT));		
 		cout<<"out_real is "<<temp<<endl;        		
		out_real.write(temp);    		
		
        temp=(data[DL+tmp_val])*pow(2,SFT);
	    out_imag.write(temp);
		cout<<"out_write is"<<data[DL+tmp_val]<<endl;
		cout<<"out_write is"<<temp<<endl;
	}
	 
    data_valid.write(true);
    wait_until(data_req.delayed() == false);
    data_valid.write(false);
	tmp_val++;
    wait();
  }
}


int source::getMat(const char *file) {
  MATFile *pmat;
  char **dir;
  const char *name;
  int ndir;
  int i;
  int dim_data;
  mxArray *pa;
  
  printf("Reading file %s...\n\n", file);

  /* Open file to get directory. */
  pmat = matOpen(file, "r");
  if (pmat == NULL) {
    printf("Error opening file %s\n", file);
    return(1);
  }
  
  /* Get directory of MAT-file. */
  dir = matGetDir(pmat, &ndir);
  if (dir == NULL) {
    printf("Error reading directory of file %s\n", file);
    return(1);
  } else {
    printf("Directory of %s:\n", file);
    for (i=0; i < ndir; i++)
      printf("%s\n", dir[i]);
  }
  mxFree(dir);

  /* In order to use matGetNextXXX correctly, reopen file to 
     read in headers. */
  if (matClose(pmat) != 0) {
    printf("Error closing file %s\n",file);
    return(1);
  }
  pmat = matOpen(file, "r");
  if (pmat == NULL) {
    printf("Error reopening file %s\n", file);
    return(1);
  }

  /* Get headers of all variables. */
  printf("\nExamining the header for each variable:\n");
  for (i=0; i < ndir; i++) {
    pa = matGetNextVariableInfo(pmat, &name);	
    if (pa == NULL) {
      printf("Error reading in file %s\n", file);
      return(1);
    }
    /* Diagnose header pa. */
    dim_data=mxGetNumberOfDimensions(pa);
    printf("According to its header, array %s has %d dimensions\n",name, dim_data);	
    if (mxIsFromGlobalWS(pa))
      printf("  and was a global variable when saved\n");
    else
      printf("  and was a local variable when saved\n");
    mxDestroyArray(pa);
  }
    
    
  /* Reopen file to read in actual arrays. */
  if (matClose(pmat) != 0) {
    printf("Error closing file %s\n",file);
    return(1);
  }
  pmat = matOpen(file, "r");
  if (pmat == NULL) {
    printf("Error reopening file %s\n", file);
    return(1);
  }

  /* Read in each array. */
  printf("\nReading in the actual array contents:\n");
  pa = matGetNextVariable(pmat, &name);
  if (pa == NULL) {  printf("Error reading in file %s\n", file); return (1);}
  double *pr_data=mxGetPr(pa);
  for(int j=0;j<DL*2;j++) {	
		data[j]=*pr_data;
		cout<<"Data["<<j<<"]="<<data[j]<<endl;
		pr_data++;
	}	
  
  
    /*
     * Diagnose array pa
     */
    
   if (mxIsFromGlobalWS(pa))
      printf("  and was a global variable when saved\n");
    else
      printf("  and was a local variable when saved\n");
    mxDestroyArray(pa);
  

  if (matClose(pmat) != 0) {
    printf("Error closing file %s\n",file);
    return(1);
  }
  printf("Done\n");
  return(0);
}

