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
