format longg
angle = 10;
radian = deg2rad(angle)
Rx = makehgtform('xrotate',radian)
Ry = makehgtform('zrotate',radian)
Rz = makehgtform('yrotate',radian)
Raxis = makehgtform('axisrotate',[3,4,5],radian)



vec = [1;2;3;0]

Rx*vec
Ry*vec
Rz*vec
Raxis*vec


%% check order of operations
angle = 20;
radian = deg2rad(angle)
Rx * Ry * Rz
Ry * Rx * Rz
%=> does matter!


%% check inverse

Rx = makehgtform('xrotate', radian);
Rxinv = makehgtform('xrotate', -radian);
Ry = makehgtform('yrotate', radian);
Ryinv = makehgtform('yrotate', -radian);
Rz = makehgtform('zrotate', radian);
Rzinv = makehgtform('zrotate', -radian);

vec = [1;0;0;0]
plot3([0,vec(1)],[0,vec(1)],[0,vec(3)])
t = (Ry * Rx )*vec
plot3([0,t(1)],[0,t(1)],[0,t(3)])
t = (Rx * Ry )*vec
plot3([0,t(1)],[0,t(1)],[0,t(3)])
hold on
t = (Ryinv * Rxinv) * t

Rx * Ry * Ryinv * Rxinv
