#include <bits/stdc++.h>
using namespace std;

/**
 *
 * Project : Discrete simulation project 
 * author  : Mohamed Abdalazez Abdallah Mohamed
 *
**/

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

vector<float> getRand(int n) // get random number with a size of customers
{
  srand((unsigned)time(NULL));
  vector<float> R;
  for (int i = 0; i < n; i++)
  {
    float value = (float)rand() / RAND_MAX;
    R.push_back(((int)(value * 100 + .5) / 100.0));
  }
  return R;
}

vector<int> getInterarrivalTime(vector<int> timeBetweenArrivals, vector<float> probability, int n)
{
  vector<int> InterarrivalTime;
  vector<float> random; // random numbers to generate the interarrival
  random = getRand(n);  //random numbers to generate the interarrival
  /*for (auto it : random)
    cout << it << " ";
  cout << endl;*/
  fillT(timeBetweenArrivals, probability, n);
  /*for (auto it : timeBetweenArrivalsAndCdf)
    cout << it.first << " " << it.second << endl;*/
  for (int i = 0; i < n; i++)
  {
    stack<float> st;
    for (auto it : timeBetweenArrivalsAndCdf)
    {
      st.push(it.first);                                // to get last true index
      if (st.size() == 1 && random[i] - it.first < 0.0) // first random les than InterarrivalTime
      {
        InterarrivalTime.push_back(timeBetweenArrivalsAndCdf[st.top()]);
        break;
      }
      if (st.size() == n && random[i] - it.first > 0.0)
      {
        InterarrivalTime.push_back(timeBetweenArrivalsAndCdf[st.top()]);
        break;
      }
      if (random[i] - it.first == 0.0)
      {
        InterarrivalTime.push_back(timeBetweenArrivalsAndCdf[st.top()]);
        break;
      }
      if (random[i] - it.first < 0.0)
      {
        st.pop();
        InterarrivalTime.push_back(timeBetweenArrivalsAndCdf[st.top()]);
        break;
      }
    }
  }
  /*for (auto it : timeBetweenArrivalsAndCdf)cout << it.first << " " << it.second << endl;*/
  return InterarrivalTime;
}

vector<int> getServiceTime(vector<int> serviceTime, vector<float> probability, int n)
{
  vector<int> ServiceTime;
  vector<float> random; // random numbers to generate the interarrival
  random = getRand(n);  //random numbers to generate the interarrival
  /*for (auto it : random)
    cout << it << " ";
  cout << endl;*/

  fillS(serviceTime, probability, n);
  /*for (auto it : serviceTimeAndCdf)
    cout << it.first << " " << it.second << endl;*/
  for (int i = 0; i < n; i++)
  {
    stack<float> st;
    for (auto it : serviceTimeAndCdf)
    {
      st.push(it.first); // to get last true index

      st.push(it.first);                                // to get last true index
      if (st.size() == 1 && random[i] - it.first < 0.0) // first random les than InterarrivalTime
      {
        ServiceTime.push_back(serviceTimeAndCdf[st.top()]);
        break;
      }
      if (st.size() == n && random[i] - it.first > 0.0)
      {
        ServiceTime.push_back(serviceTimeAndCdf[st.top()]);
        break;
      }

      if (random[i] - it.first == 0.0)
      {
        ServiceTime.push_back(serviceTimeAndCdf[st.top()]);
        break;
      }
      if (random[i] - it.first < 0.0)
      {
        //cout << "true" << endl;
        st.pop();
        ServiceTime.push_back(serviceTimeAndCdf[st.top()]);
        break;
      }
    }
  }

  /*for (auto it : serviceTimeAndCdf)cout << it.first << " " << it.second << endl;*/
  return ServiceTime;
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

  for (auto it : getInterarrivalTime(timeBetweenArrivals, probability, n))
  {
    cout << it << " ";
  }
  cout << endl;
  for (auto it : getServiceTime(serviceTime, probabilityI, m))
  {
    cout << it << " ";
  }
  cout << endl;
}
