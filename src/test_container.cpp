#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

constexpr auto low_bound = -1000;
constexpr auto up_bound = 1000;
constexpr int vlow_bound = 0;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(-1000, 1000);
auto time_vector_search(int size) {
  std::uniform_int_distribution<int> vdist(0, size);
  std::vector<int> v(size);
  auto start = std::chrono::high_resolution_clock::now();
  for (int i=0; i<=size; ++i) { (i<size) ? v[i]=int(dist(gen)) : v[int(vdist(gen))]=int(dist(gen));}
  auto end=std::chrono::high_resolution_clock::now();
  auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
  return duration.count();
};
auto time_unordered_map_search(int size) {
  std::unordered_map<int,int> um;
  auto start = std::chrono::high_resolution_clock::now();
  for (int i=0; i<size; ++i) { um[int(dist(gen))] = 0;}
  int oldkey = int(dist(gen));
  if (um.find(oldkey)!=um.end()) {
    um.erase(oldkey);
    um[int(dist(gen))]=0;}
  auto end=std::chrono::high_resolution_clock::now();
  auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
  return duration.count();
}
int main()
{
  int search_size = 1000000/10000-1;
  int time_difference[search_size];
  int time_i = 0;
  //std::cout<<"Replacing element of container of size n"<<std::endl;
  //std::cout<<"Vector\tUnordered_map\tN"<<std::endl;
  for (int i=10000; i<1000000; i+=10000) {
    int vtime=time_vector_search(i);
    int umtime=time_unordered_map_search(i);
    //std::cout<<vtime<<"\t"<<umtime<<"\t"<<i<<std::endl;
    time_difference[time_i++]=vtime-umtime;}
  int time_sum=0;
  for (int t=0; t<search_size; ++t) {time_sum+=time_difference[t];}
  double time_mu=time_sum/search_size;
  double time_sigma_sq=0;
  for (int t=0; t<search_size; ++t) {time_sigma_sq+=(time_difference[t]-time_mu)*(time_difference[t]-time_mu);}
  time_sigma_sq/=search_size;
  double time_sigma=sqrt(time_sigma_sq);
  std::cout<<"Mu and sigma of time differences for replacing random element of vector vs. unordered map"<<std::endl;
  std::cout<<"Mu: "<<time_mu<<"\tSigma: "<<time_sigma<<std::endl;
  return 0;
}
