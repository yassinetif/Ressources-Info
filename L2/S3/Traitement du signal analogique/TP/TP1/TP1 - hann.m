function w = hann(N)
% Calculates Hanning window samples.
% Calculates and returns the N points of w
% Hanning window.

w = .5*(1 - cos(2*pi*(1:N)'/(N+1))); 
