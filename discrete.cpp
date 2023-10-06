#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

double g = 9.8e6;
double rho = 1e-15;
double s = 0.0728e12;
double V;
double inf[20002], sup[20002];
double sphere[20002];
int R = 10000;
double a = s*R*R*R*R/V/V;	// \alpha V^2 \gg sR^2

std::mt19937 ran((int)time(0));
std::uniform_real_distribution<double> distr(0,1);

double Random() {
	return distr(ran);		// random number in [0,1]
}

double H(double *h) {
	double E = 0, w = V;
	for(int r=0;r<=2*R;r++)
		E += 0.5 * rho * g * r * pow(h[r], 2.0) + s * r * sqrt(1 + pow(h[r+1] - h[r], 2.0));
	for(int r=0;r<=2*R;r++)
		w += r * h[r];
	return E + a * pow(w, 2.0);
}

int main() {


	double *z = new double[20002];

	for(int r=0;r<=2*R;r++) {
		z[r] = fmax(0.0, sqrt(R*R*2 - r*r) - R);
		sphere[r] = z[r];
		V += r * z[r];
		sup[r] = z[r] + z[0]/10.0;
		inf[r] = fmax(0.0, z[r] - z[0]/10.0);
	}
	double T_0 = 1e3, T = 1e3, beta = 0.999;
	while(T >= 1e-13) {
		double *h = new double[20002];
		for(int r=0;r<=2*R;r++) {
			double infimum = inf[r] + (z[r] - inf[r]) * T / T_0;
			double supremum = z[r] + (sup[r] - z[r]) * T / T_0;
			h[r] = infimum + (supremum - infimum) * Random();
		}
		double p = exp(-H(z)/T);
		double q = exp(-H(h)/T);
		q /= (p + q);
		double d = Random();
		if(d <= q)
			z = h;
		T *= beta;
	}

	freopen("discrete.out", "w", stdout);

	for(int r=0;r<=2*R;r+=100) {
		printf("%4.4f    %4.4f\n", z[r], z[r] - sphere[r]);
	}

	return 0;
}


