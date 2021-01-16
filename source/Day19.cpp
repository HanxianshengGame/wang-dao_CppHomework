// Authors: Handling
// Created by 15870 on 2020/10/12.
// This is 
#include <bits/stdc++.h>
using namespace std;
class BracketMatching{
 public:

  /* unit test               s         result
  functional test          "()[]{}"    true
						   "{{()}}{]"  false
  boundary test            "{}"        true
  negative test            "{{}"/""    false      奇数与空串都不是
  */
  bool isValid(string s) {
	if(s.size() & 0x1 ==1)
	  return false;
	if(s.size() == 0)
	  return true;
	map<char,char> bracketsMap{{')','('},{'}','{'},{']','['}};
	stack<char> leftBrackStack;
	int index = 0;
	while(index < s.size()){
	  if(s.at(index) == ')' || s.at(index) ==']' || s.at(index) == '}'){
		if(leftBrackStack.size() > 0 && leftBrackStack.top() == bracketsMap.at(s.at(index))){
		  leftBrackStack.pop();
		}
		else
		  return false;
	  }
	  else
		leftBrackStack.push(s.at(index));
	  ++index;
	}
	return leftBrackStack.size()==0;
  }
};



class MyLRU {
 private:
  int capcity_;
  list<pair<int,int>> lru_list_;
  unordered_map<int, list<pair<int,int>>::iterator> cache_;
 public:
  explicit  MyLRU(int cap): capcity_(cap) {}
  //放入键值，得到缓存值
  int get(const int key, int *out_val);
  int put(const int key, const int val);
};
int MyLRU::get(const int key, int *out_val) {
  auto hash_iter = cache_.find(key);
  if(hash_iter != cache_.end()) {
    auto val = hash_iter->second->second;
    lru_list_.erase(hash_iter->second);
    lru_list_.push_front({key,val});
    cache_[key] = lru_list_.begin();
    *out_val = val;
    return 0;
  }
  return -1;
}
int MyLRU::put(const int key, const int val) {
  auto hash_iter = cache_.find(key);
  if(hash_iter == cache_.end()) {
    if(lru_list_.size() == capcity_) {
      lru_list_.pop_back();
    }
    lru_list_.push_front({key, val});
    cache_[key] = lru_list_.begin();
  } else {
    auto erase_iter = hash_iter->second;
    lru_list_.erase(erase_iter);
    lru_list_.push_front({key,val});
    cache_[key] = lru_list_.begin();
  }
  return 0;
}

class WordSolitair {
  int LadderLength(string begin_word, string end_word, vector<string> &word_list) {
    unordered_set<string> s;
    for(auto &elem :word_list) {
      s.insert(elem);
    }
    queue<pair<string, int>> q;
    q.push({begin_word, 1});
    string tmp;
    int step;
    while(!q.empty()) {
      if(q.front().first == end_word) {
        return (q.front().second);
      }
      tmp = q.front().first;
      step = q.front().second;
      q.pop();

      char ch;
      for(int i = 0; i < tmp.length(); ++i) {
        ch = tmp[i];
        for(char c = 'a'; c <= 'z'; ++c) {
          if(ch == c)
			continue;
          tmp[i] = c;
          if(s.find(tmp) != s.end()) {
            q.push({tmp, step + 1});
            s.erase(tmp);
          }
          tmp[i] = ch;
        }
      }
    }
    return 0;
  }
};