#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double get_val(double v1, double v2, int op){

  switch(op){
    case 0: return v1 + v2;
    case 1: return v1 - v2;
    case 2: return v1 * v2;
    case 3: 
      if(v2==0) return nan("");
      else      return v1/v2;
    default:
      if(v1<0 && int(v2) - v2 != 0) return nan("");
      else return pow(v1, v2);
  }
  
  return 0;

}

double get_val(vector<int> num, vector<int> ops, int ord){

  double lh, rh, md;

  switch(ord){
    case 0:
      lh = get_val(num[0], num[1], ops[0]);
      rh = get_val(num[2], num[3], ops[2]);
      return get_val(lh, rh, ops[1]);
    case 1:
      lh = get_val(num[0], num[1], ops[0]);
      lh = get_val(lh, num[2], ops[1]);
      return get_val(lh, num[3], ops[2]);
    case 2:
      md = get_val(num[1], num[2], ops[1]);
      md = get_val(num[0], md, ops[0]);
      return get_val(md, num[3], ops[2]);
    case 3:
      md = get_val(num[1], num[2], ops[1]);
      md = get_val(md, num[3], ops[2]);
      return get_val(num[0], md, ops[0]);
    default:
      rh = get_val(num[2], num[3], ops[2]);
      rh = get_val(num[1], rh, ops[1]);
      return get_val(num[0], rh, ops[0]);
  }

  return 0;

}

string get_str(string pattern, vector<int> num, vector<int> ops){

  char os[5] = {'+', '-', '*', '/', '^'};
  char buffer[50];

  sprintf(buffer, pattern.c_str(), num[0], os[ops[0]],
                                   num[1], os[ops[1]],
                                   num[2], os[ops[2]],
                                   num[3]);
  
  return string(buffer);

}

string get_str(vector<int> num, vector<int> ops, int ord){

  switch(ord){
    case 0:  return get_str("(%d%c%d)%c(%d%c%d)", num, ops);
    case 1:  return get_str("((%d%c%d)%c%d)%c%d", num, ops);
    case 2:  return get_str("(%d%c(%d%c%d))%c%d", num, ops);
    case 3:  return get_str("%d%c((%d%c%d)%c%d)", num, ops);
    default: return get_str("%d%c(%d%c(%d%c%d))", num, ops);
  }
  
  return "";

}

vector< vector<int> > get_perms(vector<int> b){

  sort(b.begin(), b.end());

  vector< vector<int> > out;
  do {
    out.push_back(b);
  } while(next_permutation(b.begin(), b.end()));

  return out;
  
}

bool is_same_within_error(double a, double b){

  if(a==0 || b==0) return a==b;

  double eps = numeric_limits<double>::epsilon();

  return fabs(a-b) < b*eps;

}

void make_tgt(vector<int> base, int tgt=24){

  vector< vector<int> > all_ops;
  for(int i=0; i<5; i++){  
  for(int j=0; j<5; j++){  
  for(int k=0; k<5; k++){
    vector<int> ops = {i, j, k};
    all_ops.push_back(ops);
  }}}
  
  vector< vector<int> > perms = get_perms(base);
  
  for(int p=0; p<int(perms.size()); p++){
  for(int a=0; a<int(all_ops.size()); a++){
  for(int ord=0; ord<5; ord++){
    vector<int> num = perms[p];
    double val = get_val(perms[p], all_ops[a], ord);
    if( is_same_within_error(val, tgt) ) {
      cout << get_str(perms[p], all_ops[a], ord) 
           << " = " << val << endl;
    }
  }}}
  
}

int main(int argc, char* argv[]){

  vector<int> base = {2,3,3,4};
  int tgt = 24;
  
  if(argc>4){
    for(int i=0; i<4; i++) base[i] = stoi(argv[i+1]);
  }
  
  if(argc>5) tgt = stoi(argv[5]);
  
  make_tgt(base, tgt);
  
  return 0;

}
