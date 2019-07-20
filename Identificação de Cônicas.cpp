#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

//By Yure Pablo em 27/06/2019
//Este programa identifica qual é a cônica a partir de uma equação de segundo grau dada

using namespace std;

#define PI 3.14159265

void isTwoSquares(double c){
    //P(x,y) = x² + cy² = 0
    if (c == 0)
    {
        //P(x,y) = x²
        cout << "Uma Reta" << endl;
    }
    else
    {
        if (c > 0)
        {
            //P(x,y) = x² + cy² = 0 
            //A soma de ambos positivos dar zero só é possível no ponto (0,0)
            cout << "Um Ponto" << endl;
        }
        else
        {
            if (c < 0)
            {
                //P(x,y) = x² = cy²
                //x = +ou- cy
                cout << "Duas retas concorrentes" << endl;
            }
        }            
    }
}

void transladar(double *c_linear, double *c_quadratico, double *f){
    double k = (*c_linear) / (2*(*c_quadratico));
    *c_quadratico = (*c_linear) / (2*k);
    *f = *f -((*c_linear)*k) + ((*c_quadratico) * (k * k));
    *c_linear = 0;
}

void verificarF(double *c, double *a, double *f){
	*a = *a / (*f);
    *c = *c / (*f);
    *f = 1;
	
	if (*c == 0)
	{
		//P(x,y) = ax² + 1 = 0
	    if (*a > 0)
	    {
	        //P(x,y) = ax² = -1
	        cout << "Vazio" << endl;
	    }
	    else
	    {
	        if (*a < 0)
	        {
	            //P(x,y) = ax² = 1
	            // x = +ou- 1/a
	            cout << "Duas Retas paralelas" << endl;
	        }
	    }
	}
	else
	{
		if (*a > 0 && *c > 0)
	    {
	        //P(x,y) = ax² + cy² = -1
	        cout << "Vazio" << endl;
	    }
	    else
	    {
	        if (*a < 0 && *c < 0)
	        {
	            //P(x,y) = ax² + cy² = 1 (*-1)
	            if (*a == *c)
	            {
	                cout << "Circunferência" << endl;
	            }
	            else
	                cout << "Elipse" << endl;
	        }
	        else
	        {
	            if (*a < 0 || *c < 0)
	            {
	                //P(x,y) = ax² - cy² = 1
	                cout << "Hiperbole" << endl;
	            }
	        }  		
		}
	}
}

