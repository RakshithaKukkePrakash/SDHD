%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Testbench Communication from FreeSoc2 to Matlab
% Version 1.0, Bannwarth, 30.05.2020
%
% Behaviour: 
% - Everytime Matlab writes ‘s’ on the UART, the PSoC sends new measurement 
%    results and Matlab writes 'o' if these data are received.
% - The Script terminates after 10 data transfers.
%
% Using:
% 1. Connect FreeSoc2 to USB (i.e. Power Up)
% 2. Check the correct serial Port Settings
% 3. Start this Matlab Script
% 4. Run this Script
% 5. Press the external Push Button to start measuring
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;
clc;

% CA CFAR Parameters
NG = 1;     % Number of Guard Cells
NR = 10;    % Number of Reference Cells
PFA = 10^-6; % Probability of False Alarm

% Serial port settings
priorPorts = instrfind;
delete(priorPorts);
PSoC = serial('COM7', 'BaudRate', 9600, 'InputBufferSize', 14000);
fopen(PSoC);

f1 = figure;
count = 1;
flg_data_avai = 0;
fwrite(PSoC, 's', 'uchar'); % means send, I am ready to receive

while(flg_data_avai == 0)
    if PSoC.BytesAvailable >= 3072
        fwrite(PSoC, 'o', 'uchar'); % means I received all expected data
        rx_data_adc = fread(PSoC, 1024, 'uint16');
        fprintf(" Transfer %i DONE \n", count);
        rx_data_fft = fread(PSoC, 2048, 'int32');
        fprintf(" Transfer %i DONE \n", count);

        % Plotting the received data
        figure(f1)
        subplot(5, 1, 1)
        plot([0:(length(rx_data_adc)-1)], rx_data_adc(1:(length(rx_data_adc))));
        title(['Received Time Domain Data No.:', num2str(count)]);
        
        subplot( 5,1, 2)
        plot([0:1023], 20*log10(1/length(rx_data_adc) * abs(fft(rx_data_adc))));
        title('FFT - Matlab');

        % Plot Magnitude Spectrum
        subplot(5, 1, 3)
        plot(0:length(rx_data_fft)-1, 20*log10(abs(rx_data_fft)));
        title('FFT Mag - PSoC');

        % Save the received data
        save(strcat('CW_rx_data_adc_', int2str(count), '.mat'), 'rx_data_adc');

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
    end

    if count == 11
        break;
    end

    fwrite(PSoC, 's', 'uchar'); % means send, I am ready to receive
end

fclose(PSoC);
fprintf("Script End \n");
