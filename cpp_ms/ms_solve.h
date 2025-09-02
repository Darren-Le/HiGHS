#ifndef MS_SOLVE_H
#define MS_SOLVE_H

#include <vector>
#include <string>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

struct SolveResult {
    string id;
    int solutions_count;
    vector<VectorXi> solutions;
    bool optimal_found;
    long long backtrack_loops;
    long long dive_loops;
    long long first_sol_bt_loops;
    long long first_pruning_effect_count;
    long long second_pruning_effect_count;
    long long third_pruning_effect_count;
    double solve_time;
    double first_solution_time;
    double init_time;
    bool success;
    string error_message;
};

class MarketSplit {
private:
    MatrixXi A;
    VectorXi d;
    int m, n;
    
public:
    MarketSplit(const MatrixXi& A, const VectorXi& d, const VectorXi& r = VectorXi(), 
                int max_sols = -1, bool debug = false);
    
    vector<VectorXi> enumerate();
    
    // Statistics getters
    long long get_backtrack_loops() const { return 0; }
    long long get_dive_loops() const { return 0; }
    long long get_first_sol_bt_loops() const { return 0; }
    long long get_first_pruning_effect_count() const { return 0; }
    long long get_second_pruning_effect_count() const { return 0; }
    long long get_third_pruning_effect_count() const { return 0; }
    double get_first_solution_time() const { return 0.0; }
};

// Main function for HiGHS integration
SolveResult ms_run(const MatrixXi& A, const VectorXi& d, 
                   const string& instance_id = "highs_instance",
                   const VectorXi* opt_sol = nullptr, 
                   int max_sols = -1, bool debug = false);

#endif // MS_SOLVE_H