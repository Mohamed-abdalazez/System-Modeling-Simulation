#include <bits/stdc++.h>

using namespace std;

map<float, int> timeBetweenArrivalsAndCdf;
map<float, int> serviceTimeAndCdf;

vector<float> cumulativeSum(vector<float> probability, int n) // get CDF
{
  vector<float> cdf(n);
  cdf[0] = probability[0];
  for (int i = 1; i < n; i++)
  {
    cdf[i] = cdf[i - 1] + probability[i];
  }
  return cdf;
}

void fillT(vector<int> timeBetweenArrivals, vector<float> probability, int n) // map<float, int> timeBetweenArrivalsAndCdf;
{
  for (int i = 0; i < probability.size(); i++)
  {
    timeBetweenArrivalsAndCdf[cumulativeSum(probability, n)[i]] = timeBetweenArrivals[i];
  }
}
void fillS(vector<int> serviceTime, vector<float> probability, int n) // map<float, int> serviceTimeAndCdf;
{
  for (int i = 0; i < probability.size(); i++)
  {
    serviceTimeAndCdf[cumulativeSum(probability, n)[i]] = serviceTime[i];
  }
}

int main()
{
  int n, m;
  cin >> n >> m;
  vector<int> timeBetweenArrivals(n), serviceTime(m);
  vector<float> probability(n), probabilityI(m);
  for (auto &i : timeBetweenArrivals)
    cin >> i;
  for (auto &i : probability)
    cin >> i;
  for (auto &i : serviceTime)
    cin >> i;
  for (auto &i : probabilityI)
    cin >> i;

  fillT(timeBetweenArrivals, probability, n);
  fillS(serviceTime, probabilityI, m);

  for (auto it : timeBetweenArrivalsAndCdf)
    cout << it.first << " " << it.second << endl;

  cout << "\n";

  for (auto it : serviceTimeAndCdf)
    cout << it.first << " " << it.second << endl;
}
