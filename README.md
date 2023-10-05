# DropletShape
To determine the shape of a droplet of water on a horizontal surface.

Basic parameters:
- $Mg = 0.03465034531487723$
- $M = 0.0035357495219262474$
- $g = 9.8$
- Volume: $V = 3.5357495219262473\times 10^{-6}$
- Contact angle: $45^\circ$
- Surface tension: $\sigma = 0.0728N/m$

Describe it with $z(r)$ (by symmetry). Then energy is computed by

$E = 2 \pi \int \rho g z^2 r \mathrm{d}r + 2\pi\sigma \int \sqrt{1 + (z')^2} r \mathrm{d}r,$

with constrain

$V = 2 \pi \int z r \mathrm{d}r.$

Then we have

$\delta \int \left( \rho g z^2 r + \sigma \sqrt{1 + (z')^2} r - \lambda zr \right) \mathrm{d}r = 0.$
