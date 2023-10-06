# DropletShape
To determine the shape of a droplet of water on a horizontal surface.

## Basic Parameters
- $Mg = 0.03465034531487723 \mathrm{N}$
- $M = 0.0035357495219262474 \mathrm{kg}$
- $g = 9.8 \mathrm{m / s^2} $
- Density: $\rho = 1000 \mathrm{kg/m^3}$
- Volume: $V = 3.5357495219262473\times 10^{6} m^3$
- Contact angle: $45^\circ$
- Radius: $R = 10\mathrm{mm} = 10000\mathrm{\mu m}$
- Surface tension: $\sigma = 0.0728\mathrm{N}/\mathrm{m}$

Note that these conditions are clearly not independent, but are consistent.

Describe it with $z(r)$ (by symmetry). Then energy is computed by

$$ E = 2 \pi \int \frac{1}{2}\rho g z^2 r \mathrm{d}r + 2\pi\sigma \int \sqrt{1 + (z')^2} r \mathrm{d}r, $$

with constrain

$$ V = 2 \pi \int z r \mathrm{d}r. $$

Then we have

$$ \delta \int \left( \frac{1}{2}\rho g z^2 r + \sigma \sqrt{1 + (z')^2} r + \lambda zr \right) \mathrm{d}r = 0, $$

which can be rewritten as

$$ \delta \int \left[ \frac{1}{2}\rho g \left( z + \frac{\lambda}{\rho g} \right)^2 r + \sigma \sqrt{1+(z')^2} r - \frac{\lambda^2}{2\rho g} r \right] \mathrm{d}r = 0. $$

## About Constrains

1. Contact angle is hard to use if we are to employ the variation method.
2. And as you see, if we add a constrain of Volume, the problem gets really tricky. I think we can apply the following method:
   Introduce some energy that is proportional to the change in volume.

For simplicity's sake, take the square do no harm:

$$ E' = \alpha\left( \int zr \mathrm{d}r - \frac{V}{2\pi} \right)^2, \quad \text{where} \quad \alpha V^2 \gg \sigma R^2. $$

We just need to find the minimum of

$$ E = \int \left( \frac{1}{2}\rho g z^2 r + \sigma \sqrt{1 + (z')^2} r \right) \mathrm{d}r + \alpha\left( \int zr \mathrm{d}r - \frac{V}{2\pi} \right)^2. $$

## Discrete Variation

Instead of the continuous function $z(r)$, we consider a sequence `a[20002]` where the unit is $\mathrm{\mu m}$.

Then we use

| Continuous                  | Discrete        |
| --------------------------- | --------------- |
| $z(r)$                      | `z[r]`          |
| $z'(r)$                     | `z[r+1] - z[r]` |
| $\int f(z(r)) \mathrm{d} r$ | $\sum f$ `z[r]` |

to do the calculations.

We apply the method of simulate annealing to find the minimum.





