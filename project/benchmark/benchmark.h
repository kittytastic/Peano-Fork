#include <chrono>
#include <iostream>
#include <vector>
#include <numeric>
#include <optional>
#include <functional>
#include <iomanip>
#include <cmath>
#include <string>
#include <cassert>



namespace benchmark{
namespace core{
std::pair<double, double> calc_mean_std(std::vector<long long> v){

    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();

    double sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / v.size() - mean * mean);


    return std::pair<double, double> (mean, stdev);
}


std::string smart_print_time(long long time_ns){
    const long long micro_s = 1e3;
    const long long mill_s = 1e6;
    const long long s = 1e9;
    const long long min = 1e9 * 60;

    std::ostringstream out_str;
    
    if(time_ns<micro_s){
        out_str<<time_ns<<"ns";
    }else if (time_ns<mill_s){
        out_str<<std::fixed<<std::setprecision(1)<<(double)time_ns/micro_s<<"µs";
    }else if (time_ns<s){
        out_str<<std::fixed<<std::setprecision(1)<<(double)time_ns/mill_s<<"ms";
    }else if (time_ns<min){
        out_str<<std::fixed<<std::setprecision(1)<<(double)time_ns/s<<"s";
    }else{
        out_str <<time_ns/min<<"m "<<std::fixed<<std::setprecision(1)<<(double)(time_ns%min)/s<<"s";
    }

    return out_str.str();
}

int by_trials(std::function<void()> func, int trials, std::vector<long long> &out){
    int done_trials = 0;
    while(done_trials<trials){
        auto t1 = std::chrono::high_resolution_clock::now();
        func();
        auto t2 = std::chrono::high_resolution_clock::now();
        long long ns_int = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

        out.push_back(ns_int);
    
        done_trials +=1;
    }

    return done_trials;
}

int by_time(std::function<void()> func, double target_dur_s , std::vector<long long> &out){
    int done_trials = 0;
    long long run_duration = 0;
    long long target_duration=(long long)(target_dur_s*1e9);
    
    auto start = std::chrono::high_resolution_clock::now();
    do{
        auto t1 = std::chrono::high_resolution_clock::now();
        func();
        auto t2 = std::chrono::high_resolution_clock::now();
        long long ns_int = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
        
        run_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - start).count();

        out.push_back(ns_int);
    
        done_trials +=1;
    }while(run_duration<target_duration);

    return done_trials;
}
}
/**
 * @brief Benchmark the runtime of a function.
 * 
 * @param func The function to be benchmark 
 * @param trials [Optional] The number of trials 
 * @param target_dur_s [Optional] The target test duration (in s)
 */
void benchmark(std::function<void()> func, std::optional<int> trials, std::optional<double> target_dur_s){
    
    if(!trials.has_value() && !target_dur_s.has_value()){
        std::cout << "Failed to run benchmark. Please provide a number of trails or target length."<<std::endl;
        return;
    }

    int target_trials = trials.has_value()?trials.value():0;
    
    std::vector<long long> observed_run_times;
    int done_trials;

    auto g1 = std::chrono::high_resolution_clock::now();
    if (trials.has_value()){
        done_trials = core::by_trials(func, trials.value(), observed_run_times);
    }else if(target_dur_s.has_value()){
        done_trials = core::by_time(func, target_dur_s.value(), observed_run_times);
    }

    auto g2 = std::chrono::high_resolution_clock::now();
    assert(done_trials==observed_run_times.size());

    auto m_a_s = core::calc_mean_std(observed_run_times);
    double mean = m_a_s.first/1000;
    double std = m_a_s.second/1000;
    long long global_run_time = std::chrono::duration_cast<std::chrono::nanoseconds>(g2 - g1).count();


    const int lfw = 20;
    const int rfw = 10;
    std::cout << std::setw(lfw) << std::left << "Trials:" << std::setw(rfw) << std::right << done_trials << std::endl; 
    std::cout << std::setw(lfw) << std::left<< "Total run time:"<< std::setw(rfw) << std::right<<core::smart_print_time(global_run_time)<< std::endl;
    std::cout << std::setw(lfw) << std::left<< "Mean run time:"<< std::setw(rfw) << std::right << core::smart_print_time((long long)mean) << std::endl;
    std::cout << std::setw(lfw) << std::left<< "STD:"<< std::setw(rfw) << std::right << core::smart_print_time((long long)std)<< std::endl;
}

const auto NONE = std::nullopt;
}

