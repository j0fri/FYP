M = readmatrix('initial.txt');
            
x = M(:,1);
rho = M(:,2);
E = M(:,3);

figure(1);
clf
hold on
plot(x, rho);
plot(x, E);
legend('Charge distribution', 'Electric field');
