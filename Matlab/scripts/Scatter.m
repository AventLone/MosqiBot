clc, clear, close all

x = linspace(0, 10, 30);
% y1 = rand(1, 100);
% y2 = rand(1, 100) * 100 - 25;
y1 = rand(1, 30) * 100 +200;
y2 = rand(1, 30) * 100 +300;
disp(mean(y1))
disp(mean(y2))

figure
scatter(x, y1, 360, 'filled', 'MarkerEdgeColor', '#000000', 'MarkerFaceColor', '#EDB120')
hold on
scatter(x, y2, 360, 'filled', 'MarkerEdgeColor', '#000000', 'MarkerFaceColor', '#4DBEEE')

grid on
set(gca, 'GridLineStyle', '--');
set(gca, 'linewidth', 4, 'fontsize', 20, 'fontname', 'TimesRoman', 'fontweight', 'bold')
xlabel('Time (s)')
ylabel('Displacement (m)')
legend('y1', 'y2')
