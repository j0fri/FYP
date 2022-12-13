files = ["initialElectrons", "initialIons"];

for i = 1:length(files)
    m = readmatrix(files(i));
    writematrix(m, files(i), 'delimiter', ' ');
end