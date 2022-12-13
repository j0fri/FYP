T = 10;
dt = [0.01, 0.1, 0.5, 1.0];
styles = ["-","--","o","-o"];

figure;
clf;
semilogy(t, Pe(1)*exp(-5e-2*t),'color','r');
hold on;
for i = 1:length(dt)
    M = readmatrix(['energy',num2str(i),'.txt']);     
    t = M(:,1);
    Ke = M(:,2);
    Pe = M(:,3);
    semilogy(t, Pe, styles(i), 'color', 'k');
end    
