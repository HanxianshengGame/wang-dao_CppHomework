// Authors: Handling
// Created by 15870 on 2020/9/21.
// This is 词典类

#include <bits/stdc++.h>
using namespace std;
namespace dictionary {
struct Word {
	string word_;
	int frequency;
	bool operator<(const Word &rhs) {
	  return word_ < rhs.word_;
	}
};

class Dictionary {
 public:
  Dictionary();
  void read(const string &file_name);
  void store(const string &file_name);
 private:
  vector<Word> dict_;
  map<string, Word*> search_map;
};
Dictionary::Dictionary() {
  dict_.reserve(1000);
}
void Dictionary::read(const string &file_name) {
  ifstream ifs(file_name);

  if(ifs.is_open()) {
	string line;
	while(getline(ifs,line)) {
	  istringstream iss(line);
	  string word;
	  while(iss >> word) {
	    auto search_iter = search_map.find(word);
	    if(search_iter == search_map.end()) {
	      dict_.push_back({word, 1});
	      search_map[word] = &dict_.back();
	    } else {
	      ++search_iter->second->frequency;
	    }
	  }
	}
  } else {
	throw std::runtime_error("open file error!\n");
  }
  ifs.close();
}
void Dictionary::store(const string &file_name) {
  ofstream ofs(file_name);
  if(ofs.is_open()) {
    sort(dict_.begin(), dict_.end()); //写入文件前先以词的字典序排序
    for(decltype(dict_.size()) i = 0; i != dict_.size(); ++i) {
      ofs << dict_[i].word_ << " " << dict_[i].frequency << endl;
    }
  } else {
	throw std::runtime_error("open file error!\n");
  }
  ofs.close();
}

}

