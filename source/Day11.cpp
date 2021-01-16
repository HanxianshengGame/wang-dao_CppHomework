// Authors: Handling
// Created by 15870 on 2020/9/26.
// This is
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

namespace textquery {
struct QueryResult {
  string query_word;
  int     frequency = 0;
  set<int> *p_result_lines = nullptr;
  vector<string> *p_content_ = nullptr;
};
class TextQuery {
 public:
  void ReadFile(const string &file_name);
  QueryResult&& Query(const string &word);
 private:
  vector<string> contents_;   //存放文本内容
  map<string, set<int>> word_; //存放词的出现行号
  map<string, int> dict_; //存放词频度
};
void TextQuery::ReadFile(const string &file_name) {
  try {
	ifstream ifs(file_name);
	if(ifs.is_open()) {
	  string line;
	  while(getline(ifs, line)) {
		contents_.push_back(line);
	    stringstream ss(line);
	    string word;
	    while(ss >> word) {
	      word_[word].insert(contents_.size() - 1);
	      ++dict_[word];
	    }
	  }
	} else {
	  throw std::runtime_error("open file failure!");
	}
	ifs.close();

  } catch (...) {

  }
}
QueryResult&& TextQuery::Query(const string &word) {
  QueryResult query_result;

  query_result.query_word = word;
  if(dict_.find(word) != dict_.end()) {
	query_result.p_result_lines = &word_[word];
	query_result.frequency = dict_[word];
	query_result.p_content_ = &contents_;
  }
  return std::move(query_result);
}


void Print(ostream &os, const QueryResult &result) {
  os << result.query_word << "occurs" << result.frequency << "times" << endl;
}
}

namespace TinyXml2 {

}