int main(void){
    //P(x,y) = ax² + bxy + cy² + dx + ey + f

    double a, b, c, d, e, f;

    cout << "P(x,y) = ax^2 + bxy + cy^2 + dx + ey + f" << endl;
    cin >> a >> b >> c >> d >> e >> f;

    if (a == c && b == 2*a && d == 0 && e == 0 && f == 0)
    {
        //quadrado perfeito
        cout << "Uma reta" << endl;
        return 0;
    }

    if (b != 0) //rotacionar
    {
        double ang = 0;
        //matriz inversa que retorna x e y antigos a partir de x' e y' novos
        //double matrizDeRotacao[2][2] = {{cos(ang), sin(ang)}, {-sin(ang), cos(ang)}};
        
        //double x1, y1;
        //double x = x1*matrizDeRotacao[0][0] + y1*matrizDeRotacao[0][1];
        //double y = x1*matrizDeRotacao[1][0] + y1*matrizDeRotacao[1][1];
        //double P = a*x*x + b*x*y + c*y*y + d * x + e*y + f;
        
        if (c != a)
        {
            ang = (atan(b/(c-a))/2);
        }
        else
        {
            ang = PI/4;
        }
        double aux = a;
        a = a*cos(ang)*cos(ang) + c*sin(ang)*sin(ang) - b * cos(ang) * sin(ang); //a * (cos(ang)*cos(ang) + sen(ang)*sen(ang) = cos(ang - ang) = cos(0))
        c = c*cos(ang)*cos(ang) + aux*sin(ang)*sin(ang) + b * cos(ang) * sin(ang); 
		b = 0; //(a - c) * sin(2*ang) + b * cos(2*ang)
        aux = d;
		d =  d * cos(ang) - e* sin(ang);
        e = aux * sin(ang) + e * cos(ang);
        //Novo sistema de coordenadas
        //P(x,y) = ax² + cy² + dx + ey + f
        printf("a = %f  b = %f  c = %f  d = %f  e = %f  f = %f\n", a, b, c, d, e, f);
    }
    //b == 0
    if (a!=0 || c!=0)
    {
        if (a == 0) //a sempre sera != 0
        {
            a = c;
            c = 0;
            //Novo sistema de coordenadas (trocar x por y e vice-versa)
            //P(x,y) = ax² + dx + ey + f
            printf("a = %f  b = %f  c = %f  d = %f  e = %f  f = %f\n", a, b, c, d, e, f);
        }
        //transladar em x
        if (d != 0) transladar(&d, &a, &f);
        //Novo sistema de coordenadas em x
        //P(x,y) = ax² + cy² + ey + f = 0
        printf("a = %f  b = %f  c = %f  d = %f  e = %f  f = %f\n", a, b, c, d, e, f);

        if (f == 0)
        {
            //P(x,y) = ax² + cy² + ey = 0
            //dividindo coeficientes por a
            c = c / a;
            e = e / a;
			a = 1;
            //Novos coeficientes
            //P(x,y) = x² + cy² + ey = 0
            printf("a = %f  b = %f  c = %f  d = %f  e = %f  f = %f\n", a, b, c, d, e, f);

            if (e == 0)
            {
                //P(x,y) = x² + cy² = 0
                isTwoSquares(c);
            }
            else
            {
                //P(x,y) = x² + cy² + ey = 0
                if (c == 0)
                {
                    //P(x,y) = ax² + ey = 0
                    cout << "Parabola" << endl;
                }
                else
                {
                    //P(x,y) = x² + cy² + ey = 0
                    //Transladamos em y
                    transladar(&e, &c, &f);
                    //Novo sistema de coordenadas em y
                    //P(x,y) = x² + cy² + f = 0
                    printf("a = %f  b = %f  c = %f  d = %f  e = %f  f = %f\n", a, b, c, d, e, f);
                    if (f == 0)
                    	isTwoSquares(c);
                    else
                    {
                    	verificarF(&c, &a, &f);
                    	printf("a = %f  b = %f  c = %f  d = %f  e = %f  f = %f\n", a, b, c, d, e, f);
                	}
            	}  
        	}
    	}
        else //f!=0
        {
            //P(x,y) = ax² + cy² + ey + f = 0
            //dividindo por f
            a = a / f;
            c = c / f;
            e = e / f;
            f = 1;
            //Novos coeficientes
            //P(x,y) = ax² + cy² + ey + 1 = 0
            printf("a = %f  b = %f  c = %f  d = %f  e = %f  f = %f\n", a, b, c, d, e, f);

            if (c == 0)
            {
                //P(x,y) = ax² + ey + 1 = 0
                if (e == 0)
                {
                    //P(x,y) = ax² + 1 = 0
                    if (a > 0)
                    {
                        //P(x,y) = ax² = -1
                        cout << "Vazio" << endl;
                    }
                    else
                    {
                        if (a < 0)
                        {
                            //P(x,y) = ax² = 1
                            // x = +ou- 1/a
                            cout << "Duas Retas paralelas" << endl;
                        }
                    }
                }
                else //e!=0
                {
                    //P(x,y) = ax² + ey + 1 = 0 
                    cout << "Parabola" << endl;
                }
            }
            else //c!=0
            {
                //P(x,y) = ax² + cy² + ey + 1 = 0
                //Transladamos em y
                    if (e!=0) transladar(&e, &c, &f);
                    //Novo sistema de coordenadas em y
                    //P(x,y) = ax² + cy² + f = 0
                    printf("a = %f  b = %f  c = %f  d = %f  e = %f  f = %f\n", a, b, c, d, e, f);

                    verificarF(&c, &a, &f);
                    printf("a = %f  b = %f  c = %f  d = %f  e = %f  f = %f\n", a, b, c, d, e, f);
            }
        }
    }
    else //a == 0 e c == 0
    {
       //P(x,y) = dx + ey + f
       cout << "Uma reta" << endl;

    }

    return 0;
    
}
