#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <math.h>
#include <string.h>

// FLOATZERO : Epsilon pour palier à l'imprécision des nombres en virgule flottante
#define		FLOATZERO		1e-6

// PIXTYPE : type du pixel (float, double, int, char)
typedef double PIXTYPE;    

// sqr(x) : carré d'une valeur
#define sqr(x)  ((x) * (x))
// sqrNorm(x, y) : norme au carré d'un vecteur (x, y)
#define sqrNorm(x, y) (sqr(x) + sqr(y))

// sign(x) : signe de x
#define sign(x) (x>0 ? 1 : -1)

#ifndef M_PI 
	#define	M_PI		3.14159265358979323846
#endif

inline bool IsZero(const PIXTYPE& in_dVal){
	return (fabs(in_dVal) < FLOATZERO);
}

inline bool IsSupTo(  // ajouter a nvmath.cpp
	double i_dVal1,
	double i_dVal2
)
{
	return((!IsZero(i_dVal1 - i_dVal2)) && (i_dVal1 > i_dVal2));
}

//#ifndef WIN32
//#define printf snprintf
//#endif

#ifdef WIN32

#define snprintf _snprintf

inline double gammln(double xx)
{
        double x,y,tmp,ser;
        static double cof[6]={76.18009172947146,-86.50532032941677,
                24.01409824083091,-1.231739572450155,
                0.1208650973866179e-2,-0.5395239384953e-5};
        int j;

        y=x=xx;
        tmp=x+5.5;
        tmp -= (x+0.5)*log(tmp);
        ser=1.000000000190015;
        for (j=0;j<=5;j++) ser += cof[j]/++y;
        return -tmp+log(2.5066282746310005*ser/x);
}

#define ITMAX 100
#define EPS 3.0e-7
#define FPMIN 1.0e-30
inline void gcf(double *gammcf, double a, double x, double *gln)
{
        int i;
        double an,b,c,d,del,h;

        *gln=gammln(a);
        b=x+1.0-a;
        c=1.0/FPMIN;
        d=1.0/b;
        h=d;
        for (i=1;i<=ITMAX;i++) {
                an = -i*(i-a);
                b += 2.0;
                d=an*d+b;
                if (fabs(d) < FPMIN) d=FPMIN;
                c=b+an/c;
                if (fabs(c) < FPMIN) c=FPMIN;
                d=1.0/d;
                del=d*c;
                h *= del;
                if (fabs(del-1.0) < EPS) break;
        }
        if (i > ITMAX) exit(1);
        *gammcf=exp(-x+a*log(x)-(*gln))*h;
}
#undef ITMAX
#undef EPS
#undef FPMIN

#define ITMAX 100
#define EPS 3.0e-7
inline void gser(double *gamser, double a, double x, double *gln)
{
        double gammln(double xx);
        int n;
        double sum,del,ap;

        *gln=gammln(a);
        if (x <= 0.0) {
                if (x < 0.0) exit(1);
                *gamser=0.0;
                return;
        } else {
                ap=a;
                del=sum=1.0/a;
                for (n=1;n<=ITMAX;n++) {
                        ++ap;
                        del *= x/ap;
                        sum += del;
                        if (fabs(del) < fabs(sum)*EPS) {
                                *gamser=sum*exp(-x+a*log(x)-(*gln));
                                return;
                        }
                }
                exit(1);
                return;
        }
}
#undef ITMAX
#undef EPS

inline double gammp(double a, double x)
{
        double gamser,gammcf,gln;

        if (x < 0.0 || a <= 0.0) 
			exit(1);

        if (x < (a+1.0)) {
                gser(&gamser,a,x,&gln);
                return gamser;
        } else {
                gcf(&gammcf,a,x,&gln);
                return 1.0-gammcf;
        }
}

inline double erf(double x)
{
        return x < 0.0 ? -gammp(0.5,x*x) : gammp(0.5,x*x);
}

#endif

#endif

