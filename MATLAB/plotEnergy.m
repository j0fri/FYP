M = readmatrix('energy.txt');
            
t = M(:,1);
Ke = M(:,2);
Pe = M(:,3);

figure(1);
clf
hold on
plot(t, Pe);
plot(t, Ke);
plot(t, Pe + Ke);
legend('Field energy', 'Kinetic energy', 'Total energy');
xlabel('Time')
ylabel('Energy')

figure(2);
clf
semilogy(t, Pe);
hold on
semilogy(t, Pe(1)*exp(-5e-2*t));
grid on
xlabel('Time')
ylabel('E^{2}')