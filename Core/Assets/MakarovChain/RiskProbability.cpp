#include "RiskProbability.hpp"
#include <algorithm>

RiskProbability::RiskProbability() {
    memo.assign(201, std::vector<double>(201,0.0));
    computed.assign(201, std::vector<bool>(201,false));

    transitions[{3,2}]={{2,0,0.292566},{1,1,0.335777},{0,2,0.371657}};
    transitions[{3,1}]={{1,0,0.340278},{0,1,0.659722}};
    transitions[{2,2}]={{2,0,0.448302},{1,1,0.324074},{0,2,0.227624}};
    transitions[{2,1}]={{1,0,0.421296},{0,1,0.578704}};
    transitions[{1,2}]={{1,0,0.745370},{0,1,0.254630}};
    transitions[{1,1}]={{1,0,0.583333},{0,1,0.416667}};
}

double RiskProbability::solve(int a,int d){
    if(d==0) return 1.0;
    if(a<2) return 0.0;
    if(computed[a][d]) return memo[a][d];
    computed[a][d]=true;
    int ad=std::min(3,a-1), dd=std::min(2,d);
    double res=0.0;
    for(const auto&t:transitions[{ad,dd}]){
        res += t.probability * solve(a-t.attackerLoss,d-t.defenderLoss);
    }
    memo[a][d]=res;
    return res;
}

double RiskProbability::winProbability(int attackers,int defenders){
    return solve(attackers,defenders);
}
