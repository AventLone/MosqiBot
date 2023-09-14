clc, clear
close all

data = [0.1 0.2 0.3 0.4];
labels = {'a', 'b', 'c', 'd'};
explode = [0 0 0 1];

%% plot pi chart
% pie(data, explode, labels)
% create pie chart without outline
figure
pie(data, explode)
% 坐标轴边框线宽1.6, 坐标轴字体与大小为Times New Roman和16
set(gca, 'linewidth', 2, 'fontsize', 20, 'fontname', 'TimesRoman', 'fontweight', 'bold')
title('Pie Chart')
legend(labels)

% % plot 3D pie chart
% figure
% % pie3(data,explode,labels)
% pie3(data, explode)
% title('3D Pie Chart')
% % legend(labels, 'Location', 'EastOutside')
% legend(labels)
