function [alpha leftstd rightstd] = estimateaggdparam(vec)% 零均值AGGD参数估计


gam   = 0.2:0.001:10;% 给定候选的形状参数，a在（0.2,10）区间范围每隔0.001取值
r_gam = ((gamma(2./gam)).^2)./(gamma(1./gam).*gamma(3./gam));%计算所有可能的参数估计


leftstd            = sqrt(mean((vec(vec<0)).^2));%估计方差1
rightstd           = sqrt(mean((vec(vec>0)).^2));%估计方差2
gammahat           = leftstd/rightstd;
rhat               = (mean(abs(vec)))^2/mean((vec).^2);
rhatnorm           = (rhat*(gammahat^3 +1)*(gammahat+1))/((gammahat^2 +1)^2);
[min_difference, array_position] = min((r_gam - rhatnorm).^2);
alpha              = gam(array_position);


