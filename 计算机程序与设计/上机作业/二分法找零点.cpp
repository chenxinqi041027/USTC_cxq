#include<stdio.h>
#include<math.h>
double f(double x);
const double eps=1e-6;

int main(){
	double x0,x1=0,x2=3,fx0;
	
	if(f(x1)*f(x2)<0){
		while(fabs(f(x0))>eps){
			x0=(x1+x2)/2.0;
			if(f(x0)*f(x1)<0) x2=x0;
			else if(f(x0)*f(x2)<0) x1=x0;
		}
	}
	printf("Numerical answer x = %.8lf\n",x0);
	printf("Error |f(x)| = %.8lf\n",f(x0));
	return 0;
}
double f(double x){
	return 2*x*x*x-4*x*x+3*x-5;
}
	//fx0=f(x0);
			//if(fabs(f(x0))<eps) break;
			//else
				//printf("%lf %lf\n",x0,fx0);
		
