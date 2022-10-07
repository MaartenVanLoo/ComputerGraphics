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



%% inverse shear
syms hxy hxz hyz hyx hzx hzy
T = [1, 0, hxy,0; 
     0,1, hzy,0; 
     0, 0,1,0;
     0,0,0,1]
inv(T)

A = [
    [34, 23, 5, 0],
    [37, 25, 6, 0],
    [6, 4, 1, 0],
    [0, 0, 0, 1]]

B = [
    [-6, 17, -5, 0],
    [-13, 25, -6, 0],
    [2, -4, 1, 0],
    [0, 0, 0, 1]]

Tx = [1, 0, 0,0; 
     1,1, 0,0; 
     2, 0,1,0;
     0,0,0,1]

Ty = [1, 3, 0,0; 
     0,1, 0,0; 
     0, 4,1,0;
     0,0,0,1]

Tz = [1, 0, 5,0; 
     0,1, 6,0; 
     0, 0,1,0;
     0,0,0,1]
RTx = [1, 0, 0,0; 
     -1,1, 0,0; 
     -2, 0,1,0;
     0,0,0,1]

RTy = [1, -3, 0,0; 
     0,1, 0,0; 
     0, -4,1,0;
     0,0,0,1]

RTz = [1, 0, -5,0; 
     0,1, -6,0; 
     0, 0,1,0;
     0,0,0,1]
inv(Tx)
inv(Ty)
inv(Tz)
transf = (Tz*Ty*Tx) * eye(4)
invtransf = (RTx*RTy*RTz) * eye(4)
inv(transf)
transf * invtransf