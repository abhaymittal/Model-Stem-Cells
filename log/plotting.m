%Average value of E-Beta vs Time
fig1 = figure(1);
data = csvread('averageEB.csv');
x=data(:,1);
y=data(:,2);
plot(x,y);
title('Average value of E-Beta vs Time');
xlabel('Time (iteration)');
ylabel('Average value of E-Beta');
saveas(fig1, 'averageEB.fig');
saveas(fig1, 'averageEB.png');
close(fig1);

%Number of normal cells vs Time
fig2 = figure(2);
data = csvread('numNormalCells.csv');
x=data(:,1);
y=data(:,2);
plot(x,y);
title('Number of normal cells vs Time');
xlabel('Time (iteration)');
ylabel('Number of normal cells');
saveas(fig2, 'numNormalCells.fig');
saveas(fig2, 'numNormalCells.png');
close(fig2);

%Number of stem cells vs Time
fig3 = figure(3);
data = csvread('numStemCells.csv');
x=data(:,1);
y=data(:,2);
plot(x,y);
title('Number of stem cells vs Time');
xlabel('Time (iteration)');
ylabel('Number of stem cells');
saveas(fig3, 'numStemCells.fig');
saveas(fig3, 'numStemCells.png');
close(fig3);

%Number of TA cells vs Time
fig4 = figure(4);
data = csvread('numTACells.csv');
x=data(:,1);
y=data(:,2);
plot(x,y);
title('Number of TA cells vs Time');
xlabel('Time (iteration)');
ylabel('Number of TA cells');
saveas(fig4, 'numTACells.fig');
saveas(fig4, 'numTACells.png');
close(fig4);

%Total number of cells vs Time
fig5 = figure(5);
data = csvread('numTotalCells.csv');
x=data(:,1);
y=data(:,2);
plot(x,y);
title('Total number of cells vs Time');
xlabel('Time (iteration)');
ylabel('Total number of cells');
saveas(fig5, 'numTotalCells.fig');
saveas(fig5, 'numTotalCells.png');
close(fig5);

%Number of ECM Fibers vs Time
fig6 = figure(6);
data = csvread('totalECMFiber.csv');
x=data(:,1);
y=data(:,2);
plot(x,y);
title('Number of ECM Fibers vs Time');
xlabel('Time (iteration)');
ylabel('Number of ECM Fibers');
saveas(fig6, 'totalECMFiber.fig');
saveas(fig6, 'totalECMFiber.png');
close(fig6);
