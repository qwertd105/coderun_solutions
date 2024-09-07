## 240.Coins
### [Problem](https://coderun.yandex.ru/problem/coins/description?currentPage=2&groups=data-analytics&groups=ml&pageSize=20&search=)

### Idea of my solution:
####    Coinflips come from Bernoulli distribution, so lets use [Clopper pearson confidence interval](https://en.wikipedia.org/wiki/Binomial_proportion_confidence_interval) with 99% of confidence to each coinflip and then sort coinflips my middle of intervals