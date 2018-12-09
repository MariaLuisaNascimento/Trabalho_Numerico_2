#include <stdio.h>
#include <math.h>

/*Função que calcula a N-ésima dereivada da função*/
double calcDerivada(double x, int n){
    double derivada;
    if(n ==2)
        derivada = (1 - pow(x, 2))*exp((-0.5)*pow(x, 2)); //calcula a segunda derivada de f
    else if(n == 4)
        derivada = (-pow(x, 2)+6*pow(x, 2)-3)*exp((-0.5)*pow(x, 2)); //calcula a quarta derivada de f
    return derivada;
}

double TrapezioComposta(int N, double hT, int a, int b){
    double ItN = hT*(exp((-0.5)*pow(a, 2))+exp((-0.5)*pow(b, 2)))/2;
    for (int i = 1; i < N;i++){
        ItN += hT*(2*exp((-0.5)*pow((double)(a + (i*hT)), 2)))/2;
    }
    return ItN;
}

double SimpsonComposta(int N, double hS, int a, int b){
    double ItS = hS*(exp((-0.5)*pow(a, 2))+exp((-0.5)*pow(b, 2)))/3;
    for (int i = 1; i < N;i++){
        if(i%2 ==0){
            ItS += hS*(2*exp((-0.5)*pow((double)(a + (i*hS)), 2)))/3;
        }else{
            ItS += hS*(4*exp((-0.5)*pow((double)(a + (i*hS)), 2)))/3; 
        }
    }
    return ItS;
}

int main(){
   double x = 0;
   int a = 0, b = 1;
   double erro = 0.00000001;
   double hT, hS;
   double valorReal = 0.8556243919;
    /*double function = exp((-0.5)*pow(x, 2));
    printf(" Valor de f: %lf\n", function);*/

    double derivada2 = fabs(calcDerivada(x, 2));
    double derivada4 = fabs(calcDerivada(x, 4));
    int Nt, Ns;
    Nt = ceil(sqrtf(pow((b-a), 3)/(12*erro)));
    Ns = ceil(pow(pow((b-a), 5)*3/(180*erro), 1.0/4));
    printf("Nt: %d Ns: %d\n", Nt, Ns);

    double majoranteT = pow((b-a), 3)*derivada2/(12*pow(Nt, 2));
    double majoranteS = pow((b-a), 3)*derivada4/(180*pow(Ns, 4));
    printf("Valor de f: %lf para x = %lf\nValor de f: %lf para x = %lf\n\n", derivada2, x, derivada4, x);
    printf("Valor do majoranteT de f: %.10lf\nValor do majoranteS de f: %.10lf\n", majoranteT, majoranteS);
    hT = (double)(b-a)/Nt;
    hS = (double)(b-a)/Ns;
    double It = TrapezioComposta(Nt, hT, a, b);
    double Is = SimpsonComposta(Ns, hS, a, b);
    printf("Integral Método do Trapézio:%.10lf para hT = %lf\n", It, hT);
    printf("Integral Método do Trapézio:%.10lf para hT = %lf\n", Is, hS);
    printf("ErroT: %.10lf \nErroS: %.10lf\n", fabs(It - valorReal), fabs(Is - valorReal));



    /*Depois da Transformação da integral de f, temos que f = exp((-0.5)*(pow(0.5+x/2), 2)))
    Acessando a Tabela, para N = 6, obtém-se:
    
    x0 = 0.932470             A0 = 0.171324
    x1 = 0.661209             A1 = 0.360761
    x2 = 0.238619             A2 = 0.467913
    x3 = -0.932470            A3 = 0.171324
    x4 = -0.661209            A4 = 0.360761
    x5 = -0.238619            A5 = 0.467913
    */
   double Il =  0.171324*exp((-0.5)*(pow(0.5+(0.932470*0.5), 2))) + 
                0.360761*exp((-0.5)*(pow(0.5+(0.661209*0.5), 2))) +
                0.467913*exp((-0.5)*(pow(0.5+(0.238619*0.5), 2))) +
                0.171324*exp((-0.5)*(pow(0.5+((-0.932470)*0.5), 2))) +
                0.360761*exp((-0.5)*(pow(0.5+((-0.661209)*0.5), 2))) +
                0.467913*exp((-0.5)*(pow(0.5+((-0.238619)*0.5), 2)));

    printf("Il = %.10lf\n", Il/2);

    return 0;
}