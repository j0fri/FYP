M = readmatrix('initialVelocities.txt');

[p, x] = hist(M(:,1));
figure(1)
clf
plot(x, p/sum(p))
