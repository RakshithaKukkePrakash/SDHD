%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Testbench Communication from FreeSoc2 to Matlab
% Version 1.0, Bannwarth, 30.05.2020
%
% Behaviour: 
% - Load ADC data from files in a specified folder
% - Perform FFT and CFAR on the loaded data
% - Plot the results
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;
clc;

% CA CFAR Parameters
NG = 1;     % Number of Guard Cells
NR = 10;    % Number of Reference Cells
PFA = 10^-6; % Probability of False Alarm
% Folder containing ADC data files
dataFolder = 'C:\Sandbox\Sem2\SDHD\data_adc_RADAR\data'; 
filePattern = fullfile(dataFolder, 'CW_rx_data_adc_*.mat');
dataFiles = dir(filePattern);

f1 = figure;
count = 1;

for k = 1:length(dataFiles)
    baseFileName = dataFiles(k).name;
    fullFileName = fullfile(dataFolder, baseFileName);
    fprintf('Now reading %s\n', fullFileName);
    
    % Load ADC data from file
    load(fullFileName, 'rx_data_adc');

    % Plotting the received data
    figure(f1)
    subplot(3, 1, 1)
    plot([0:(length(rx_data_adc)-1)], rx_data_adc(1:(length(rx_data_adc))));
    title(['Received Time Domain Data No.:', num2str(count)]);

    subplot(3, 1, 2)
    plot([0:1023], 20*log10(1/length(rx_data_adc) * abs(fft(rx_data_adc))));
    title('FFT - Matlab');

    % CFAR Implementation
    N = length(rx_data_adc); % Update N to the length of received ADC data
    X = fft(rx_data_adc);
    X_mag_squared = abs(X).^2;
    fs = 256; % Sample rate 
    f = (0:N-1) * (fs / N); % Adjust frequency calculation based on sample rate
    alpha = NR * (PFA^(-1/NR)-1);
    threshold_cfar = zeros(N, 1);
    signal_cfar = zeros(N, 1);

    for i = (NR + NG + 1):(N - (NR + NG))
        leading_window = X_mag_squared(i - NR - NG:i - NG - 1);
        lagging_window = X_mag_squared(i + NG + 1:i + NR + NG);
        noise_level = sum(leading_window) + sum(lagging_window);
        threshold = (alpha / (2 * NR)) * noise_level;
        threshold_cfar(i) = threshold;
        
        if X_mag_squared(i) > threshold
            signal_cfar(i) = X_mag_squared(i);
        end
    end

    % Apply a noise threshold to filter out low-level noise detections
    % Factor 2 can be adjusted 
    noise_threshold = median(X_mag_squared) * 2; 
    signal_cfar(signal_cfar < noise_threshold) = 0;

    % Further refine the detection by applying a minimum peak height criteria
    % Can adjust the factor for stricter peak detection
    min_peak_height = 20 * median(X_mag_squared); 
    [pks, locs] = findpeaks(signal_cfar, 'MinPeakHeight', min_peak_height);

    % Plot the resulting threshold and detected targets in the spectra plot
    subplot(3, 1, 3)
    p1 = plot(f, X_mag_squared, 'b');
    hold on
    p2 = plot(f, threshold_cfar, 'r', 'LineWidth', 1.5);
    p3 = plot(f(locs), pks, 'go');
    title('CFAR Detection');
    legend([p1, p2], 'Spectrum', 'CA-CFAR Threshold');
    if ~isempty(pks)
        legend([p1, p2, p3], 'Spectrum', 'CA-CFAR Threshold', 'Detected Targets');
    end
    hold off

    count = count + 1;

    if count == 11
        break;
    end
end

fprintf("Script End \n");
