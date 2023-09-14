clc, clear, close all

% Get the mean, standard deviation and variance of the data
data1 = rand(1, 30) * 100 +200;
data2 = rand(1, 30) * 100 +300;

mean_data1 = mean(data1);
std_data1 = std(data1);
var_data1 = var(data1);

mean_data2 = mean(data2);
std_data2 = std(data2);
var_data2 = var(data2);

% disp(mean_data1 +  * std_data)
% disp(mean_data1 - 6 * std_data)
% Plot the normal distribution based on the mean and standard deviation
x = 0:0.1:600;
y1 = normpdf(x, mean_data1, std_data1);
y2 = normpdf(x, mean_data2, std_data2);
plot(x, y1, 'linewidth', 4.5, 'Color', '#4DBEEE');
hold on
plot(x, y2, 'linewidth', 4.5, 'Color', '#77AC30');
% Plot the mean and standard deviation of the data
% plot([mean_data1, mean_data1], [0, 0.015], 'g-');

axis([0, 600, -0.001, 0.02]);
% grid on
% set(gca, 'GridLineStyle', '--');
set(gca, 'linewidth', 4, 'fontsize', 20, 'fontname', 'TimesRoman', 'fontweight', 'bold')
xlabel('Pixel area of target insect')
% ylabel('Displacement (m)')
