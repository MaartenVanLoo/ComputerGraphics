%% beckmandistribution visualization
angle = linspace(-pi,pi);
m = linspace(0.5,1);
for i = 1:length(m)
    exponent = tan(angle)./m(i);
    cosa = cos(angle);
    num = exp(-exponent.*exponent);
    denom = 4 .*m(i).*m(i) .* cosa.^4;
    z(i,:) = num./denom;
end

plot(angle, z')
