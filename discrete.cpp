#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

double g = 9.8;
double rho = 1e3;
double s = 0.0728;
double V;
double inf[20002], sup[20002];
double sphere[20002];
int R = 10000;
double a;		// \alpha V^2 \gg sR^2

bool plot[202][52];
bool plotsph[202][52];

std::mt19937 ran((int)time(0));
std::uniform_real_distribution<double> distr(0,1);

double Random() {
	return distr(ran);			// Random number in [0,1]
}

double H(double *h) {			// Calculating the energy
	double E = 0, w = 0;
	for(int r=0;r<=2*R;r++)		// Actual energy (multiplied by 1e6)
		E += 0.5 * rho * g * r / 1e6 * pow(h[r] / 1e6, 2.0) + s * r / 1e6 * sqrt(1 + pow(h[r+1] - h[r], 2.0));
	for(int r=0;r<=2*R;r++)		// Change in Volume (multiplied by 1e6)
		w += r / 1e6 * h[r] / 1e6;
	return E + a * pow(w - V, 2.0);
}

int main() {

	freopen("debug.out", "w", stdout);

	double *z = new double[20002];

	for(int r=0;r<=2*R;r++) {
		z[r] = fmax(0.0, sqrt(R*R*2 - r*r) - R);
		sphere[r] = z[r];		// The equation of a sphere
		V += r / 1e6 * z[r] / 1e6;			// The original Volume (multiplied by 1e6)
		sup[r] = z[r] + z[0]/10.0;
		inf[r] = fmax(0.0, z[r] - z[0]/10.0);	// Set the boundary for variation
	}

	a = s * R * R / V / V / 1e6 * 0;		// \alpha V^2 \gg sR^2
	printf("\\alpha = %f\n", a);

	double T_0 = 100, beta = 0.999;
	double T = T_0;
	while(T >= 1e-11) {
		double *h = new double[20002];
		for(int r=0;r<=2*R;r++) {
			double infimum = inf[r] + (z[r] - inf[r]) * T / T_0;
			double supremum = z[r] + (sup[r] - z[r]) * T / T_0;
			h[r] = infimum + (supremum - infimum) * Random();	// Variation at each point
		}
		printf("H = %f\n", H(h));
		// double p = exp(-H(z)/T);
		// double q = exp(-H(h)/T);
		// q /= (p + q);
		/*
		double p = exp((H(h) - H(z)) / T);		// Simulate annealing, using the Boltzmann distribution
		double q = 1 / (1 + p);
		double d = Random();
		if(d <= q)
			z = h, printf("*");				// Update the equation
		*/
		if(H(h) < H(z))			// Greedy Algorithm
			z = h;
		T *= beta;				// Cooling down
	}

	double v=0;
	for(int r=0;r<=2*R;r++) {
		v += r / 1e6 * z[r] / 1e6;
	}
	printf("\nVolume = %f    Difference: %f\n", v, v - V);
	
	printf("Original Energy: %f    Current Energy: %f\n", H(sphere), H(z));

	freopen("discrete.out", "w", stdout);

	for(int r=0;r<=2*R;r+=100) {
		printf("%9.4f    %9.4f    %9.4f\n", z[r], sphere[r], z[r] - sphere[r]);		// Display the difference from a sphere
		plot[r/100][int(45.0 * z[r] / sphere[0])] = true;
		plotsph[r/100][int(45.0 * sphere[r] / sphere[0])] = true;
	}

	for(int i=45;i>=0;i--) {
		for(int j=0;j<=150;j++) {
			if(plot[j][i]) {
				printf("*");
			} else if(plotsph[j][i]) {
				printf("-");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}

	return 0;
}


