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

vector<int> cumulativeSumInt(vector<int> probability, int n) // get CDF
{
  vector<int> cdf(n);
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

vector<int> getInterarrivalTime(vector<int> timeBetweenArrivals, vector<float> probability, int n, int numberOfcustomers)
{
  vector<int> InterarrivalTime;
  vector<float> random;                // random numbers to generate the interarrival
  random = getRand(numberOfcustomers); //random numbers to generate the interarrival
  /*for (auto it : random)
    cout << it << " ";
  cout << endl;*/
  fillT(timeBetweenArrivals, probability, n);
  /*for (auto it : timeBetweenArrivalsAndCdf)
    cout << it.first << " " << it.second << endl;*/
  for (int i = 0; i < numberOfcustomers; i++)
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

vector<int> getServiceTime(vector<int> serviceTime, vector<float> probability, int n, int numberOfcustomers)
{
  vector<int> ServiceTime;
  vector<float> random;                // random numbers to generate the interarrival
  random = getRand(numberOfcustomers); //random numbers to generate the interarrival
  /*for (auto it : random)
    cout << it << " ";
  cout << endl;*/

  fillS(serviceTime, probability, n);
  /*for (auto it : serviceTimeAndCdf)
    cout << it.first << " " << it.second << endl;*/
  for (int i = 0; i < numberOfcustomers; i++)
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

vector<int> get_Queue(vector<int> timeServiceEnds, vector<int> arrivalTime, vector<int> timeServiceBegins, int customers)
{
  vector<int> ans;
  queue<int> length;
  for (int i = 0; i < timeServiceEnds[customers - 1]; i++)
  {
    if (count(arrivalTime.begin(), arrivalTime.end(), i))
    {
      for (int j = 0; j < customers; j++)
      {
        if (arrivalTime[j] == i)
        {
          if (timeServiceBegins[j] != i)
          {
            length.push(1);
          }
        }
      }
    }
    if (count(timeServiceBegins.begin(), timeServiceBegins.end(), i))
    {
      if (!length.empty())
        length.pop();
    }
    if (count(arrivalTime.begin(), arrivalTime.end(), i))
      ans.push_back(length.size());
  }
  return ans;
}

void printAlltable(vector<int> interarrivalTime, vector<int> arrivalTime, vector<int> serviceTime, vector<int> timeServiceBegins, vector<int> waitingTime, vector<int> timeServiceEnds, vector<int> TimeSpendInSystem, vector<int> Idle, vector<int> queue_len)
{
  cout << "interarrivalTime : ";
  for (auto it : interarrivalTime)
    cout << it << " ";
  cout << endl;
  cout << "arrivalTime : ";
  for (auto it : arrivalTime)
    cout << it << " ";
  cout << endl;
  cout << "serviceTime : ";
  for (auto it : serviceTime)
    cout << it << " ";
  cout << endl;
  cout << "timeServiceBegins : ";
  for (auto it : timeServiceBegins)
    cout << it << " ";
  cout << endl;
  cout << "waitingTime : ";
  for (auto it : waitingTime)
    cout << it << " ";
  cout << endl;
  cout << "timeServiceEnds : ";
  for (auto it : timeServiceEnds)
    cout << it << " ";
  cout << endl;
  cout << "TimeSpendInSystem : ";
  for (auto it : TimeSpendInSystem)
    cout << it << " ";
  cout << endl;
  cout << "Idle : ";
  for (auto it : Idle)
    cout << it << " ";
  cout << endl;
  cout << "queue_len : ";
  for (auto it : queue_len)
    cout << it << " ";
  cout << endl;
}

int sum(vector<int> v)
{
  int sumi = 0;
  for (auto it : v)
    sumi += it;
  return sumi;
}

void printExpressions(vector<int> waitingTime, vector<int> Idle, vector<int> timeServiceEnds, vector<int> serviceTime, vector<int> interarrivalTime, vector<int> TimeSpendInSystem, vector<int> queue_len, int customers)
{
  cout << "Average waiting time : ";
  cout << (float)sum(waitingTime) / (float)customers << endl;
  cout << "Probability of waiting : ";
  cout << float(customers - count(waitingTime.begin(), waitingTime.end(), 0)) / (float)customers << endl;
  cout << "Probability of the server being idle : ";
  cout << (float)sum(Idle) / (float)timeServiceEnds[customers - 1] << endl;
  cout << "Average service time : ";
  cout << (float)sum(serviceTime) / (float)customers << endl;
  cout << "Average Interarrival Time : ";
  cout << (float)sum(interarrivalTime) / (float)customers << endl;
  cout << "Average TimeSpendInSystem : ";
  cout << (float)sum(TimeSpendInSystem) / (float)customers << endl;
  cout << "Average waiting time for those who wait : ";
  cout << (float)sum(waitingTime) / float(customers - count(waitingTime.begin(), waitingTime.end(), 0)) << endl;
  cout << "Server utilization : ";
  cout << (float)sum(serviceTime) / (float)timeServiceEnds[customers - 1] << endl;
  cout << "Average queue length : ";
  cout << (float)sum(queue_len) / (float)customers << endl;
}

int main()
{
  cout << "Do you have an Inter Arrival time and Service time or you need the program generate it?\n1)Yes.\n2)Please, generate it." << endl;
  int mode;
  vector<int> interarrivalTime, arrivalTime, serviceTime, timeServiceBegins, waitingTime, timeServiceEnds, TimeSpendInSystem, Idle, queue_len;

  cin >> mode;
  if (mode == 1)
  {
    int customers;
    cout << "Enter Number of Customers.\n";
    cin >> customers;

    // resize all the vectors with the size of customers
    interarrivalTime.resize(customers);
    serviceTime.resize(customers);
    timeServiceBegins.resize(customers);
    waitingTime.resize(customers);
    timeServiceEnds.resize(customers);
    TimeSpendInSystem.resize(customers);
    Idle.resize(customers);

    cout << "Enter the interarrivalTime.\n";
    for (auto &it : interarrivalTime)
      cin >> it;
    cout << "Enter the serviceTime.\n";
    for (auto &it : serviceTime)
      cin >> it;
    arrivalTime = cumulativeSumInt(interarrivalTime, customers);

    // initial values in the row one in the table
    timeServiceBegins[0] = arrivalTime[0];
    waitingTime[0] = timeServiceBegins[0] - arrivalTime[0];
    timeServiceEnds[0] = serviceTime[0] + timeServiceBegins[0];
    TimeSpendInSystem[0] = waitingTime[0] + serviceTime[0];
    Idle[0] = timeServiceBegins[0];

    //main loop
    queue<int> length, ttt;
    for (int i = 1; i < customers; i++)
    {
      timeServiceBegins[i] = max(timeServiceEnds[i - 1], arrivalTime[i]);
      waitingTime[i] = timeServiceBegins[i] - arrivalTime[i];
      timeServiceEnds[i] = serviceTime[i] + timeServiceBegins[i];
      TimeSpendInSystem[i] = waitingTime[i] + serviceTime[i];
      Idle[i] = timeServiceBegins[i] - timeServiceEnds[i - 1];
    }
    queue_len = get_Queue(timeServiceEnds, arrivalTime, timeServiceBegins, customers);

    cout << "1) If You want to construct the simulation table press (1)\n2) for calculating some expression press (2) \n3) Show me both press(3)\n";
    // printing all the table.
    int Check;
    cin >> Check;
    if (Check == 1)
      // printing all the table.
      printAlltable(interarrivalTime, arrivalTime, serviceTime, timeServiceBegins, waitingTime, timeServiceEnds, TimeSpendInSystem, Idle, queue_len);
    else if (Check == 2)
    {
      printExpressions(waitingTime, Idle, timeServiceEnds, serviceTime, interarrivalTime, TimeSpendInSystem, queue_len, customers);
    }
    else
    {
      printAlltable(interarrivalTime, arrivalTime, serviceTime, timeServiceBegins, waitingTime, timeServiceEnds, TimeSpendInSystem, Idle, queue_len);
      printExpressions(waitingTime, Idle, timeServiceEnds, serviceTime, interarrivalTime, TimeSpendInSystem, queue_len, customers);
    }
  }
  else if (mode == 2)
  {
    int n, m, customers;
    cout << "Enter Number of Customers.\n";
    cin >> customers;
    cout << "Enter size of Time Between Arrivals -> n, Service Time -> m.\n";
    cin >> n >> m;
    vector<int> timeBetweenArrivals(n), serviceTime(m);
    vector<float> probability(n), probabilityI(m);

    cout << "Enter timeBetweenArrivals.\n";
    for (auto &i : timeBetweenArrivals)
      cin >> i;
    cout << "Enter probability Of timeBetweenArrivals.\n";
    for (auto &i : probability)
      cin >> i;
    cout << "Enter serviceTime.\n";
    for (auto &i : serviceTime)
      cin >> i;
    cout << "Enter probability Of serviceTime.\n";
    for (auto &i : probabilityI)
      cin >> i;

    interarrivalTime = getInterarrivalTime(timeBetweenArrivals, probability, n, customers);
    arrivalTime = cumulativeSumInt(interarrivalTime, customers);
    serviceTime = getServiceTime(serviceTime, probabilityI, m, customers);

    //resize all the vectors with the size of customers
    timeServiceBegins.resize(customers);
    waitingTime.resize(customers);
    timeServiceEnds.resize(customers);
    TimeSpendInSystem.resize(customers);
    Idle.resize(customers);

    // initial values in the row one in the table
    timeServiceBegins[0] = arrivalTime[0];
    waitingTime[0] = timeServiceBegins[0] - arrivalTime[0];
    timeServiceEnds[0] = serviceTime[0] + timeServiceBegins[0];
    TimeSpendInSystem[0] = waitingTime[0] + serviceTime[0];
    Idle[0] = timeServiceBegins[0];

    //main loop
    for (int i = 1; i < customers; i++)
    {
      timeServiceBegins[i] = max(timeServiceEnds[i - 1], arrivalTime[i]);
      waitingTime[i] = timeServiceBegins[i] - arrivalTime[i];
      timeServiceEnds[i] = serviceTime[i] + timeServiceBegins[i];
      TimeSpendInSystem[i] = waitingTime[i] + serviceTime[i];
      Idle[i] = timeServiceBegins[i] - timeServiceEnds[i - 1];
    }
    queue_len = get_Queue(timeServiceEnds, arrivalTime, timeServiceBegins, customers);

    cout << "1) If You want to construct the simulation table press (1)\n2) for calculating some expression press (2) \n3) Show me both press(3)\n";

    int Check;
    cin >> Check;
    if (Check == 1)
      // printing all the table.
      printAlltable(interarrivalTime, arrivalTime, serviceTime, timeServiceBegins, waitingTime, timeServiceEnds, TimeSpendInSystem, Idle, queue_len);
    else if (Check == 2)
    {
      printExpressions(waitingTime, Idle, timeServiceEnds, serviceTime, interarrivalTime, TimeSpendInSystem, queue_len, customers);
    }
    else
    {
      printAlltable(interarrivalTime, arrivalTime, serviceTime, timeServiceBegins, waitingTime, timeServiceEnds, TimeSpendInSystem, Idle, queue_len);
      printExpressions(waitingTime, Idle, timeServiceEnds, serviceTime, interarrivalTime, TimeSpendInSystem, queue_len, customers);
    }
  }
  else
  {
    cout << "Please select the correct mode and try again :)\n";
  }
  return 0;
}
