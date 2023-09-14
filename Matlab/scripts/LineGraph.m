% clc, clear, close all
x = linspace(0, 3 * pi, 40);
y1 = sin(x);
y2 = 0.1 * x - 0.5;
% y3 = cos(x + pi / 2);

figure
% 黑色实线, 圆圈标记, 线宽1.0, 标记内部填充颜色从网上找好看的配色
plot(x, y1, 'linewidth', 4.5,'Color','')
grid on
set(gca, 'GridLineStyle', '--');
hold on
plot(x, y2, 'linewidth', 4.5)
% 设置坐标轴范围
axis([0, 3 * pi, -1.5 1.5])
% 坐标轴边框线宽1.6, 坐标轴字体与大小为Times New Roman和16
set(gca, 'linewidth', 4, 'fontsize', 20, 'fontname', 'TimesRoman', 'fontweight', 'bold')
xlabel('Time (s)')
ylabel('Displacement (m)')
legend('sin(x)', '0.1x-0.5')
