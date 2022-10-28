%% beckmandistribution visualization
angle = linspace(-pi/2,pi/2,10000);
m = linspace(0.5,1);
z(length(m),length(angle))=0;
for i = 1:length(m)
    z(i,:) = beckmann(angle,m(i));
end

plot(angle,beckmann(angle,0.01))
hold on
plot(angle, z')

function [val] = beckmann(angle, m)
    exponent = tan(angle)./m;
    cosa = cos(angle);
    num = exp(-exponent.*exponent);
    denom = 4 .*m.*m .* cosa.^4;
    val = num./denom;
end