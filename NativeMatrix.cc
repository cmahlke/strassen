#include <assert.h>
#include <iostream.h>
#include <math.h>
#include <stdlib.h>
#include "ipm-2.0a/IPM_timer.h"

void timer(double);
void matmultNaive(int);

int main(int argc, char* argv[]) {
	int size = atoi(argv[1]);
	matmultNaive(size);
  	return 0;
}

void timer(double bound) {
	IPM_timer t;
  
	// defalut = 200
  	char report[IPM_TIMER_REPORT_LEN+3];

  	int  i;
  	float x = 0;
 
	// initialize the IPM timer to 0
  	IPM_timer_clear(&t);
  
  	IPM_timer_start (&t);
  	for (i = 0; i < bound; i++) {
		x=x*.99 + 1.0;
    	x=x*.99 + 1.0;
    	x=x*.99 + 1.0;
    	x=x*.99 + 1.0;
  	}
  	IPM_timer_stop(&t);
	
	// format the report string
  	IPM_timer_report("timing computations", &t, report);
  	cout << report;

  	float time = IPM_timer_read(&t);
  	cout << "Elapsed time: " << time << endl;
  	cout << "MFlops: "<< (8.*bound/time)/1000000 << endl;
}

// Multiplies two square matrices of size n in naive 2n^3 operations
void matmultNaive(int n) {
	IPM_timer t;
  
  	char report[IPM_TIMER_REPORT_LEN+3];

	// create two square matrices
  	float matrix1 [n][n];
  	float matrix2 [n][n];
  	float result [n][n];

  	for (int i = 0; i < n; i++) {  
		for (int j = 0; j < n; j++) {
			// populate the matrices with data
			matrix1 [i][j] = j*.99 + 1.0;
			matrix2 [i][j] = j*.99 + 1.0;
		}
	}

	// initialize the timer to 0
  	IPM_timer_clear(&t);
  
  	IPM_timer_start(&t);
  	for (int i = 0; i < n; i++){  
    	for (int j = 0; j < n; j++) {      // multiply them out
      		result[i][j] = 0;
			for (int r = 0; r<n; r++) {
				result[i][j] = result[i][j] + matrix1[i][r] * matrix2[r][j];
			}
		}
	}
  	IPM_timer_stop(&t);

	cout << "*************" << endl;
 	cout << "* Matrix 1  *" << endl;
	cout << "*************\n" << endl;
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < n; j++) {
      		cout << matrix1[i][j] << " ";
		}
    	cout << endl;
	}
  
	cout << "*************" << endl;
  	cout << "* Matrix 2  *" << endl;
	cout << "*************\n" << endl;
  	for (int i = 0; i < n; i++){  
    	for (int j = 0; j < n; j++) {
			cout << matrix2[i][j] << " ";
		}
		cout << endl;
	}
  
	cout << "************" << endl;
  	cout << "* Product: *" << endl;
	cout << "************\n" << endl;
  	for (int i = 0; i < n; i++){  
    	for (int j = 0; j < n; j++) {
      		cout << result[i][j] << " ";
		}
		cout << endl;
	}
  	cout << endl;

	// Format the report string for printing to stdout
  	IPM_timer_report("timing", &t, report);
  	cout << report;

	// People often mean MFLOPS to mean different things, but a general
	// definition would be the number of full word-size fp multiply operations
	// that can be performed per second (the M stands for 'Million'). 
  	float time = IPM_timer_read(&t);
  	cout << "Elapsed time to compute: " << time *pow(10,6) << "u"<< endl;
 	cout << "MFlops: "<< ((2*pow(n, 3))/time)/1000000 << endl;
}
