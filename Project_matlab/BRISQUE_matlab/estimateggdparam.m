function [gamparam sigma] = estimateggdparam(vec)%零均值GGD参数估计



gam                              = 0.2:0.001:10; %给定候选的形状参数
r_gam                            = (gamma(1./gam).*gamma(3./gam))./((gamma(2./gam)).^2);%比值

sigma_sq                         = mean((vec).^2);% 方差的零均值估计
sigma                            = sqrt(sigma_sq);
E                                = mean(abs(vec));
rho                              = sigma_sq/E^2;
[min_difference, array_position] = min(abs(rho - r_gam));
gamparam                         = gam(array_position);  






